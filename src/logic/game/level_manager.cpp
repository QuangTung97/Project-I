#include <logic/game/level_manager.hpp>
#include <logic/game/plane.hpp>
#include <logic/abstract/wait_process.hpp>
#include <logic/abstract/call_once_process.hpp>

namespace tung {
namespace state {

class PlaneGenerator: public Process {
private:
    PlayingState& state_;
    milliseconds elapsed_time_;
    milliseconds cycle_;

    const float Tmax_ = 1.0f;
    const float Tmin_ = 0.4f;
    const float after_seconds_ = 60;
    const float value_down_to_ = 0.6f;

    milliseconds get_T() {
        float M = (Tmax_ - Tmin_) / (value_down_to_ - Tmin_);
        float T = Tmin_ + (Tmax_ - Tmin_) 
            * std::pow(M, -elapsed_time_.count() / (1000.0f * after_seconds_));
        return milliseconds(int(T * 1000));
    }

protected:
    void on_init() override {
        Process::on_init();
        elapsed_time_ = 0ms;
        cycle_ = 1000ms;
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        if (elapsed_time_ >= get_T()) {
            elapsed_time_ = 0ms;
            auto plane = std::make_shared<game::Plane>(
                state_.manager_, 1.0f
            );
            plane->init();
            plane->start_fly();
            state_.planes_.insert(plane->get_id());
        }
    }

    void on_success() override {
    }

    void on_fail() override {
    }

public:
    PlaneGenerator(PlayingState& state)
    : state_{state} {}
};

// Tiến trình sinh máy bay (đang được sử dụng) 
class PlaneGeneratorV2: public Process {
private:
    PlayingState& state_;
    milliseconds elapsed_time_; // Thời gian đã trôi qua từ lần sinh trước 
    milliseconds cycle_; // Chu trình sinh máy bay 
    const float frequency_; // Tần số sinh 

protected:
    void on_init() override {
        Process::on_init();
        elapsed_time_ = 0ms;
        // Tính giá trị chu trình sinh máy bay. 
        cycle_ = milliseconds{int(1000 / frequency_)};
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        // Nếu thời gian đã trôi qua lớn hơn chu trình sinh máy bay 
        if (elapsed_time_ >= cycle_) {
            elapsed_time_ = 0ms;

            // Tạo một máy bay
            auto plane = std::make_shared<game::Plane>(
                state_.manager_, frequency_
            );
            plane->init();
            plane->start_fly();
            state_.planes_.insert(plane->get_id());
        }
    }

    void on_success() override {
    }

    void on_fail() override {
    }

public:
    PlaneGeneratorV2(PlayingState& state, float frequency)
    : state_{state}, frequency_{frequency} {}
};


//-----------------------------------------------
// Level Manager
// Class kiểm soát level của game 
//-----------------------------------------------
void LevelManager::init() {
    // Khởi tạo View để hiện thị Level hiện tại 
    text_level_ = std::make_shared<TextView>(
        350, 30, 24, Color::BLUE, "Level: 0"
    );
    // Khởi tạo view để hiển thị New Level
    text_new_level_ = std::make_shared<TextView>(
        240, 240, 40, Color::RED, "New Level"
    );
}

// Hàm được gọi khi chuyển sang một level mới 
void LevelManager::show_new_level() {
    // Đợi 2s, rồi hiển thị level mới. 
    // Đồng thời hiển thị chữ New Level lên màn hình 
    auto begin_process = std::make_shared<CallOnceProcess>(2000ms, [this]() {
        text_level_->set_text("Level: " + std::to_string(level_));
        root_.add_view(text_new_level_);
    });

    // 1s tiếp theo
    // Ẩn đi chữ New Level
    auto end_process = std::make_shared<CallOnceProcess>(1000ms, [this]() {
        root_.remove_view(text_new_level_);
    });

    // end_process sẽ là tiến trình con của begin_process
    // sẽ bắt đầu chạy ngay sau khi tiến trình cha kết thúc.
    begin_process->attach_child(end_process);
    // Bắt đầu chạy tiến trình
    process_manager_.attach_process(begin_process);
}

// Hàm được gọi khi chuyển sang một level mới 
void LevelManager::next_level() {
    level_++;
    // Kết thúc tiến trình sinh máy bay. 
    if (plane_generator_)
        plane_generator_->succeed();

    // Tăng tần số sinh máy bay. 
    const float frequency = (level_ - 1) * 0.2 + 1.0;
    // Tạo một tiến trình sinh máy bay mới 
    plane_generator_ = std::make_shared<PlaneGeneratorV2>(playing_state_, frequency);
    // Tính từ bắt đầu của các level mà  >= 2 
    if (level_ >= 2) {
        // Sẽ chờ một khoảng thời gian để hiện New Level lên màn hình 
        show_new_level();

        // Tiến trình sinh máy bay sẽ được kích hoạt sau 3s. 
        // Nhờ là con của tiến trình wait_process 
        auto wait_process = std::make_shared<WaitProcess>(3000ms);
        wait_process->attach_child(plane_generator_);
        process_manager_.attach_process(wait_process);
    }
    else {
        // Còn nếu level = 1
        // Thì kích hoạt ngay lập tức tiến trình sinh máy bay. 
        process_manager_.attach_process(plane_generator_);
        text_level_->set_text("Level: " + std::to_string(level_));
    }
}

// Bắt đầu trạng thái Playing 
void LevelManager::entry() {
    // Hiển thị level hiện tại 
    root_.add_view(text_level_);
    level_ = 0;
}

// Kết thúc trạng thái playing 
void LevelManager::exit() {
    // Kết thúc tiến trình sinh máy bay 
    plane_generator_->succeed();
    // Ẩn đi level hiện tại. 
    root_.remove_view(text_level_);
}

} // namespace state
} // namespace tung