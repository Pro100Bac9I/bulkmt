#pragma once

#include "Observer.h"
#include "ThreadPool.h"

#include <mutex>
#include <functional>

using FnType = std::function<void(sPtrBlock&&, const std::string&)>;

class CoutObserver : public Observer
{
public:
  CoutObserver(int i_threadNum);

  void update(sPtrBlock i_block) override;

private:
  void print(sPtrBlock&& i_block, const std::string &i_workerName);

private: 
  std::mutex d_mutex;
  ThreadPool<FnType, sPtrBlock> d_pool;

};

