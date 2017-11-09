#include <logic/system/graphics.hpp>
#include <logic/actor/events.hpp>
#include <logic/game_logic.hpp>

namespace tung {
namespace system {

Graphics::Graphics(IEventManager& event_manager)
: event_manager_{event_manager} {
    auto actor_created = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::CreatedEvent&>(event_);
        auto tmp_actor = GameLogic::get().get_actor(event.get_id()).lock();
        if (tmp_actor) {
            auto comp = tmp_actor->get_component<actor::GraphicsImage>().lock();
            if (comp)
                graphics_image_components_[event.get_id()] = comp;
        }

    };

    auto actor_destroy = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::DestroyEvent&>(event_);
        auto find_it = graphics_image_components_.find(event.get_id());
        if (find_it != graphics_image_components_.end()) {
            auto comp = find_it->second.lock();
            comp->set_owner(nullptr);
            graphics_image_components_.erase(find_it);
        }
    };

    auto actor_move = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::MoveEvent&>(event_);
        auto find_it = graphics_image_components_.find(event.get_id());
        if (find_it != graphics_image_components_.end()) {
            auto comp = find_it->second.lock();
            comp->move_to(event.get_x(), event.get_y());
        }
    };

    auto actor_rotate = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::RotateEvent&>(event_);
        auto find_it = graphics_image_components_.find(event.get_id());
        if (find_it != graphics_image_components_.end()) {
            auto comp = find_it->second.lock();
            comp->rotate(event.get_angle());
        }
    };

    auto graphics_image_show = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::GraphicsImageShowEvent&>(event_);
        auto find_it = graphics_image_components_.find(event.get_id());
        if (find_it != graphics_image_components_.end()) {
            auto comp = find_it->second.lock();
            comp->show();
        }
    };

    auto graphics_image_hide = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::GraphicsImageHideEvent&>(event_);
        auto find_it = graphics_image_components_.find(event.get_id());
        if (find_it != graphics_image_components_.end()) {
            auto comp = find_it->second.lock();
            comp->hide();
        }
    };

    actor_created_listener_ = actor_created;
    actor_destroy_listener_ = actor_destroy;
    actor_move_listener_ = actor_move;
    actor_rotate_listener_ = actor_rotate;
    graphics_image_show_listener_ = graphics_image_show;
    graphics_image_hide_listener_ = graphics_image_hide;

    event_manager_.add_listener(actor::EVENT_CREATED, actor_created_listener_);
    event_manager_.add_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    event_manager_.add_listener(actor::EVENT_MOVE, actor_move_listener_);
    event_manager_.add_listener(actor::EVENT_ROTATE, actor_rotate_listener_);
    event_manager_.add_listener(actor::EVENT_GRAPHICS_IMAGE_SHOW, 
        graphics_image_show_listener_);
    event_manager_.add_listener(actor::EVENT_GRAPHICS_IMAGE_HIDE, 
        graphics_image_hide_listener_);
}

Graphics::~Graphics() {
    event_manager_.remove_listener(actor::EVENT_GRAPHICS_IMAGE_HIDE, 
        graphics_image_hide_listener_);
    event_manager_.remove_listener(actor::EVENT_GRAPHICS_IMAGE_SHOW, 
        graphics_image_show_listener_);
    event_manager_.remove_listener(actor::EVENT_ROTATE, actor_rotate_listener_);
    event_manager_.remove_listener(actor::EVENT_MOVE, actor_move_listener_);
    event_manager_.remove_listener(actor::EVENT_DESTROY, actor_destroy_listener_);
    event_manager_.remove_listener(actor::EVENT_CREATED, actor_created_listener_);
}

} // namespace system
} // namespace tung