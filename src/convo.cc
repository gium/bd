#include "convo.hh"
#include <cmath>

template <typename T>
T q(T a)
{
  return a * a;
}

static int dist(std::vector<unsigned char>& a, std::vector<unsigned  char>& b)
{
  return sqrt(q(a[0]-b[0]) + q(a[1]-b[1]) + q(a[2]-b[2]));
}

Image<unsigned> contours(image& im)
{
  Image<unsigned> img(im.width_get(), im.height_get());
  int bb = 15;
  for (unsigned i = 1; i < im.width_get(); ++i)
    for (unsigned j = 1; j < im.height_get(); ++j)
    {
      if (dist(im[j][i], im[j - 1][i]) >= bb ||
	  dist(im[j][i], im[j][i - 1]) >= bb)
	img[j][i] = 0;
      else
	img[j][i] = 255;
    }

  return img;
}

image blur(Image<bool>& bubble, image& im)
{
  float mat[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
  std::vector<unsigned> white(3, 255);
  std::vector<unsigned> black(3, 0);

  image img = im.clone();

  int sum_mat = 0;
  for (unsigned i = 0; i < 3; ++i)
    for (unsigned j = 0; j < 3; ++j)
      sum_mat += mat[i][j];

  std::cout << sum_mat << std::endl;

  if (sum_mat == 0)
    sum_mat = 1;

  for (unsigned i = 1; i < im.height_get() - 1; ++i)
    for (unsigned j = 1; j < im.width_get() - 1; ++j)
    {
      if (!bubble[i][j])
	continue;

      std::vector<float> sum(3, 0);
      for (int k = -1; k < 2; ++k)
	for (int l = -1; l < 2; ++l)
	{
	  sum[0] += mat[k + 1][l + 1] * im[(unsigned) (k + (int) i)][(unsigned) (l + (int) j)][0];
	  sum[1] += mat[k + 1][l + 1] * im[(unsigned) (k + (int) i)][(unsigned) (l + (int) j)][1];
	  sum[2] += mat[k + 1][l + 1] * im[(unsigned) (k + (int) i)][(unsigned) (l + (int) j)][2];
	}

      for (unsigned k = 0; k < 3; ++k)
      {
	// std::cout << sum[k] << " ";
	if (sum[k] != 0)
	  sum[k] /= (sum_mat);
	// std::cout << sum[k] << std::endl;
	img[i][j][k] = sum[k];
      }
    }

  for (unsigned i = 0; i < im.height_get(); ++i)
    for (unsigned j = 0; j < 3; ++j)
      img[i][0][j] = img[i][im.width_get() - 1][j] = white[j];

  for (unsigned i = 0; i < im.width_get(); ++i)
    for (unsigned j = 0; j < 3; ++j)
      img[0][i][j] = img[im.height_get() - 1][i][j] = white[j];

  return img;
}
