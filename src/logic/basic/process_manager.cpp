#include <logic/basic/process_manager.hpp>

namespace tung {

void ProcessManager::update_processes(milliseconds dt) {
    auto it = process_list_.begin();
    // Duyệt qua từng tiến trình 
    while (it != process_list_.end()) {
        StrongProcessPtr current = *it;

        // Nếu trạng thái là chưa khởi tạo 
        if (current->get_state() == Process::UNINITIALIZED)
            current->on_init();

        // Nếu trạng thái là đang chạy 
        if (current->get_state() == Process::RUNNING) 
            current->on_update(dt);

        // Nếu trạng thái là đã chết 
        if (current->is_dead()) {
            Process::State state = current->get_state();
            // Theo kiểu thành công 
            if (state == Process::SUCCEEDED) {
                current->on_success();
                // Lấy con của nó và thêm lại vào danh sách các tiến trình 
                auto child = current->remove_child();
                if (child)
                    attach_process(child);
            }
            // Theo kiểu fail 
            else if (state == Process::FAILED) {
                current->on_fail();
            }
            // Theo kiểu abort 
            else if (state == Process::ABORTED) {
                current->on_abort();
            }
            current->set_attached(false);
            // Xóa tiến trình hiện tại khỏi danh sách 
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
    // Hủy các tiến trình ngay lập tức 
    if (immediate) {
        for (auto& process: process_list_) {
            process->on_abort();
        }
        process_list_.clear();
    }
    else {
        // Còn không thì phải đợi đến lần update tiếp theo 
        for (auto& process: process_list_) {
            if (process->is_alive())
                process->set_state(Process::ABORTED);
        }
    }
}

ProcessManager::~ProcessManager() {}

} // namespace tung
