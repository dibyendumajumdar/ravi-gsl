/****************************
**************************************************
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

#ifndef RAVI_GSL_INTERNAL_H
#define RAVI_GSL_INTERNAL_H


#define GSL_FUNC_D_D(name) \
  static int ravi_##name(lua_State *L) { \
    double x = luaL_checknumber(L, 1); \
    double y = name(x); \
    lua_pushnumber(L, y); \
    return 1; \
  }

// func(column[default 1] of a matrix) -> value 
#define GSL_FUNC_D_MI(name) \
  static int ravi_##name(lua_State *L) { \
    const ravi_matrix_lua_api_t *api = ravi_matrix_get_api(true); \
    ravi_matrix_t *v = api->check_ismatrix(L, 1); \
    int col = (int) luaL_optinteger(L, 2, 1) - 1; \
    luaL_argcheck(L, col >= 0 && col < v->n, 2, "invalid column"); \
    double y = name(&v->data[col*v->m], 1, v->m); \
    lua_pushnumber(L, y); \
    return 1; \
  }

// func(column[default 1] of a matrix, [m]) -> value 
#define GSL_FUNC_D_MI_m(name, altname) \
  static int ravi_##name(lua_State *L) { \
    const ravi_matrix_lua_api_t *api = ravi_matrix_get_api(true); \
    ravi_matrix_t *v = api->check_ismatrix(L, 1); \
    int col = (int) luaL_optinteger(L, 2, 1) - 1; \
    luaL_argcheck(L, col >= 0 && col < v->n, 2, "invalid column"); \
    double y; \
    if (lua_gettop(L) >= 3 && lua_isnumber(L, 3)) { \
      y = altname(&v->data[col*v->m], 1, v->m, lua_tonumber(L,3)); \
    } \
    else { \
      y = name(&v->data[col*v->m], 1, v->m); \
    } \
    lua_pushnumber(L, y); \
    return 1; \
  }

// func(column[default 1] of a matrix, [m]) -> value 
#define GSL_FUNC_D_MIN(name) \
  static int ravi_##name(lua_State *L) { \
    const ravi_matrix_lua_api_t *api = ravi_matrix_get_api(true); \
    ravi_matrix_t *v = api->check_ismatrix(L, 1); \
    double m = luaL_checknumber(L, 2); \
    int col = (int) luaL_optinteger(L, 3, 1) - 1; \
    luaL_argcheck(L, col >= 0 && col < v->n, 3, "invalid column"); \
    double y = name(&v->data[col*v->m], 1, v->m, m); \
    lua_pushnumber(L, y); \
    return 1; \
  }


#endif