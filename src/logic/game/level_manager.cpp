#include <logic/game/level_manager.hpp>
#include <logic/game/plane.hpp>

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
                state_.manager_, true
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


//-----------------------------------------------
// Level Manager
//-----------------------------------------------
void LevelManager::next_level() {
}

void LevelManager::entry() {
    plane_generator_ = std::make_shared<PlaneGenerator>(playing_state_);
    process_manager_.attach_process(plane_generator_);
}

void LevelManager::exit() {
    plane_generator_->succeed();
}

} // namespace state
} // namespace tung