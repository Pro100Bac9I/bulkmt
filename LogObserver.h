#pragma once

#include "Observer.h"
#include "ThreadPool.h"

#include <ctime>
#include <string>
#include <functional>

using FnType = std::function<void(sPtrBlock&&, const std::string&)>;

class LogObserver : public Observer
{
public:
  LogObserver(int i_threadNum);
  void update(sPtrBlock i_block) override;
private:
  std::string getFileName(const std::time_t &i_time, int i_blockSeq) const;

  void print(sPtrBlock&& timedBlock, const std::string& i_workerName) const;

private:
  ThreadPool<FnType, sPtrBlock> d_pool;
};
