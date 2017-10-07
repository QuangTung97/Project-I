#ifndef LOGIC_PROCESS_MANAGER_HPP
#define LOGIC_PROCESS_MANAGER_HPP

#include <list>
#include <logic/abstract/process.hpp>

namespace tung {

class ProcessManager {
private:
    typedef std::list<StrongProcessPtr> ProcessList;
    ProcessList process_list_;

public:
    ProcessManager() = default;

    void update_processes(unsigned long delta_ms);

    void attach_process(StrongProcessPtr process);

    void abort_all_processes(bool immediate = true);

    ~ProcessManager();

};

} // namespace tung

#endif
