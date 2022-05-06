#ifndef CEDITVIEWMODEL_H
#define CEDITVIEWMODEL_H

#include <QObject>

class CEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString str READ str WRITE setStr NOTIFY strChanged)

public:
    CEditViewModel();
    ~CEditViewModel();
    QString str() const;

signals:
    void strChanged(QString str);

public slots:
    void setStr(QString str);

private:
    QString m_str = "SomeString";

};

#endif // CEDITVIEWMODEL_H
