#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <logic/abstract/process.hpp>
#include <logic/process_manager.hpp>

using namespace tung;

using ::testing::AtLeast;

class FakeProcess: public Process {
public:
    MOCK_METHOD1(on_update, void(milliseconds));
    MOCK_METHOD0(on_success, void());
    MOCK_METHOD0(on_fail, void());
};

TEST(ProcessManager, normal) {
    auto process1 = std::make_shared<FakeProcess>();
    auto process2 = std::make_shared<FakeProcess>();
    auto process3 = std::make_shared<FakeProcess>();

    ProcessManager manager;
    manager.attach_process(process1);
    manager.attach_process(process2);

    EXPECT_CALL(*process1, on_update(0ms)).Times(1);
    EXPECT_CALL(*process2, on_update(0ms)).Times(1);

    manager.update_processes(0ms);
}

TEST(ProcessManager, succeed_fail_and_child) {
    auto process1 = std::make_shared<FakeProcess>();
    auto process2 = std::make_shared<FakeProcess>();
    auto process3 = std::make_shared<FakeProcess>();
    auto child1 = std::make_shared<FakeProcess>();
    auto child2 = std::make_shared<FakeProcess>();
    auto child3 = std::make_shared<FakeProcess>();

    process1->attach_child(child1);
    process2->attach_child(child2);
    process3->attach_child(child3);

    ProcessManager manager;
    manager.attach_process(process1);
    manager.attach_process(process2);
    manager.attach_process(process3);

    EXPECT_CALL(*process1, on_update(0ms)).Times(2);
    EXPECT_CALL(*process1, on_success()).Times(0);

    EXPECT_CALL(*process2, on_update(0ms)).Times(0);
    EXPECT_CALL(*process2, on_fail()).Times(1);

    EXPECT_CALL(*process3, on_update(0ms)).Times(1);
    EXPECT_CALL(*process3, on_success()).Times(1);

    EXPECT_CALL(*child1, on_update(0ms)).Times(0);
    EXPECT_CALL(*child1, on_success()).Times(0);

    EXPECT_CALL(*child2, on_update(0ms)).Times(0);
    EXPECT_CALL(*child2, on_success()).Times(0);
    EXPECT_CALL(*child2, on_fail()).Times(0);

    EXPECT_CALL(*child3, on_update(0ms)).Times(1);
    EXPECT_CALL(*child3, on_success()).Times(0);

    process2->fail();
    manager.update_processes(0ms);
    process3->succeed();
    manager.update_processes(0ms);

}
