#pragma once

#include <vector>
#include <string>

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>

template<typename Func, typename Type>
class ThreadPool
{
public:
  ThreadPool(int i_threadNum, const std::string& i_workerName)
    : d_active(true)
  {
    for (int i = 0; i < i_threadNum; ++i)
    {
      auto name = i_workerName + std::to_string(i + 1);
      d_workers.emplace_back(std::thread(&ThreadPool::work, this, name));
    }
  }

  ~ThreadPool()
  {
    d_active = false;
    d_cv.notify_all();
    for (auto& thread : d_workers)
      thread.join();
  }

  void setFunc(Func i_func)
  {
    d_func = i_func;
  }

  void work(const std::string &i_workerName)
  {
    while (d_active || !d_queue.empty())
    {
      std::unique_lock<std::mutex> ulock(d_mutex);
      d_cv.wait(ulock, [&]()
      {
        return !d_queue.empty() || !d_active;
      });

      if (d_queue.empty() && !d_active)
        return;

      Type arg = d_queue.front();
      d_queue.pop();

      ulock.unlock();
      
      d_func(std::move(arg), i_workerName);
    }
  }

  void addTask(Type arg)
  {
    std::unique_lock<std::mutex> ulock(d_mutex);
    d_queue.push(arg);
    d_cv.notify_one();
  }

private:
  Func d_func;
  std::mutex d_mutex;
  std::condition_variable d_cv;
  std::queue<Type> d_queue;
  std::vector<std::thread> d_workers;
  std::atomic<bool> d_active;
};
