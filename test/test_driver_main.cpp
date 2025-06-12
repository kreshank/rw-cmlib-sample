#include "test_utils/tregistry.hpp"
#include <iostream>

int main(const int argc, const char *argv[])
{
  if (argc == 0)
  {
    std::cout << "Usage: " << argv[0] << " [files...] \n";
    return 0;
  }
  else 
  {
    return UTestRegistry::instance().run_all();
  }
}