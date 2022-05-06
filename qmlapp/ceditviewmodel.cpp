#include "ceditviewmodel.h"
#include <QDebug>

CEditViewModel::CEditViewModel()
{
    qDebug() << __PRETTY_FUNCTION__;
}

CEditViewModel::~CEditViewModel()
{
    qDebug() << __PRETTY_FUNCTION__;
}

QString CEditViewModel::str() const
{
    return m_str;
}

void CEditViewModel::setStr(QString str)
{
    if (m_str == str)
        return;

    m_str = str;
    emit strChanged(str);
}
