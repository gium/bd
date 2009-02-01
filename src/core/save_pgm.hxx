
#include <math.h>
#include <iostream>
#include <fstream>
#include <cassert>

namespace bd
{
  namespace io
  {
    namespace pgm
    {
      void save(const cov_matrix& img, char const* filename)
      {
	return save(img, std::string(filename));
      }


      template <typename T>
      void save(const Image<T>& img, const std::string& filename)
      {
	std::ofstream stream(filename.c_str ());

	if (!stream.is_open())
	  throw std::string("Unable to open the file");

	stream << "P5" << std::endl;
	stream << img.width_get() << " " << img.height_get() << std::endl;
	stream << 255 << std::endl;

	for (unsigned i = 0; i < img.height_get(); ++i)
	{
	  for (unsigned j = 0; j < img.width_get(); ++j)
	  {
	    float res = 0;
	    for (unsigned k = 0; k < 3; ++k)
	      res += img[i][j][k];
	    char c = res / 3;
	    stream.write(&c, 1);
	  }
	}

	stream.close();
      }

      template <>
      void save(const Image<unsigned>& img, const std::string& filename)
      {
	std::ofstream stream(filename.c_str ());

	if (!stream.is_open())
	  throw std::string("Unable to open the file");

	stream << "P5" << std::endl;
	stream << img.width_get() << " " << img.height_get() << std::endl;
	stream << 255 << std::endl;

	for (unsigned i = 0; i < img.height_get(); ++i)
	{
	  for (unsigned j = 0; j < img.width_get(); ++j)
	  {
	    char c = img[i][j];
	    stream.write(&c, 1);
	  }
	}

	stream.close();
      }

      template <>
      void save<std::vector<std::vector<float> > >
      (const cov_matrix& img, const std::string& filename)
      {
	std::ofstream stream(filename.c_str ());

	if (!stream.is_open())
	  throw std::string("Unable to open the file");

	stream << "P5" << std::endl;
	stream << img.width_get() << " " << img.height_get() << std::endl;
	stream << 255 << std::endl;

	for (unsigned i = 0; i < img.height_get(); ++i)
	{
	  for (unsigned j = 0; j < img.width_get(); ++j)
	  {
	    float res =
	      sqrt(img[i][j][0][0]) +
	      sqrt(img[i][j][1][1]) +
	      sqrt(img[i][j][2][2]);
	    char c = (res / 3) * 2;
	    stream.write(&c, 1);
	  }
	}

	stream.close();
      }
    }
  }
}
