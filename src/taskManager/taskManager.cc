/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskManager.h"

static struct TaskManagerData{
  int threardsCount;
  static const int threardsNotUsed = 3;

  //Task in progress or in the task list
  int taskPending;
  std::mutex lock_taskPending;

  std::vector<std::thread> threads;

  std::vector<std::shared_ptr<ROTOM::Task>> taskList;
  std::mutex lock_taskList;

  bool isOff;

  std::condition_variable cv;

} taskManagerData;

static void addNextTasksOf(std::shared_ptr<ROTOM::Task> task) {
  taskManagerData.lock_taskPending.lock();
  --taskManagerData.taskPending;
  taskManagerData.lock_taskPending.unlock();

  taskManagerData.lock_taskList.lock();
  for (unsigned int i = 0; i < task->nextTaskList_.size(); ++i) {
    taskManagerData.taskList.push_back(task->nextTaskList_.at(i));

    taskManagerData.lock_taskPending.lock();
    ++taskManagerData.taskPending;
    taskManagerData.lock_taskPending.unlock();
  }
  task = NULL;
  taskManagerData.lock_taskList.unlock();
  taskManagerData.cv.notify_all();
}

static std::shared_ptr<ROTOM::Task> getNextTask() {
  std::shared_ptr<ROTOM::Task> task;
  taskManagerData.lock_taskList.lock();
  if (taskManagerData.taskList.size() > 0) {
    /*if (taskManagerData.taskList.size() > 1) {
      printf("%d\n", taskManagerData.taskList.size());
    }*/
    task = taskManagerData.taskList.at(taskManagerData.taskList.size() - 1);
    taskManagerData.taskList.pop_back();
  }
  taskManagerData.lock_taskList.unlock();
  return task;
}

static void threadLoop(int ID) {
  std::shared_ptr<ROTOM::Task> actualTask = NULL;
  //std::unique_lock<std::mutex> lck(taskManagerData.lock_taskList);
  //taskManagerData.cv.wait(lck);

  while (!taskManagerData.isOff) {
    actualTask = getNextTask();
    if (actualTask) {
      actualTask->run();
      addNextTasksOf(actualTask);
    } /*else {
      taskManagerData.cv.wait(lck);
    }*/
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
  bool threadsWorking = true;
  while (threadsWorking) {
    taskManagerData.lock_taskPending.lock();
    if (taskManagerData.taskPending <= 0) {
      taskManagerData.lock_taskList.lock();
      if (taskManagerData.taskList.size() <= 0) {
        threadsWorking = false;
      }
      taskManagerData.lock_taskList.unlock();
    }
    taskManagerData.lock_taskPending.unlock();
  }

  taskManagerData.isOff = true;

  for (unsigned int i = 0; i < taskManagerData.threads.size(); ++i) {
    if (taskManagerData.threads.at(i).joinable()) {
      taskManagerData.threads.at(i).join();
    }
  }
  while (taskManagerData.threads.size() > 0) {
    taskManagerData.threads.pop_back();
  }
  taskManagerData.threads.clear();
}

void ROTOM::TASKMANAGER::addTask(std::shared_ptr<Task> task) {
  taskManagerData.lock_taskList.lock();
  taskManagerData.taskList.push_back(task);
  taskManagerData.lock_taskList.unlock();

  taskManagerData.lock_taskPending.lock();
  ++taskManagerData.taskPending;
  taskManagerData.lock_taskPending.unlock();
  taskManagerData.cv.notify_all();
}

/*int ROTOM::TASKMANAGER::taskPendingCount() {
  taskManagerData.lock_taskPending.lock();
  int pendingCount = taskManagerData.taskPending;
  taskManagerData.lock_taskPending.unlock();
  return pendingCount;
}*/

/*void ROTOM::TASKMANAGER::waitUntilFinish() {
  bool hasTaskManagerFinishTheFrame = false;
  while (!hasTaskManagerFinishTheFrame) {
    taskManagerData.lock_taskPending.lock();
    if (taskManagerData.taskPending <= 0) {
      hasTaskManagerFinishTheFrame = true;
    }
    taskManagerData.lock_taskPending.unlock();
  }
}*/