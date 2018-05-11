#include <QCoreApplication>
#include "log.h"
#include "communicatingthread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    logging("Enter.");

    std::shared_ptr<CommunicatingThread> thread1(new CommunicatingThread(1));
    std::shared_ptr<CommunicatingThread> thread2(new CommunicatingThread(2));
    thread1->start();
    thread2->start();
    thread1->join();
    thread2->join();
    logging("Leave.");
    return a.exec();
}
