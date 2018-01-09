#include <logic/game/cannon.hpp>
#include <logic/actor/graphics_image.hpp>
#include <logic/actor/events.hpp>
#include <logic/game_logic.hpp>
#include <logic/game/bullet.hpp>
#include <logic/actor/collision.hpp>

namespace tung {
namespace game {

void Cannon::init() {
    auto base = std::make_shared<actor::Actor>(actor::IdGenerator::new_id());
    base_id_ = base->get_id();

    auto head = std::make_shared<actor::Actor>(actor::IdGenerator::new_id());
    head_id_ = head->get_id();

    const float x = 0, y = -1;
    const float base_height = 0.2;
    const float head_height = 0.13;

    // Tạo graphics component cho nòng súng 
    auto head_image = std::make_shared<actor::GraphicsImage>(
        x, y, 
        state_manager_.get_image_factory(),
        state_manager_.get_upper_group(),
        head_height, "assets/cannon_head.png"
    );
    head->add_component(std::move(head_image));

    // Tạo graphics component cho phần bệ 
    auto base_image = std::make_shared<actor::GraphicsImage>(
        x, y, 
        state_manager_.get_image_factory(),
        state_manager_.get_upper_group(),
        base_height, "assets/cannon_base.png"
    );
    base->add_component(std::move(base_image));

    // Kiểu va đập hình tròn
    auto collision = std::make_shared<actor::CircleCollision>(
        x, y, base_height / 2
    );
    add_component(std::move(collision));

    // Thêm actor 
    GameLogic::get().add_actor(shared_from_this());
    // Gửi sự kiện tạo mới actor 
    actor::CreatedEvent actor_created{get_id()};
    state_manager_.get_event_manager().trigger(actor_created);

    // Làm tương tự với phần đầu và phần bệ 
    GameLogic::get().add_actor(head);
    actor::CreatedEvent head_created{head_id_};
    state_manager_.get_event_manager().trigger(head_created);

    GameLogic::get().add_actor(base);
    actor::CreatedEvent base_created{base_id_};
    state_manager_.get_event_manager().trigger(base_created);

    // Xoay cho nòng súng hướng thẳng đứng
    rotate(90);
}

void Cannon::rotate(float degree) {
    head_angle_ = degree;
    // Gửi sự kiện xoay nóng súng 
    actor::RotateEvent rotate_head{head_id_, degree};
    state_manager_.get_event_manager().trigger(rotate_head);
}

actor::ActorId Cannon::shot() {
    // Tạo một viên đại 
    auto bullet = std::make_shared<game::Bullet>(
        state_manager_, 0, -1, head_angle_);
    bullet->init();
    // Và cho nó di chuyển 
    bullet->start_fly();
    return bullet->get_id();
}

Cannon::~Cannon() {
    // Gửi sự kiện hủy phần nòng súng và phần bệ 
    actor::DestroyEvent destroy_head{head_id_};
    state_manager_.get_event_manager().trigger(destroy_head);

    actor::DestroyEvent destroy_base{base_id_};
    state_manager_.get_event_manager().trigger(destroy_base);
}

} // namespace game
} // namespace tung
