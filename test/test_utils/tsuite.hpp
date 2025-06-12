#ifndef UTEST_SUITE_H
#define UTEST_SUITE_H

#include "tresult.hpp"
#include "utest.hpp"
#include <memory>

// This is an interface for test suites, to allow heterogeneous test suites
// that can contain different types of unit tests.
// It should be used to add tests, run them, and evaluate the results.
class ITestSuite
{
public:
  virtual ~ITestSuite() = default;
  // The add_test() method should add a test to the suite
  virtual void add_test(std::shared_ptr<IUnitTest> testcase) = 0;
  // The run_test() method should run all tests in the suite
  virtual void run_tests() = 0;
  // The eval() method should evaluate the results of the tests
  virtual void eval() = 0;
  // The result() method should return the results of the tests
  virtual UTestResult &result() = 0;
  virtual const UTestResult &result() const = 0;
};

// This is a concrete implementation of the ITestSuite interface
class TestSuite : public ITestSuite
{
public:
  explicit TestSuite(std::string name) : res(std::move(name)) {};
  TestSuite() = default;

  void add_test(std::shared_ptr<IUnitTest> testcase) override
  {
    testcases.emplace_back(std::move(testcase));
  }

  // Generic add_test for expected and actual values with a comparison function
  // This allows for a more flexible way to add tests with different types 
  template <typename Ta, typename Tb, typename F>
  void add_test(std::string name, Ta&& expected, Tb &&actual, F &&compare)
  {
    using UT = UnitTest<
        std::decay_t<Ta>,
        std::decay_t<Tb>,
        std::decay_t<F>>;
    static_assert(
        std::is_constructible_v<
            UT,
            std::string,
            std::decay_t<Ta>,
            std::decay_t<Tb>,
            std::decay_t<F>>,
        "UnitTest constructor is not valid");
    testcases.emplace_back(
        std::make_shared<UT>(
            std::move(name),
            std::forward<Ta>(expected),
            std::forward<Tb>(actual),
            std::forward<F>(compare)));
  }

  // Generic add_test for any type of unit test
  template <typename UT, typename... Args>
  void add_test(Args &&...args)
  {
    static_assert(std::is_base_of_v<IUnitTest, UT>, "UT must be derived from IUnitTest");
    testcases.emplace_back(std::make_shared<UT>(std::forward<Args>(args)...));
  }

  void run_tests() override
  {
    for (auto &ut : testcases)
    {
      int result = ut->Run();
      if (result == 1)
        res.passed++;
      else if (result == 0)
        res.failed++;
      else
        res.error++;
      res.outputs.emplace_back(ut->output());
    }
  }

  UTestResult &result() override
  {
    return res;
  }

  const UTestResult &result() const override
  {
    return res;
  }

  void eval() override
  {
    std::cout << res << "\n";
  }

private:
  std::vector<std::shared_ptr<IUnitTest>>
      testcases;
  UTestResult res;
};

#endif