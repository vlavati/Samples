#include <iostream>
#include "model.h"
#include "cservicecontainer.h"
#include "cservicecreator.h"
#include "di.h"

//TODO: support modules
//TODO: support objects wiring - run static functions that make connections between objects

void testContainerCreator()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    CServiceContainer services;
    services.set(std::make_shared<CService>());

    CServiceCreator creator;
    creator.addDependencies<CObject, CService>();

    auto object = creator.make<CObject>(services);
    object->process();
}

void testDI()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    DI di;
    di.addDependencies<CService>();
    di.addDependencies<CObject, CService>();
    di.addMethod<CObject, CService>(&CObject::prepareIt);

    auto object = di.get<CObject>();

    object->process();
}

int main()
{
    testContainerCreator();
    testDI();

    std::cout << "Terminated" << std::endl;
    return 0;
}
