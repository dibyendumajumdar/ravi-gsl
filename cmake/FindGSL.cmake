find_path(GSL_INCLUDE_DIR gsl/gsl_version.h
  PATHS
  c:/ravi/include
  /usr/include
)

find_library(GSL_LIBRARY
  NAMES gsl libgsl
  PATHS
  c:/ravi/lib
  /usr/lib
)

set( GSL_INCLUDE_DIRS "${GSL_INCLUDE_DIR}" )
set( GSL_LIBRARIES "${GSL_LIBRARY}" )
