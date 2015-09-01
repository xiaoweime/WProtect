#include "AInterface.hpp"

AInterface::AInterface()
{
}

AInterface::~AInterface()
{
}

typedef Algorithms (AInterface::*r_fuc)(long);
typedef long (*MyFn)(long);

/*
Algorithms AInterface::b_add(long _key)
{
  using namespace AsmJit;
  Algorithms a;
  Compiler c;
  c.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<char,char>());
  c.add(_key,c.argGP(0));
  c.ret(_key);
  c.endFunction();
  compiler_list.push_back(c);
  a.Decryption = function_cast<MyFn>compiler_list.back().make();
  a.Encryption.add(nbx,_key);
  a.type = 1;
  return a;
  }*/
Algorithms AInterface::b_add(long _key)
  {
  }


Algorithms AInterface::w_add()
{
}

Algorithms AInterface::d_add()
{
}

Algorithms AInterface::random_algorithms()
{
  r_fuc algorithms_array[]=
    {
      &AInterface::b_add
    }
  int count = sizeof(algorithms_array) / sizeof(Algorithms);
  int r = rand()%count;
  r_fuc fuc;
  fuc = algorithms_array[r];
  return (this->*fuc)(rand());
}
