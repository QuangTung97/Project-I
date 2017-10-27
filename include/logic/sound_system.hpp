#ifndef SOUND_SYSTEM_HPP
#define SOUND_SYSTEM_HPP

#include <logic/abstract/event_manager.hpp>

namespace tung {

class SoundSystem {
private:
    IEventManager& manager_;

public:
    SoundSystem(IEventManager& manager);

    ~SoundSystem();
};

} // namespace tung

#endif