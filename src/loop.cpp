#include <iostream>

#include <list>
#include <functional>

class ActionList : public std::list<std::function<void(int)> >
{
public:
  ActionList& operator +=(std::function<void(int)> f)
  {
    this->push_back(f);
    return *this;
  }

  // deletion does not work with std::function, since it is not
  // equality comparable...
 //  ActionList& operator -=(std::function<void(int)> f)
//   {
//     // this->remove(f);
//     // this may work with deletions:
//     //https://coderwall.com/p/u4w9ra/implementing-signals-in-c-11
//     return *this;
//   }
};

class Loop
{
public:
  Loop(unsigned int repetitions) :
    counter_(0),
    repetitions_(repetitions)
  {
  }

  void reset()
  {
    counter_ = 0;
  }
  
  void run()
  {
    for (counter_ = 0; counter_ < repetitions_; ++counter_)
      {
	step(counter_);
      }
  }

  bool hasNextStep()
  {
    return counter_ < repetitions_;
  }

  void step()
  {
    step(counter_++);
  }
  
  ActionList preIterationActions;
  ActionList postIterationActions;
  
private:

  void step(unsigned int i)
  {
    firePreIterationActions(i);
    firePostIterationActions(i);
  }
  
  void firePreIterationActions(unsigned int i)
  {
    for (auto a : preIterationActions)
      a(i);
  }

  void firePostIterationActions(unsigned int i)
  {
    for (auto& a : postIterationActions)
      a(i);
  }
  
  unsigned int repetitions_;
  unsigned int counter_;
};

void preIterationGreet(unsigned int i)
{
  std::cout << "Hello pre iteration " << i << std::endl;
}

void postIterationGreet(unsigned int i)
{
  std::cout << "Hello post iteration " << i << std::endl;
}

int main(int argc, char** argv)
{
  Loop l(10);

  l.preIterationActions += preIterationGreet;
  l.postIterationActions += postIterationGreet;

  while (l.hasNextStep())
    {
      l.step();
    }
  
  return 0;
}
