#ifndef CVIEWMODEL_H
#define CVIEWMODEL_H

#include <QObject>

class CViewModel : public QObject
{
    Q_OBJECT
public:
    explicit CViewModel(QObject *parent = 0);
    ~CViewModel();

    Q_INVOKABLE void startAsync();

private slots:
    void onStartedHere();
    void onStoppedHere();

signals:
    void started();
    void stopped();

public slots:
};

#endif // CVIEWMODEL_H
