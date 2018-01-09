#include <logic/game/plane.hpp>
#include <logic/game/bomb.hpp>
#include <logic/actor/events.hpp>
#include <logic/abstract/call_once_process.hpp>
#include <logic/game_logic.hpp>
#include <logic/actor/sound.hpp>
#include <logic/actor/collision.hpp>
#include <logic/actor/sprite.hpp>
#include <logic/actor/graphics_image.hpp>
#include <logic/game/playing_state.hpp>
#include <random>

namespace tung {
namespace game {

static std::random_device rd;
static std::mt19937 generator{rd()};
static std::uniform_real_distribution<float> uniform(0, 1);
static std::uniform_real_distribution<float> y_uniform(-0.2, 0.8);
static std::uniform_int_distribution<int> uniform_int02(0, 2);
static std::uniform_int_distribution<int> uniform_int01(0, 1);
static std::uniform_real_distribution<float> bomb_x_uniform(-0.5f, 0.5f);

class FlyProcess: public Process {
private:
    std::weak_ptr<Plane> plane_;
    bool dropped_bomb_ = false;
    state::PlayingState& playing_state_;
    float x0_;
    milliseconds elapsed_time_ = 0s;

public:
    FlyProcess(std::shared_ptr<Plane> plane, state::PlayingState& state)
    : plane_{std::move(plane)}, playing_state_{state} {}

protected:
    void on_init() override {
        Process::on_init();
        auto plane_ptr = plane_.lock();
        // Nếu máy bay còn tồn tại 
        if (plane_ptr) {
            auto& plane = *plane_ptr;
            x0_ = plane.x_;
            // Plane's Sound
            // bắt đầu chơi nhạc (hiện tại chưa có)
            actor::SoundStartedEvent event{plane.get_id(), 0};
            plane.state_manager_.get_event_manager().trigger(event);
        }
        else {
            // Còn nếu không, kết thúc tiến trình 
            succeed();
        }
    }

    void on_update(milliseconds dt) override {
        elapsed_time_ += dt;
        // Nếu máy bay đã bị hủy 
        if (plane_.expired()) {
            // Kết thúc tiến trình 
            fail();
            return;
        }
        auto plane_ptr = plane_.lock();
        auto& plane = *plane_ptr;

        // Tính toán tọa độ của máy bay hiện tại 
        plane.x_ = x0_ + plane.velocity_ * elapsed_time_.count() / 1000.0f;
        // Nếu nó đã đi quá một khoảng cách 
        if (plane.x_ - x0_ > plane.max_distance_) {
            // Kết thúc tiến trình 
            succeed();
            return;
        }

        // Thả bom nếu nó đến một vị trí xác định 
        if (!dropped_bomb_ && plane.will_drop_bomb_ && plane.x_ >= plane.drop_bomb_x_position_) {
            dropped_bomb_ = true;
            // Khởi tạo một quả bom 
            auto bomb = std::make_shared<Bomb>(
                plane.state_manager_, plane.x_, plane.y_ - 0.15f
            );
            bomb->init();
            // Cho nó thả 
            bomb->start_fly();
            // Thêm nó vào danh sách các bomb trong playing state
            playing_state_.bombs_.insert(bomb->get_id());
        }

        // Gửi sự kiện di chuyển máy bay 
        actor::MoveEvent event{plane.get_id(), plane.x_, plane.y_};
        plane.state_manager_.get_event_manager().trigger(event);
    }

    void on_success() override {
        auto plane_ptr = plane_.lock();
        // Nếu máy bay còn tồn tại 
        if (plane_ptr) {
            auto& plane = *plane_ptr;
            // Plane's Sound
            actor::SoundEndedEvent event{plane.get_id(), 0};
            plane.state_manager_.get_event_manager().trigger(event);

            // Destroy actor
            // Gửi sự kiện hủy máy bay 
            actor::DestroyEvent destroy_event{plane.get_id()};
            plane.state_manager_.get_event_manager().trigger(destroy_event);
        }
    }

    void on_fail() override {
        auto plane_ptr = plane_.lock();
        // Nếu máy bay còn tồn tại 
        if (plane_ptr) {
            auto& plane = *plane_ptr;
            // Plane's Sound
            actor::SoundEndedEvent event{plane.get_id(), 0};
            plane.state_manager_.get_event_manager().trigger(event);
        }
    }

