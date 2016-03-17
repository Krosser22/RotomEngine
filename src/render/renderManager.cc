/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/renderManager.h"
#include "render/displayList.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

static struct RenderManagerData{
  int threardsCount_;
  static const int threardsNotUsed_ = 2;

  //Task in progress or in the task list
  int taskPending_;
  std::shared_ptr<std::mutex> lock_taskPending_;

  std::vector<std::thread> threads_;

  std::vector<std::shared_ptr<ROTOM::Command>> taskList_;
  std::shared_ptr<std::mutex> lock_taskList_;

  bool isOff_;

  ROTOM::DisplayList displayListA;

  ROTOM::DisplayList displayListB;

  //std::condition_variable cv_;

  //std::shared_ptr<std::lock_guard<std::mutex>> lk_;
} renderManagerData;

static void addNextTasksOf(std::shared_ptr<ROTOM::Command> command) {
  renderManagerData.lock_taskPending_->lock();
  --renderManagerData.taskPending_;
  renderManagerData.lock_taskPending_->unlock();

  renderManagerData.lock_taskList_->lock();
  /*for (unsigned int i = 0; i < command->nextCommandList_.size(); ++i) {
    taskManagerData.taskList_.push_back(command->nextCommandList_.at(i));

    taskManagerData.lock_taskPending_->lock();
    ++taskManagerData.taskPending_;
    taskManagerData.lock_taskPending_->unlock();
  }*/
  command = NULL;
  renderManagerData.lock_taskList_->unlock();
  //cv_.notify_all();
}

static std::shared_ptr<ROTOM::Command> getNextCommand() {
  std::shared_ptr<ROTOM::Command> command;
  renderManagerData.lock_taskList_->lock();
  if (renderManagerData.taskList_.size() > 0) {
    command = renderManagerData.taskList_.at(renderManagerData.taskList_.size() - 1);
    renderManagerData.taskList_.pop_back();
  }
  renderManagerData.lock_taskList_->unlock();
  return command;
}

static void threadLoop(int ID) {
  std::shared_ptr<ROTOM::Command> actualTask = NULL;
  //std::unique_lock<std::mutex> lck(taskManager->lock_taskList_);
  //taskManager->cv_.wait(lck);

  while (!renderManagerData.isOff_) {
    actualTask = getNextCommand();
    if (actualTask) {
      actualTask->run();
      addNextTasksOf(actualTask);
    } /*else {
      taskManager->cv_.wait(lck);
      }*/
  }
}

void swapDisplayLists() {}

void ROTOM::RENDERMANAGER::init() {
  renderManagerData.isOff_ = false;
  renderManagerData.taskPending_ = 0;
  renderManagerData.lock_taskPending_ = std::make_shared<std::mutex>();
  renderManagerData.lock_taskList_ = std::make_shared<std::mutex>();

  //std::shared_ptr<std::lock_guard<std::mutex>> lk(std::lock_guard<std::mutex>(lock_taskList_));
  //lk_ = lk.get();

  renderManagerData.threardsCount_ = std::thread::hardware_concurrency();
  //printf("Task Manager Threads: [%d]\n", threardsCount_ - threardsNotUsed_);
  //self_ = std::shared_ptr<TaskManagerData>(taskManagerData);
  for (int i = 0; i < renderManagerData.threardsCount_ - renderManagerData.threardsNotUsed_; ++i) {
    renderManagerData.threads_.push_back(std::thread(&threadLoop, i));
  }
}

void ROTOM::RENDERMANAGER::destroy() {
  bool threadsWorking = true;
  while (threadsWorking) {
    renderManagerData.lock_taskPending_->lock();
    if (renderManagerData.taskPending_ <= 0) {
      renderManagerData.lock_taskList_->lock();
      if (renderManagerData.taskList_.size() <= 0) {
        threadsWorking = false;
      }
      renderManagerData.lock_taskList_->unlock();
    }
    renderManagerData.lock_taskPending_->unlock();
  }

  renderManagerData.isOff_ = true;

  for (unsigned int i = 0; i < renderManagerData.threads_.size(); ++i) {
    if (renderManagerData.threads_.at(i).joinable()) {
      renderManagerData.threads_.at(i).join();
    }
  }
  while (renderManagerData.threads_.size() > 0) {
    renderManagerData.threads_.pop_back();
  }
  renderManagerData.threads_.clear();
}

void ROTOM::RENDERMANAGER::addCommand(std::shared_ptr<Command> task) {
  renderManagerData.lock_taskList_->lock();
  renderManagerData.taskList_.push_back(task);
  renderManagerData.lock_taskList_->unlock();

  renderManagerData.lock_taskPending_->lock();
  ++renderManagerData.taskPending_;
  renderManagerData.lock_taskPending_->unlock();
  //cv_.notify_all();
}

void ROTOM::RENDERMANAGER::draw() {
  bool hasTaskManagerFinishTheFrame = false;
  while (!hasTaskManagerFinishTheFrame) {
    renderManagerData.lock_taskPending_->lock();
    if (renderManagerData.taskPending_ <= 0) {
      hasTaskManagerFinishTheFrame = true;
    }
    renderManagerData.lock_taskPending_->unlock();
  }
}
