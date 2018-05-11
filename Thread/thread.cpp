#include "thread.h"
#include "log.h"
#include <assert.h>

Runnable::~Runnable(){}

Thread::Thread(std::shared_ptr<Runnable> runnable,bool detached):runnable_(runnable),detached_(detached) {
  if(!runnable) {
      logging("error, runnable is NULL");
      exit(1);
  }
}

Thread::Thread(bool detached):runnable_(NULL),detached_(detached){}

Thread::~Thread() {}

void* Thread::start_thread_runnable(void *arg) {
  Thread* runnable_thread = static_cast<Thread*> (arg);
  assert(runnable_thread);
  runnable_thread->result_ = runnable_thread->runnable_->run();
  runnable_thread->setCompleted();
  return runnable_thread->result_;
}

void* Thread::start_thread(void* arg){
  Thread* thread = static_cast<Thread*> (arg);
  assert(thread);
  thread->result_ = thread->run();
  thread->setCompleted();
  return thread->result_;
}

void Thread::start() {
  int status = pthread_attr_init(&thread_attribute_);
  check_status("pthread_attr_init",status);

  status = pthread_attr_setscope(&thread_attribute_,PTHREAD_SCOPE_SYSTEM);
  check_status("pthread_attr_setscope",status);

  if(!detached_){
    if(!runnable_.get()) {
      int status = pthread_create(&thread_id_,&thread_attribute_,Thread::start_thread,(void*)this);
      check_status("pthread_create",status);
    } else {
      int status = pthread_create(&thread_id_,&thread_attribute_,Thread::start_thread_runnable,(void*)this);
      check_status("pthread_create",status);
    }
  } else {
    //set the detachstate attribute to the detached_
    status = pthread_attr_setdetachstate(&thread_attribute_,PTHREAD_CREATE_DETACHED);
    check_status("pthread_attr_setdetachstate",status);

    if(!runnable_.get()) {
      int status = pthread_create(&thread_id_,&thread_attribute_,Thread::start_thread,(void*)this);
      check_status("pthread_create",status);
    } else {
      int status = pthread_create(&thread_id_,&thread_attribute_,Thread::start_thread_runnable,(void*)this);
      check_status("pthread_create",status);
    }
  }

  status = pthread_attr_destroy(&thread_attribute_);
  check_status("pthread_attr_destroy",status);
}

void* Thread::join() {
  int status = pthread_join(thread_id_,NULL);
  check_status("pthread_join",status);
  return result_;
}

void Thread::setCompleted(){}

void Thread::print_error(const char* msg, int status, const char* function_name,int line_number) {
  logging("[%s:%d] %s faild,",function_name,line_number,msg,strerror(status));
  return;
}

void Thread::check_status(const char* msg, int status) {
  if(0 != status) {
    print_error(msg,status,__FUNCTION__,__LINE__);
    exit(status);
  }
}
