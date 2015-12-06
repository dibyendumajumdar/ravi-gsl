/******************************************************************************
* Copyright (C) 2015 Dibyendu Majumdar
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

#include <ravi_gsl.h>
#include <ravi_lua_utils.h>
#include <ravi_matrix.h>
#include <ravi_matrixlib.h>

#include "ravi_gsl_internal.h"

#define RAVI_ENABLED 1

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_statistics_double.h>

GSL_FUNC_D_D(gsl_sf_bessel_J0)
GSL_FUNC_D_MI(gsl_stats_mean)
GSL_FUNC_D_MI_m(gsl_stats_variance, gsl_stats_variance_m)
GSL_FUNC_D_MI_m(gsl_stats_sd, gsl_stats_sd_m)
GSL_FUNC_D_MI_m(gsl_stats_tss, gsl_stats_tss_m)
GSL_FUNC_D_MIN(gsl_stats_variance_with_fixed_mean)
GSL_FUNC_D_MIN(gsl_stats_sd_with_fixed_mean)

static const struct luaL_Reg mylib[] = {{"sf_bessel_J0", ravi_gsl_sf_bessel_J0},
                                        {"stats_mean", ravi_gsl_stats_mean},
                                        {"stats_variance", ravi_gsl_stats_variance},
                                        {"stats_sd", ravi_gsl_stats_sd },
                                        {"stats_tss", ravi_gsl_stats_tss },
                                        {"stats_variance_with_fixed_mean", ravi_gsl_stats_variance_with_fixed_mean },
                                        {"stats_sd_with_fixed_mean", ravi_gsl_stats_sd_with_fixed_mean },
                                        {NULL, NULL}};

int luaopen_ravigsl(lua_State *L) {
  fprintf(stderr, "Initializing RaviGSL\n");
  raviU_create_library(L, mylib);
  fprintf(stdout, "RaviGSL initialized successfully\n");
  return 1;
}
