#ifndef GAME_LOGIC_ACTOR_COMPONENT_HPP
#define GAME_LOGIC_ACTOR_COMPONENT_HPP

namespace tung {

enum class ActorComponentId {
    // TODO: Add here
};

class ActorComponent;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef std::weak_ptr<ActorComponent> WeakActorComponentPtr;

class Actor;
typedef std::shared_ptr<Actor> StrongActorPtr;

class ActorComponent {
private:
    StrongActorPtr owner_;
    friend class Actor;
    friend class ActorFactory;

public:
    virtual ActorComponentId get_id() const = 0;

    virtual ~ActorComponent() {}

private:
    void set_owner(StrongActorPtr owner) {
        this->owner_ = std::move(owner);
    }
};

} // namespace tung

#endif