#ifndef LOGIC_ACTOR_SOUND_HPP
#define LOGIC_ACTOR_SOUND_HPP

#include "component.hpp"
#include "actor.hpp"
#include <sound/abstract/sound.hpp>
#include <unordered_map>

namespace tung {
namespace actor {

class Sound: public Component {
private:
    std::unordered_map<int, ISoundPtr> sounds_;
    ISoundManager& manager_;

public:
    static const ComponentId COMPONENT_ID;

    Sound(ISoundManager& manager)
    : manager_{manager} {}

    ComponentId get_id() const override {
        return COMPONENT_ID;
    }

    void add_sound(int index, const std::string& filename);

    void start(int index);

    void end(int index);
};

} // namspace actor
} // namspace tung

#endif