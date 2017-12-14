#ifndef LOGIC_ACTOR_SPRITE_HPP
#define LOGIC_ACTOR_SPRITE_HPP

#include <logic/basic/event.hpp>
#include "actor.hpp"
#include "component.hpp"
#include <graphics/gl/sprite_drawable.hpp>
#include <graphics/gl/sprite_factory.hpp>
#include <logic/basic/process_manager.hpp>

namespace tung {

namespace system {
class Sprite;
}

namespace actor {

class Sprite;

// Tiến trình cho phép animation có thể hoạt động. 
class SpriteProcess: public Process {
private:
    milliseconds current_time_;
    const std::shared_ptr<SpriteDrawable> drawable_;
    const std::weak_ptr<Sprite> owner_;
    IDrawableManagerPtr root_;
    const int fps_ = 24;
    float x_, y_;
    friend class Sprite;

public:
    // Constructor 
    // @owner: Sprite component mà chứa process này. 
    // @drawable: Sprite Drawable dùng để hiển thị animation. 
    SpriteProcess(const std::shared_ptr<Sprite>& owner, 
    std::shared_ptr<SpriteDrawable> drawable);

    // Dịch chuyển đến vị trí mới 
    // @x, @y: Tọa độ của animation sẽ được hiển thị. 
    void move_to(float x, float y) { x_ = x; y_ = y; }

protected:
    void on_init() override;

    void on_update(milliseconds dt) override;

    void on_success() override;

    void on_fail() override;
};

// Component phục vụ việc hiển thị animation
// Ví dụ: Vụ nổ. 
class Sprite: public Component {
private:
    friend class SpriteProcess;
    std::unordered_map<int, std::shared_ptr<SpriteProcess>> processes_;
    IDrawableManagerPtr root_;
    SpriteFactory& factory_;
    ProcessManager& manager_;

public:
    // Factory
    // @root: Gốc của cây drawable
    // @factory: Factory để tạo SpriteDrawable
    // @manager: Manager quản lý các process. 
    Sprite(IDrawableManagerPtr root, SpriteFactory& factory, ProcessManager& manager)
    : root_{std::move(root)}, factory_{factory}, manager_{manager} {}

    static const ComponentId COMPONENT_ID;

    ComponentId get_id() const override {
        return COMPONENT_ID;
    }

    // Thêm một sprite 
    // @index: Vị trí muốn thêm 
    // @image: Đường dẫn đến file hình ảnh. 
    // @rows: Số dòng trong ảnh sprite đó. 
    // @cols: Số cột trong ảnh sprite đó. 
    // @height: Chiều cao của hình sẽ được vẽ (chiều rộng được suy ra từ kích thước ảnh)
    void add_sprite(int index, const std::string& image, 
        int rows, int cols, float height);

    // Di chuyển đến một vị trí khác 
    // @x, @y: Tọa độ của vị trí mới 
    void move_to(float x, float y);

    // Bắt đầu animation của một sprite, tại vị trí @index 
    void start(int index);

    // Kết thúc animation của một sprite, tại vị trí @index 
    void end(int index);
};

} // namespace actor
} // namespace tung

#endif