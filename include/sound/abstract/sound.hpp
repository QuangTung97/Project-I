#ifndef SOUND_ABSTRACT_HPP
#define SOUND_ABSTRACT_HPP

#include <memory>
#include <string>

namespace tung {

// Lớp thể hiện lỗi khi load âm thanh 
class SoundError: public std::exception {
private:
    std::string error_;

public:
    // Constructor
    SoundError(std::string error): error_{std::move(error)} {}

    // Trả về chi tiết thông tin lỗi 
    const char *what() const noexcept override {
        return error_.c_str(); 
    }
};

struct ISound;

typedef std::shared_ptr<ISound> ISoundPtr;

// Lớp trừu tượng (interface) đại diện cho một âm thanh đã load
struct ISound {
    // Chơi nhạc 
    virtual void play() = 0;

    // Tạm dừng 
    virtual void pause() = 0;
    
    // Hủy tạm dừng 
    virtual void resume() = 0;

    // Dừng phát nhạc 
    virtual void stop() = 0;

    // Thiết lập âm lượng 
    virtual void volume(float value) = 0;

    // Trả về giá trị âm lượng 
    virtual float volume() = 0;

    // Thiết lập vòng lặp 
    virtual void loop(bool value) = 0;

    // Trả về true nếu có vòng lặp 
    virtual bool loop() = 0;

    // Thực hiện sao chép 
    virtual ISoundPtr clone() = 0;

    // Destructor 
    virtual ~ISound() {}
};

// Interface dùng để load âm thanh 
// Có 2 kiểu load 
struct ISoundManager {
    // Load toàn bộ file âm thanh vào bộ nhớ 
    // @filename: Đường dẫn đến thư mục 
    // Return: Con trỏ đến ISound 
    virtual ISoundPtr load(const std::string& filename) = 0;

    // Load một phần file âm thanh, khi nào cần sử dụng phần nào của file nhạc thì mới load 
    // @filename: Đường dẫn đến thư mục 
    // Return: Con trỏ đến ISound 
    virtual ISoundPtr stream(const std::string& filename) = 0;

    // Để âm thanh có thể được phát. 
    // Cần gọi hàm này liên tục trong game loop 
    virtual void update() = 0;

    // Destructor
    virtual ~ISoundManager() {}
};

} // namespace tung

#endif
