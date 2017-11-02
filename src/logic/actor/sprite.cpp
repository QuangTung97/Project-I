#include <logic/actor/sprite.hpp>

namespace tung {
namespace actor {

SpriteProcess::SpriteProcess(Sprite& owner, std::shared_ptr<SpriteDrawable> drawable)
: owner_{owner}, drawable_{std::move(drawable)} {}

void SpriteProcess::on_init() {
    Process::on_init();
    current_time_ = seconds{0};
    drawable_->translate({x_, y_, 0});
    owner_.root_->attach_drawable(drawable_);
}

void SpriteProcess::on_update(milliseconds dt) {
    current_time_ += dt;
    int index = current_time_.count() * fps_ / 1000;
    if (index >= drawable_->get_sprite_count()) {
        succeed();
        return;
    }

    drawable_->use_sprite(index);
}

void SpriteProcess::on_success() {
    owner_.root_->detach_drawable(drawable_);
}

void SpriteProcess::on_fail() {
    owner_.root_->detach_drawable(drawable_);
}

// *************
// Sprite
// *************
void Sprite::add_sprite(int index, const std::string& filename, 
        int rows, int cols, float height)
{
    auto sprite = factory_.new_sprite(filename, rows, cols, height);
    auto process = std::make_shared<SpriteProcess>(*this, std::move(sprite));
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