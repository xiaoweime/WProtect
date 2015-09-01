#include "AlgorithmsLibrary.h"
#include <stdio.h>
#include <time.h>
#include <WProtectConfig.h>
#include <string>

using namespace AsmJit;

AlgorithmsLib::AlgorithmsLib()
{
  srand((int)time(0));
}

AlgorithmsLib::~AlgorithmsLib()
{
}

void AlgorithmsLib::rand_encryption()
{
  typedef void (AlgorithmsLib::*en_fuc)();
  //en_fuc tst=shr;
  int count = 7;
  en_fuc en_fuc_array[]=
    {
      &AlgorithmsLib::_shr,&AlgorithmsLib::_shl,
      &AlgorithmsLib::_ror,&AlgorithmsLib::_rol,
      &AlgorithmsLib::_add,//&AlgorithmsLib::_sub,
      &AlgorithmsLib::_not,&AlgorithmsLib::_neg
    };
  
    en_fuc rand_fuc = en_fuc_array[wrand(0,count)];

   (this->*rand_fuc)();
  
  
  /*  en_fuc en_fuc_array[]=
    {
      shr,shl,ror,rol,add,sub,_not,neg
      }*/
  
}


void AlgorithmsLib::_shr()
{
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);

  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>()); //加密
  {
    GPVar num(en.argGP(0));

    en.shr(num,imm(key));
    en.ret(num);
    Assembler a;
#ifdef PROTECT_X64
    a.shr(rax,key);
#else
    a.shr(eax,key);
#endif
    encode_size = a.getCodeSize();
    memcpy(encode_buf,a.getCode(),encode_size);
    
  }
  en.endFunction();
  enfuc = (int(*)(int))en.make();
  
  de.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>());
  {
    GPVar num(de.argGP(0));
    de.shl(num,imm(key));
    de.ret(num);
    Assembler a;
#ifdef PROTECT_X64
    a.shl(rax,key);
#else
    a.shl(eax,key);
#endif
    decode_size = a.getCodeSize();
    memcpy(decode_buf,a.getCode(),decode_size);
  }
  de.endFunction();
  defuc = (int(*)(int))de.make();
}


void AlgorithmsLib::_shl()
{
  de.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>()); //加密
  {
    GPVar num(de.argGP(0));
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
    de.shr(num,imm(key));
    de.ret(num);
    Assembler a;
    a.shr(eax,key);
    encode_size = a.getCodeSize();
    memcpy(encode_buf,a.getCode(),encode_size);
    
  }
  de.endFunction();
  defuc = (int(*)(int))de.make();
    
  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>());
  {
    GPVar num(en.argGP(0));
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
    en.shl(num,imm(key));
    en.ret(num);
    Assembler a;
#ifdef PROTECT_X64
    a.shl(rax,key);
#else
    a.shl(eax,key);
#endif
    decode_size = a.getCodeSize();
    memcpy(decode_buf,a.getCode(),decode_size);
  }
  en.endFunction();
  enfuc = (int(*)(int))en.make();
}

void AlgorithmsLib::_ror()
{
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>()); //加密
  {
    GPVar num(en.argGP(0));

    en.ror(num,imm(key));
    
    en.ret(num);
    
    Assembler a;
#ifdef PROTECT_X64
    a.ror(rax,key);
#else
    a.ror(eax,key);
#endif
    //encode_buf = a.getCode();
    encode_size = a.getCodeSize();
    memcpy(encode_buf,a.getCode(),encode_size);
    
  }
  en.endFunction();

  enfuc = (int(*)(int))en.make();

  de.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>());
  {
    GPVar num(de.argGP(0));

    de.rol(num,imm(key));
    de.ret(num);

    Assembler a;
#ifdef PROTECT_X64
    a.rol(rax,key);
#else
    a.rol(eax,key);
#endif
    //decode_buf = a.getCode();
    decode_size = a.getCodeSize();
    memcpy(decode_buf,a.getCode(),decode_size);
    
  }
  de.endFunction();

  defuc = (int(*)(int))de.make();
}

