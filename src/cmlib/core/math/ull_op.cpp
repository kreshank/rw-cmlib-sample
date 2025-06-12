#include "cmlib/core/math/ull_op.hpp"

void ull_add(uint64_t a, uint64_t b, uint64_t &res, uint64_t &carry)
{
  res = a + b;
  carry = res < a;
}

void ull_sub(uint64_t a, uint64_t b, uint64_t &res, uint64_t &borrow)
{
  res = a - b - borrow;
  borrow = res > a;
}

void ull_mult(uint64_t a, uint64_t b, uint64_t &res, uint64_t &carry)
{
  uint64_t x, y, z, w;

  x = ULL_MASK_RIGHT(a) * ULL_MASK_RIGHT(b);
  y = ULL_MASK_LEFT(a) * ULL_MASK_RIGHT(b);
  z = ULL_MASK_RIGHT(a) * ULL_MASK_LEFT(b);
  w = ULL_MASK_LEFT(a) * ULL_MASK_LEFT(b);

  res = ULL_MASK_RIGHT(x);
  carry = ULL_MASK_LEFT(x) + ULL_MASK_RIGHT(y) + ULL_MASK_RIGHT(z);
  res |= (ULL_MASK_RIGHT(carry) << 32);

  carry = ULL_MASK_LEFT(carry) + ULL_MASK_LEFT(y) + ULL_MASK_LEFT(z) + w;
}
