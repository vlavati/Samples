#ifndef DIMODULE_H
#define DIMODULE_H

#include "internal.h"

class DI;

class DIModule
{
public:
    template <typename T>
    struct Function
    {
        typedef std::function<std::shared_ptr<T>(DI&)> type;
    };

    template <typename T>
    struct InjectionMethodWrapper
    {
        typedef std::function<void(DI&,T&)> type;
    };

    template <class T>
    void addDependencies(typename Function<T>::type wrapperCreator)
    {
        auto key = Internal::typeId<T>();
        auto wrapper = std::make_shared<FunctionContainer<T> >(wrapperCreator);

        m_contstructors[key] = wrapper;
    }

    template <typename T>
    void addMethod(typename InjectionMethodWrapper<T>::type wrapperMethod)
    {
        auto key = Internal::typeId<T>();
        auto wrapper = std::make_shared<InjectionMethodContainer<T> >(wrapperMethod);

        m_methods[key] = wrapper;
    }

    void addModule(DIModule &subModule)
    {
        for (auto keyValue : subModule.m_methods)
            m_methods[keyValue.first] = keyValue.second;

        for (auto keyValue : subModule.m_contstructors)
            m_contstructors[keyValue.first] = keyValue.second;
    }

protected:
    template <typename T>
    struct FunctionContainer : Internal::Delegate
    {
        typename Function<T>::type function;
        FunctionContainer(typename Function<T>::type _function) : function(_function) {}
    };

    template <typename T>
    struct InjectionMethodContainer : Internal::Delegate
    {
        typename InjectionMethodWrapper<T>::type function;
        InjectionMethodContainer(typename InjectionMethodWrapper<T>::type _function) : function(_function) {}
    };

    Internal::TypeMap m_contstructors;
    Internal::TypeMap m_methods;
};


#endif // DIMODULE_H
