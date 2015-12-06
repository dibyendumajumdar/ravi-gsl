GNU Scientific Library Bindings
===============================

Note: this is work in progress.

Usage
-----

To initialize the library use following::

  gsl = require 'ravigsl'
  matrix = require 'ravimatrix'

Reference
---------

gsl.sf_bessel_J0(number) -> number
  As gsl_sf_bessel_J0

gsl.stats_mean(matrix [, column]) -> number
  Calculates mean of a column vector; as in gsl_stats_mean

gsl.stats_variance(matrix [, column [, mean]]) -> number
  Calculates variance of a column vector; as in gsl_stats_variance and gsl_stats_variance_m