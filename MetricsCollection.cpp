#include "MetricsCollection.h"
#include "Metrics.h"

#include <iostream>

MetricsCollection& MetricsCollection::getInstance()
{
  static MetricsCollection instance;
  return instance;
}

Metrics& MetricsCollection::getById(const std::string &i_threadName)
{
  auto it = d_metrics.find(i_threadName);

  if (it != d_metrics.end())
    return it->second;

  addThread(i_threadName);

  return d_metrics[i_threadName];
}

void MetricsCollection::addThread(const std::string &i_threadName)
{
  d_metrics.emplace(i_threadName, Metrics());
}

void MetricsCollection::print() const
{
  for (auto& pair : d_metrics)
  {
    std::cout << pair.first << " thread: " << pair.second << std::endl;
  }
}

void MetricsCollection::update(const std::string& i_workerName, int i_size)
{
  auto& inst = MetricsCollection::getInstance().getById(i_workerName);
  inst.incBlocks();
  inst.incCommands(i_size);
}