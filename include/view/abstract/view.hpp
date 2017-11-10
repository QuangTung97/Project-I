#ifndef GRAPHICS_ABSTRACT_VIEW_H
#define GRAPHICS_ABSTRACT_VIEW_H

#include <memory>
#include <functional>

namespace tung {

struct IView {
    struct IMouseEvent {
        enum Button {
            LEFT,
            RIGHT, 
            MIDDE,
            NONE
        };

        enum Type {
            MOUSE_DOWN,
            MOUSE_UP,
            MOUSE_MOVE,
        };

        virtual Button button() const = 0;

        virtual Type type() const = 0;
        
        virtual float x() const = 0;

        virtual float y() const = 0;
    };

    virtual void set_size(float width, float height) = 0;

    virtual void set_top_left(float x, float y) = 0;

    virtual bool on_mouse_event(const IMouseEvent& event) = 0;

    typedef std::function<bool(const IMouseEvent&)> MouseListener;

    virtual void set_mouse_listener(MouseListener listener) = 0;

    virtual ~IView() {}
};

typedef std::shared_ptr<IView> IViewPtr;

struct IViewManager {
    virtual void add_view(const IViewPtr& view) = 0;

    virtual void remove_view(const IViewPtr& view) = 0;

    virtual ~IViewManager() {}
};

typedef std::shared_ptr<IViewManager> IViewManagerPtr;

} // namespace tung

#endif
