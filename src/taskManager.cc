/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager.h"
#include "security.h"

ROTOM::Task::Task() {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Task);
}

ROTOM::Task::~Task() {
  ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Task);
}

ROTOM::TaskManager::TaskManager() {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_TaskManager);
  
  isOff_ = false;

  taskPending_ = 0;

  lock_taskPending_ = std::make_shared<std::mutex>();
  lock_taskList_ = std::make_shared<std::mutex>();

  //std::shared_ptr<std::lock_guard<std::mutex>> lk(std::lock_guard<std::mutex>(lock_taskList_));
  //lk_ = lk.get();

  threardsCount_ = std::thread::hardware_concurrency();
  //printf("Task Manager Threads: [%d]\n", threardsCount_ - threardsNotUsed_);
  self_ = std::shared_ptr<TaskManager>(this);
  for (int i = 0; i < threardsCount_ - threardsNotUsed_; ++i) {
    char c = i + 1;
    threads_.push_back(std::thread(&ROTOM::TaskManager::threadLoop, self_, i + 1, c));
  }
}

ROTOM::TaskManager::~TaskManager() {
  if (ROTOM::SECURITY::checkSecurityCount(ROTOM::SECURITY::MyClass::MyClass_TaskManager) > 0) {
    ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass::MyClass_TaskManager);

    bool threadsWorking = true;
    while (threadsWorking) {
      lock_taskPending_->lock();
      if (taskPending_ <= 0) {
        lock_taskList_->lock();
        if (taskList_.size() <= 0) {
          threadsWorking = false;
        }
        lock_taskList_->unlock();
      }
      lock_taskPending_->unlock();
    }

    isOff_ = true;

    for (unsigned int i = 0; i < threads_.size(); ++i) {
      if (threads_.at(i).joinable()) {
        threads_.at(i).join();
      }
    }

    //self_.reset();
  } /*else {
    printf("ERROR: ~TaskManager() called more than once\n");
  }*/
}

void ROTOM::TaskManager::addTask(std::shared_ptr<Task> task) {
  lock_taskList_->lock();
  taskList_.push_back(task);
  lock_taskList_->unlock();

  lock_taskPending_->lock();
  ++taskPending_;
  lock_taskPending_->unlock();
  //cv_.notify_all();
}

void ROTOM::TaskManager::addNextTasksOf(std::shared_ptr<Task> task) {
  lock_taskPending_->lock();
  --taskPending_;
  lock_taskPending_->unlock();

  lock_taskList_->lock();
  for (unsigned int i = 0; i < task->nextTaskList_.size(); ++i) {
    taskList_.push_back(task->nextTaskList_.at(i));

    lock_taskPending_->lock();
    ++taskPending_;
    lock_taskPending_->unlock();
  }
  task = NULL;
  lock_taskList_->unlock();
  //cv_.notify_all();
}

std::shared_ptr<ROTOM::Task> ROTOM::TaskManager::getNextTask() {
  std::shared_ptr<ROTOM::Task> task;
  lock_taskList_->lock();
  if (taskList_.size() > 0) {
    task = taskList_.at(taskList_.size() - 1);
    taskList_.pop_back();
  }
  lock_taskList_->unlock();
  return task;
}

void ROTOM::TaskManager::waitUntilFinish() {
  bool hasTaskManagerFinishTheFrame = false;
  while (!hasTaskManagerFinishTheFrame) {
    lock_taskPending_->lock();
    if (taskPending_ <= 0) {
      hasTaskManagerFinishTheFrame = true;
    }
    lock_taskPending_->unlock();
  }
}

void ROTOM::TaskManager::threadLoop(std::shared_ptr<TaskManager> taskManager, int ID, char c) {
  std::shared_ptr<Task> actualTask = NULL;
  //std::unique_lock<std::mutex> lck(taskManager->lock_taskList_);
  //taskManager->cv_.wait(lck);

  while (!taskManager->isOff_ || true) {
    actualTask = taskManager->getNextTask();
    if (actualTask) {
      actualTask->run();
      taskManager->addNextTasksOf(actualTask);
    } /*else {
      taskManager->cv_.wait(lck);
    }*/
  }
}
