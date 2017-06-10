#include <iostream>
#include <list>

template<typename T>
class mylist : public std::list<T>
{
public:
  mylist<T>& operator +=(T i)
  {
    this->push_back(i);
    return *this;
  }

  mylist<T>& operator -=(T i)
  {
    this->remove(i);
    return *this;
  }
};

int main(int argc, char** argv)
{
  mylist<std::string> l;

  l += "jan";
  l += "piet";
  for (const auto& i : l)
    std::cout << i << std::endl;

  l -= "jan";
  for (const auto& i : l)
    std::cout << i << std::endl;

  return 0;
}
