#ifndef CORE_LOAD_PPM_HH
# define CORE_LOAD_PPM_HH

#include "image.hh"
#include <vector>

namespace bd
{
  namespace io
  {
    namespace ppm
    {
      /*!
      ** Load a PPM image.
      */
      image load(const std::string& filename);
      image load(char const* filename);
    }
  }
}
#endif
