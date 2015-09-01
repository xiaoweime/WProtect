#include <stdio.h>
#include "AsmJit.h"
#include <MyString.h>
#include "AsmJitEnlarge.h"


GPReg  text_to_reg(char * src){
  strupr( src );
  for ( int i = 0; i < 8*5; i++ ) {
    if (strcmp( src, ia86_reg[ i ] ) == 0)
    {
      return jit_reg[ i ];
    }
  }
  
}
