#include <logic/process_manager.hpp>

namespace tung {

void ProcessManager::update_processes(unsigned long delta_ms) {
    auto it = process_list_.begin();
    while (it != process_list_.end()) {
        StrongProcessPtr current = *it;

        if (current->get_state() == Process::UNINITIALIZED)
            current->on_init();

        if (current->get_state() == Process::RUNNING) 
            current->on_update(delta_ms);

        if (current->is_dead()) {
            Process::State state = current->get_state();
            if (state == Process::SUCCEEDED) {
                current->on_success();
                auto child = current->remove_child();
                if (child)
                    attach_process(child);
            }
            else if (state == Process::FAILED) {
                current->on_fail();
            }
            else if (state == Process::ABORTED) {
                current->on_abort();
            }
            it = process_list_.erase(it);
            continue; // no need for ++it
        }
        ++it;
    }
}

void ProcessManager::attach_process(StrongProcessPtr process) {
    process_list_.push_back(std::move(process));
}

void ProcessManager::abort_all_processes(bool immediate) {
    if (immediate) {
        for (auto& process: process_list_) {
            process->on_abort();
        }
        process_list_.clear();
    }
    else {
        for (auto& process: process_list_) {
            process->set_state(Process::ABORTED);
        }
    }
}

} // namespace tung
