#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QObject>

class SearchThread : public QThread
{
    Q_OBJECT

public:
    //SearchThread();
    ~SearchThread();

    //单件模式 获取对象
    static SearchThread* Get()
    {
        static SearchThread vt;
        return &vt;
    }


    void run();

protected:
    QMutex mutex;
    SearchThread();
};

#endif // SEARCHTHREAD_H
