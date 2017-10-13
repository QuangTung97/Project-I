#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include "abstract/view.hpp"
#include <graphics/abstract/drawable.hpp>
#include <vector>

namespace tung {

class MouseEvent: public IView::IMouseEvent {
private:
    const Type type_;
    const float x_, y_;

public:
    MouseEvent(Type type, float x, float y);

    Type type() const override;
    
    float x() const override;

    float y() const override;
};

class View: public IView {
protected:
    MouseListener mouse_listener_ = nullptr;
    float x_, y_, w_, h_;
    IDrawablePtr drawable_;

public:
    View(float x, float y, float width, float height);

    void set_size(float width, float height) override;

    void set_top_left(float x, float y) override;

    void set_mouse_listener(MouseListener listener) override;

    bool on_mouse_event(const IMouseEvent& event) override;

    const IDrawablePtr& get_drawable() const {
        return drawable_;
    }

    virtual ~View() {}
};

class ViewGroup: public View, public IViewManager {
private:
    typedef std::vector<IViewPtr> ViewList;
    ViewList view_list_;

    IView *view_mouse_move_ = nullptr;

public:
    ViewGroup(float x, float y, float width, float height);

    bool on_mouse_event(const IMouseEvent& event) override;

    void add_view(const IViewPtr& view) override;

    void remove_view(const IViewPtr& view) override;

    virtual ~ViewGroup() {}
};

} // namespace tung

#endif
