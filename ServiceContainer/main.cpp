#include <iostream>
#include "model.h"
#include "cservicecontainer.h"
#include "cservicecreator.h"
#include "di.h"

//TODO: support modules
//TODO: support objects wiring - run static functions that make connections between objects
//TODO: support late initialization - run initialization function after object was created

void testContainerCreator()
{
    CServiceContainer services;
    services.set(std::make_shared<CService>());

    CServiceCreator creator;
    creator.addDependencies<CObject, CService>();

    auto object = creator.make<CObject>(services);
    object->process();
}

void testDI()
{
    DI di;
    di.addDependencies<CObject, CService>();

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
