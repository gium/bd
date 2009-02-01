#ifndef CORE_LOAD_PGM_HH
# define CORE_LOAD_PGM_HH

#include "image.hh"
#include <vector>

namespace bd
{
  namespace io
  {
    namespace pgm
    {
      /*!
      ** Load a PGM image.
      */
      image load(const std::string& filename);
      image load(char const* filename);
    }
  }
}
#endif
