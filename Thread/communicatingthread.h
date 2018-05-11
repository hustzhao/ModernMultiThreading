#ifndef COMMUNICATINGTHREAD_H
#define COMMUNICATINGTHREAD_H
#include "thread.h"


const unsigned int count_number = 10000000;

class CommunicatingThread:public Thread {
public:
  CommunicatingThread(int id):my_id_(id){}
  virtual void* run();
private:
  int my_id_;
};

#endif // COMMUNICATINGTHREAD_H
