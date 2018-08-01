#pragma once

#include <iostream>
#include <atomic>

struct Metrics
{
  Metrics() = default;

  Metrics(Metrics &&i_other);

  void incLines();
  void incBlocks();
  void incCommands(int i_num = 1);

  std::atomic<int> d_lines{0};
  std::atomic<int> d_blocks{0};
  std::atomic<int> d_commands{0};

  friend std::ostream &operator<<(std::ostream &os, const Metrics &i_metric);
};



