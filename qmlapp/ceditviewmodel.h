#ifndef CEDITVIEWMODEL_H
#define CEDITVIEWMODEL_H

#include <QObject>

class CEditViewModel : public QObject
{
    Q_OBJECT
public:
    explicit CEditViewModel(QObject *parent = 0);

signals:

public slots:
};

#endif // CEDITVIEWMODEL_H