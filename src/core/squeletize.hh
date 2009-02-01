#ifndef CORE_SQUELETIZE_HH
# define CORE_SQUELETIZE_HH

#include <core/image.hh>

using namespace bd;

template <class T>
Image<T> squeletize(Image<T>& im);

#include "squeletize.cc"

#endif
