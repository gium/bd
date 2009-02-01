#ifndef TREE_HH
# define TREE_HH

# include <list>
# include <ios>
# include <core/image.hh>

class Tree
{
public:
  typedef std::list<Tree*> ltree;
  Tree(unsigned width, unsigned height)
    : childs_(new ltree()), from_(std::make_pair(0, 0)),
      to_(std::make_pair(width, height))
  {
  }

  Tree(unsigned from_x, unsigned from_y,
       unsigned to_x, unsigned to_y,
       unsigned point_x, unsigned point_y)
    : childs_(new ltree()),
      from_(std::make_pair(from_x, from_y)),
      to_(std::make_pair(to_x, to_y)),
      point_(std::make_pair(point_x, point_y))
  {
  }

  ~Tree();
  void add(Tree* t);
  void print();
  void print(std::string ws);
  void draw(bd::Image<unsigned>& im);
  void draw(bd::Image<unsigned>& im, unsigned);
  bool no_child();
  ltree* childs_get() const;
private:
  ltree* childs_;
public:				// By laziness
  std::pair<unsigned, unsigned> from_;
  std::pair<unsigned, unsigned> to_;
  std::pair<unsigned, unsigned> point_;
private:
  bool in(std::pair<unsigned, unsigned> val,
	  std::pair<unsigned, unsigned> from,
	  std::pair<unsigned, unsigned> to);
};

#endif	// TREE_HH
