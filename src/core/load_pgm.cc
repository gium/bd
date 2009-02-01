#include <iostream>
#include <fstream>
#include <cassert>
#include "load_pgm.hh"

namespace bd
{
  namespace io
  {
    namespace pgm
    {
      image load(char const* filename)
      {
	return load(std::string(filename));
      }

      image load(const std::string& filename)
      {
	std::ifstream stream(filename.c_str ());

	if (!stream.is_open())
	  throw std::string("Unable to open the file");

	char magic[10];
	stream.read(magic, 2);
	magic[2] = 0;
	std::string magic_number = std::string(magic);

	if (magic_number != "P2" && magic_number != "P5")
	  throw std::string("Bad magic number " + magic_number);

	unsigned width;
	stream >> width;
	unsigned height;
	stream >> height;
	unsigned maxval;
	stream >> maxval;

	image img(width, height, std::vector<unsigned char>(3, 0));

	char tmp;
	stream.get(tmp);

	if (magic_number == "P5")
	  for (unsigned i = 0; i < height; ++i)
	    for (unsigned j = 0; j < width; ++j)
	    {
	      stream.get(reinterpret_cast<char&>(img[i][j][0]));
	      img[i][j][1] = img[i][j][2] = img[i][j][0];
	    }
	else
	  for (unsigned i = 0; i < height; ++i)
	    for (unsigned j = 0; j < width; ++j)
	    {
	      stream >> img[i][j][0];
	      img[i][j][1] = img[i][j][2] = img[i][j][0];
	    }

	stream.close();
	return img;
      }
    }
  }
}
