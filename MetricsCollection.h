#pragma once

#include <map>
#include <string>

struct Metrics;

class MetricsCollection
{
public:
  static MetricsCollection& getInstance();

  Metrics& getById(const std::string &i_threadName);

  void addThread(const std::string &i_threadName);

  void print() const;
  void update(const std::string& i_workerName, int i_size);
protected:
  MetricsCollection() = default;

private:
  MetricsCollection(const MetricsCollection &i_other) = delete;
  MetricsCollection& operator=(const MetricsCollection &i_other) = delete;

private:
  std::map<std::string, Metrics> d_metrics;
};