void AlgorithmsLib::_rol()
{
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
  de.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>()); //加密
  {
    GPVar num(de.argGP(0));

    en.ror(num,imm(key));
    
    en.ret(num);
    
    Assembler a;
#ifdef PROTECT_X64
    a.ror(rax,key);
#else
    a.ror(eax,key);
#endif
    //encode_buf = a.getCode();
    decode_size = a.getCodeSize();
    memcpy(decode_buf,a.getCode(),decode_size);
    
  }
  de.endFunction();

  defuc = (int (*)(int))de.make();

  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>());
  {
    GPVar num(en.argGP(0));

    en.rol(num,imm(key));
    en.ret(num);

    Assembler a;
#ifdef PROTECT_X64
    a.rol(rax,key);
#else
    a.rol(eax,key);
#endif
    //decode_buf = a.getCode();
    encode_size = a.getCodeSize();
    memcpy(encode_buf,a.getCode(),encode_size);
    
  }
  en.endFunction();

  enfuc = (int(*)(int))en.make();
}

void AlgorithmsLib::_not()
{
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>()); //加密
  {
    GPVar num(en.argGP(0));

    en.not_(num);
    
    en.ret(num);
    
    Assembler a;
#ifdef PROTECT_X64
    a.not_(rax);
#else
    a.not_(eax);
#endif
    //encode_buf = a.getCode();
    encode_size = a.getCodeSize();
    decode_size = encode_size;
    memcpy(encode_buf,a.getCode(),encode_size);
    memcpy(decode_buf,a.getCode(),decode_size);
  }
  en.endFunction();

  enfuc = (int(*)(int))en.make();
  defuc = (int(*)(int))en.make();
 }

void AlgorithmsLib::_neg()
{
  int mode = 32;
#ifdef PROTECT_X64
  mode = 64;
#endif
  int key = wrand(0,mode);
  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>());
  {
    GPVar num(en.argGP(0));
    en.neg(num);
    en.ret(num);
    Assembler a;
#ifdef PROTECT_X64
    a.neg(rax);
#else
    a.neg(eax);
#endif
    encode_size = a.getCodeSize();
    decode_size = a.getCodeSize();
    memcpy(encode_buf,a.getCode(),encode_size);
    memcpy(decode_buf,a.getCode(),decode_size);
  }
  en.endFunction();
  enfuc = (int (*)(int))en.make();
  defuc = enfuc;
}


inline long AlgorithmsLib::wrand(long start,long end)
{
  return start+(rand()%(end-start+1));
}


void AlgorithmsLib::_add()
{
  de.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>()); //加密
  {
    GPVar num(de.argGP(0));
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
    de.lea(num,ptr(num,key));
    de.ret(num);
    Assembler a;
#ifdef PROTECT_X64
    a.lea(rax,ptr(rax,key));
#else 
    a.add(eax,ptr(eax,key));
#endif /* PROTECT */
    
    encode_size = a.getCodeSize();
    memcpy(encode_buf,a.getCode(),encode_size);
    
  }
  de.endFunction();
  defuc = (int(*)(int))de.make();
    
  en.newFunction(CALL_CONV_DEFAULT,FunctionBuilder1<int,int>());
  {
    GPVar num(en.argGP(0));
    int mode = 32;
#ifdef PROTECT_X64
    mode = 64;
#endif
    int key = wrand(0,mode);
    //en.sub(num,imm(key));
    en.lea(num,ptr(num,-key));
    en.ret(num);
    Assembler a;
#ifdef PROTECT_X64
    a.lea(rax,ptr(eax,-key));
#else
    a.lea(eax,ptr(eax,-key));
#endif
    decode_size = a.getCodeSize();
    memcpy(decode_buf,a.getCode(),decode_size);
  }
  en.endFunction();
  enfuc = (int(*)(int))en.make();
}
