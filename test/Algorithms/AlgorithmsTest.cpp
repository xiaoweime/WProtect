#include <iostream>
#include "AlgorithmsLibrary.h"

using namespace std;

int main()
{
  AlgorithmsLib lib;
  // lib.ror();
  lib.rand_encryption();
  
  //  lib.defuc(1);
  // cout << lib.defuc(1) << endl;
  cout << lib.defuc(1) << endl;
  cout << lib.enfuc(1) << endl;
  
  for (int i = 0 ; i < lib.encode_size ; i++)
  {
    //cout << lib.encode_buf[i] <<endl ;
    //   printf("%x\r\n",lib.encode_buf[i]);
  }

  for (int i = 0 ; i < lib.decode_size; i++)
  {
    //  printf("%x\r\n",lib.decode_buf[i]);
  }
  
  
  return 0;
}
