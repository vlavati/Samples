#ifndef DI_H
#define DI_H

#include "internal.h"

class DI
{
public:
    template <typename T, typename... Dependencies>
    void addDependencies()
    {
        auto key = Internal::typeId<T>();
        auto wrapper = std::make_shared<FunctionContainer<T> >(&DI::creator<T, Dependencies ...>);

        m_contstructors[key] = wrapper;
    }

    template <typename T>
    void set(const std::shared_ptr<T> &instance)
    {
        auto key = Internal::typeId<T>();
        auto wrapper = std::make_shared<Container<T> >(instance);

        m_instances[key] = wrapper;
    }

    template <typename T>
    std::shared_ptr<T> get()
    {
        auto key = Internal::typeId<T>();
        auto it = m_instances.find(key);

        if (it == m_instances.end())
        {
            auto newInstance = make<T>();
            set<T>(newInstance);
            return newInstance;
        }

        auto wrapper = it->second.get();
        auto container = static_cast<Container<T>*>(wrapper);

        return container->instance;
    }

private:
    template <typename T>
    std::shared_ptr<T> make()
    {
        auto key = Internal::typeId<T>();
        auto it = m_contstructors.find(key);

        if (it == m_contstructors.end())
        {
            return std::shared_ptr<T>();
        }

        auto wrapper = it->second.get();
        auto container = static_cast<FunctionContainer<T>*>(wrapper);

        return container->function(*this);
    }

    template <typename T, typename... Dependencies>
    static std::shared_ptr<T> creator(DI &di)
    {
        return std::make_shared<T>(di.get<Dependencies>() ...);
    }

    template <typename T>
    struct Container : Internal::Delegate
    {
        std::shared_ptr<T> instance;
        Container(const std::shared_ptr<T> &instance) : instance(instance) {}
    };

    template <typename T>
    struct Function
    {
        typedef std::function<std::shared_ptr<T>(DI&)> type;
    };

    template <typename T>
    struct FunctionContainer : Internal::Delegate
    {
        typename Function<T>::type function;
        FunctionContainer(typename Function<T>::type _function) : function(_function) {}
    };

    Internal::TypeMap m_instances;
    Internal::TypeMap m_contstructors;
};

#endif // DI_H
