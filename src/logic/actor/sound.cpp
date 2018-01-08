#include <logic/actor/sound.hpp>

namespace tung {
namespace actor {

const ComponentId Sound::COMPONENT_ID = ComponentId::SOUND;

void Sound::add_sound(int index, const std::string& filename) {
    // Load âm thanh từ cache 
    auto sound = manager_.get_sound(filename);
    // Lưu nó vào danh sách các âm thanh 
    sounds_[index] = std::move(sound);
}

void Sound::start(int index) {
    // Tìm và phát âm thanh 
    auto find_it = sounds_.find(index);
    if (find_it != sounds_.end()) {
        find_it->second->play();
    }
}

void Sound::end(int index) {
    // Tìm và dừng phát âm thanh 
    auto find_it = sounds_.find(index);
    if (find_it != sounds_.end()) {
        find_it->second->stop();
    }
}

} // namespace actor
} // namespace tung
