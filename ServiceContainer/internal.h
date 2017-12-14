#ifndef INTERNAL_H
#define INTERNAL_H

#include <unordered_map>

namespace Internal {

typedef std::string TypeId;

struct Delegate
{
    virtual ~Delegate() {}
};

template<typename T>
static TypeId typeId() { return typeid(T).name(); }

typedef std::unordered_map<TypeId, std::shared_ptr<Delegate> > TypeMap;

}

#endif // INTERNAL_H
