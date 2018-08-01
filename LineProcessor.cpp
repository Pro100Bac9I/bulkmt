#include "LineProcessor.h"
#include "CommandBlock.h"
#include "MetricsCollection.h"
#include "Metrics.h"

#include "CoutObserver.h"
#include "LogObserver.h"

#include <memory>

LineProcessor::LineProcessor(int i_len)
  : d_block(std::make_shared<CommandBlock>(i_len))
{
  d_block->subscribe(std::make_unique<CoutObserver>(2));
  d_block->subscribe(std::make_unique<LogObserver>(2));
}

LineProcessor::~LineProcessor()
{
  d_block.reset();
  MetricsCollection::getInstance().print();
}

void LineProcessor::run()
{
  std::string line;
  while (std::getline(std::cin, line))
    processLine(line);

  d_block->setStatus(Status::endBlock);
}

void LineProcessor::processLine(const std::string &i_line)
{
  auto& inst = MetricsCollection::getInstance().getById("Main");
  inst.incLines();
  
  if (i_line == "{")
  {
    ++d_bracketCounter;
    if (d_bracketCounter == 1)
      d_block->setStatus(Status::openBracket);
  }
  else if (i_line == "}")
  {
    --d_bracketCounter;
    if (d_bracketCounter == 0)
      d_block->setStatus(Status::closeBracket);
  }
  else
    d_block->append(i_line);
}
