#ifndef SOUND_SYSTEM_HPP
#define SOUND_SYSTEM_HPP

#include <logic/abstract/event_manager.hpp>

namespace tung {
namespace system {

class Sound {
private:
    IEventManager& manager_;

public:
    Sound(IEventManager& manager);

    ~Sound();
};

} // namespace system
} // namespace tung

#endif