#include "cviewmodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <chrono>
#include <functional>
#include <future>
#include <thread>

#if 0
namespace
{
template <typename A, typename B>
using Func = std::function<B(A)>;

template <typename X, typename Y>
auto mbind(X task, Y continuation)
{
    return [=] (auto a)
    {
        return continuation(task(a));
    };
}

template <typename A, typename B>
class Task
{
    Func<A, B> _func;
public:
    Task(Func<A, B> func) : _func(func) {}
    B result(A a)
    {
        auto f = QtConcurrent::run([=]() { return _func(a);});
        return f.result();
    }
};


template <typename T, typename Function>
const QFuture<T> &onResultReady(const QFuture<T> &future, QObject *guard, Function f)
{
    auto watcher = new QFutureWatcher<T>();
    QObject::connect(watcher, &QFutureWatcherBase::finished, watcher, &QObject::deleteLater);
    QObject::connect(watcher, &QFutureWatcherBase::resultReadyAt, guard, [f, watcher](int index) {
        f(watcher->future().resultAt(index));
    });
    watcher->setFuture(future);
    return future;
}
template<typename T, typename Function>
const QFuture<T> &onFinished(const QFuture<T> &future, QObject *guard, Function f)
{
    auto watcher = new QFutureWatcher<T>();
    QObject::connect(watcher, &QFutureWatcherBase::finished, watcher, &QObject::deleteLater);
    QObject::connect(watcher, &QFutureWatcherBase::finished, guard, [f, watcher]() {
        f(watcher->future());
    });
    watcher->setFuture(future);
    return future;
}
}
#endif
void testExceptions()
{
    QTimer::singleShot(1, qApp,
                       [](){
        qDebug() << "Timer start";
        auto future = QtConcurrent::run([]() {
            qDebug() << "Before exception";
            throw  std::runtime_error("This exception");
            qDebug() << "After exception";
        });
        qDebug() << "Wait future";

        try {
            future.waitForFinished();
        }  catch (const QException&) {
            qDebug() << "Catch QException";
        }  catch (const std::exception&) {
            qDebug() << "Catch std::exception";
        }  catch (...) {
            qDebug() << "Catch everything";
        }
        qDebug() << "Timer stop";

    });
}

QFuture<QString> downloadFile(const QString &filename)
{
    return QtConcurrent::run([filename]() {
        qDebug() << "downloadFile";
        return filename;
    });
}

QFuture<int> countWords(const QString &fileData)
{
    return QtConcurrent::run([fileData]() {
        qDebug() << "countWords";
        return (int)fileData.size();
    });
}


template <typename T1,
          typename T2>
QFuture<T2> mbind(const QFuture<T1> &parentFuture,
                  std::function<QFuture<T2>(const T1 &)> continuation)
{
    if (parentFuture.isFinished())
        return continuation(parentFuture.result());

    QFutureInterface<T2> fi;

    auto watcher = new QFutureWatcher<T1>();
    if (QThread::currentThread() != QCoreApplication::instance()->thread())
    {
        watcher->moveToThread(QCoreApplication::instance()->thread());
    }

    QObject::connect(watcher, &QFutureWatcher<T1>::finished,
                     [watcher, fi, continuation](){
        auto watcher2 = new QFutureWatcher<T2>();
        if (QThread::currentThread() != QCoreApplication::instance()->thread())
        {
            watcher2->moveToThread(QCoreApplication::instance()->thread());
        }
        QObject::connect(watcher2, &QFutureWatcher<T2>::finished,
                         [watcher2, fi, continuation](){
            QFutureInterface<T2> promise(fi);
            promise.reportResult(watcher2->result());
            promise.reportFinished();
        });
        watcher2->setFuture(continuation(watcher->result()));
    });

    watcher->setFuture(parentFuture);

    return fi.future();
}

void testMonad()
{
    QTimer::singleShot(1, qApp,
                       [](){
        qDebug() << "Timer start";

        auto future = mbind<QString, int>(downloadFile("MyFilename"), countWords);
        //auto future = downloadFile("MyFilename");

        qDebug() << "Wait future";

        try {
//            future.waitForFinished();
//            qDebug() << "Result:" << future.result();
        }  catch (const QException&) {
            qDebug() << "Catch QException";
        }  catch (const std::exception&) {
            qDebug() << "Catch std::exception";
        }  catch (...) {
            qDebug() << "Catch everything";
        }
        qDebug() << "Timer stop";
    });
}

void testFuture()
{
    QTimer::singleShot(1, qApp,
                       [](){
        qDebug() << "Timer start";
        QFutureInterface<int> fi;
        QFuture<int> intFuture = fi.future();
        QtConcurrent::run([&fi]() {
            qDebug() << "Before Set";
            fi.reportResult(5);
            fi.reportFinished();
            qDebug() << "After Set";
        });
        qDebug() << "Wait future";

        try {
            intFuture.waitForFinished();
            qDebug() << "Result:" << intFuture.result();
        }  catch (const QException&) {
            qDebug() << "Catch QException";
        }  catch (const std::exception&) {
            qDebug() << "Catch std::exception";
        }  catch (...) {
            qDebug() << "Catch everything";
        }
        qDebug() << "Timer stop";

    });
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<CViewModel>("com.mycompany.qmlasync", 1, 0, "CViewModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#if 0


    Func<float, int> x = [](float a){ return (int)(a + 0.5); };
    Func<int, double> y = [](int b){ return (double)(b * 2.); };

    auto z = mbind(x, y);
    auto out = z(3.6);
    qDebug() << out;


    QtConcurrent::run([=]()
    {
        auto x2 = QtConcurrent::run([=]() { return x(3.6); } );
        auto z2 = QtConcurrent::run([=]() { return y(x2.result()); } );
        qDebug() << z2.result();
    });

    Task<float, int> X(x);
    Task<int, double> Y(y);
    Task
#endif

    testMonad();
    return app.exec();
}
