/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager.h"
#include "security.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

struct TaskManagerData {
  int threardsCount_;
  static const int threardsNotUsed_ = 2;

  //Task in progress or in the task list
  int taskPending_;
  std::shared_ptr<std::mutex> lock_taskPending_;

  std::vector<std::thread> threads_;

  std::vector<std::shared_ptr<ROTOM::Task>> taskList_;

  std::shared_ptr<std::mutex> lock_taskList_;

  bool isOff_;

  //std::condition_variable cv_;

  //std::shared_ptr<std::lock_guard<std::mutex>> lk_;

};

static TaskManagerData taskManagerData;

static void addNextTasksOf(std::shared_ptr<ROTOM::Task> task) {
  taskManagerData.lock_taskPending_->lock();
  --taskManagerData.taskPending_;
  taskManagerData.lock_taskPending_->unlock();

  taskManagerData.lock_taskList_->lock();
  for (unsigned int i = 0; i < task->nextTaskList_.size(); ++i) {
    taskManagerData.taskList_.push_back(task->nextTaskList_.at(i));

    taskManagerData.lock_taskPending_->lock();
    ++taskManagerData.taskPending_;
    taskManagerData.lock_taskPending_->unlock();
  }
  task = NULL;
  taskManagerData.lock_taskList_->unlock();
  //cv_.notify_all();
}

static std::shared_ptr<ROTOM::Task> getNextTask() {
  std::shared_ptr<ROTOM::Task> task;
  taskManagerData.lock_taskList_->lock();
  if (taskManagerData.taskList_.size() > 0) {
    task = taskManagerData.taskList_.at(taskManagerData.taskList_.size() - 1);
    taskManagerData.taskList_.pop_back();
  }
  taskManagerData.lock_taskList_->unlock();
  return task;
}

void threadLoop(int ID) {
  std::shared_ptr<ROTOM::Task> actualTask = NULL;
  //std::unique_lock<std::mutex> lck(taskManager->lock_taskList_);
  //taskManager->cv_.wait(lck);

  while (!taskManagerData.isOff_) {
    actualTask = getNextTask();
    if (actualTask) {
      actualTask->run();
      addNextTasksOf(actualTask);
    } /*else {
      taskManager->cv_.wait(lck);
      }*/
  }
}

void ROTOM::TaskManager::init() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_TaskManager);
  
  taskManagerData.isOff_ = false;

  taskManagerData.taskPending_ = 0;

  taskManagerData.lock_taskPending_ = std::make_shared<std::mutex>();
  taskManagerData.lock_taskList_ = std::make_shared<std::mutex>();

  //std::shared_ptr<std::lock_guard<std::mutex>> lk(std::lock_guard<std::mutex>(lock_taskList_));
  //lk_ = lk.get();

  taskManagerData.threardsCount_ = std::thread::hardware_concurrency();
  //printf("Task Manager Threads: [%d]\n", threardsCount_ - threardsNotUsed_);
  //self_ = std::shared_ptr<TaskManagerData>(taskManagerData);
  for (int i = 0; i < taskManagerData.threardsCount_ - taskManagerData.threardsNotUsed_; ++i) {
    taskManagerData.threads_.push_back(std::thread(&threadLoop, i));
  }
}

void ROTOM::TaskManager::destroy() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_TaskManager);

  bool threadsWorking = true;
  while (threadsWorking) {
    taskManagerData.lock_taskPending_->lock();
    if (taskManagerData.taskPending_ <= 0) {
      taskManagerData.lock_taskList_->lock();
      if (taskManagerData.taskList_.size() <= 0) {
        threadsWorking = false;
      }
      taskManagerData.lock_taskList_->unlock();
    }
    taskManagerData.lock_taskPending_->unlock();
  }

  taskManagerData.isOff_ = true;

  for (unsigned int i = 0; i < taskManagerData.threads_.size(); ++i) {
    if (taskManagerData.threads_.at(i).joinable()) {
      taskManagerData.threads_.at(i).join();
    }
  }
  while (taskManagerData.threads_.size() > 0) {
    taskManagerData.threads_.pop_back();
  }
  taskManagerData.threads_.clear();
}

void ROTOM::TaskManager::addTask(std::shared_ptr<Task> task) {
  taskManagerData.lock_taskList_->lock();
  taskManagerData.taskList_.push_back(task);
  taskManagerData.lock_taskList_->unlock();

  taskManagerData.lock_taskPending_->lock();
  ++taskManagerData.taskPending_;
  taskManagerData.lock_taskPending_->unlock();
  //cv_.notify_all();
}

void ROTOM::TaskManager::waitUntilFinish() {
  bool hasTaskManagerFinishTheFrame = false;
  while (!hasTaskManagerFinishTheFrame) {
    taskManagerData.lock_taskPending_->lock();
    if (taskManagerData.taskPending_ <= 0) {
      hasTaskManagerFinishTheFrame = true;
    }
    taskManagerData.lock_taskPending_->unlock();
  }
}
