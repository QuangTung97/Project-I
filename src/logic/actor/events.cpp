#include <logic/actor/events.hpp>

namespace tung {
namespace actor {
//----------------------
// Basic
//----------------------
EventType<9000> EVENT_DESTROY;
EventType<9001> EVENT_CREATED;
EventType<9002> EVENT_MOVE;

//----------------------
// Collision Handling
//----------------------
EventType<7001> EVENT_COLLIDE;

//----------------------
// Sprite Handling
//----------------------
EventType<11000> EVENT_SPRITE_STARTED;
EventType<11001> EVENT_SPRITE_ENDED;

//----------------------
// Sound Handling
//----------------------
EventType<1300> EVENT_SOUND_STARTED;
EventType<1300> EVENT_SOUND_ENDED;

} // namespace actor
} // namespace tung