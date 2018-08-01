#include "LogObserver.h"
#include "CommandBlock.h"
#include "MetricsCollection.h"
#include "TimedBlock.h"

#include <fstream>
#include <sstream>


using namespace std::placeholders;

LogObserver::LogObserver(int i_threadNum)
  : d_pool(i_threadNum, "file")
{
  auto fn = std::bind(&LogObserver::print, this, _1, _2);
  d_pool.setFunc(fn);
}

void LogObserver::update(sPtrBlock i_block)
{
  d_pool.addTask(i_block);
}

void LogObserver::print(sPtrBlock&& i_timedBlock, const std::string& i_workerName) const
{
  std::ofstream ofile(getFileName(i_timedBlock->d_timeStamp, i_timedBlock->d_blockSeq));
  ofile << *i_timedBlock; 
  auto &commands = i_timedBlock->d_commands;
  ofile.close();
  
  MetricsCollection::getInstance().update(i_workerName, commands.size());
}

std::string LogObserver::getFileName(const std::time_t &time, int i_blockSeq) const
{
  std::ostringstream oss;
  oss << "bulk" << time << '_' << i_blockSeq <<".log";
  return oss.str();
}



