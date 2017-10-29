#ifndef LOGIC_BASE_HPP
#define LOGIC_BASE_HPP

#include <memory>

namespace tung {
namespace actor {

class Actor;
class Component;

using StrongActorPtr = std::shared_ptr<Actor>;
using WeakActorPtr =  std::weak_ptr<Actor>;

typedef int ActorId;

using StrongComponentPtr = std::shared_ptr<Component>;
using WeakComponentPtr = std::weak_ptr<Component>;

} // namespace actor
} // namespace tung

#endif