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

#define RAVI_ENABLED 1

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <gsl/gsl_sf_bessel.h>

static int sf_bessel_J0(lua_State *L) {
  double x = luaL_checknumber(L, 1);
  double y = gsl_sf_bessel_J0(x);
  lua_pushnumber(L, y);
  return 1;
}

static const struct luaL_Reg mylib[] = {{"sf_bessel_J0", sf_bessel_J0},
                                        {NULL, NULL}};

int luaopen_ravigsl(lua_State *L) {
  fprintf(stderr, "Initializing RaviGSL\n");
  raviU_create_library(L, mylib);
  fprintf(stdout, "RaviGSL initialized successfully\n");
  return 1;
}
