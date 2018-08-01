#include "CoutObserver.h"
#include "CommandBlock.h"
#include "MetricsCollection.h"
#include "TimedBlock.h"

#include <iostream>
#include <string>
#include <mutex>

using namespace std::placeholders;

CoutObserver::CoutObserver(int i_threadNum)
  : d_pool(i_threadNum, "log")
{
  auto fn = std::bind(&CoutObserver::print, this, _1, _2);
  d_pool.setFunc(fn);
}

void CoutObserver::update(sPtrBlock i_block)
{
  d_pool.addTask(i_block);
}

void CoutObserver::print(sPtrBlock&& i_timedBlock, const std::string &i_workerName)
{
  auto &commands = i_timedBlock->d_commands;
  {
    std::unique_lock<std::mutex> ulock(d_mutex); 
    std::cout << *i_timedBlock;
  }

  MetricsCollection::getInstance().update(i_workerName, commands.size());
}
