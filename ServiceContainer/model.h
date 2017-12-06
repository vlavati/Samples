#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <iostream>

class CService
{
public:
    CService() {}
    void run() { std::cout << "Service run" << std::endl; }
};

class CObject
{
public:
    CObject(std::shared_ptr<CService> service) : m_service(service) {}
    void process() { m_service->run(); }
private:
    std::shared_ptr<CService> m_service;
};

#endif // MODEL_H
