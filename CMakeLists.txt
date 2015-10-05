cmake_minimum_required(VERSION 2.8)
project(RaviGSL)

enable_language(C)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

if (WIN32)
  option(USE_OPENBLAS "Controls whether OpenBLAS will be used" ON)
endif(WIN32)

#BLAS
if (USE_OPENBLAS)
  find_package(OpenBLAS REQUIRED)
  set(BLAS_LIBRARIES ${OPENBLAS_LIBRARIES})
else()
  find_package(BLAS REQUIRED)
endif(USE_OPENBLAS)
find_package(RAVI REQUIRED)
find_package(RaviLuaUTILS REQUIRED)
find_package(RaviMatrix REQUIRED)
find_package(GSL REQUIRED)

message( STATUS "BLAS_LIBRARIES        : " ${BLAS_LIBRARIES} )
message( STATUS "BLAS_LINKER_FLAGS     : " ${BLAS_LINKER_FLAGS} )
message( STATUS "LUA_LIBRARIES         : " ${LUA_LIBRARIES} )
message( STATUS "LUA_INCLUDE_DIRS      : " ${LUA_INCLUDE_DIRS} )
message( STATUS "OPENBLAS_LIBRARIES    : " ${OPENBLAS_LIBRARIES} )
message( STATUS "OPENBLAS_INCLUDE_DIRS : " ${OPENBLAS_INCLUDE_DIRS} )
message( STATUS "GSL_LIBRARIES         : " ${GSL_LIBRARIES} )
message( STATUS "GSL_INCLUDE_DIRS      : " ${GSL_INCLUDE_DIRS} )

if (MSVC)
  set(CMAKE_C_FLAGS_DEBUG "/Od /D_DEBUG /MDd /Zi /RTC1 /EHsc")
  set(CMAKE_C_FLAGS_RELEASE "/DNDEBUG /O2 /MD /EHsc")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "/DNDEBUG /O2 /MD /Zi /EHsc")
  set(CMAKE_C_FLAGS_MINSIZEREL "/DNDEBUG /O2 /MD /EHsc")    

  set(CMAKE_CXX_FLAGS "/EHsc")
  set(CMAKE_CXX_FLAGS_DEBUG "/Od /D_DEBUG /MDd /Zi /RTC1 /EHsc")
  set(CMAKE_CXX_FLAGS_RELEASE "/DNDEBUG /O2 /MD  /EHsc")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/DNDEBUG /O2 /MD /Zi /EHsc")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/DNDEBUG /O2 /MD /EHsc")  
  
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG /STACK:10000000")
  SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "/RELEASE /INCREMENTAL:NO /STACK:10000000")
  SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG /RELEASE /INCREMENTAL:NO /STACK:10000000")
  SET(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/RELEASE /INCREMENTAL:NO /STACK:10000000")

  SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${TCMALLOC_LINK_FLAGS}")
  SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
  SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
  SET(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}")
  SET(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL}")

  # Disable signed/unsigned int conversion warnings.
  add_definitions("/wd4018")
  # Disable warning about using struct/class for the same symobl.
  add_definitions("/wd4099")
  # Disable performance warning about int-to-bool conversion.
  add_definitions("/wd4800")
  # Disable signed/unsigned int conversion warnings.
  add_definitions("/wd4018")
  # Disable warning about the insecurity of using "std::copy".
  add_definitions("/wd4996")
  add_definitions("/wd4291")
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS_DEBUG "-Werror -std=c99 -O0 -g3 -fsanitize=address -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
  set(CMAKE_C_FLAGS_RELEASE "-Werror -std=c99 -O3 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Werror -std=c99 -O1 -g3 -fsanitize=address -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
  set(CMAKE_CXX_FLAGS_RELEASE "-Werror -fno-rtti -O3 -Wall -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
  set(CMAKE_CXX_FLAGS_DEBUG "-Werror -fno-rtti -O0 -fsanitize=address -g3 -Wall -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Werror -fno-rtti -O1 -g3 -fsanitize=address -Wall -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
endif()

if (APPLE)
  set(CMAKE_C_FLAGS "-std=c99 -O1 -g3 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_C_FLAGS_DEBUG "-std=c99 -O0 -g3 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_C_FLAGS_RELEASE "-std=c99 -O3 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-std=c99 -O1 -g3 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_CXX_FLAGS "-O1 -g3 -Wall -fno-rtti -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_CXX_FLAGS_RELEASE "-fno-rtti -O3 -Wall -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_CXX_FLAGS_DEBUG "-fno-rtti -O0 -g3 -Wall -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-fno-rtti -O1 -g3 -Wall -Wno-sign-compare -std=c++11 -fno-exceptions -DLUA_COMPAT_5_2 -DLUA_USE_MACOSX")
endif()

add_definitions(-DLUA_COMPAT_MODULE)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${LUA_INCLUDE_DIRS}")
include_directories("${RAVILUAUTILS_INCLUDE_DIRS}")
include_directories("${RAVIMATRIX_INCLUDE_DIRS}")
include_directories("${GSL_INCLUDE_DIRS}")
if (APPLE)
  include_directories("/System/Library/Frameworks")
endif()
if (WIN32)
  if (NOT USE_OPENBLAS)
    set(BLAS_LIBRARIES "libgslcblas.lib")
  endif()
elseif(APPLE)
else()                   
endif()
link_directories("${CMAKE_INSTALL_PREFIX}/bin")

set (RAVIGSL_SRCS src/ravi_gsl.c)
file(GLOB RAVIGSL_HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

if (MSVC)
  source_group("Source Files" FILES ${RAVIGSL_SRCS})
  source_group("Headers" FILES ${RAVIGSL_HEADERS})
endif()

#Main library
add_library(ravigsl SHARED 
  ${RAVIGSL_HEADERS} ${LUA_HEADERS}
  ${RAVIGSL_SRCS})
# RAVIGSL_IMPLEMENTATION is set when compiling shared library so that 
# appropriate export declarations can be set 
set_target_properties(ravigsl 
  PROPERTIES DEFINE_SYMBOL "RAVIGSL_IMPLEMENTATION")
target_link_libraries(ravigsl ${GSL_LIBRARIES} ${LUA_LIBRARIES} 
  ${BLAS_LIBRARIES} ${RAVILUAUTILS_LIBRARIES} ${RAVIMATRIX_LIBRARIES}) 

install(TARGETS ravigsl
        DESTINATION bin)
install(FILES ${RAVIGSL_HEADERS} 
        DESTINATION include)