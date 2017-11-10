#include <view/view.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/gl/null_drawable.hpp>
#include <algorithm>

namespace tung {

static const auto null_drawable = std::make_shared<NullDrawable>();

// Mouse Event
MouseEvent::MouseEvent(Button button, Type type, float x, float y)
: button_{button}, type_{type}, x_{x}, y_{y} {}

MouseEvent::Button MouseEvent::button() const {
    return button_;
}

MouseEvent::Type MouseEvent::type() const {
    return type_;
}

float MouseEvent::x() const {
    return x_;
}

float MouseEvent::y() const {
    return y_;
}

// View
View::View(float x, float y, float width, float height) {
    x_ = x;
    y_ = y;
    w_ = width;
    h_ = height;
    drawable_ = null_drawable;
}

void View::set_size(float width, float height) {
    w_ = width;
    h_ = height;
}

void View::set_top_left(float x, float y) {
    x_ = x;
    y_ = y;
    drawable_->translate({x, y, 0});
}

void View::set_mouse_listener(MouseListener listener) {
    mouse_listener_ = listener;
}

bool View::on_mouse_event(const IMouseEvent& event) {
    if (mouse_listener_ == nullptr)
        return false;

    if (event.type() == IMouseEvent::MOUSE_DOWN) {
        if (event.x() < x_ && event.x() > x_ + w_)
            return false;

        if (event.y() < y_ && event.y() > y_ + h_)
            return false;
    }

    return mouse_listener_(event);
}


// View Group
ViewGroup::ViewGroup(float x, float y, float width, float height)
    : View(x, y, width, height) 
{
    drawable_ = std::make_shared<DrawableGroup>();
}

bool ViewGroup::on_mouse_event(const IMouseEvent& event) {
    if (event.button() != IMouseEvent::Button::LEFT) {
        for (const auto& view: view_list_) {
            MouseEvent new_event(
                event.button(),
                event.type(),
                event.x() - this->x_,
                event.y() - this->y_
            );

            bool result = view->on_mouse_event(new_event);
            if (result == true)
                return true;
        }

        return false;
    }

    if (event.type() == IMouseEvent::MOUSE_DOWN) {
        for (const auto& view: view_list_) {
            MouseEvent new_event(
                event.button(),
                event.type(), 
                event.x() - this->x_,
                event.y() - this->y_
            );

            bool result = view->on_mouse_event(new_event);
            if (result == true) {
                view_left_drag_ = view.get();
                return true;
            }
        }
        view_left_drag_ = nullptr;
    }
    else if (view_left_drag_) {
        return view_left_drag_->on_mouse_event(event);
    }

    if (mouse_listener_ == nullptr)
        return false;

    return mouse_listener_(event);
}

void ViewGroup::add_view(const IViewPtr& view) {
    view_list_.push_back(view);
    dynamic_cast<DrawableGroup&>(*this->drawable_).attach_drawable(
            dynamic_cast<View&>(*view).get_drawable());
}

void ViewGroup::remove_view(const IViewPtr& view) {
    auto it = 
        std::remove(view_list_.begin(), view_list_.end(), view);
    view_list_.erase(it, view_list_.end());

    dynamic_cast<DrawableGroup&>(*this->drawable_).detach_drawable(
            dynamic_cast<View&>(*view).get_drawable());
}

} // namespace tung
