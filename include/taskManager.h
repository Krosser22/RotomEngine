/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>

namespace ROTOM {
  enum TaskType {
    TaskType_none = 0,
    TaskType_CalculateMatrix,
  };

  class Task {
  public:
    Task();
    virtual ~Task();
    
    TaskType taskType_ = TaskType_none;

    virtual void run() = 0;

    //void setNextTasks(int countTasks, std::vector<std::shared_ptr<Task>> nextTasksList);
    //std::vector<std::shared_ptr<Task>> getNextTasksList();

    std::vector<std::shared_ptr<Task>> nextTaskList_;
  };

  class TaskManager {
  public:
    TaskManager();
    ~TaskManager();

    void addTask(std::shared_ptr<Task> task);

    void addNextTasksOf(std::shared_ptr<Task> task);

    //void removeTask(std::shared_ptr<Task> task);

    std::shared_ptr<Task> getNextTask();

    void waitUntilFinish();

  private:
    int threardsCount_;
    static const int threardsNotUsed_ = 2;

    //Task in progress or in the task list
    int taskPending_;
    std::shared_ptr<std::mutex> lock_taskPending_;

    std::vector<std::thread> threads_;

    std::vector<std::shared_ptr<Task>> taskList_;

    std::shared_ptr<std::mutex> lock_taskList_;

    bool isOff_;

    std::shared_ptr<TaskManager> self_;

    //std::condition_variable cv_;

    //std::shared_ptr<std::lock_guard<std::mutex>> lk_;

    static void threadLoop(std::shared_ptr<TaskManager> taskManager, int ID, char c);
  };
}

#endif //__TASK_MANAGER_H__