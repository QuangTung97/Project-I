#ifndef LOGIC_ACTOR_SPRITE_HPP
#define LOGIC_ACTOR_SPRITE_HPP

#include <logic/basic/event.hpp>
#include <vector>
#include "actor.hpp"
#include "component.hpp"
#include <graphics/gl/sprite_drawable.hpp>
#include <graphics/gl/sprite_factory.hpp>

namespace tung {

namespace system {
class Sprite;
}

namespace actor {

extern EventType<11000> EVENT_SPRITE_STARTED;
extern EventType<11001> EVENT_SPRITE_ENDED;

class SpriteStartedEvent: public EventData {

};

class SpriteElement {
private:
    std::shared_ptr<SpriteDrawable> drawable_;
    
public:
    void start();
    void end();
};

class Sprite: public Component {
private:
    std::vector<SpriteElement> elements_;

public:
    Sprite(std::string filename, int rows, int cols, float height);

    ComponentId get_id() const override {
        return ComponentId::SPRITE;
    }

    void start(int index);

    void end(int index);
};

} // namespace actor
} // namespace tung

#endif