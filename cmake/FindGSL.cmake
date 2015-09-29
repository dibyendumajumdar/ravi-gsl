find_path(GSL_INCLUDE_DIR gsl/gsl_version.h
  PATHS
  c:/ravi/include
)

find_library(GSL_LIBRARY
  NAMES gsl libgsl
  PATHS
  c:/ravi/bin
)

set( GSL_INCLUDE_DIRS "${GSL_INCLUDE_DIR}" )
set( GSL_LIBRARIES "${GSL_LIBRARY}" )
