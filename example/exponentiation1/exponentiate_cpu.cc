#include "example/exponentiation1/exponentiate_cpu.h"

#include <iostream>

#include "sxt/base/num/fast_random_number_generator.h"
#include "sxt/curve21/type/element_p3.h"
#include "sxt/curve21/operation/scalar_multiply.h"

namespace sxt {
//--------------------------------------------------------------------------------------------------
// exponentiate_cpu
//--------------------------------------------------------------------------------------------------
void exponentiate_cpu(c21t::element_p3* res, int n) noexcept {
  c21t::element_p3 g{
      .X{3990542415680775, 3398198340507945, 4322667446711068, 2814063955482877,
         2839572215813860},
      .Y{1801439850948184, 1351079888211148, 450359962737049, 900719925474099,
         1801439850948198},
      .Z{1, 0, 0, 0, 0},
      .T{1841354044333475, 16398895984059, 755974180946558, 900171276175154,
         1821297809914039},
  };
  for (int i=0; i<n; ++i) {
    unsigned char a[32] = {1};
    c21o::scalar_multiply(res[i], a, g);
    /* res[i] = g; */
  }
}
}  // namespace sxt
