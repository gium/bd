#include <tree_misc.hh>
#include <queue>
#include <stack>
#include <list>
#include "boost/tuple/tuple.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace
{
  struct RemoveNoChild
  {
    bool operator()(Tree* t)
    {
      return t->no_child();
    }
  };

  class FindBubble
  {
  public:
    FindBubble(Image<unsigned>& img)
      : img_(img)
    {
      mark_ = new Image<bool>(img.width_get(), img.height_get(), false);
    }

    ~FindBubble()
    {
      // delete mark_;
    }

    bool operator()(Tree* t)
    {
      unsigned pos_x, pos_y;
      boost::tie(pos_x, pos_y) = t->point_;
      if ((*mark_)[pos_y][pos_x])
	return true;

      std::queue<std::pair<unsigned, unsigned> > queue;
      queue.push(std::make_pair(pos_x, pos_y));

      while (!queue.empty())
      {
	int x, y;
	boost::tie(x, y) = queue.front();
	queue.pop();

	if (x < 0 || y < 0 || (unsigned) x >= img_.width_get()
	    || (unsigned) y >= img_.height_get()
	    || (*mark_)[y][x] || img_[y][x] != 255)
	  continue;


	(*mark_)[y][x] = true;
	queue.push(std::make_pair(x + 1, y));
	queue.push(std::make_pair(x - 1, y));
	queue.push(std::make_pair(x, y + 1));
	queue.push(std::make_pair(x, y - 1));
      }

      return false;
    }

  private:
    Image<unsigned>& img_;
    Image<bool>* mark_;
  };
} // anonymous

void truncate_tree(Tree* t)
{
  Tree::ltree* childs = t->childs_get();
  RemoveNoChild r;
  childs->remove_if(r);
}

void find_bubble(Tree* t, Image<unsigned>& img)
{
  Tree::ltree* childs = t->childs_get();
  FindBubble f(img);
  (void) childs;

  for (Tree::ltree::iterator it = childs->begin(); it != childs->end(); ++it)
    (*it)->childs_get()->remove_if(f);
}

Image<bool> mark_bubble(Tree* t, Image<unsigned>& img, image& origin)
{
  (void) origin;
  Tree::ltree* childs = t->childs_get();
  Image<bool> mark = Image<bool>(img.width_get(), img.height_get(), false);

  for (Tree::ltree::iterator it = childs->begin(); it != childs->end(); ++it)
  {
    Tree::ltree* subchild = (*it)->childs_get();
    for (Tree::ltree::iterator it2 = subchild->begin(); it2 != subchild->end(); ++it2)
    {
      unsigned pos_x, pos_y;
      boost::tie(pos_x, pos_y) = (*it2)->point_;

      std::queue<std::pair<unsigned, unsigned> > queue;
      queue.push(std::make_pair(pos_x, pos_y));

      while (!queue.empty())
      {
	int x, y;
	boost::tie(x, y) = queue.front();
	queue.pop();

	if (x < 0 || y < 0 || (unsigned) x >= img.width_get()
	    || (unsigned) y >= img.height_get())
	  continue;


	if (mark[y][x] || img[y][x] != 255)
	  continue;

	mark[y][x] = true;

	queue.push(std::make_pair(x + 1, y));
	queue.push(std::make_pair(x - 1, y));
	queue.push(std::make_pair(x, y + 1));
	queue.push(std::make_pair(x, y - 1));
      }

    }
  }

  return mark;
}

void extend_mask(const Tree* t, const Image<unsigned>& contour, Image<bool>& bubble)
{
  Tree::ltree* childs = t->childs_get();
  Image<bool> sbub = bubble.clone();

  for (Tree::ltree::iterator it = childs->begin(); it != childs->end(); ++it)
  {
    Tree::ltree* subchild = (*it)->childs_get();

    for (Tree::ltree::iterator it2 = subchild->begin(); it2 != subchild->end(); ++it2)
    {
      Image<bool> mark(contour.width_get(), contour.height_get(), false);

      unsigned pos_x, pos_y;
      boost::tie(pos_x, pos_y) = (*it2)->point_;

      std::queue<std::pair<unsigned, unsigned> > queue;
      queue.push(std::make_pair(pos_x, pos_y));

      while (!queue.empty())
      {
	int x, y;
	boost::tie(x, y) = queue.front();
	queue.pop();

	if ((unsigned) x < (*it)->from_.first ||
	    (unsigned) y < (*it)->from_.second ||
	    (unsigned) x >= (*it)->to_.first
	    || (unsigned) y >= (*it)->to_.second)
	  continue;

	if (mark[y][x] || !sbub[y][x])
	{
	  bubble[y][x] = true;
	  mark[y][x] = true;
	  unsigned i = 0;
	  while (y + ++i < (*it)->to_.second && i < 3)
	    bubble[y][x+i] = true;

	  i = 0;
	  while (y - ++i >= (*it)->from_.second && i < 3)
	    bubble[y][x-i] = true;

	  i = 0;
	  while (x + ++i < (*it)->to_.first && i < 3)
	    bubble[y+i][x] = true;

	  i = 0;
	  while (x - ++i >= (*it)->from_.first && i < 3)
	    bubble[y-i][x] = true;

	  continue;
	}

	mark[y][x] = true;

	queue.push(std::make_pair(x + 1, y));
	queue.push(std::make_pair(x - 1, y));
	queue.push(std::make_pair(x, y + 1));
	queue.push(std::make_pair(x, y - 1));
      }
    }
  }
}

