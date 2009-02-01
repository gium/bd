#ifndef CONVO_HH
# define CONVO_HH

# include "core/image.hh"

using namespace bd;

Image<unsigned> contours(image& im);
image blur(Image<bool>& bubble, image& im);

#endif // !CONVO_HH
