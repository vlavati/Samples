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
        auto wrapperCreator = [] (DI &di) { return std::make_shared<T>(di.get<Dependencies>() ...); };
        auto wrapper = std::make_shared<FunctionContainer<T> >(wrapperCreator);

        m_contstructors[key] = wrapper;
    }

    template <typename T, typename... Dependencies>
    struct InjectionMethod
    {
        typedef void (T::* type) (std::shared_ptr<Dependencies> ...);
    };

    template <typename T, typename... Dependencies>
    void addMethod(typename InjectionMethod<T, Dependencies ...>::type method)
    {
        auto key = Internal::typeId<T>();
        auto wrapperMethod = [method] (DI &di, T* obj) { (obj->*method)(di.get<Dependencies>() ...); };
        auto wrapper = std::make_shared<InjectionMethodContainer<T> >(wrapperMethod);

        m_methods[key] = wrapper;
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
            runMethod(newInstance.get());
            set<T>(newInstance);
            return newInstance;
        }

        auto wrapper = it->second.get();
        auto container = static_cast<Container<T>*>(wrapper);

        return container->instance;
    }

    template <typename T>
    void runMethod(T *obj)
    {
        auto key = Internal::typeId<T>();
        auto it = m_methods.find(key);

        if (it == m_methods.end())
        {
            std::cerr << "There is no method for " << typeid(T).name() << std::endl;
            return;
        }

        auto wrapper = it->second.get();
        auto container = static_cast<InjectionMethodContainer<T>*>(wrapper);

        container->function(*this, obj);
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

    template <typename T>
    struct Function
    {
        typedef std::shared_ptr<T> (*type)(DI&);
    };

    template <typename T>
    struct FunctionContainer : Internal::Delegate
    {
        typename Function<T>::type function;
        FunctionContainer(typename Function<T>::type _function) : function(_function) {}
    };

    template <typename T, typename... Dependencies>
    struct InjectionMethodWrapper
    {
        typedef std::function<void(DI&,T*)> type;
    };

    template <typename T>
    struct InjectionMethodContainer : Internal::Delegate
    {
        typename InjectionMethodWrapper<T>::type function;
        InjectionMethodContainer(typename InjectionMethodWrapper<T>::type _function) : function(_function) {}
    };

    Internal::TypeMap m_instances;
    Internal::TypeMap m_contstructors;
    Internal::TypeMap m_methods;
};

#endif // DI_H
