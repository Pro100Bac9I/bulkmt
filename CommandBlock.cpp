#include "CommandBlock.h"
#include "Observer.h"
#include "MetricsCollection.h"
#include "TimedBlock.h"

#include <thread>

CommandBlock::CommandBlock(int i_len)
  : d_timedBlock(std::make_shared<TimedBlock>())
  , d_status(Status::startBlock)
  , d_blockLen(i_len)
  , d_blockSeq(0)
{
}

void CommandBlock::setStatus(Status i_status)
{
  if (i_status == Status::endBlock)
  {
    notify();
    d_status = Status::startBlock;
  }

  if (i_status == Status::openBracket)
  {
    notify();
    d_status = Status::openBracket;
  }

  if (i_status == Status::closeBracket)
  {
    notify();
    d_status = Status::startBlock;
  }
}

void CommandBlock::subscribe(std::unique_ptr<Observer> i_observer)
{
  d_subscribers.push_back(std::move(i_observer));
}

void CommandBlock::notify()
{
  if (d_timedBlock->empty())
    return;

  d_timedBlock->d_blockSeq = d_blockSeq;

  for (auto& sub : d_subscribers)
    sub->update(d_timedBlock);

  MetricsCollection::getInstance().update("Main", d_timedBlock->d_commands.size());

  d_timedBlock = std::make_shared<TimedBlock>();
  ++d_blockSeq;
}

void CommandBlock::append(const std::string& i_command)
{
  if (d_timedBlock->d_commands.size() == 0)
    d_timedBlock->d_timeStamp = std::time(nullptr);

  if (d_status == Status::startBlock)
  {
    d_timedBlock->d_commands.push_back(i_command);
    if (d_timedBlock->d_commands.size() == d_blockLen)
      setStatus(Status::endBlock);
  }
  else
    d_timedBlock->d_commands.push_back(i_command);
}
