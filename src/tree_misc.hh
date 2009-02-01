#ifndef TREE_MISC_HH
# define TREE_MISC_HH

#include <tree.hh>
#include <core/image.hh>

using namespace bd;

void truncate_tree(Tree* t);
void find_bubble(Tree* t, Image<unsigned>& img);
Image<bool>  mark_bubble(Tree* t, Image<unsigned>& img, image& origin);
void extend_mask(const Tree* t, const Image<unsigned>& contour, Image<bool>& bubble);
void print_bubble(image& im, Image<bool>& bubble);
Image<unsigned> distance(const Tree* t, Image<bool>& bubble, image& img);
void create_final_image(const Tree* t, Image<bool>& bubble,
			image& img, Image<unsigned>& dist);


#endif // !TREE_MISC_HH
