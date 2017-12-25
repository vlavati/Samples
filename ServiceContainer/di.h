#ifndef DI_H
#define DI_H

#include "internal.h"
#include "dimodule.h"

class DI : public DIModule
{
public:
    template <typename T, typename... Dependencies>
    struct Inject {
        typedef void (T::* type) (std::shared_ptr<Dependencies> ...);

        static std::shared_ptr<T> factory(DI &di)
        {
            return std::make_shared<T>(di.get<Dependencies>() ...);
        }

        template <type Method>
        static void method(DI &di, T &obj)
        {
            (obj.*Method)(di.get<Dependencies>() ...);
        }
    };

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
            tryRunMethod(*newInstance.get());
            set<T>(newInstance);
            return newInstance;
        }

        auto wrapper = it->second.get();
        auto container = static_cast<Container<T>*>(wrapper);

        return container->instance;
    }

    template <typename T>
    bool tryRunMethod(T &obj)
    {
        auto key = Internal::typeId<T>();
        auto it = m_methods.find(key);

        if (it == m_methods.end())
            return false;

        auto wrapper = it->second.get();
        auto container = static_cast<InjectionMethodContainer<T>*>(wrapper);

        container->function(*this, obj);
        return true;
    }

    template <typename T>
    void runMethod(T &obj)
    {
        if (tryRunMethod(obj))
            return;

        std::cerr << "There is no method for " << typeid(T).name() << std::endl;
    }

private:
    template <typename T>
    std::shared_ptr<T> make()
    {
        auto key = Internal::typeId<T>();
        auto it = m_contstructors.find(key);

        if (it == m_contstructors.end())
        {
            std::cerr << "There is no constuctor for " << typeid(T).name() << std::endl;
            return std::shared_ptr<T>();
        }

        auto wrapper = it->second.get();
        auto container = static_cast<FunctionContainer<T>*>(wrapper);

        return container->function(*this);
    }

    template <typename T>
    struct Container : Internal::Delegate
    {
        std::shared_ptr<T> instance;
        Container(const std::shared_ptr<T> &instance) : instance(instance) {}
    };

    Internal::TypeMap m_instances;
};

#endif // DI_H
