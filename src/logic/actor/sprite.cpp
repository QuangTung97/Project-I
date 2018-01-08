#include <logic/actor/sprite.hpp>

namespace tung {
namespace actor {

SpriteProcess::SpriteProcess(const std::shared_ptr<Sprite>& owner, 
    std::shared_ptr<SpriteDrawable> drawable)
: owner_{owner}, drawable_{std::move(drawable)} {}

void SpriteProcess::on_init() {
    // Gọi hàm của super class 
    Process::on_init();
    current_time_ = seconds{0};
    // Dịch chuyển nó đến vị trí (x_, y_)
    drawable_->translate({x_, y_, 0});
    auto owner = owner_.lock();
    // Nếu owner tồn tại 
    if (owner) {
        root_ = owner->root_;
        // Thêm drawable vào root 
        root_->attach_drawable(drawable_);
    }
    else {
        // Còn không tồi tại 
        root_ = nullptr;
        // Tiến trình fail 
        fail();
    }
}

void SpriteProcess::on_update(milliseconds dt) {
    // Nếu owner đã chết 
    if (owner_.expired()) {
        // Tiến trình fail 
        fail();
        return;
    }

    // Tăng thời gian 
    current_time_ += dt;
    // Tính toán vị trí index của sprite sẽ vẽ 
    int index = current_time_.count() * fps_ / 1000;
    // Nếu index vượt quá số sprite 
    if (index >= drawable_->get_sprite_count()) {
        // Tiến trình kết thúc thành công 
        succeed();
        return;
    }

    // Kích hoạt index mới 
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
    // Tạo một sprite 
    auto sprite = factory_.new_sprite(filename, rows, cols, height);
    // Tạo một shared_ptr đến chính nó 
    auto this_ = std::dynamic_pointer_cast<Sprite>(shared_from_this());
    // Tạo một tiến trình dùng để chạy animation 
    auto process = std::make_shared<SpriteProcess>(this_, std::move(sprite));
    // Thêm tiến trình vào danh sách các tiến trình 
    processes_[index] = std::move(process);
}

void Sprite::start(int index) {
    // Tìm và chạy tiến trình 
    auto process = processes_[index];
    process->reset();
    manager_.attach_process(std::move(process));
}

void Sprite::move_to(float x, float y) {
    // Gọi hàm move của mỗi tiến trình 
    for (auto& e: processes_) {
        e.second->move_to(x, y);
    }
}

void Sprite::end(int index) {
    // Tìm và hủy tiến trình 
    processes_[index]->fail();
}


} // namespace actor
} // namespace tung
