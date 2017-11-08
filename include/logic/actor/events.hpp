#ifndef LOGIC_ACTOR_EVENTS_HPP
#define LOGIC_ACTOR_EVENTS_HPP

#include <logic/basic/event.hpp>
#include "base.hpp"

namespace tung {
namespace actor {
//----------------------
// Basic
//----------------------
extern EventType<9000> EVENT_DESTROY;
extern EventType<9001> EVENT_CREATED;
extern EventType<9002> EVENT_MOVE;

class DestroyEvent: public EventData {
private:
    const ActorId id_;

public:
    DestroyEvent(ActorId id)
    : EventData(TimePoint{}, EVENT_DESTROY), id_{id} {}

    ActorId get_id() const { return id_; }

    IEventDataPtr clone() const override {
        return std::make_unique<DestroyEvent>(id_);
    }

    virtual ~DestroyEvent() {}
};

class CreatedEvent: public EventData {
private:
    const ActorId id_;

public:
    CreatedEvent(ActorId id)
    : EventData(TimePoint{}, EVENT_CREATED), id_{id} {}

    ActorId get_id() const { return id_; }

    IEventDataPtr clone() const override {
        return std::make_unique<CreatedEvent>(id_);
    }

    virtual ~CreatedEvent() {}
};

class MoveEvent: public EventData {
private:
    const ActorId id_;
    const float x_, y_;

public:
    MoveEvent(ActorId id, float x, float y)
    : EventData{TimePoint{}, EVENT_MOVE}, id_{id}, x_{x}, y_{y} {}

    ActorId get_id() const {
        return id_;
    }

    float get_x() const { return x_; }

    float get_y() const { return y_; }

    IEventDataPtr clone() const override {
        return std::make_unique<MoveEvent>(id_, x_, y_);
    }
};

//----------------------
// Collision Handling
//----------------------
extern EventType<7001> EVENT_COLLIDE;

class CollideEvent: public EventData {
private:
    ActorId id_;

public:
    CollideEvent(TimePoint time_point, ActorId id)
    : EventData{time_point, EVENT_COLLIDE}, id_{id} {}

    IEventDataPtr clone() const override {
        return std::make_unique<CollideEvent>(time_point_, id_);
    }

    ActorId get_id() const { return id_; }
};


//----------------------
// Sprite Handling
//----------------------
extern EventType<11000> EVENT_SPRITE_STARTED;
extern EventType<11001> EVENT_SPRITE_ENDED;

class SpriteStartedEvent: public EventData {
private:
    ActorId id_;
    int index_;

public:
    SpriteStartedEvent(ActorId id, int index)
    : EventData(TimePoint{}, EVENT_SPRITE_STARTED), 
    id_{id}, index_{index} {}

    IEventDataPtr clone() const override {
        return std::make_unique<SpriteStartedEvent>(id_, index_);
    }

    ActorId get_id() const { return id_; }

    int get_index() const { return index_; }
};

class SpriteEndedEvent: public EventData {
private:
    ActorId id_;
    int index_;

public:
    SpriteEndedEvent(ActorId id, int index)
    : EventData(TimePoint{}, EVENT_SPRITE_ENDED), 
    id_{id}, index_{index} {}

    IEventDataPtr clone() const override {
        return std::make_unique<SpriteEndedEvent>(id_, index_);
    }

    ActorId get_id() const { return id_; }

    int get_index() const { return index_; }
};


//----------------------
// Sound Handling
//----------------------
extern EventType<1300> EVENT_SOUND_STARTED;
extern EventType<1300> EVENT_SOUND_ENDED;

class SoundStartedEvent: public EventData {
private:
    ActorId id_;
    int index_;

public:
    SoundStartedEvent(ActorId id, int index)
    : EventData{TimePoint{}, EVENT_SOUND_STARTED},
    id_{id}, index_{index} {}

    IEventDataPtr clone() const override {
        return std::make_unique<SoundStartedEvent>(id_, index_);
    }

    ActorId get_id() const { return id_; }

    int get_index() const { return index_; }
};

class SoundEndedEvent: public EventData {
private:
    ActorId id_;
    int index_;

public:
    SoundEndedEvent(ActorId id, int index)
    : EventData{TimePoint{}, EVENT_SOUND_ENDED},
    id_{id}, index_{index} {}

    IEventDataPtr clone() const override {
        return std::make_unique<SoundEndedEvent>(id_, index_);
    }

    ActorId get_id() const { return id_; }

    int get_index() const { return index_; }
};

//----------------------
// Graphics Image Handling
//----------------------
extern EventType<3300> EVENT_GRAPHICS_IMAGE_SHOW;
extern EventType<3301> EVENT_GRAPHICS_IMAGE_HIDE;

} // namespace actor
} // namespace tung

#endif