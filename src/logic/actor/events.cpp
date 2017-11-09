#include <logic/actor/events.hpp>

namespace tung {
namespace actor {
//----------------------
// Basic
//----------------------
EventType<9000> EVENT_DESTROY;
EventType<9001> EVENT_CREATED;
EventType<9002> EVENT_MOVE;
EventType<9003> EVENT_ROTATE;

//----------------------
// Collision Handling
//----------------------
EventType<7001> EVENT_COLLIDE;
EventType<7002> EVENT_DISABLE_COLLISION;
EventType<7003> EVENT_ENABLE_COLLISION;

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

//----------------------
// Graphics Image Handling
//----------------------
EventType<3300> EVENT_GRAPHICS_IMAGE_SHOW;
EventType<3301> EVENT_GRAPHICS_IMAGE_HIDE;
EventType<3301> EVENT_GRAPHICS_IMAGE_ROTATE;

} // namespace actor
} // namespace tung