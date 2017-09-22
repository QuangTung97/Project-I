#ifndef GRAPHICS_ABSTRACT_VIEW_H
#define GRAPHICS_ABSTRACT_VIEW_H

#include <memory>
#include <functional>

namespace tung {

struct IView {
    virtual void on_draw() = 0;

    virtual void set_size(float width, float height) = 0;

    virtual void set_center(float x, float y) = 0;

    struct IMouseEvent {
        enum Type {
            MOUSE_DOWN,
            MOUSE_UP,
            MOUSE_MOVE,
        };

        virtual Type type() const = 0;
        
        virtual float x() const = 0;

        virtual float y() const = 0;
    };

    virtual void set_mouse_listener(
        std::function<void(const IMouseEvent&)> listener) = 0;

    virtual ~IView() {}
};

typedef std::shared_ptr<IView> IViewPtr;

struct IViewGroup: IView {
    virtual void add_view(const IViewPtr& view) = 0;

    virtual void remove_view(const IViewPtr& view) = 0;

    virtual ~IViewGroup() {}
};

} // namespace tung

#endif
