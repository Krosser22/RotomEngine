/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskManager.h"

struct TaskManagerData {
  int threardsCount;
  const int threardsNotUsed = 3;

  //Task in progress or in the task list
  int taskPending;
  std::mutex lock_taskPending;

  std::vector<std::thread> threads;
  std::mutex lock_threads;

  std::vector<std::shared_ptr<ROTOM::Task>> taskList;
  std::mutex lock_taskList;

  bool isOff;

  //std::condition_variable cv;

} taskManagerData;

void addNextTasksOf(std::shared_ptr<ROTOM::Task> task) {
  taskManagerData.lock_taskPending.lock();
  taskManagerData.lock_taskList.lock();

  --taskManagerData.taskPending;
  for (unsigned int i = 0; i < task->nextTaskList_.size(); ++i) {
    taskManagerData.taskList.push_back(task->nextTaskList_.at(i));
    ++taskManagerData.taskPending;
  }
  task = NULL;

  taskManagerData.lock_taskPending.unlock();
  taskManagerData.lock_taskList.unlock();

  //taskManagerData.cv.notify_all();
}

std::shared_ptr<ROTOM::Task> getNextTask() {
  std::shared_ptr<ROTOM::Task> task;
  taskManagerData.lock_taskList.lock();
  if (taskManagerData.taskList.size() > 0) {
    task = taskManagerData.taskList.at(taskManagerData.taskList.size() - 1);
    taskManagerData.taskList.pop_back();
  }
  taskManagerData.lock_taskList.unlock();
  return task;
}

void threadLoop(int ID) {
  std::shared_ptr<ROTOM::Task> actualTask = NULL;
  //std::unique_lock<std::mutex> lock(taskManagerData.lock_threads);
  //taskManagerData.cv.wait(lock);

  while (!taskManagerData.isOff) {
    actualTask = getNextTask();
    if (actualTask) {
      actualTask->run();
      addNextTasksOf(actualTask);
    } else {
      //taskManagerData.cv.wait(lock);
    }
  }
}

void ROTOM::TASKMANAGER::init() {
  taskManagerData.isOff = false;
  taskManagerData.taskPending = 0;
  taskManagerData.threardsCount = std::thread::hardware_concurrency();
  for (int i = 0; i < taskManagerData.threardsCount - taskManagerData.threardsNotUsed; ++i) {
    taskManagerData.threads.push_back(std::thread(&threadLoop, i));
  }
}

void ROTOM::TASKMANAGER::destroy() {
  taskManagerData.isOff = true;
  taskManagerData.lock_taskList.lock();
  taskManagerData.taskList.clear();
  taskManagerData.lock_taskList.unlock();

  bool threadsWorking = true;
  while (threadsWorking) {
    taskManagerData.lock_taskPending.lock();
    if (taskManagerData.taskPending <= 0) {
      threadsWorking = false;
    }
    taskManagerData.lock_taskPending.unlock();
  }

  //taskManagerData.cv.notify_all();
  for (unsigned int i = 0; i < taskManagerData.threads.size(); ++i) {
    taskManagerData.threads.at(i).join();
  }
}

void ROTOM::TASKMANAGER::addTask(std::shared_ptr<Task> task) {
  taskManagerData.lock_taskList.lock();
  taskManagerData.taskList.push_back(task);
  taskManagerData.lock_taskList.unlock();

  taskManagerData.lock_taskPending.lock();
  ++taskManagerData.taskPending;
  taskManagerData.lock_taskPending.unlock();
  //taskManagerData.cv.notify_all();
}