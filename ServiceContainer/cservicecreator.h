#ifndef CSERVICECREATOR_H
#define CSERVICECREATOR_H

#include <functional>
#include "cservicecontainer.h"

class CServiceCreator
{
public:

    template <typename T>
    struct Function
    {
        typedef std::function<std::shared_ptr<T>(CServiceContainer&)> type;
    };

    template <typename T, typename... Dependencies>
    void addDependencies()
    {
        auto key = Internal::typeId<T>();
        auto wrapper = std::make_shared<FunctionContainer<T> >(&CServiceCreator::creator<T, Dependencies ...>);

        m_contstructors[key] = wrapper;
    }

    template <typename T>
    std::shared_ptr<T> make(CServiceContainer &services) const
    {
        auto key = Internal::typeId<T>();
        auto it = m_contstructors.find(key);

        if (it == m_contstructors.end())
        {
            std::cerr << "There is no constuctor for " << typeid(T).name();
            return std::shared_ptr<T>();
        }

        auto wrapper = it->second.get();
        auto container = static_cast<FunctionContainer<T>*>(wrapper);

        return container->function(services);
    }

private:
    template <typename T, typename... Dependencies>
    static std::shared_ptr<T> creator(CServiceContainer &services)
    {
        return std::make_shared<T>(services.get<Dependencies>() ...);
    }

    template <typename T>
    struct FunctionContainer : Internal::Delegate
    {
        typename Function<T>::type function;
        FunctionContainer(typename Function<T>::type _function) : function(_function) {}
    };

    Internal::TypeMap m_contstructors;
};


#endif // CSERVICECREATOR_H
