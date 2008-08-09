#ifndef ISL_LP_PIPLIB_H
#define ISL_LP_PIPLIB_H

#include <isl_lp.h>

#if defined(__cplusplus)
extern "C" {
#endif

enum isl_lp_result isl_pip_solve_lp(struct isl_basic_map *bmap, int maximize,
				      isl_int *f, isl_int denom, isl_int *opt);

#if defined(__cplusplus)
}
#endif

#endif
