#include <logic/game/playing_state.hpp>
#include <logic/game/manager.hpp>
#include <logic/game/bullet.hpp>
#include <logic/game/plane.hpp>
#include <logic/game/bomb.hpp>

#include <graphics/gl/glfw.hpp>
#include <logic/actor/events.hpp>
#include <logic/game_logic.hpp>
#include <cmath>
#include <fstream>

#include <iostream>

namespace tung {
namespace state {

PlayingState::PlayingState(Manager& manager)
: GameState(manager) 
{
    level_manager_ = std::make_unique<LevelManager>(
            *this, manager_.process_manager_, *manager_.get_view_root()
    );
    level_manager_->init();

    background_ = manager_.get_image_factory()
        .new_drawable("assets/playing_background.png", 2);

    show_score_ = std::make_shared<TextView>(
        20, 30, 24, Color::RED, "Score: 0"
    );

    show_high_score_ = std::make_shared<TextView>(
        150, 30, 24, Color::RED, "High Score: 0"
    );

    init_heart_views();

    auto plane_destroy = [this](const IEventData& event_) {
        auto& event = dynamic_cast<const actor::DestroyEvent&>(event_);
        // remove plane
        auto find_it = planes_.find(event.get_id());
        if (find_it != planes_.end()) {
            planes_.erase(find_it);
        }

        // remove bomb
        find_it = bombs_.find(event.get_id());
        if (find_it != bombs_.end()) {
            bombs_.erase(find_it);
        }

        // remove bullet
        auto it = bullets_.find(event.get_id());
        if (it != bullets_.end()) {
            bullets_.erase(it);
        }
    };
    plane_destroy_listener_ = plane_destroy;

    collide_listener_ = [this](const IEventData& event_) {
        const auto& event = dynamic_cast<const actor::CollideEvent&>(event_);
        handle_collide_event(event);
    };
}

void PlayingState::handle_collide_event(const actor::CollideEvent& event) {
    auto find_it = planes_.find(event.get_id());
    if (find_it != planes_.end()) {
        auto bullet_it = bullets_.find(event.get_collide_width_id());
        if (bullet_it == bullets_.end())
            return;

        auto ptr = GameLogic::get().get_actor(event.get_id()).lock();
        if (ptr) {
            auto plane = std::dynamic_pointer_cast<game::Plane>(ptr);
            if (plane->is_fighter()) {
                increase_score(1);
            }
            else {
                reduce_heart_count(1);
                if (heart_count_ == 0) {
                    MakeTransition event{*manager_.start_};
                    manager_.get_event_manager().queue(event);
                }
            }
            plane->explode();
        }
        return;
    }

    find_it = bombs_.find(event.get_id());
    if (find_it != bombs_.end()) {
        auto collide_with_id = event.get_collide_width_id();
        if (collide_with_id != cannon_->get_id() &&
            bullets_.find(collide_with_id) == bullets_.end())
            return;

        auto ptr = GameLogic::get().get_actor(event.get_id()).lock();
        if (ptr) {
            auto bomb = std::dynamic_pointer_cast<game::Bomb>(ptr);
            bomb->explode();
        }
        return;
    }

    auto it = bullets_.find(event.get_id());
    if (it != bullets_.end() && 
        event.get_collide_width_id() != cannon_->get_id()) {

        auto ptr = GameLogic::get().get_actor(event.get_id()).lock();
        if (ptr) {
            auto bullet = std::dynamic_pointer_cast<game::Bullet>(std::move(ptr));
            bullet->end_fly();
        }
        return;
    }

    if (event.get_id() == cannon_->get_id()) {
        auto bomb_it = bombs_.find(event.get_collide_width_id());
        if (bomb_it == bombs_.end())
            return;

        reduce_heart_count(1);
        if (heart_count_ == 0) {
            MakeTransition event{*manager_.start_};
            manager_.get_event_manager().queue(event);
        }
        return;
    }
}

void PlayingState::init_heart_views() {
    const float base_x = GLFW::get_screen_width() - 170;
    heart_view_group_ = std::make_shared<ViewGroup>(
        base_x, 0, 40 * 40, 40
    );
    for (int i = 0; i < max_heart_count_; i++) {
        float x = i * 40;
        auto view = std::make_shared<ImageView>(
            x, 10, 30, 30, "assets/heart.png"
        );
        heart_views.push_back(view);
        heart_view_group_->add_view(view);
    }
}

void PlayingState::reset_heart_count() {
    for (auto& view: heart_views) 
        view->set_image("assets/heart.png");
    heart_count_ = max_heart_count_;
}

void PlayingState::reduce_heart_count(int value) {
    if (heart_count_ == 0)
        return;

    int prev_index = heart_count_ - 1;
    heart_count_ -= value;
    int curr_index = heart_count_ - 1;
    for (int i = curr_index + 1; i <= prev_index; i++) {
        heart_views[i]->set_image("assets/black_heart.png");
    }
}

void PlayingState::reset_score() {
    score_ = 0;
    show_score_->set_text("Score: " + std::to_string(score_));
}

void PlayingState::increase_score(int value) {
    score_ += value;
    show_score_->set_text("Score: " + std::to_string(score_));
    if (score_ > high_score_) {
        high_score_ = score_;
        show_high_score_->set_text("High Score: " + std::to_string(high_score_));
    }

    const int base_score = 10;
    const int level = level_manager_->level();
    if (score_ >= level * level * base_score) {
        level_manager_->next_level();
    }
}

void PlayingState::load_high_score() {
    std::ifstream file{"high_score"};
    if (file) {
        file >> high_score_;
    } 
    else {
        high_score_ = 0;
    }
    show_high_score_->set_text("High Score: " + std::to_string(high_score_));
}

void PlayingState::store_high_score() {
    std::ofstream file{"high_score"};
    file << high_score_;
}

void PlayingState::entry() {
    manager_.get_event_manager().add_listener(actor::EVENT_DESTROY, 
        plane_destroy_listener_);
    manager_.get_event_manager().add_listener(actor::EVENT_COLLIDE, 
        collide_listener_);

    manager_.get_root()->attach_drawable(background_);
    cannon_ = std::make_shared<game::Cannon>(manager_);
    cannon_->init();

    reset_score();
    load_high_score();
    reset_heart_count();

    level_manager_->entry();
    level_manager_->next_level();

    manager_.get_view_root()->add_view(show_score_);
    manager_.get_view_root()->add_view(show_high_score_);
    manager_.get_view_root()->add_view(heart_view_group_);
}

void PlayingState::exit() {
    level_manager_->exit();

    manager_.get_view_root()->remove_view(heart_view_group_);
    manager_.get_view_root()->remove_view(show_high_score_);
    manager_.get_view_root()->remove_view(show_score_);

    store_high_score();
    // Destroy cannon
    actor::DestroyEvent destroy_cannon{cannon_->get_id()};
    manager_.get_event_manager().trigger(destroy_cannon);
    cannon_ = nullptr;

    manager_.get_root()->detach_drawable(background_);
    manager_.get_event_manager().remove_listener(actor::EVENT_DESTROY, 
        plane_destroy_listener_);
    manager_.get_event_manager().remove_listener(actor::EVENT_COLLIDE, 
        collide_listener_);

    // Destroy planes
    auto planes = planes_;
    for (auto plane: planes) {
        actor::DestroyEvent event{plane};
        manager_.get_event_manager().trigger(event);
    }

    auto bullets = bullets_;
    for (auto bullet: bullets) {
        actor::DestroyEvent event{bullet};
        manager_.get_event_manager().trigger(event);
    }

    auto bombs = bombs_;
    for (auto bomb_id: bombs) {
        actor::DestroyEvent event{bomb_id};
        manager_.get_event_manager().trigger(event);
    }

    planes_.clear();
    bullets_.clear();
    bombs_.clear();
}

bool PlayingState::on_mouse_event(MouseButton button,
    MouseEventType type, float x, float y) 
{
    if (button == MouseButton::LEFT && type == MouseEventType::DOWN) {
        float height = GLFW::get_screen_height();
        float width = GLFW::get_screen_width();
        float ux = x - width / 2;
        float uy = height - y;
        if (ux != 0) {
            float radian = std::atan(uy / ux);
            float degree = radian * 180 / 3.141592654;
            if (ux < 0)
                degree = 180 + degree;

            cannon_->rotate(degree);
            auto bullet_id = cannon_->shot();
            bullets_.insert(bullet_id);
        }
        return true;
    }
    return true;
}

float normalize(float angle) {
    if (angle < 0) 
        return 0;
    if (angle > 180) 
        return 180;
    return angle;
}

bool PlayingState::on_key_event(const KeyEvent& event) {
    if (event.type() == KeyType::UP)
        return true;

    float angle = cannon_->angle();

    switch (event.button()) {
    case KeyButton::LEFT:
        angle = normalize(angle + 10);
        cannon_->rotate(angle);
        break;

    case KeyButton::RIGHT:
        angle = normalize(angle - 10);
        cannon_->rotate(angle);
        break;

    case KeyButton::SPACE:
    case KeyButton::ENTER:
        auto bullet_id = cannon_->shot();
        bullets_.insert(bullet_id);
        break;
    }
    return true;
}

} // namespace state
} // namespace tung