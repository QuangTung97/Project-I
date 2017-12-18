#ifndef GRAPHICS_ABSTRACT_VIEW_H
#define GRAPHICS_ABSTRACT_VIEW_H

#include <memory>
#include <functional>

namespace tung {

class KeyEvent;

// Chứa thông tin của một View để vẽ lên giao diện UI 
struct IView {
    // Chứa thông tin của một sự kiện click hoặc di chuyển chuột 
    struct IMouseEvent {
        enum Button {
            LEFT, // Ấn chuột trái 
            RIGHT, // Ấn chuột phải 
            MIDDE, // Ấn chuột giữa 
            NONE // Không ấn nút nào 
        };

        enum Type {
            MOUSE_DOWN, // Ấn nút xuống 
            MOUSE_UP, // Thả nút 
            MOUSE_MOVE, // Giữ nút và di chuyển 
        };

        // Trả loại nút của event này 
        virtual Button button() const = 0;

        // Trả về cách thức bấm nút tương ứng với event này 
        virtual Type type() const = 0;
        
        // Tọa độ theo x của con trỏ chuột trên màn hình 
        virtual float x() const = 0;

        // Tọa độ theo y của con trỏ chuột trên màn hình. 
        virtual float y() const = 0;
    };

    // Thiết lập kích thước của view
    // @with: CHiều rộng của view
    // @height: Chiều cao của view 
    virtual void set_size(float width, float height) = 0;

    // Thiết lập tọa độ của view, được tính từ góc trên bên trái so với màn hình. 
    // @x: Tọa độ theo phương ngang, từ trái sang phải (theo pixel)
    // @y: Tọa độ theo phương thẳng đứng, từ trên xuống dưới (theo pixel)
    virtual void set_top_left(float x, float y) = 0;

    // Hàm sẽ được gọi mỗi khi có một sự kiện chuột 
    // Hàm gọi đệ quy, từ gốc của View cho đến các lá của cây View 
    // @event: Sự kiện chuột tương ứng 
    virtual bool on_mouse_event(const IMouseEvent& event) = 0;

    // Hàm sẽ được gọi mỗi khi có một sự kiện bàn phím 
    // Hàm gọi đệ quy, từ gốc của View cho đến các lá của cây View 
    // @event: Sự kiện bàn phím tương ứng
    virtual bool on_key_event(const KeyEvent& event) = 0;

    // Định nghĩa lại kiểu dữ liệu cho hàm callback 
    typedef std::function<bool(const IMouseEvent&)> MouseListener;
    typedef std::function<bool(const KeyEvent&)> KeyListener;

    // Thiết lập hàm lắng nghe mà sẽ được gọi mỗi khi 
    // on_mouse_event được gọi. 
    // @listener: Hàm lắng nghe được chỉ định. 
    virtual void set_mouse_listener(MouseListener listener) = 0;

    // Thiết lập hàm lắng nghe mà sẽ được gọi mỗi khi 
    // on_key_event được gọi. 
    // @listener: Hàm lắng nghe được chỉ định. 
    virtual void set_key_listener(KeyListener listener) = 0;

    // Thiết lập giá trị của focus
    // Focus nghĩa là view này đang nhận sự kiện bàn phím 
    virtual void focus(bool value) = 0;

    // Trả về giá trị của focus 
    virtual bool focus() const = 0;

    // Destructor 
    virtual ~IView() {}
};

// Định nghĩa lại kiểu con trỏ cho IView 
typedef std::shared_ptr<IView> IViewPtr;

// Interface chứa những thủ tục cần thiết để xây dựng các view thành
// một cấu trúc cây 
struct IViewManager {
    // Thêm một view vào nút hiện tại 
    // @view: View muốn thêm. 
    virtual void add_view(const IViewPtr& view) = 0;

    // Xóa một view từ nút hiện tại 
    // @view: View muốn xóa. 
    virtual void remove_view(const IViewPtr& view) = 0;

    // Destructor 
    virtual ~IViewManager() {}
};

typedef std::shared_ptr<IViewManager> IViewManagerPtr;

} // namespace tung

#endif
