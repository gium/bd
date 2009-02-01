#include <build_tree.hh>
#include <queue>
#include "boost/tuple/tuple.hpp"

using namespace bd;

void search(Tree* tree, Image<bool>& mark, Image<unsigned>& img,
	    unsigned pos_x, unsigned pos_y)
{
  std::queue<std::pair<unsigned, unsigned> > queue;
  queue.push(std::make_pair(pos_x, pos_y));

  int from_x = pos_x;
  int to_x = pos_x;
  int from_y = pos_y;
  int to_y = pos_y;

  while (!queue.empty())
  {
    int x, y;
    boost::tie(x, y) = queue.front();
    queue.pop();

    if (x < 0 || y < 0 || (unsigned) x >= img.width_get()
	|| (unsigned) y >= img.height_get()
	|| mark[y][x] || img[y][x] != 0)
      continue;

    if (x < from_x) from_x = x;
    if (x > to_x) to_x = x;
    if (y < from_y) from_y = y;
    if (y > to_y) to_y = y;

    mark[y][x] = true;
    queue.push(std::make_pair(x + 1, y));
    queue.push(std::make_pair(x - 1, y));
    queue.push(std::make_pair(x, y + 1));
    queue.push(std::make_pair(x, y - 1));
  }

  //   to_x << " " << to_y << " " << pos_x << " " <<
  //   pos_y << std::endl;


  if (from_x != to_x && from_y != to_y)
    tree->add(new Tree(from_x, from_y, to_x, to_y, pos_x, pos_y));
}

Tree* build_tree(Image<unsigned>& img)
{
  Image<bool>* mark = new Image<bool>(img.width_get(),
				     img.height_get(), false);

  Tree* tree = new Tree(img.width_get(), img.height_get());

  // tree->print();

  for (unsigned i = 0; i < img.height_get(); ++i)
  for (unsigned j = 0; j < img.width_get(); ++j)
  {
    if (img[i][j] == 0 && (*mark)[i][j] == false)
    {

      search(tree, *mark, img, j, i);

      // tree->print();
    }
  }

  delete mark;
  return tree;
}
