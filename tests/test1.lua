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
		error(msg .. " failed")
	end
end


local rawa: number[] =
  make_vector(.0421, .0941, .1064, .0242, .1331,
   .0773, .0243, .0815, .1186, .0356,
   .0728, .0999, .0614, .0479)

local rawb: number[] =
  make_vector(.1081, .0986, .1566, .1961, .1125,
   .1942, .1079, .1021, .1583, .1673,
   .1675, .1856, .1688, .1512)

local raww: number[] = 
  make_vector(.0000, .0000, .0000, 3.000, .0000,
   1.000, 1.000, 1.000, 0.000, .5000,
   7.000, 5.000, 4.000, 0.123)


local function stats_tests() 

	local expected: number
    local mean: number
    local var: number
    local sd: number
    local ss: number
    local absdev: number
    local skew: number
    local kurt: number

	mean = gsl.stats_mean(rawa)
	expected = 0.0728
	check(mean, expected, "stats_mean")

    var = gsl.stats_variance_with_fixed_mean(rawa, 1, mean)
    expected = 0.00113837428571429
	check(var, expected, "stats_variance_with_fixed_mean")

    sd = gsl.stats_sd_with_fixed_mean(rawa, 1, mean)
    expected = 0.0337398026922845
	check(sd, expected, "stats_sd_with_fixed_mean")

    var = gsl.stats_variance(rawb)
    expected = 0.00124956615384615
	check(var, expected, "stats_variance")

    sd = gsl.stats_sd(rawa)
    expected = 0.0350134479659107
	check(sd, expected, "stats_sd")

    ss = gsl.stats_tss(rawb)
    expected = 0.01624436
    check(ss, expected, "stats_tss")

    ss = gsl.stats_tss(rawa, 1, mean)
    expected = 1.59372400000000e-02
    check(ss, expected, "stats_tss_m")

    absdev = gsl.stats_absdev(rawa)
    expected = 0.0287571428571429
    check(absdev, expected, "stats_absdev")

    skew = gsl.stats_skew(rawa)
    expected = 0.0954642051479004
    check(skew, expected, "stats_skew")

    kurt = gsl.stats_kurtosis(rawa)
    expected = -1.38583851548909
    check(kurt, expected, "stats_kurtosis")

end

stats_tests()
print 'Ok'