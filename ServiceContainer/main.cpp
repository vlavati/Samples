#include <iostream>
#include "model.h"
#include "cservicecontainer.h"
#include "cservicecreator.h"
#include "di.h"
#include "dimodule.h"

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

    DIModule module;
    module.addDependencies<CService>(DI::Inject<CService>::factory);
    module.addDependencies<CObject>(DI::Inject<CObject, CService>::factory);
    module.addMethod<CObject>(DI::Inject<CObject, CService>::method<&CObject::prepareIt>);

    DI di;
    di.addDependencies<CService>(DI::Inject<CService>::factory);
    di.addDependencies<CObject>(DI::Inject<CObject, CService>::factory);
    di.addMethod<CObject>(DI::Inject<CObject, CService>::method<&CObject::prepareIt>);

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
