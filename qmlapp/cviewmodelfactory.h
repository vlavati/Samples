#ifndef CVIEWMODELFACTORY_H
#define CVIEWMODELFACTORY_H

#include <QObject>

class CViewModelFactory : public QObject
{
    Q_OBJECT
public:
    explicit CViewModelFactory(QObject *parent = 0);

signals:

public slots:
};

#endif // CVIEWMODELFACTORY_H