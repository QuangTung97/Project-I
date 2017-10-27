#include <logic/sound_system.hpp>

namespace tung {

SoundSystem::SoundSystem(IEventManager& manager)
: manager_{manager} {

}

SoundSystem::~SoundSystem() {

}

} // namespace tung