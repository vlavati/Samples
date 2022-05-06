#include "cviewmodel.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <chrono>
#include <future>
#include <thread>
#define __PRETTY_FUNCTION__ __FUNCSIG__

namespace {

void printThreadId(const QString& str, QObject* obj = NULL)
{
    qDebug() << "Thread:" << QThread::currentThreadId() << str << obj;
}

}

CViewModel::CViewModel(QObject* parent)
    : QObject(parent)
{
    printThreadId("Constructing");
    QObject::connect(
        this, &CViewModel::started, this, &CViewModel::onStartedHere);
    QObject::connect(
        this, &CViewModel::stopped, this, &CViewModel::onStoppedHere);
}

CViewModel::~CViewModel()
{
    printThreadId("Destroying", this);
}

namespace {

template <typename T>
class FutureWrapper : public QFutureWatcher<T> {
public:
    FutureWrapper() { printThreadId(__PRETTY_FUNCTION__, this); }
    ~FutureWrapper() { printThreadId(__PRETTY_FUNCTION__, this); }
};

template <typename T, typename Future>
QFuture<T> watchWith(const Future& future, QObject* owner, const QString& name = QString())
{
    auto watcher = new FutureWrapper<T>();
    watcher->setObjectName(name);

    if ((QThread::currentThread() != QCoreApplication::instance()->thread())
        && (owner == 0
            || QThread::currentThread() != owner->thread())) {
        // Move watcher to main thread if context object is not set.
        watcher->moveToThread(QCoreApplication::instance()->thread());
    }

    printThreadId("Future planning", watcher);
    QPointer<QObject> watcherAlive = watcher;

    // Cleanup
    QObject::connect(owner, &QObject::destroyed,
        watcher, [watcherAlive, watcher]() {
            printThreadId("Context destroying", watcher);
            if (!watcherAlive.isNull()) {
                delete watcher;
            }
            printThreadId("Context destroyed");
        });

    // Finishing
    QObject::connect(watcher, &QFutureWatcherBase::canceled,
        owner, [watcher]() {
            printThreadId("Future canceled", watcher);
            delete watcher;
        });
    QObject::connect(watcher, &QFutureWatcherBase::finished,
        owner, [watcher]() {
            printThreadId("Future fisnished", watcher);
            delete watcher;
        });

    watcher->setFuture(QtConcurrent::run([watcher, future] {
        printThreadId("Future starting", watcher);
        return future();
    }));

    return watcher->future();
}

}

void CViewModel::startAsync()
{
    // Starting
    printThreadId("Setup on");
    QPointer<CViewModel> viewmodel = this;

    auto task = [viewmodel]() {
        if (!viewmodel.isNull())
            emit viewmodel->started();

        printThreadId("Task Started - main");
        int cnt = 0;

        auto getSubtask = [](int emCnt) {
            return [emCnt]() {
                printThreadId("Task Started - embedded");
                QThread::sleep(1);
                return emCnt;
            };
        };

        QObject g;
        auto future = watchWith<int>(getSubtask(cnt++), &g, "embedded");

        printThreadId("Task waiting - main");
        future.waitForFinished();
        printThreadId("Task waiting done - main");

        printThreadId("Task Stopped - main");
        if (!viewmodel.isNull())
            emit viewmodel->stopped();

        return 42;
    };
    watchWith<int>(task, this, "main");
}

void CViewModel::onStartedHere()
{
    printThreadId("Task Start Notified");
}

void CViewModel::onStoppedHere()
{
    printThreadId("Task Stop Notified");
}
