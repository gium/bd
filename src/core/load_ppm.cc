#include <iostream>
#include <fstream>
#include <cassert>
#include "load_ppm.hh"

namespace bd
{
  namespace io
  {
    namespace ppm
    {
      image load(char const* filename)
      {
	return load(std::string(filename));
      }

      image load(const std::string& filename)
      {
	std::ifstream stream(filename.c_str (), std::ios::binary | std::ios::in);

	if (!stream.is_open())
	  throw std::string("Unable to open the file");

	char magic[10];
	stream.read(magic, 2);
	magic[2] = 0;
	std::string magic_number = std::string(magic);

	if (magic_number != "P3" && magic_number != "P6")
	  throw std::string("Bad magic number " + magic_number);

	unsigned width;
	stream >> width;
	unsigned height;
	stream >> height;
	unsigned maxval;
	stream >> maxval;

	image img(width, height, std::vector<unsigned char>(3));

	char tmp;
	stream.get(tmp);
	if (magic_number == "P6")
	  for (unsigned i = 0; i < height; ++i)
	    for (unsigned j = 0; j < width; ++j)
	      for (int k = 0; k < 3; ++k)
		stream.get(reinterpret_cast<char&>(img[i][j][k]));
	else
	  for (unsigned i = 0; i < height; ++i)
	    for (unsigned j = 0; j < width; ++j)
	      for (int k = 0; k < 3; ++k)
		stream >> img[i][j][k];

	stream.close();
	return img;
      }
    }
  }
}
