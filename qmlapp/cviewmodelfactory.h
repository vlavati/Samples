#ifndef CVIEWMODELFACTORY_H
#define CVIEWMODELFACTORY_H

#include <QObject>
#include <QHash>
#include <functional>

using Creator =  std::function<QObject*()>;

class CViewModelFactory : public QObject
{
    Q_OBJECT
public:
    CViewModelFactory();

    Q_INVOKABLE QObject *get(const QString &key, QObject *parent);
    void add(const QString &key, Creator creator);

private:
    QHash<QString, Creator> m_creators;

};

#endif // CVIEWMODELFACTORY_H
