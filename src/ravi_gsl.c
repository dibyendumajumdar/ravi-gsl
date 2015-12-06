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

// M - Matrix
// D - Double
// I - Integer
// col - column (integer)

GSL_FUNC_D_D(gsl_sf_bessel_J0)
GSL_FUNC_D_Mcol(gsl_stats_mean)
GSL_ALTFUNC_D_McolD(gsl_stats_variance, gsl_stats_variance_m)
GSL_ALTFUNC_D_McolD(gsl_stats_sd, gsl_stats_sd_m)
GSL_ALTFUNC_D_McolD(gsl_stats_tss, gsl_stats_tss_m)
GSL_ALTFUNC_D_McolD(gsl_stats_absdev, gsl_stats_absdev_m)
GSL_FUNC_D_McolD(gsl_stats_variance_with_fixed_mean)
GSL_FUNC_D_McolD(gsl_stats_sd_with_fixed_mean)
GSL_FUNC_D_Mcol(gsl_stats_skew)
GSL_FUNC_D_McolDD(gsl_stats_skew_m_sd)
GSL_FUNC_D_Mcol(gsl_stats_kurtosis)
GSL_FUNC_D_McolDD(gsl_stats_kurtosis_m_sd)
GSL_ALTFUNC_D_McolD(gsl_stats_lag1_autocorrelation, gsl_stats_lag1_autocorrelation_m)
GSL_FUNC_D_McolMcol(gsl_stats_covariance)
GSL_FUNC_D_McolMcol(gsl_stats_correlation)

static const struct luaL_Reg mylib[] = {{"sf_bessel_J0", ravi_gsl_sf_bessel_J0},
                                        {"stats_mean", ravi_gsl_stats_mean},
                                        {"stats_variance", ravi_gsl_stats_variance},
                                        {"stats_sd", ravi_gsl_stats_sd },
                                        {"stats_tss", ravi_gsl_stats_tss },
                                        {"stats_absdev", ravi_gsl_stats_absdev },
                                        {"stats_variance_with_fixed_mean", ravi_gsl_stats_variance_with_fixed_mean },
                                        {"stats_sd_with_fixed_mean", ravi_gsl_stats_sd_with_fixed_mean },
                                        {"stats_skew", ravi_gsl_stats_skew},
                                        {"stats_skew_m_sd", ravi_gsl_stats_skew_m_sd},
                                        {"stats_kurtosis", ravi_gsl_stats_kurtosis},
                                        {"stats_skew_m_sd", ravi_gsl_stats_kurtosis_m_sd},
                                        {"stats_lag1_autocorrelation", ravi_gsl_stats_lag1_autocorrelation},
                                        {"stats_covariance", ravi_gsl_stats_covariance},
                                        {"stats_correlation", ravi_gsl_stats_correlation},
                                        {NULL, NULL}};

int luaopen_ravigsl(lua_State *L) {
  fprintf(stderr, "Initializing RaviGSL\n");
  raviU_create_library(L, mylib);
  fprintf(stdout, "RaviGSL initialized successfully\n");
  return 1;
}