void print_bubble(image& im, Image<bool>& bubble)
{
  unsigned blue[3] = {0, 0, 255};

  for (unsigned i = 0; i < im.height_get(); ++i)
    for (unsigned j = 0; j < im.width_get(); ++j)
      if (bubble[i][j])
	for (unsigned k = 0; k < 3; ++k)
	  im[i][j][k] = blue[k];
}

std::vector<unsigned char> operator+=(std::vector<unsigned char>& a,
				      std::vector<unsigned char>& b)
{
  for (unsigned i = 0; i < a.size(); ++i)
    a[i] += b[i];
  return a;
}

std::vector<unsigned char> operator/=(std::vector<unsigned char>& a, int b)
{
  for (unsigned i = 0; i < a.size(); ++i)
    a[i] /= b;
  return a;
}

template<typename A, typename B>
A operator+=(A& a,
	     B& b)
{
  for (unsigned i = 0; i < a.size(); ++i)
    a[i] += b[i];
  return a;
}


std::vector<unsigned> operator/=(std::vector<unsigned>& a, int b)
{
  if (b == 0)
    b = 1;
  for (unsigned i = 0; i < a.size(); ++i)
    a[i] /= b;
  return a;
}

std::vector<unsigned> operator-(std::vector<unsigned char>& a,
				std::vector<unsigned char>& b)
{
  std::vector<unsigned> res;
  for (unsigned i = 0; i < 3; ++i)
    res.push_back(a[i] - b[i]);
  return res;
}

std::vector<unsigned> operator*(std::vector<unsigned>& a,
				std::vector<unsigned>& b)
{
  std::vector<unsigned> res;
  for (unsigned i = 0; i < 3; ++i)
    res.push_back(a[i] * b[i]);
  return res;
}

void green(std::vector<unsigned char>& px)
{
  px[0] = 0;
  px[1] = 255;
  px[2] = 0;
}

void color(std::vector<unsigned char>& px)
{
  px[0] = 0;
  px[1] = 255;
  px[2] = 255;
}

void red(std::vector<unsigned char>& px)
{
  px[0] = 255;
  px[1] = 0;
  px[2] = 0;
}

void blue(std::vector<unsigned char>& px)
{
  px[0] = 0;
  px[1] = 0;
  px[2] = 255;
}

