#include "sxt/multiexp/bitset_multiprod/multiproduct.h"

#include <vector>

#include "sxt/base/test/unit_test.h"
#include "sxt/multiexp/bitset_multiprod/test_operator.h"
#include "sxt/multiexp/bitset_multiprod/value_cache.h"
#include "sxt/multiexp/bitset_multiprod/value_cache_utility.h"

using namespace sxt;
using namespace sxt::mtxbmp;

TEST_CASE("we can compute the multiproduct from a bitset") {
  size_t add_counter = 0;
  test_operator op{&add_counter};

  std::vector<uint64_t> values = {1, 2, 3, 4, 5};
  std::vector<uint64_t> cache_data(compute_cache_size(values.size()));
  value_cache cache{cache_data.data(), values.size()};
  init_value_cache(cache, op, basct::cspan<uint64_t>{values});

  uint64_t res;

  SECTION("we can compute sums with only a single term") {
    compute_multiproduct(res, cache, op, 0b1);
    REQUIRE(res == 1);
    REQUIRE(add_counter == 0);

    compute_multiproduct(res, cache, op, 0b10);
    REQUIRE(res == 2);
    REQUIRE(add_counter == 0);

    compute_multiproduct(res, cache, op, 0b100);
    REQUIRE(res == 3);
    REQUIRE(add_counter == 0);

    compute_multiproduct(res, cache, op, 0b10000);
    REQUIRE(res == 5);
    REQUIRE(add_counter == 0);
  }

  SECTION("we can compute products with two terms") {
    compute_multiproduct(res, cache, op, 0b11);
    REQUIRE(res == 3);
    REQUIRE(add_counter == 1);

    add_counter = 0;
    compute_multiproduct(res, cache, op, 0b101);
    REQUIRE(res == 4);
    REQUIRE(add_counter == 1);

    add_counter = 0;
    compute_multiproduct(res, cache, op, 0b10100);
    REQUIRE(res == 8);
    REQUIRE(add_counter == 1);
  }

  SECTION("we don't recompute values") {
    compute_multiproduct(res, cache, op, 0b11);
    compute_multiproduct(res, cache, op, 0b11);
    REQUIRE(res == 3);
    REQUIRE(add_counter == 1);
  }

  SECTION("we can compute products with more than two terms") {
    compute_multiproduct(res, cache, op, 0b1101);
    REQUIRE(res == 8);
    REQUIRE(add_counter == 2);
  }
}
