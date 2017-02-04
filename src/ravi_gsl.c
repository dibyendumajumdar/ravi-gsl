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
#include <ravi_matrix.h>
#include <ravi_matrixlib.h>

#include "ravi_gsl_internal.h"

#define RAVI_ENABLED 1

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_errno.h>

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
GSL_FUNC_D_McolMcol(gsl_stats_wmean)
GSL_ALTFUNC_D_McolMcolD(gsl_stats_wvariance, gsl_stats_wvariance_m)
GSL_ALTFUNC_D_McolMcolD(gsl_stats_wsd, gsl_stats_wsd_m)
GSL_ALTFUNC_D_McolMcolD(gsl_stats_wtss, gsl_stats_wtss_m)
GSL_ALTFUNC_D_McolMcolD(gsl_stats_wabsdev, gsl_stats_wabsdev_m)
GSL_FUNC_D_McolMcol(gsl_stats_wskew)
GSL_FUNC_D_McolMcol(gsl_stats_wkurtosis)
GSL_FUNC_D_McolMcolD(gsl_stats_wvariance_with_fixed_mean)
GSL_FUNC_D_McolMcolD(gsl_stats_wsd_with_fixed_mean)
GSL_FUNC_6D_McolMcol(gsl_fit_linear)

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
                                        {"stats_wmean", ravi_gsl_stats_wmean},
                                        {"stats_wvariance", ravi_gsl_stats_wvariance},
                                        {"stats_wsd", ravi_gsl_stats_wsd},
                                        {"stats_wvariance_with_fixed_mean", ravi_gsl_stats_wvariance_with_fixed_mean},
                                        {"stats_wsd_with_fixed_mean", ravi_gsl_stats_wsd_with_fixed_mean},
                                        {"stats_wtss", ravi_gsl_stats_wtss},
                                        {"stats_wabsdev", ravi_gsl_stats_wabsdev},
                                        {"stats_wskew", ravi_gsl_stats_wskew},
                                        {"stats_wkurtosis", ravi_gsl_stats_wkurtosis},
										{"fit_linear", ravi_gsl_fit_linear},
                                        {NULL, NULL}};

// adds to an existing table
// table must be on stop of the stack
static void raviU_add_to_library(lua_State* L, const struct luaL_Reg* regs) {
	int i = 0;
	for (; regs[i].name != NULL; i++) {
		lua_pushcclosure(L, regs[i].func, 0);
		lua_setfield(L, -2, regs[i].name);
	}
}

// creates a table of functions which is a library in Lua
// terms. We use this as a portable way across 5.1 and 5.2 which
// follows the latest conventions - i.e. avoid polluting global
// namespace
static void raviU_create_library(lua_State* L, const struct luaL_Reg* regs) {
	int count = 0;
	int i = 0;
	for (; regs[i].name != NULL; i++) {
		count++;
	}
	lua_createtable(L, 0, count);
	raviU_add_to_library(L, regs);
	// leave table on the stack
}

int luaopen_ravigsl(lua_State *L) {
  fprintf(stderr, "Initializing RaviGSL\n");
  raviU_create_library(L, mylib);
  fprintf(stdout, "RaviGSL initialized successfully\n");
  return 1;
}
