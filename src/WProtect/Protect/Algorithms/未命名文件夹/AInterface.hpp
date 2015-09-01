/*
 *
 *   Copyrigth (C) Tue May 28 01:07:00 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _AINTERFACE_H_
#define _AINTERFACE_H_

#include <iostream>
#include <AsmJit.h>

using namespace std;

typedef struct _ALGORITHMS_
{
  unsigned char type; //1代表可以加密byte 2表示word 4表示dword
  AsmJit::Assembler Encryption;
  long (*Decryption)(long);
}Algorithms,*pAlgorithms;

class AInterface
{
public:
  AInterface();
  virtual ~AInterface();
public:
  Algorithms b_add(long _key);
  Algorithms w_add();
  Algorithms d_add();
  Algorithms q_add();
  Algorithms b_rol();
  Algorithms w_rol();
  Algorithms d_rol();
  Algorithms q_rol();
  Algorithms b_xor();
  Algorithms w_xor();
  Algorithms d_xor();
  Algorithms q_xor();
  Algorithms b_not();
  Algorithms w_not();
  Algorithms d_not();
  Algorithms q_not();
  // std::list <Algorithms> algorithms_list;
  Algorithms random_algorithms();
  std::list <Compiler> compiler_list;
  
};

#endif /* _AINTERFACE_H_ */
