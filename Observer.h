#pragma once

#include <memory>

struct TimedBlock;

using sPtrBlock = std::shared_ptr<TimedBlock>;

class Observer
{
public:
  virtual ~Observer() = default;

  virtual void update(sPtrBlock i_block) = 0;
};
