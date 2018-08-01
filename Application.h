#pragma once

class Application
{
public:
  Application(int i_blockLen);
  
  void run();

private:
  int blockLen;
};

