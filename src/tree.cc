#include <tree.hh>
#include <iostream>

void rectangle(bd::Image<unsigned>& im, unsigned fx, unsigned fy,
	       unsigned tx, unsigned ty, unsigned color)
{
  for (unsigned i = fy; i <= ty; ++i)
    for (unsigned j = fx; j <= tx; ++j)
      im[i][j] = color;
}

Tree::~Tree()
{
  for (ltree::iterator i = childs_->begin(); i != childs_->end(); ++i)
    delete *i;
  delete childs_;
}

void Tree::add(Tree* t)
{
  for (ltree::iterator i = childs_->begin(); i != childs_->end(); ++i)
  {
    if (in(t->from_, (*i)->from_, (*i)->to_) &&
	in(t->to_, (*i)->from_, (*i)->to_))
    {
      (*i)->add(t);
      return;
    }
  }
  childs_->push_front(t);
}

void Tree::print()
{
  std::cout << "print"<< std::endl;
  std::cout << "(" << from_.first << ", "
	    << from_.second << ") (" << to_.first << ", "
	    << to_.second << ")" << std::endl;

  for (ltree::iterator i = childs_->begin(); i != childs_->end(); ++i)
  {
    (*i)->print(std::string("  "));
  }
}

void Tree::print(std::string ws)
{
  std::cout << ws << "(" << from_.first << ", "
	    << from_.second << ") (" << to_.first << ", "
	    << to_.second << ")" << std::endl;

  for (ltree::iterator i = childs_->begin(); i != childs_->end(); ++i)
  {
    (*i)->print(ws + "  ");
  }
}

void Tree::draw(bd::Image<unsigned>& im)
{
  for (ltree::iterator i = childs_->begin(); i != childs_->end(); ++i)
  {
    (*i)->draw(im, 1);
  }
}

void Tree::draw(bd::Image<unsigned>& im, unsigned level)
{

  // 	    << from_.second << ") (" << to_.first << ", "
  // 	    << to_.second << ")" << std::endl;

  if (level == 2)
    rectangle(im, from_.first, from_.second, to_.first,
	      to_.second, 255);

  for (ltree::iterator i = childs_->begin(); i != childs_->end(); ++i)
  {
    (*i)->draw(im, level + 1);
  }
}

bool Tree::no_child()
{
  return childs_->empty();
}

Tree::ltree* Tree::childs_get() const
{
  return childs_;
}

// private

bool Tree::in(std::pair<unsigned, unsigned> val,
	      std::pair<unsigned, unsigned> from,
	      std::pair<unsigned, unsigned> to)
{
  return from.first <= val.first && val.first <= to.first
    && from.second <= val.second && val.second <= to.second;
}
