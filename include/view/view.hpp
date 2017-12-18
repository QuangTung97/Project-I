#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include "abstract/view.hpp"
#include <graphics/abstract/drawable.hpp>
#include <vector>

namespace tung {

// Kết thừa từ abtract/view.hpp
class MouseEvent: public IView::IMouseEvent {
private:
    const Type type_;
    const Button button_;
    const float x_, y_;

public:
    // Constructor
    // @button: Loại nút đã ấn 
    // @type: Cách thức ấn nút 
    // @x, @y: Tạo độ của con trỏ chuột lúc đó. 
    MouseEvent(Button button, Type type, float x, float y);

    Button button() const override;

    Type type() const override;
    
    float x() const override;

    float y() const override;
};

// Kế thừa từ abstract/view.hpp
class View: public IView {
protected:
    MouseListener mouse_listener_ = nullptr;
    KeyListener key_listener_ = nullptr;
    bool focus_ = false;
    float x_, y_, w_, h_;
    IDrawablePtr drawable_;

public:
    // Constructor 
    // @x, @y: Tọa độ của view trên màn hình, tương đối so với view chứa nó. (theo pixel)
    // @width, @height: Chiều rộng và chiều cao của view đó (theo pixel) 
    // So với màn hình nếu mà nó là root view 
    View(float x, float y, float width, float height);

    void set_size(float width, float height) override;

    void set_top_left(float x, float y) override;

    void set_mouse_listener(MouseListener listener) override;

    void set_key_listener(KeyListener listener) override;

    bool on_mouse_event(const IMouseEvent& event) override;

    bool on_key_event(const KeyEvent& event) override;

    void focus(bool value) override { focus_ = value; }

    bool focus() const override { return focus_; }

    // Trả về drawable_ chứ các thông tin để vẽ view này lên màn hình. 
    const IDrawablePtr& get_drawable() const {
        return drawable_;
    }

    // Destructor 
    virtual ~View() {}
};

// Class vừa là view, vừa là nút trung gian trong cây view. 
class ViewGroup: public View, public IViewManager {
private:
    typedef std::vector<IViewPtr> ViewList;
    ViewList view_list_;

    IView *view_left_drag_ = nullptr;

public:
    // @x, @y: Tọa độ góc trên bên trái của view. 
    // @width, @height: Chiều rộng và chiều cao của view. 
    ViewGroup(float x, float y, float width, float height);

    // Chỉnh sửa lại hàm on_mouse_event từ view để gọi đệ quy. 
    bool on_mouse_event(const IMouseEvent& event) override;

    // Chỉnh sửa lại hàm on_mouse_event từ view để gọi đệ quy. 
    bool on_key_event(const KeyEvent& event) override;

    void add_view(const IViewPtr& view) override;

    void remove_view(const IViewPtr& view) override;

    virtual ~ViewGroup() {}
};

} // namespace tung

#endif
