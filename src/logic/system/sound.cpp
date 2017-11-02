#include <logic/system/sound.hpp>
#include <logic/actor/events.hpp>

namespace tung {
namespace system {

Sound::Sound(IEventManager& manager)
: manager_{manager} {
}

Sound::~Sound() {
}

} // namespace system
} // namespace tung