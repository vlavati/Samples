#ifndef CSERVICECONTAINER_H
#define CSERVICECONTAINER_H

#include <memory>
#include <iostream>
#include "internal.h"

class CServiceContainer
{
public:
    template <typename T>
    void set(const std::shared_ptr<T> &instance)
    {
        auto key = Internal::typeId<T>();
        auto wrapper = std::make_shared<Container<T> >(instance);

        m_instances[key] = wrapper;
    }

    template <typename T>
    std::shared_ptr<T> get() const
    {
        auto key = Internal::typeId<T>();
        auto it = m_instances.find(key);

        if (it == m_instances.end())
        {
            std::cerr << "Service not found: " << typeid(T).name();
            return std::shared_ptr<T>();
        }

        auto wrapper = it->second.get();
        auto container = static_cast<Container<T>*>(wrapper);

        return container->instance;
    }

private:
    template <typename T>
    struct Container : Internal::Delegate
    {
        std::shared_ptr<T> instance;
        Container(const std::shared_ptr<T> &instance) : instance(instance) {}
    };

    Internal::TypeMap m_instances;
};

#endif // CSERVICECONTAINER_H
