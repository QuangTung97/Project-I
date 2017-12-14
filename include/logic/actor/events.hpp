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
extern EventType<9003> EVENT_ROTATE;

// Sự kiện actor bị hủy. 
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

// Sự kiện actor được tạo. 
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

// Sự kiện actor được di chuyển 
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

// Sự kiện quay hình ảnh.
class RotateEvent: public EventData {
private:
    const ActorId id_;
    const float degree_;

public:
    RotateEvent(ActorId id, float degree)
    : EventData{TimePoint{}, EVENT_ROTATE}, id_{id}, degree_{degree} 
    {}

    ActorId get_id() const {
        return id_;
    }

    float get_angle() const { return degree_; }

    IEventDataPtr clone() const override {
        return std::make_unique<RotateEvent>(id_, degree_);
    }
};

//----------------------
// Collision Handling
//----------------------
extern EventType<7001> EVENT_COLLIDE;
extern EventType<7002> EVENT_DISABLE_COLLISION;
extern EventType<7003> EVENT_ENABLE_COLLISION;

// Sự kiện actor bị va chạm. 
class CollideEvent: public EventData {
private:
    const ActorId id_;
    const ActorId collide_width_id_;

public:
    CollideEvent(TimePoint time_point, 
        ActorId id, ActorId collide_width_id)
    : EventData{time_point, EVENT_COLLIDE}, 
        id_{id}, collide_width_id_{collide_width_id} {}

    IEventDataPtr clone() const override {
        return std::make_unique<CollideEvent>(time_point_, id_, collide_width_id_);
    }

    ActorId get_id() const { return id_; }

    ActorId get_collide_width_id() const { return collide_width_id_; }
};

// Sự kiện actor bị disable 
class DisableCollisionEvent: public EventData {
private:
    const ActorId id_;

public:
    DisableCollisionEvent(ActorId id)
    : EventData{TimePoint{}, EVENT_DISABLE_COLLISION}, id_{id} {}

    IEventDataPtr clone() const override {
        return std::make_unique<DisableCollisionEvent>(id_);
    }

    ActorId get_id() const { return id_; }
};

// Sự kiện actor được enable 
class EnableCollisionEvent: public EventData {
private:
    const ActorId id_;

public:
    EnableCollisionEvent(ActorId id)
    : EventData{TimePoint{}, EVENT_ENABLE_COLLISION}, id_{id} {}

    IEventDataPtr clone() const override {
        return std::make_unique<EnableCollisionEvent>(id_);
    }

    ActorId get_id() const { return id_; }
};

//----------------------
// Sprite Handling
//----------------------
extern EventType<11000> EVENT_SPRITE_STARTED;
extern EventType<11001> EVENT_SPRITE_ENDED;

// Sprite bắt đầu animation 
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

// Sprite kết thúc animation 
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

// Bắt đầu chơi nhạc 
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

// Kết thúc chơi nhạc 
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
extern EventType<3301> EVENT_GRAPHICS_IMAGE_ROTATE;

// Sự kiện hiển thị hình ảnh. 
class GraphicsImageShowEvent: public EventData {
private:
    ActorId id_;

public:
    GraphicsImageShowEvent(ActorId id)
    : EventData{TimePoint{}, EVENT_GRAPHICS_IMAGE_SHOW},
    id_{id} {}

    IEventDataPtr clone() const override {
        return std::make_unique<GraphicsImageShowEvent>(id_);
    }

    ActorId get_id() const { return id_; }
};

// Sự kiện ẩn hình ảnh. 
class GraphicsImageHideEvent: public EventData {
private:
    ActorId id_;

public:
    GraphicsImageHideEvent(ActorId id)
    : EventData{TimePoint{}, EVENT_GRAPHICS_IMAGE_HIDE},
    id_{id} {}

    IEventDataPtr clone() const override {
        return std::make_unique<GraphicsImageHideEvent>(id_);
    }

    ActorId get_id() const { return id_; }
};

} // namespace actor
} // namespace tung

#endif