#ifndef LOGIC_PROCESS_MANAGER_HPP
#define LOGIC_PROCESS_MANAGER_HPP

#include <list>
#include <logic/abstract/process.hpp>

namespace tung {

// Quản lý các tiến trình 
class ProcessManager {
private:
    typedef std::list<StrongProcessPtr> ProcessList;
    ProcessList process_list_;

public:
    ProcessManager() = default;

    // Cập nhật tất cả các tiến trình đang quản lý
    // @dt: khoảng thời gian giữa 2 lần cập nhật. 
    void update_processes(milliseconds dt);

    // Thêm một tiến trình 
    // @process: Tiến trình sẽ được thêm 
    void attach_process(StrongProcessPtr process);

    // Chuyển tất cả các tiến trình về trạng thái hủy 
    // @immediate: Chuyển ngay lập tức hay không
    // Ngay lập tức nghĩa là các hàm on_abort sẽ được gọi luôn, 
    // các tiến trình được xóa khỏi danh sách 
    // Còn không sẽ chỉ chuyển trạng thái về ABORTED, on_abort sẽ được gọi ở lần update tiếp theo 
    void abort_all_processes(bool immediate = true);

    // Destructor
    ~ProcessManager();
};

} // namespace tung

#endif
