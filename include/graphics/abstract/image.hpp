#ifndef GRAPHICS_ABSTRACT_IMAGE_HPP
#define GRAPHICS_ABSTRACT_IMAGE_HPP

#include <memory>
#include <string>
#include <exception>

namespace tung {

// Class chứa thông tin của các lỗi khi load hình ảnh 
class ImageException: public std::exception {
private:
    std::string what_;

public:
    // Constructor 
    // @what: xâu chứa thông tin chi tiết của lỗi 
    ImageException(std::string what): what_{what} {}

    // Trả về: Thông tin chi tiết của lỗi 
    const char *what() const noexcept override {
        return what_.c_str();
    }
};

// Interface đại diện cho một hình ảnh đã được load 
struct IImage {
    enum Format {
        FORMAT_RGB,
        FORMAT_RGBA,
    };

    enum BitDepth {
        BIT_DEPTH_8,
        BIT_DEPTH_16,
    };

    // Trả về: Chiều rộng của hình ảnh 
    virtual int width() const = 0;

    // Trả về: Chiều cao của hình ảnh 
    virtual int height() const = 0;

    // Trả về: Dữ liệu nhị phân của ảnh (khi đã được giải nén)
    virtual const void *data() const = 0;

    // Trả về: Số phần tử màu của ảnh. Tùy thuộc vào Format 
    virtual int color_component_count() const = 0;

    // Trả về: Số bit để lưu trữ một phần tử màu của ảnh. 
    virtual BitDepth bit_depth() const = 0;

    // Trả về: Format của ảnh. 
    virtual Format format() const = 0;

    // Destructor
    virtual ~IImage() {}
};

typedef std::shared_ptr<IImage> IImagePtr;

// Interface cho việc load hình ảnh
struct IImageLoader {
    // @filename: Đường dẫn file đến hình ảnh 
    // Return: Một shared_ptr đến hình ảnh đã được load 
    virtual IImagePtr load(const std::string& filename) = 0;

    // Destructor
    virtual ~IImageLoader() {}
};

} // namespace tung

#endif
