find_path(RAVIMATRIX_INCLUDE_DIR ravi_matrix.h
  PATHS
  c:/ravi/include
  ~/ravi/include
)

find_library(RAVIMATRIX_LIBRARY
  NAMES ravimatrix libravimatrix
  PATHS
  c:/ravi/bin
  ~/ravi/bin
)

set( RAVIMATRIX_INCLUDE_DIRS "${RAVIMATRIX_INCLUDE_DIR}" )
set( RAVIMATRIX_LIBRARIES "${RAVIMATRIX_LIBRARY}" )
