#include <core/image.hh>
#include <gray.hh>

using namespace bd;

Image<unsigned> gray(image& img)
{
  Image<unsigned> gr =
    Image<unsigned>(img.width_get(), img.height_get());

  for (unsigned i = 0; i < img.height_get(); ++i)
  for (unsigned j = 0; j < img.width_get(); ++j)
    gr[i][j] = (img[i][j][0] + img[i][j][1] + img[i][j][2]) / 3;

  return gr;
}
