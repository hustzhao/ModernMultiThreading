#include "communicatingthread.h"
#include "log.h"

unsigned int number = 0;//shared variable

void* CommunicatingThread::run() {
  logging("thread:%d is running",my_id_);

  for(unsigned int i = 0;i< count_number;i++) {
    number = number + 1;
  }

  logging("my_id_ = %d, number = %d.\n",my_id_,number);
  return 0;
}
