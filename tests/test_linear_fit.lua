-- The tests here are taken from GSL tests
-- GSL license applies

local gsl = require 'ravigsl'
local matrix = require 'ravimatrix'

local function make_vector(...)
  local data: number[] = { ... }
  return matrix.vectorR(data)
end

local function check(got: number, expected: number, msg)
  if (math.abs(got-expected) > 1e-10) then
  	print('got ', got)
    error(msg .. " failed")
  end
end


local norris_x: number[] =
  make_vector(0.2, 337.4, 118.2, 884.6, 10.1, 226.5, 666.3, 996.3,
                      448.6, 777.0, 558.2, 0.4, 0.6, 775.5, 666.9, 338.0, 
                      447.5, 11.6, 556.0, 228.1, 995.8, 887.6, 120.2, 0.3, 
                      0.3, 556.8, 339.1, 887.2, 999.0, 779.0, 11.1, 118.3,
                      229.2, 669.1, 448.9, 0.5)

local norris_y: number[] =
  make_vector(0.1, 338.8, 118.1, 888.0, 9.2, 228.1, 668.5, 998.5,
                      449.1, 778.9, 559.2, 0.3, 0.1, 778.1, 668.8, 339.3, 
                      448.9, 10.8, 557.7, 228.3, 998.0, 888.8, 119.6, 0.3, 
                      0.6, 557.6, 339.3, 888.0, 998.5, 778.9, 10.2, 117.6,
                      228.9, 668.4, 449.2, 0.2)


local c0, c1, cov00, cov01, cov11, sumsq = gsl.fit_linear(norris_x, 1, norris_y, 1)

check(c0, -0.262323073774029, 'norris gsl_fit_linear c0')
check(c1, 1.00211681802045, 'norris gsl_fit_linear c1')
check(cov00, 0.232818234301152^2.0, 'norris gsl_fit_linear cov00')
check(cov01, -7.74327536339570e-05, 'norris gsl_fit_linear cov01')
check(cov11, 0.429796848199937E-03^2.0, 'norris gsl_fit_linear cov11')
check(sumsq, 26.6173985294224, 'norris gsl_fit_linear sumsq')