Image<unsigned> distance(const Tree* t, Image<bool>& bubble, image& img)
{
  Tree::ltree* childs = t->childs_get();
  Image<unsigned> dist(bubble.width_get(), bubble.height_get(),
		       bubble.height_get() * bubble.width_get());
  Image<bool> mark(bubble.width_get(), bubble.height_get(), false);

  for (Tree::ltree::iterator it = childs->begin(); it != childs->end(); ++it)
  {
    Tree::ltree* subchild = (*it)->childs_get();

    for (Tree::ltree::iterator it2 = subchild->begin(); it2 != subchild->end(); ++it2)
    {

      unsigned pos_x, pos_y;
      boost::tie(pos_x, pos_y) = (*it2)->point_;

      std::queue<std::pair<unsigned, unsigned> > queue;
      std::stack<std::pair<unsigned, unsigned> > stack;
      queue.push(std::make_pair(pos_x, pos_y));

      std::vector<unsigned> b_mean(3, 0);
      std::vector<unsigned char> border_mean(3, 0);
      unsigned nb_border = 0;
      typedef std::list<std::vector<unsigned char> > list_px;
      list_px border_list;

      while (!queue.empty())
      {
	int x, y;
	boost::tie(x, y) = queue.front();
	queue.pop();

	if ((unsigned) x < (*it)->from_.first + 2 ||
	    (unsigned) y < (*it)->from_.second + 2||
	    (unsigned) x >= (*it)->to_.first - 2
	    || (unsigned) y >= (*it)->to_.second - 2)
	  continue;

	if (mark[y][x] || !bubble[y][x])
	{
	  if (!mark[y][x])
	  {
	    mark[y][x] = true;
	    dist[y][x] = 1;
	    b_mean += img[y][x];
	    ++nb_border;
	    border_list.push_front(img[y][x]);
	  }
	  continue;
	}

	mark[y][x] = true;

	stack.push(std::make_pair(x, y));

	queue.push(std::make_pair(x + 1, y));
	queue.push(std::make_pair(x - 1, y));
	queue.push(std::make_pair(x, y + 1));
	queue.push(std::make_pair(x, y - 1));
      }

      b_mean /= nb_border;

      border_mean[0] = (b_mean[0]);
      border_mean[1] = (b_mean[1]);
      border_mean[2] = (b_mean[2]);

      // stddev
      bool uni = false;
      {
	std::vector<unsigned> stddev(3, 0);
	for (list_px::iterator it = border_list.begin();
	     it != border_list.end();
	     ++it)
	{
	  std::vector<unsigned> r = (*it) - border_mean;
	  r = (r * r);
	  stddev += r;
	}
	float res = stddev[0] + stddev[1] + stddev[2];
	res = sqrt(res / nb_border);
	if (res < 50)
	  uni = true;
      }

      while (!stack.empty())
      {
	int x, y;
	boost::tie(x, y) = stack.top();
	stack.pop();

	dist[y][x] = std::min(std::min(std::min(dist[y][x], dist[y][x + 1]),
				       std::min(dist[y][x - 1], dist[y + 1][x])),
			      dist[y - 1][x]) + 1;

	(void) img;
	bool done = true;
 	dist[y][x] = 0;

	if (uni)
	  img[y][x] = border_mean;
	else
	  do
	  {
	    done = true;

	    if (y+dist[y][x] < (*it)->to_.second - 2 && !bubble[y+dist[y][x]][x])
	    {
	      img[y][x] = img[y+dist[y][x]][x];
	    }
	    else
	      if ((unsigned) y > dist[y][x] &&
		  y-dist[y][x] >= (*it)->from_.second + 2 &&
		  !bubble[y-dist[y][x]][x])
	      {
		img[y][x] = img[y-dist[y][x]][x];
	      }
	      else
		if (x+dist[y][x] < (*it)->to_.first - 2 && !bubble[y][x+dist[y][x]])
		{
		  img[y][x] = img[y][x+dist[y][x]];
		}
		else
		  if ((unsigned) x > dist[y][x] &&
		      x-dist[y][x] >= (*it)->from_.first - 2 &&
		      !bubble[y][x-dist[y][x]])
		  {
		    img[y][x] = img[y][x-dist[y][x]];
		  }
		  else
		  {
		    done = false;
		    ++dist[y][x];
		  }
	  } while (!done);
      }
    }
  }

  return dist;
}

void create_final_image(const Tree* t, Image<bool>& bubble,
			image& img, Image<unsigned>& dist)
{
  Tree::ltree* childs = t->childs_get();
  Image<bool> mark(bubble.width_get(), bubble.height_get(), false);

  for (Tree::ltree::iterator it = childs->begin(); it != childs->end(); ++it)
  {
    Tree::ltree* subchild = (*it)->childs_get();

    for (Tree::ltree::iterator it2 = subchild->begin(); it2 != subchild->end(); ++it2)
    {

      unsigned pos_x, pos_y;
      boost::tie(pos_x, pos_y) = (*it2)->point_;

      std::queue<std::pair<unsigned, unsigned> > queue;
      queue.push(std::make_pair(pos_x, pos_y));

      while (!queue.empty())
      {
	int x, y;
	boost::tie(x, y) = queue.front();
	queue.pop();

	if ((unsigned) x < (*it)->from_.first ||
	    (unsigned) y < (*it)->from_.second ||
	    (unsigned) x >= (*it)->to_.first
	    || (unsigned) y >= (*it)->to_.second)
	  continue;

	if (mark[y][x] || !bubble[y][x])
	  continue;

	mark[y][x] = true;

	(void) img;
	(void) dist;

	if (dist[y][x] < (unsigned) y &&
	    (unsigned) y - dist[y][x] >= (*it)->from_.second &&
	    !bubble[y - dist[y][x]][x])
	  img[y][x] = img[y - dist[y][x]][x];
	else
	  if ((unsigned) y + dist[y][x] < (*it)->to_.second &&
	      !bubble[y + dist[y][x]][x])
	  {
	    img[y][x] = img[y + dist[y][x]][x];
	  }
	  else
	    if ((unsigned) x + dist[y][x] < (*it)->to_.first &&
		!bubble[y][x + dist[y][x]])
	      img[y][x] = img[y][x + dist[y][x]];

	    else
	      if (dist[y][x] < (unsigned) x &&
		  (unsigned) x - dist[y][x] >= (*it)->from_.first &&
		  !bubble[y][x - dist[y][x]])
		img[y][x] = img[y][x - dist[y][x]];
	queue.push(std::make_pair(x + 1, y));
	queue.push(std::make_pair(x - 1, y));
	queue.push(std::make_pair(x, y + 1));
	queue.push(std::make_pair(x, y - 1));
      }
    }
  }
}
