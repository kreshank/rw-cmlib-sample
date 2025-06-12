#ifndef UOP_TEST
#define UOP_TEST

#include "cmlib/core/math/ull_op.hpp"
#include "test_utils/tregistry.hpp"

TestSuite ULLOpTestSuite("ULL Op Tests");

void ULLOpTestInit()
{
  auto uint64_equal = [](const uint64_t &a, const uint64_t &b){ return a == b; };
  uint64_t a, b, res, carry, borrow;
  {   // Multiplication
    { // 1 x 1 = 1
      a = 1ULL, b = 1ULL;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("1 x 1 == 1",
                               1ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("1 x 1 == 1",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 0 x 134 = 0
      a = 0ULL, b = 134ULL;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("0 x 134 == 0",
                               0ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("0 x 134 == 0",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 0 x 0 = 0
      a = 0ULL, b = 0ULL;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("0 x 0 == 0",
                               0ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("0 x 0 == 0",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 123403 x 134 = 0
      a = 123403ULL, b = 134ULL;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("123403 x 134 == 16536002",
                               16536002ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("123403 x 134 == 16536002",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 123402093148 x 134210394892384239 = 16561843651939863296885094372
      a = 123402093148ULL, b = 134210394892384239ULL;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("123402093148 x 134210394892384239 == 16561843651939863296885094372",
                               7192810092183386084ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("123402093148 x 134210394892384239 == 16561843651939863296885094372",
                               897819343ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 2^32 x 2^32 = 2^64
      a = 1ull << 32, b = 1ull << 32;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("2^32 x 2^32 = 2^64",
                               0ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("2^32 x 2^32 = 2^64",
                               1ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 2^32 x 2^40 = 2^64
      a = 1ull << 32, b = 1ull << 40;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("2^32 x 2^40 = 2^72",
                               0ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("2^32 x 2^40 = 2^72",
                               1ULL << 8,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 3129834932174987 x 99982134892138 = 312927578378845138402986552206
      a = 3129834932174987ULL, b = 99982134892138ULL;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("3129834932174987 x 99982134892138 = 312927578378845138402986552206",
                               8275084630881069966ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("3129834932174987 x 99982134892138 = 312927578378845138402986552206",
                               16963838015ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // (2^63 - 1) x (2^63 - 1) = 85070591730234615847396907784232501249
      a = -1, b = -1, a >>= 1, b >>= 1;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("(2^63 - 1) x (2^63 - 1) = 85070591730234615847396907784232501249",
                               1ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("(2^63 - 1) x (2^63 - 1) = 85070591730234615847396907784232501249",
                               4611686018427387903ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // (2^64 - 1) x (2^64 - 1) = 340282366920938463426481119284349108225
      a = -1, b = -1;
      ull_mult(a, b, res, carry);
      ULLOpTestSuite.add_test("(2^64 - 1) x (2^64 - 1) = 340282366920938463426481119284349108225",
                               1ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("(2^64 - 1) x (2^64 - 1) = 340282366920938463426481119284349108225",
                               18446744073709551614ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }
  }

  {   // Addition
    { // 0 + 0 = 0
      a = 0ULL, b = 0ULL;
      ull_add(a, b, res, carry);
      ULLOpTestSuite.add_test("0 + 0 = 0",
                               0ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("0 + 0 = 0",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 0 + 1 = 1
      a = 0ULL, b = 1ULL;
      ull_add(a, b, res, carry);
      ULLOpTestSuite.add_test("0 + 1 = 1",
                               1ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("0 + 1 = 1",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 1 + 0 = 1
      a = 1ULL, b = 0ULL;
      ull_add(a, b, res, carry);
      ULLOpTestSuite.add_test("1 + 0 = 1",
                               1ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("1 + 0 = 1",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 1120948 + 21342 = 1142290
      a = 1120948ULL, b = 21342ULL;
      ull_add(a, b, res, carry);
      ULLOpTestSuite.add_test("1120948 + 21342 = 1142290",
                               1142290ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("1120948 + 21342 = 1142290",
                               0ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }

    { // 17238947293847829347 + 16213894791328749823 = 33452842085176579170
      a = 17238947293847829347ULL, b = 16213894791328749823ULL;
      ull_add(a, b, res, carry);
      ULLOpTestSuite.add_test("17238947293847829347 + 16213894791328749823 = 33452842085176579170",
                               15006098011467027554ULL,
                               res,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
      ULLOpTestSuite.add_test("17238947293847829347 + 16213894791328749823 = 33452842085176579170",
                               1ULL,
                               carry,
                               [](const uint64_t &a, const uint64_t &b)
                               {
                                 return a == b;
                               });
    }
  }

  { // Subtraction
    {
      a = 0ULL, b = 0ULL, borrow = 0ULL;
      ull_sub(a, b, res, borrow);
      ULLOpTestSuite.add_test("0 - 0 == 0",
                               0ULL,
                               res,
                               uint64_equal);
      ULLOpTestSuite.add_test("0 - 0 == 0",
                               0ULL,
                               borrow,
                               uint64_equal);
    }

    {
      a = 12398ULL, b = 125ULL, borrow = 0ULL;
      ull_sub(a, b, res, borrow);
      ULLOpTestSuite.add_test("12398 - 125 == 12273",
                               12273ULL,
                               res,
                               uint64_equal);
      ULLOpTestSuite.add_test("12398 - 125 == 12273",
                               0ULL,
                               borrow,
                               uint64_equal);
    }

    {
      a = 12398ULL, b = 125ULL, borrow = 1ULL;
      ull_sub(a, b, res, borrow);
      ULLOpTestSuite.add_test("12398 - 1 - 125 == 12272",
                               12272ULL,
                               res,
                               uint64_equal);
      ULLOpTestSuite.add_test("12398 - 1 - 125 == 12272",
                               0ULL,
                               borrow,
                               uint64_equal);
    }

    {
      a = 12398ULL, b = 13000ULL, borrow = 0ULL;
      ull_sub(a, b, res, borrow);
      ULLOpTestSuite.add_test("12398 - 13000 == -602",
                               -602ULL,
                               res,
                               uint64_equal);
      ULLOpTestSuite.add_test("12398 - 13000 == -602",
                               1ULL,
                               borrow,
                               uint64_equal);
    }

    {
      a = 12398ULL, b = 13000ULL, borrow = 1ULL;
      ull_sub(a, b, res, borrow);
      ULLOpTestSuite.add_test("12398 - 1 - 13000 == -603",
                               -603ULL,
                               res,
                               uint64_equal);
      ULLOpTestSuite.add_test("12398 - 1 - 13000 == -603",
                               1ULL,
                               borrow,
                               uint64_equal);
    }


  }
}

REGISTER_SUITE(ULLOpTestSuite, ULLOpTestInit)

#endif