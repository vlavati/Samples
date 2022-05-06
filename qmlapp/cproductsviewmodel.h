#ifndef CPRODUCTSVIEWMODEL_H
#define CPRODUCTSVIEWMODEL_H

#include <QObject>

class CProductsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString str READ str WRITE setStr NOTIFY strChanged)

public:
    CProductsViewModel();
    ~CProductsViewModel();
    QString str() const;
public slots:
    void setStr(QString str);
signals:
    void strChanged(QString str);
private:
    QString m_str = "xxx";

};

#endif // CPRODUCTSVIEWMODEL_H
