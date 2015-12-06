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

// D - Double
// I - Integer
// M - Matrix
// col - Matrix column

// name(D) -> D
#define GSL_FUNC_D_D(name) \
  static int ravi_##name(lua_State *L) { \
    double x = luaL_checknumber(L, 1); \
    double y = name(x); \
    lua_pushnumber(L, y); \
    return 1; \
  }

// name(M,col) -> D
#define GSL_FUNC_D_Mcol(name) \
  static int ravi_##name(lua_State *L) { \
    const ravi_matrix_lua_api_t *api = ravi_matrix_get_api(true); \
    ravi_matrix_t *v = api->check_ismatrix(L, 1); \
    int col = (int) luaL_optinteger(L, 2, 1) - 1; \
    luaL_argcheck(L, col >= 0 && col < v->n, 2, "invalid column"); \
    double y = name(&v->data[col*v->m], 1, v->m); \
    lua_pushnumber(L, y); \
    return 1; \
  }

// name(M,col) or altname(M,col,D) -> D
#define GSL_ALTFUNC_D_McolD(name, altname) \
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

// name(M, col, D) -> D 
#define GSL_FUNC_D_McolD(name) \
  static int ravi_##name(lua_State *L) { \
    const ravi_matrix_lua_api_t *api = ravi_matrix_get_api(true); \
    ravi_matrix_t *v = api->check_ismatrix(L, 1); \
    int col = (int) luaL_checkinteger(L, 2) - 1; \
    luaL_argcheck(L, col >= 0 && col < v->n, 2, "invalid column"); \
    double m = luaL_checknumber(L, 3); \
    double y = name(&v->data[col*v->m], 1, v->m, m); \
    lua_pushnumber(L, y); \
    return 1; \
  }

// name(M, col, D, D) -> D 
#define GSL_FUNC_D_McolDD(name) \
  static int ravi_##name(lua_State *L) { \
    const ravi_matrix_lua_api_t *api = ravi_matrix_get_api(true); \
    ravi_matrix_t *v = api->check_ismatrix(L, 1); \
    int col = (int) luaL_checkinteger(L, 2) - 1; \
    luaL_argcheck(L, col >= 0 && col < v->n, 2, "invalid column"); \
    double m = luaL_checknumber(L, 3); \
    double sd = luaL_checknumber(L, 4); \
    double y = name(&v->data[col*v->m], 1, v->m, m, sd); \
    lua_pushnumber(L, y); \
    return 1; \
  }


#endif