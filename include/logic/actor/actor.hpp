#ifndef GAME_LOGIC_ACTOR_HPP
#define GAME_LOGIC_ACTOR_HPP

#include <memory>
#include <map>

#include <logic/basic/event.hpp>
#include "base.hpp"
#include "component_id.hpp"

//----------------------------------------------------
// Mỗi một thành phần trong logic của game là một actor 
// Ví dụ: máy bay, đạng, súng.
// Mỗi một actor sẽ có các thành phần (componenet) 
// như làm thế nào vẽ lên màn hình, 
// âm thanh như nào, va đập với các 
// actor ra sao. 
//----------------------------------------------------

namespace tung {
namespace actor {

// Class tự động sinh id cho các actor (id là duy nhất giữa các actor)
class IdGenerator {
private:
    static ActorId last_;

public:
    // Trả về một id mới 
    static ActorId new_id();
};

// Class chứa thông tin của một actor 
class Actor: public std::enable_shared_from_this<Actor> {
private:
    typedef std::map<ComponentId, StrongComponentPtr> ActorComponents;
    ActorId id_;
    ActorComponents components_;
    friend class ActorFactory;

public:
    // Constructor
    // @id: Id của actor 
    Actor(ActorId id): id_{id} {}

    // Trả về id của actor này. 
    ActorId get_id() const {
        return id_;
    }

    // Trả về Component ứng với component id 
    // @id: id của component
    template<typename Component_>
    std::weak_ptr<Component_> get_component(ComponentId id) {
        std::shared_ptr<Component_> ptr = nullptr;
        auto find_it = components_.find(id);
        if (find_it != components_.end()) {
            ptr = std::dynamic_pointer_cast<Component_>(find_it->second);
        }
        return ptr;
    }

    // Trả về Component ứng với component id 
    // id của actor được suy ra từ đối số class truyền vào template. 
    template<typename Component_>
    std::weak_ptr<Component_> get_component() {
        std::shared_ptr<Component_> ptr = nullptr;
        auto find_it = components_.find(Component_::COMPONENT_ID);
        if (find_it != components_.end()) {
            ptr = std::dynamic_pointer_cast<Component_>(find_it->second);
        }
        return ptr;
    }

    // Destructor
    virtual ~Actor() {}

public:
    // Thêm một component
    void add_component(StrongComponentPtr component);
};

} // namespace actor
} // namespace tung

#endif
