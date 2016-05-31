/*
defines numpy boost array types used
*/
#pragma once

#include <vector>

#include <boost/range.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm.hpp>

#include <python.h>

#include "numpy_boost_python.hpp"


// make ndarray subclass of numpy_boost?
template <typename T, int N=1>
using ndarray = numpy_boost<T, N>;


// extension method for ndarray; should be a method on class
template<typename range_t>
auto ndarray_from_range(const range_t input) {
    typedef typename boost::range_value<range_t>::type element_t;
    std::vector<element_t> tmp;
    for (element_t e : input)
        tmp.push_back(e);
    ndarray<element_t> output({(int)tmp.size()});
    boost::copy(tmp, output.begin());
    return output;
}


// ugly hack apparently required to init the numpy C API
#if PY_MAJOR_VERSION >= 3
int
#else
void
#endif
init_numpy()
{
import_array();
}