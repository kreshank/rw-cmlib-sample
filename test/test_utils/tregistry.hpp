#ifndef TEST_REG_H
#define TEST_REG_H

#include "tsuite.hpp"

// Registry for unit test suites
class UTestRegistry 
{
public:
  // Singleton instance accessor
  static UTestRegistry& instance() 
  {
    static UTestRegistry inst;
    return inst;
  }

  // Add a test suite to the (heterogenous) registry
  void add(ITestSuite* suite) 
  {
    suites_.push_back(suite);
  }

  // Run all test suites and return the total number of failed tests
  int run_all() 
  {
    int fails = 0;
    for (auto suite : suites_) 
    {
      suite->run_tests();
      suite->eval();
      auto res = suite->result();
      fails += res.failed + res.error;
    }
    return fails;
  }
private:
  std::vector<ITestSuite*> suites_;
  
  UTestRegistry() = default;
  // Delete copy and move constructors and assignment operators to ensure singleton behavior
  // Rule of five: if you define one of these, you should define all five
  ~UTestRegistry() = default;
  UTestRegistry(const UTestRegistry&) = delete;
  UTestRegistry& operator=(const UTestRegistry&) = delete;
  UTestRegistry(UTestRegistry&&) = delete;
  UTestRegistry& operator=(UTestRegistry&&) = delete;
};

// Macro to register a test suite with the registry
#define REGISTER_SUITE(SUITE_OBJ, INIT_FUN)                                               \
  namespace                                                                     \
  {                                                                             \
    struct _AutoReg                                                             \
    {                                                                           \
      _AutoReg()                                                                \
      {                                                                         \
        INIT_FUN();                                                             \
        UTestRegistry::instance().add(&SUITE_OBJ);                              \
      }                                                                         \
    } _AutoRegInstance;                                                         \
  }

#endif