#ifndef CORE_SAVE_PGM_HH
# define CORE_SAVE_PGM_HH

#include "image.hh"

namespace bd
{
  namespace io
  {
    namespace pgm
    {
      template <typename T>
      void save(const Image<T>& img, const std::string& filename);

      template <>
      void save<std::vector<std::vector<float> > >
      (const cov_matrix& img, const std::string& filename);
    }
  }
}

# include "save_pgm.hxx"

#endif
