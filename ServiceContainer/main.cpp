#include <iostream>
#include "model.h"
#include "cservicecontainer.h"
#include "cservicecreator.h"

using std::endl;

int main()
{
    CServiceContainer services;
    services.set(std::make_shared<CService>());

    CServiceCreator creator;
    creator.addDependencies<CObject, CService>();

    auto object = creator.get<CObject>(services);
    object->process();

    std::cout << "Terminated" << std::endl;
    return 0;
}
