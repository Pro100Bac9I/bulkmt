#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

using Commands = std::vector<std::string>;

struct TimedBlock
{
  friend std::ostream& operator<<(std::ostream& os, const TimedBlock& i_block);

  bool empty() const
  {
    return d_commands.empty();
  }

  Commands d_commands;
  std::time_t d_timeStamp;
  int d_blockSeq;
};

