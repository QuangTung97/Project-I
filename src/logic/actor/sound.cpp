#include <logic/actor/sound.hpp>

namespace tung {
namespace actor {

const ComponentId Sound::COMPONENT_ID = ComponentId::SOUND;

void Sound::add_sound(int index, const std::string& filename) {
    auto sound = manager_.load(filename);
    sounds_[index] = std::move(sound);
}

void Sound::start(int index) {
    auto find_it = sounds_.find(index);
    if (find_it != sounds_.end()) {
        find_it->second->play();
    }
}

void Sound::end(int index) {
    auto find_it = sounds_.find(index);
    if (find_it != sounds_.end()) {
        find_it->second->stop();
    }
}

} // namespace actor
} // namespace tung