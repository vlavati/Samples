#include "cproductsviewmodel.h"
#include <QDebug>

CProductsViewModel::CProductsViewModel()
{
    qDebug() << __PRETTY_FUNCTION__;
}

CProductsViewModel::~CProductsViewModel()
{
    qDebug() << __PRETTY_FUNCTION__;
}

QString CProductsViewModel::str() const
{
    return m_str;
}

void CProductsViewModel::setStr(QString str)
{
    if (m_str == str)
        return;

    m_str = str;
    emit strChanged(str);
}
