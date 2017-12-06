#ifndef CSERVICECONTAINER_H
#define CSERVICECONTAINER_H

#include <unordered_map>
#include <memory>
#include <iostream>

class CServiceContainer
{
public:
    template <typename T>
    void set(const std::shared_ptr<T> &instance)
    {
        auto key = typeId<T>();
        auto wrapper = std::make_shared<Container<T> >(instance);

        m_instances[key] = wrapper;
    }

    template <typename T>
    std::shared_ptr<T> get() const
    {
        auto key = typeId<T>();
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
    struct Delegate
    {
        virtual ~Delegate() {}
    };

    template <typename T>
    struct Container : Delegate
    {
        const std::shared_ptr<T> &instance;
        Container(const std::shared_ptr<T> &instance) : instance(instance) {}
    };

    typedef std::string TypeId;

    template<typename T>
    static TypeId typeId() { return typeid(T).name(); }

    std::unordered_map<TypeId, std::shared_ptr<Delegate> > m_instances;
};

#endif // CSERVICECONTAINER_H
