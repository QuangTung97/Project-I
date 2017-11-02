#include <logic/actor/sound.hpp>

namespace tung {
namespace actor {

const ComponentId Sound::COMPONENT_ID = ComponentId::SOUND;

void Sound::add_sound(int index, const std::string& filename) {
    auto sound = manager_.load(filename);
    sounds_[index] = std::move(sound);
}

void Sound::start(int index) {
    sounds_[index]->play();
}

void Sound::end(int index) {
    sounds_[index]->stop();
}

} // namespace actor
} // namespace tung