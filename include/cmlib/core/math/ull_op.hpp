#ifndef ULL_OP
#define ULL_OP

#include <cstdint>

#define ULL_MASK_LEFT(ul) (ul >> 32)
#define ULL_MASK_RIGHT(ul) (((1ULL << 32) - 1) & ul)

/**
 * `ull_add(a, b, result, carry);`
 * Adds `a` and `b`, stores result and carry values in `result`, `carry`
 *  respectively.
 */
void ull_add(uint64_t a, uint64_t b, uint64_t &res, uint64_t &carry);

/**
 * `ull_sub(a, b, result, borrow);`
 * Subtracts `a` and `b`, stores result and borrow values in `result`,
 *  `borrow` respectively.
 */
void ull_sub(uint64_t a, uint64_t b, uint64_t &res, uint64_t &borrow);

/**
 * `ull_mult(a, b, result, carry);`
 * Multiplies `a` and `b`, stores result and carry values in `result`, `carry`
 *  respectively.
 */
void ull_mult(uint64_t a, uint64_t b, uint64_t &res, uint64_t &carry);

#endif
