#ifndef CORE_SAVE_PPM_HH
# define CORE_SAVE_PPM_HH

# include <string>
# include "image.hh"

namespace bd
{
  namespace io
  {
    namespace ppm
    {
      template <typename T>
      void save(const Image<T>& img, const std::string& filename);
      template <typename T>
      void save(const Image<T>& img, char const* filename);
    }
  }
}

# include "save_ppm.hxx"
#endif
