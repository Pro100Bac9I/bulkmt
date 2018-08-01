#include "LineProcessor.h"

#include <string>

int main(int argc, char **argv)
{
  if (argc < 2)
    return 1;

  LineProcessor processor(std::stoi(argv[1]));
  processor.run();

  return 0;
}