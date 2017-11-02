#ifndef LOGIC_ACTOR_SPRITE_HPP
#define LOGIC_ACTOR_SPRITE_HPP

#include <logic/basic/event.hpp>
#include "actor.hpp"
#include "component.hpp"
#include <graphics/gl/sprite_drawable.hpp>
#include <graphics/gl/sprite_factory.hpp>
#include <logic/basic/process_manager.hpp>

namespace tung {

namespace system {
class Sprite;
}

namespace actor {

extern EventType<11000> EVENT_SPRITE_STARTED;
extern EventType<11001> EVENT_SPRITE_ENDED;

class SpriteStartedEvent: public EventData {
private:
    int index_;
public:
    SpriteStartedEvent(int index)
    : EventData(TimePoint{}, EVENT_SPRITE_STARTED), index_{index} {}

    IEventDataPtr clone() const override {
        return std::make_unique<SpriteStartedEvent>(index_);
    }
};

class SpriteEndedEvent: public EventData {
private:
    int index_;

public:
    SpriteEndedEvent(int index)
    : EventData(TimePoint{}, EVENT_SPRITE_ENDED), index_{index} {}

    IEventDataPtr clone() const override {
        return std::make_unique<SpriteEndedEvent>(index_);
    }
};

class Sprite;

class SpriteProcess: public Process {
private:
    milliseconds current_time_;
    const std::shared_ptr<SpriteDrawable> drawable_;
    Sprite& owner_;
    const int fps_ = 24;
    float x_, y_;
    friend class Sprite;

public:
    SpriteProcess(Sprite& owner, std::shared_ptr<SpriteDrawable> drawable);

    void move_to(float x, float y) { x_ = x; y_ = y; }

protected:
    void on_init() override;

    void on_update(milliseconds dt) override;

    void on_success() override;

    void on_fail() override;
};

class Sprite: public Component {
private:
    friend class SpriteProcess;
    std::unordered_map<int, std::shared_ptr<SpriteProcess>> processes_;
    IDrawableManagerPtr root_;
    SpriteFactory& factory_;
    ProcessManager& manager_;

public:
    Sprite(IDrawableManagerPtr root, SpriteFactory& factory, ProcessManager& manager)
    : root_{std::move(root)}, factory_{factory}, manager_{manager} {}

    ComponentId get_id() const override {
        return ComponentId::SPRITE;
    }

    void add_sprite(int index, const std::string& image, 
        int rows, int cols, float height);

    void move_to(float x, float y);

    void start(int index);

    void end(int index);
};

} // namespace actor
} // namespace tung

#endif