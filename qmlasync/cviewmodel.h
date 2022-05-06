#ifndef CVIEWMODEL_H
#define CVIEWMODEL_H

#include <QObject>

class CViewModel : public QObject
{
    Q_OBJECT
public:
    explicit CViewModel(QObject *parent = 0);

signals:

public slots:
};

#endif // CVIEWMODEL_H