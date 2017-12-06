#include <iostream>
#include "model.h"
#include "cservicecontainer.h"

using std::endl;

int main()
{
    CServiceContainer services;

    services.set(std::make_shared<CService>());

    CObject object(services.get<CService>());

    object.process();

    std::cout << "Terminated" << std::endl;
    return 0;
}
