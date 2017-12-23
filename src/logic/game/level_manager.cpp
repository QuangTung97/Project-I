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

class PlaneGeneratorV2: public Process {
private:
    PlayingState& state_;
    milliseconds elapsed_time_;
    milliseconds cycle_;
    const float frequency_;

protected:
    void on_init() override {
        Process::on_init();
        elapsed_time_ = 0ms;
        cycle_ = milliseconds{int(1000 / frequency_)};
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        if (elapsed_time_ >= cycle_) {
            elapsed_time_ = 0ms;

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
//-----------------------------------------------
void LevelManager::init() {
    text_level_ = std::make_shared<TextView>(
        350, 30, 24, Color::BLUE, "Level: 0"
    );
    text_new_level_ = std::make_shared<TextView>(
        240, 240, 40, Color::RED, "New Level"
    );
}

void LevelManager::show_new_level() {
    auto begin_process = std::make_shared<CallOnceProcess>(2000ms, [this]() {
        text_level_->set_text("Level: " + std::to_string(level_));
        root_.add_view(text_new_level_);
    });

    auto end_process = std::make_shared<CallOnceProcess>(1000ms, [this]() {
        root_.remove_view(text_new_level_);
    });
    begin_process->attach_child(end_process);
    process_manager_.attach_process(begin_process);
}

void LevelManager::next_level() {
    level_++;

    if (plane_generator_)
        plane_generator_->succeed();

    const float frequency = (level_ - 1) * 0.2 + 1.0;
    plane_generator_ = std::make_shared<PlaneGeneratorV2>(playing_state_, frequency);
    if (level_ >= 2) {
        show_new_level();

        auto wait_process = std::make_shared<WaitProcess>(3000ms);
        wait_process->attach_child(plane_generator_);
        process_manager_.attach_process(wait_process);
    }
    else {
        process_manager_.attach_process(plane_generator_);
        text_level_->set_text("Level: " + std::to_string(level_));
    }
}

void LevelManager::entry() {
    root_.add_view(text_level_);
    level_ = 0;
}

void LevelManager::exit() {
    plane_generator_->succeed();
    root_.remove_view(text_level_);
}

} // namespace state
} // namespace tung