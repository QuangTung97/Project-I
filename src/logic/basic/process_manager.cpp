#include <logic/basic/process_manager.hpp>

namespace tung {

void ProcessManager::update_processes(milliseconds dt) {
    auto it = process_list_.begin();
    while (it != process_list_.end()) {
        StrongProcessPtr current = *it;

        if (current->get_state() == Process::UNINITIALIZED)
            current->on_init();

        if (current->get_state() == Process::RUNNING) 
            current->on_update(dt);

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
            current->set_attached(false);
            it = process_list_.erase(it);
            continue; // no need for ++it
        }
        ++it;
    }
}

void ProcessManager::attach_process(StrongProcessPtr process) {
    if (process->is_attached())
        return;
    process->set_attached(true);
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
            if (process->is_alive())
                process->set_state(Process::ABORTED);
        }
    }
}

ProcessManager::~ProcessManager() {}

} // namespace tung
