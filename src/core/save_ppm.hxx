#include <iostream>
#include <fstream>
#include <cassert>

namespace bd
{
  namespace io
  {
    namespace ppm
    {
      template <typename T>
      void save(const Image<T>& img, char const* filename)
      {
	return save(img, std::string(filename));
      }

      template <typename T>
      void save(const Image<T>& img, const std::string& filename)
      {
	std::ofstream stream(filename.c_str ());

	if (!stream.is_open())
	  throw std::string("Unable to open the file");

	stream << "P6" << std::endl;
	stream << img.width_get() << " " << img.height_get() << std::endl;
	stream << 255 << std::endl;
	char c;
	for (unsigned i = 0; i < img.height_get(); ++i)
	  for (unsigned j = 0; j < img.width_get(); ++j)
	    for (int k = 0; k < 3; ++k)
	    {
	      c = img[i][j][k];
	      stream.write(reinterpret_cast<char*>(&c), 1);
	    }
	stream.close();
      }
    }
  }
}
