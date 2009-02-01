#include <core/image.hh>

using namespace bd;

template <class T>
Image<T> squeletize(Image<T>& im)
{
  const T limit = 70;
  Image<T> res = Image<T>(im.width_get(), im.height_get(), 255);

  for (unsigned i = 1; i < im.height_get() - 1; ++i)
    for (unsigned j = 1; j < im.width_get() - 1; ++j)
    {
      if (im[i][j] < limit)
	if (im[i + 1][j] < limit && im[i][j + 1] < limit &&
	    im[i - 1][j] < limit && im[i - 1][j] < limit)
	  res[i][j] = 0;
	else
	  res[i][j] = 0;
      else
	if (im[i][j] > 255 - (limit / 3))
	  res[i][j] = 255;
	else
	  res[i][j] = 0;
    }

  return res;
}
