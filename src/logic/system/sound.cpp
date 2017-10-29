#include <logic/system/sound.hpp>

namespace tung {
namespace system {

Sound::Sound(IEventManager& manager)
: manager_{manager} {
}

Sound::~Sound() {
}

} // namespace system
} // namespace tung