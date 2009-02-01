#include <iostream>
#include <core/image.hh>
#include <core/load_pgm.hh>
#include <core/load_ppm.hh>
#include <core/save_pgm.hh>
#include <core/save_ppm.hh>
#include <core/squeletize.hh>
#include <gray.hh>
#include <build_tree.hh>
#include <tree_misc.hh>
#include <convo.hh>
// #include <stringstream>

using namespace bd;


int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    std::cerr << "usage: " << argv[0] << " image.ppm" << std::endl;
    return 1;
  }

  image img = io::ppm::load(argv[1]);
  image origin = img.clone();
  image origin2 = img.clone();

  Image<unsigned> im = (gray(img));
  im = squeletize(im);
  Tree* t = build_tree(im);
  truncate_tree(t);
  t->draw(im);
  find_bubble(t, im);
  t->print();
  Image<bool> mark =  mark_bubble(t, im, origin);
  Image<unsigned> contour = contours(origin2);
  extend_mask(t, contour, mark);
  Image<unsigned> dist = distance(t, mark, origin);
  // create_final_image(t, mark, origin, dist);
  // print_bubble(origin, mark);

  origin = blur(mark, origin);

  std::string outfilename = argv[1];
  outfilename = outfilename.substr(0, outfilename.length() - 4);
  outfilename += "_save.ppm";

  // io::pgm::save(im, "out.ppm");
  io::ppm::save(origin, outfilename);
  // io::pgm::save(contour, "contours.ppm");
}