    void on_abort() override {
        on_success();
    }
};

//------------------------------
// Plane
//------------------------------
Plane::Plane(state::Manager& state_manager, 
    float scaling_velocity, state::PlayingState& playing_state) 
: actor::Actor{actor::IdGenerator::new_id()},
    state_manager_{state_manager}, 
    playing_state_{playing_state},
    velocity_{base_velocity_ * scaling_velocity}
{}

const std::string& get_random_fighter_image() {
    static const std::vector<std::string> jet_images = {
        "assets/fighter1.png",
        "assets/fighter2.png",
        "assets/fighter3.png"
    };
    // Ngẫu nhiên một file 
    return jet_images[uniform_int02(generator)];
}

const std::string& get_random_commercial_plane_image() {
    static const std::vector<std::string> images = {
        "assets/commercial_plane1.png",
        "assets/commercial_plane2.png"
    };

    // Ngẫu nhiên một file 
    return images[uniform_int01(generator)];
}

void Plane::init() {
    std::weak_ptr<Plane> self = 
        std::dynamic_pointer_cast<Plane>(shared_from_this());

    // Tiến trình hủy máy bay 
    // Sau 2.5s
    destroy_plane_ = std::make_shared<CallOnceProcess>(2500ms, 
        [self=std::move(self)] {
        auto this_ = self.lock();
        if (this_) {
            // Gửi sự kiện hủy máy bay nếu nó còn tồn tại 
            actor::DestroyEvent destroy_actor{this_->get_id()};
            this_->state_manager_.get_event_manager().trigger(destroy_actor);
        }
    });

    auto this_ = std::dynamic_pointer_cast<Plane>(shared_from_this());
    fly_process_ = std::make_shared<FlyProcess>(this_, playing_state_);
    const float radius = 0.15;
    const float commercial_plane_prob = 0.3;
    const float width = radius * 1.6 * 2;
    const float height = radius * 2;

    x_ = -1.5f;
    y_ = y_uniform(generator);

    // Thêm phần âm thanh 
    auto sound = std::make_shared<actor::Sound>(
        state_manager_.get_asset_manager());
    // sound->add_sound(0, "assets/plane_fly.mp3");
    sound->add_sound(1, "assets/plane_explode.mp3");
    add_component(std::move(sound));

    float prob = uniform(generator);
    if (prob <= commercial_plane_prob) {
        is_fighter_ = false;
        // Khởi tạo thành phần hình ảnh 
        auto image = std::make_shared<actor::GraphicsImage>(
            x_, y_,
            state_manager_.get_image_factory(), 
            state_manager_.get_root(),
            height, get_random_commercial_plane_image()
        );
        add_component(std::move(image));

        // Khởi tạo thành phần va chạm 
        auto collision = std::make_shared<actor::RectangleCollision>(
            x_, y_, width, height * 0.3);
        add_component(std::move(collision));
    }
    else {
        // Khởi tạo thành phần hình ảnh 
        auto image = std::make_shared<actor::GraphicsImage>(
            x_, y_,
            state_manager_.get_image_factory(), 
            state_manager_.get_root(),
            height * 0.9, get_random_fighter_image()
        );
        add_component(std::move(image));

        // Khởi tạo thành phần va chạm 
        auto collision = std::make_shared<actor::CircleCollision>(x_, y_, radius);
        add_component(std::move(collision));

        // Tính toán vị trí thả bomb 
        const float prob = 0.3f;
        will_drop_bomb_ = uniform(generator) < prob ? true : false;
        drop_bomb_x_position_ = bomb_x_uniform(generator);
    }

    // Thêm thành phần animation cho vụ nổ 
    auto sprite = std::make_shared<actor::Sprite>(
        state_manager_.get_root(), 
        state_manager_.get_sprite_factory(),
        state_manager_.get_process_manager()
    );
    sprite->add_sprite(0, "assets/explosion1.png", 6, 8, 2 * radius);
    add_component(std::move(sprite));

    // Thêm actor vào game logic 
    GameLogic::get().add_actor(shared_from_this());
    // Gửi sự kiện sinh máy bay 
    actor::CreatedEvent actor_created{get_id()};
    state_manager_.get_event_manager().trigger(actor_created);
}

void Plane::start_fly() {
    // Reset và bắt đầu tiến trình bay 
    fly_process_->reset();
    state_manager_.get_process_manager().attach_process(fly_process_);
}

void Plane::end_fly() {
    fly_process_->fail();
}

void Plane::explode() {
    // Hủy tiến trình bay 
    fly_process_->fail();
    // Hủy kích hoạt khả năng va chạm 
    actor::DisableCollisionEvent disable_collision{get_id()};
    state_manager_.get_event_manager().trigger(disable_collision);

    // Explosion's Sound
    // Bắt đầu âm thanh vụ nổ 
    actor::SoundStartedEvent sound_started{get_id(), 1};
    state_manager_.get_event_manager().trigger(sound_started);

    // bắt đầu animation vụ nổ 
    actor::SpriteStartedEvent sprite_started{get_id(), 0};
    state_manager_.get_event_manager().trigger(sprite_started);

    // Ẩn hình ảnh máy bay 
    actor::GraphicsImageHideEvent hide_event{get_id()};
    state_manager_.get_event_manager().trigger(hide_event);

    // Hủy máy bay sau 2.5s
    state_manager_.get_process_manager().attach_process(destroy_plane_);
}

Plane::~Plane() {
}

} // namespace game
} // namespace tung
