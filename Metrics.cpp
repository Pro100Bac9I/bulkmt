#include "Metrics.h"

#include <iostream>


Metrics::Metrics(Metrics &&i_other)
  : d_lines(std::move(i_other.d_lines.load()))
  , d_blocks(std::move(i_other.d_blocks.load()))
  , d_commands(std::move(i_other.d_commands.load()))
{}

void Metrics::incLines()
{
  ++d_lines;
}

void Metrics::incBlocks()
{
  ++d_blocks;
}

void Metrics::incCommands(int i_num)
{
  d_commands += i_num;
}

std::ostream &operator<<(std::ostream &os, const Metrics &i_metric)
{
  if (i_metric.d_lines)
    os << i_metric.d_lines << " lines, ";

  os << i_metric.d_commands << " commands, "
    << i_metric.d_blocks << " blocks";

  return os;
}


