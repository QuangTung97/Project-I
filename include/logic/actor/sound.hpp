#ifndef LOGIC_ACTOR_SOUND_HPP
#define LOGIC_ACTOR_SOUND_HPP

#include "component.hpp"
#include "actor.hpp"
#include <sound/abstract/sound.hpp>
#include <unordered_map>

namespace tung {
namespace actor {

// Component phục vụ cho việc phát nhạc. 
class Sound: public Component {
private:
    std::unordered_map<int, ISoundPtr> sounds_;
    ISoundManager& manager_;

public:
    static const ComponentId COMPONENT_ID;

    // Constructor 
    // @manager: Manager quản lý âm thanh. 
    Sound(ISoundManager& manager)
    : manager_{manager} {}

    ComponentId get_id() const override {
        return COMPONENT_ID;
    }

    // Thêm một âm thanh, để chuẩn bị chơi 
    // @index: Vị trí sẽ được thêm. 
    // @filename: Đường dẫn đến file âm thanh 
    void add_sound(int index, const std::string& filename);

    // Chơi nhạc 
    // @index: Vị trí của âm thanh mong muốn trong component này 
    void start(int index);

    // Kết thúc chơi nhạc 
    // @index: Vị trí của âm thanh mong muốn trong component này 
    void end(int index);
};

} // namspace actor
} // namspace tung

#endif