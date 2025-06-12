# rw-cmlib-sample

## Motivation & Design Goals

A **header-only micro test framework** (~350 LOC) I wrote for as both a learning experience and a dependency-free, single file include  for a personal C++ utilities library. It features the following:

* **Auto-registration with the Registry pattern**
  * Having a `REGISTER_SUITE` macro hooks the suite into a singleton registry - allowin
* **Exception-safe test execution**
  * `UnitTest::Run()` catches thrown exceptions without crashing the runner, and forwards the message in the output.
* **Compile-time types, zero runtime dispatch**
  * `UnitTest<TExpected, TActual, FComparator>` is fully templated for speed
  * Still supports heterogeneous tests in one suite; the registry stores everything as `std::unique_ptr<ISuite>`.
* **Tiny binary and fast builds**
  * The lack of external libraries keeps the final executable tiny and light


---

## Requirements 

Requires [CMake 3.12+](https://cmake.org/download/) and C++20.

## Quick start

### Linux
Recommended to create a new directory, `build/` in the root directory.
```bash
$ mkdir build
$ cd build
```
Build the library and files:
```bash
$ cmake ..
$ make
```
Try the tests within the `build/` directory:
```bash
$ test/run_tests
```

## Project Overview
Header files are located under the `include/` directory, and implementation files aWre in corresponding
`src/` directory. `test/` contains the test framework under `test/test_utils/`, as well as an excerpt of some correctness tests performed with this test framework.

## Limitations

* Test execution is not parallelized
* No checks for console color compatibility
* No parameterized tests; tests are static