#include "cviewmodelfactory.h"

CViewModelFactory::CViewModelFactory()
{}

QObject *CViewModelFactory::get(const QString &key, QObject *parent)
{
    auto it = m_creators.find(key);
    if (it == m_creators.end())
        throw std::runtime_error("Unknown viewmodel key");

    QObject *obj = (*it)();
    obj->setParent(parent);
    return obj;
}

void CViewModelFactory::add(const QString &key, Creator creator)
{
    m_creators[key] = creator;
}
