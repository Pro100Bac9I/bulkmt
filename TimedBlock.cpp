#include "TimedBlock.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const TimedBlock& i_block)
{
  for (auto &command : i_block.d_commands)
    os << command << ' ';

  os << std::endl;

  return os;
}
