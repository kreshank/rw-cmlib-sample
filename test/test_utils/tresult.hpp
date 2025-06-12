#ifndef TEST_RESULT_H
#define TEST_RESULT_H

#include <string>
#include <vector>
#include <iostream>

// This is a structure to hold the results of a unit test
// It contains the name of the test, the number of passed, failed, and errored tests,
// and a vector of output messages (e.g., error messages or logs).
struct UTestResult
{
  std::string name;
  int passed;
  int failed;
  int error;
  std::vector<std::string> outputs;

  UTestResult(std::string n) : name(n), passed(0), failed(0), error(0) {};
  UTestResult(std::string n, int p, int f, int e) : name(n), passed(p), failed(f), error(e) {};

  friend std::ostream &operator<<(std::ostream &stream, const UTestResult &tr)
  {
    stream << "\033[34m" << "\n-------------------------------------"
           << "\n"
           << "Test: " << tr.name
           << "\n \033[32m" << "Passed: " << tr.passed
           << "\033[31m " << "Failed: " << tr.failed
           << "\033[33m " << "Errors: " << tr.error
           << "\033[0m" << std::endl;
    if (tr.failed + tr.error != 0)
    {
      for (const std::string &err_msg : tr.outputs)
        stream << err_msg << "\n";
    }
    return stream;
  }
};

#endif 