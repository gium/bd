#ifndef CORE_IMAGE_HH
# define CORE_IMAGE_HH

# include <vector>

namespace bd
{
  template <typename P>
  class Image
  {
  public:
    typedef P point;
    Image();
    Image(unsigned width, unsigned height, P init_val);
    Image(unsigned width, unsigned height);
    Image(const Image<P>& other);
    ~Image();
    Image<P>& operator=(const Image<P>& other);
    const std::vector<point>& operator[](size_t pos) const;
    std::vector<point>& operator[](size_t pos);
    unsigned width_get() const;
    int ref_get() const;
    unsigned height_get() const;
    Image<P> clone();
  private:
    int* ref_;
    unsigned width_;
    unsigned height_;
    std::vector<std::vector<point> >* data_;
  };

  typedef Image<std::vector<unsigned char> > image;

  typedef Image<std::vector<float> > mean_matrix;
  typedef Image<std::vector<std::vector<float> > > cov_matrix;
}

# include "image.hxx"

#endif	// CORE_IMAGE_HH
