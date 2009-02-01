#include <cassert>
#include <iostream>

namespace bd
{

  template <typename P>
  Image<P>::Image()
    : ref_(new int(0))
  {
  }

  template <typename P>
  Image<P>::Image(unsigned width, unsigned height, P init_val)
    : ref_(new int(1)), width_(width), height_(height)
  {
    data_ = new std::vector<std::vector<P> >
      (height, std::vector<P>(width, init_val));
  }

  template <typename P>
  Image<P>::Image(unsigned width, unsigned height)
    : ref_(new int(1)), width_(width), height_(height)
  {
    data_ = new std::vector<std::vector<P> >
      (height, std::vector<P>(width));
  }

  template <typename P>
  Image<P>::Image(const Image<P>& o)
    // : ref_(o.ref_), width_(o.width_), height_(o.height_),
    //   data_(o.data_)
  {
    if (&o != this)
    {
      --(*ref_);      
      if (*ref_ == 0)
      {
	delete data_;
	delete ref_;
      }

      width_ = o.width_;
      height_ = o.height_;
      data_ = o.data_;
      ref_ = o.ref_;
      ++(*ref_);
    }
  }

  template <typename P>
  Image<P> Image<P>::clone()
  {
    Image<P> i(width_, height_);
    *(i.data_) = *data_;

    return i;
  }

  template <typename P>
  Image<P>::~Image()
  {
    --(*ref_);

    if (*ref_ == 0)
    {
      delete data_;
      delete ref_;
    }
  }

  template <typename P>
  Image<P>&
  Image<P>::operator=(const Image<P>& o)
  {
    if (&o != this)
    {
      --(*ref_);      
      if (*ref_ == 0)
      {
	delete data_;
	delete ref_;
      }

      width_ = o.width_;
      height_ = o.height_;
      data_ = o.data_;
      ref_ = o.ref_;
      ++(*ref_);
    }

    return *this;
  }


  template <typename P>
  inline
  const typename std::vector<P>&
  Image<P>::operator[](size_t pos) const
  {
    assert(pos < height_);
    return (*data_)[pos];
  }

  template <typename P>
  inline
  typename std::vector<P>&
  Image<P>::operator[](size_t pos)
  {
    assert(pos < height_);
    return (*data_)[pos];
  }

  template <typename P>
  inline
  unsigned
  Image<P>::width_get() const
  {
    return width_;
  }

  template <typename P>
  inline
  unsigned
  Image<P>::height_get() const
  {
    return height_;
  }

  template <typename P>
  inline
  int
  Image<P>::ref_get() const
  {
    return *ref_;
  }
}
