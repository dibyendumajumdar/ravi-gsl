gsl = require 'ravigsl'
matrix = require 'ravimatrix'

local y: number
local v: number[] = {}

y = gsl.sf_bessel_J0(5.0)
assert(y == -1.775967713143382642e-01)

local data: number[] = { 1, 2, 3.0, 4.0 }
v = matrix.vectorR(data)
y = gsl.stats_mean(v)
assert(y == 2.5)
y = gsl.stats_variance(data)
assert(math.abs(y - 1.666666666) < 1e-5)
y = gsl.stats_variance(data, 1, 3.0)
assert(math.abs(y - 2.0) < 1e-5)

local data: number[] = { 1, 2; 3.0, 4.0 }
v = matrix.matrixR(2,2,data)
y = gsl.stats_mean(v,2)
assert(y == 3.5)

