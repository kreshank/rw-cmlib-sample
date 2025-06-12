#ifndef UTEST_H
#define UTEST_H

#include <string>
#include <sstream>
#include <functional>

// This is an interface for unit tests
class IUnitTest
{
public:
  virtual ~IUnitTest() = default;
  // The Run() method should return 1 if the test passes, 0 if it fails, and -1 if an error occurs
  virtual int Run() = 0;
  virtual const std::string &output() const = 0;
};

// Concrete templated implementation of the IUnitTest interface
// Templated for expected and actual values, and a comparison function
// The comparison function should return true if the expected and actual values are equal
template <typename Ta, typename Tb, typename F>
class UnitTest : public IUnitTest
{
public:
  using Expected = Ta;
  using Actual = Tb;
  using CompareFunc = F;

  // Constructor for UnitTest
  // Essentially a wrapper around the test case so that it can avoid copying,
  // and still have a compile-time check for the types
  template <
      typename N, typename E, typename A, typename C,
      std::enable_if_t<
          std::is_constructible_v<std::string, N &&> &&
              std::is_constructible_v<Ta, E &&> &&
              std::is_constructible_v<Tb, A &&> &&
              std::is_constructible_v<F, C &&>,
          int> = 0>
  UnitTest(N &&n, E &&e, A &&a, C &&f) : name(std::forward<N>(n)),
                                         expected(std::forward<E>(e)),
                                         actual(std::forward<A>(a)),
                                         compare(std::forward<C>(f)) {}

  int Run() override
  {
    try
    {
      bool ok = compare(expected, actual);
      if (ok)
      {
        std::ostringstream oss;
        oss << name << " - OK";
        output_ = oss.str();
      }
      else
      {
        std::ostringstream oss;
        oss << name << " - Expected: " << expected << " Actual: " << actual;
        output_ = oss.str();
      }
      return ok;
    }
    catch (const std::exception &e)
    {
      std::ostringstream oss;
      oss << name << " - " << e.what();
      output_ = oss.str();
      return -1;
    }
    catch (...)
    {
      std::ostringstream oss;
      oss << name << " - Unexpected exception thrown";
      output_ = oss.str();
      return -1;
    }
  }

  const std::string &output() const override
  {
    return output_;
  }

private:
  std::string name;
  Ta expected;
  Tb actual;
  F compare; // `compare` should return 1 iff they are equal
  std::string output_;
};

#endif