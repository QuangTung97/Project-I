#include <logic/actor/sprite.hpp>

namespace tung {
namespace actor {

SpriteProcess::SpriteProcess(const std::shared_ptr<Sprite>& owner, 
    std::shared_ptr<SpriteDrawable> drawable)
: owner_{owner}, drawable_{std::move(drawable)} {}

void SpriteProcess::on_init() {
    Process::on_init();
    current_time_ = seconds{0};
    drawable_->translate({x_, y_, 0});
    auto owner = owner_.lock();
    if (owner) {
        root_ = owner->root_;
        root_->attach_drawable(drawable_);
    }
    else {
        root_ = nullptr;
        fail();
    }
}

void SpriteProcess::on_update(milliseconds dt) {
    if (owner_.expired()) {
        fail();
        return;
    }

    current_time_ += dt;
    int index = current_time_.count() * fps_ / 1000;
    if (index >= drawable_->get_sprite_count()) {
        succeed();
        return;
    }

    drawable_->use_sprite(index);
}

void SpriteProcess::on_success() {
    if (root_)
        root_->detach_drawable(drawable_);
}

void SpriteProcess::on_fail() {
    if (root_)
        root_->detach_drawable(drawable_);
}

// *************
// Sprite
// *************
const ComponentId Sprite::COMPONENT_ID = ComponentId::SPRITE;

void Sprite::add_sprite(int index, const std::string& filename, 
        int rows, int cols, float height)
{
    auto sprite = factory_.new_sprite(filename, rows, cols, height);
    auto this_ = std::dynamic_pointer_cast<Sprite>(shared_from_this());
    auto process = std::make_shared<SpriteProcess>(this_, std::move(sprite));
    processes_[index] = std::move(process);
}

void Sprite::start(int index) {
    auto process = processes_[index];
    process->reset();
    manager_.attach_process(std::move(process));
}

void Sprite::move_to(float x, float y) {
    for (auto& e: processes_) {
        e.second->move_to(x, y);
    }
}

void Sprite::end(int index) {
    processes_[index]->fail();
}


} // namespace actor
} // namespace tung