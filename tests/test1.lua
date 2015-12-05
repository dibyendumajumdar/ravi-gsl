gsl = require 'ravigsl'

local y = gsl.sf_bessel_J0(5.0)
assert(y == -1.775967713143382642e-01)