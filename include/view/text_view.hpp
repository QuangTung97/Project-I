#ifndef VIEW_TEXT_VIEW_HPP
#define VIEW_TEXT_VIEW_HPP

#include <view/view.hpp>
#include <graphics/gl/drawable.hpp>
#include <graphics/abstract/text_manager.hpp>

namespace tung {

// Class chứa thông tin cần thiết để hiển thị một view chứa text lên màn hình. 
class TextView: public View {
protected:
    static ITextManager *text_manager_;
    ITextPtr text_;

    int font_size_;
    Color color_;
    std::string string_;

    // Cập nhật lại biến drawable_ để chứa những thông tin mới. 
    void validate();

public:
    // Constructor 
    // @x, @y: Tạo độ của view, tính theo góc trên bên trái (đơn vị pixel).
    // @font_size: Kích thước của font (theo pixel)
    // @text: Văn bản hiển thị lên màn hình. 
    TextView(float x, float y, 
        int font_size, const std::string& text);

    // Constructor 
    // @x, @y: Tạo độ của view, tính theo góc trên bên trái (đơn vị pixel).
    // @font_size: Kích thước của font (theo pixel)
    // @color: Màu mà văn bản sẽ được hiển thị. 
    // @text: Văn bản hiển thị lên màn hình. 
    TextView(float x, float y, 
        int font_size, Color color, const std::string& text);

    // Thiết lập text manager cần thiết để có thể tạo được drawable
    // @manager: Một Text Manager. 
    static void set_text_manager(ITextManager& manager) {
        text_manager_ = &manager;
    }

    // Thiết lập dòng text sẽ hiển thị 
    // @text: Dòng văn bản.
    void set_text(const std::string& text);

    // Thiết lập kích thước font.
    // @size: kích thước của font (Theo pixel)
    void set_font_size(int size);

    // Thiết lập màu sắc của văn bản sẽ hiển  thị
    // @color: Màu sắc của văn bản. 
    void set_color(Color color);

    // Thiết lập kích thước của view. 
    // KHông được sử dụng. View sẽ được tính toán nhờ font và text
    void set_size(float, float) override;

    virtual ~TextView() {}
};

} // namespace tung

#endif
