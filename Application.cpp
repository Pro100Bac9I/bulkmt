#include "Application.h"
#include "CommandBlock.h"
#include "CoutObserver.h"
#include "LogObserver.h"
#include "LineProcessor.h"
#include "MetricsCollection.h"

#include <string>
#include <iostream>
#include <fstream>

#include <chrono>
#include <thread>
#include <exception>

Application::Application(int i_blockLen)
  : blockLen(i_blockLen)
{
}

void Application::run()
{
  {
    auto cb = std::make_shared<CommandBlock>(blockLen);

    cb->subscribe(std::make_unique<CoutObserver>(2));
    cb->subscribe(std::make_unique<LogObserver>(2));

    LineProcessor processor(cb);

    std::string line;
    while (std::getline(std::cin, line))
      processor.processLine(line);

    cb->setStatus(Status::endBlock);
  }
  
  MetricsCollection::getInstance().print();
}
