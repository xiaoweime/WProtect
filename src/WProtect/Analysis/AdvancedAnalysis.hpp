#ifndef _ADVANCEDANALYSIS_H_
#define _ADVANCEDANALYSIS_H_

#include <stack>
#include "Analysis.hpp"

enum 
{
  TYPE_REG = 1,
  TYPE_MEM = 2,
  TYPE_IMM = 4,
  VAR_POINT = 8,
  SIZE_BYTE = 16,
  SIZE_WORD = 32,
  SIZE_DWORD = 64,
  SIZE_QWORD = 128,
  //  VAR_OFFSET = 
  KNOWN = 256,
  UNKNOWN = 512,
  REG_NAX = 1024,
  REG_NBX = 2048,
  REG_NCX = 4096,
  REG_NDX = 8192,
  REG_NSP = 16384,
  REG_NBP = 32768,
  REG_NSI = 65536,
  REG_NDI = 131072,
  REG_32X = 262144,
  REG_16X = 524288,
  REG_8H = 1048576,
  REG_8L = 2097152,
  REG_RN = 4194304
};
  
enum
{
  CF = 1,
  PF = 4,
  AF = 16,
  ZF = 64,
  SF = 128,
  TF = 256,
  IF = 512,
  DF = 1024,
  OF = 2048
};

enum
{
  OPERATIONAL_ADD = 1,
  OPERATIONAL_SUB = 2,
  OPERATIONAL_MUL = 4,
  OPERATIONAL_DIV = 8,
  OPERATIONAL_OR = 16,
  OPERATIONAL_XOR = 32,
  OPERATIONAL_AND = 64,
  OPERATIONAL_SHL = 128,
  OPERATIONAL_SHR = 256
};

  
typedef struct _ANALYSIS_OPERAND_
{
  long operand; //操作数
  long operatonal; //操作符
}Analysis_Operand,*pAnalysis_Operand;

typedef struct__SINGLE_ANALYSIS_OPERAND_
{
  std::vector<Analysis_Operand> operand;
}Single_Analysis_Operand;
  
typedef struct _ALL_ANALYSIS_OPERAND_
{
   Single_Analysis_Operand operand_array[3];
}All_Analysis_Operand;
  
typedef struct _ANALYSIS_INSTRUCT_
{
  long set_eflag; //会改变的EFLAG
  long get_eflag; //需要的EFLAG
  long info;
  All_Analysis_Operand o;
}Analysis_Instruct,pAnalysis_Instruct;

typedef struct _VIRTUAL_REGISTER_
{
_VIRTUAL_REGISTER_::_VIRTUAL_REGISTER_() : nax(r[0]),nbx(r[1]),ncx(r[2]),ndx[3],nsp[4],nbp[5],nsi[6],ndi[7] 
{
}
  long r[30];
  long *nax;
  long *nbx;
  long *ncx;
  long *ndx;
  long *nsp;
  long *nbp;
  long *nsi;
  long *ndi;
  
}Virtual_Register;
  
typedef struct _Analysis_Fuc_
{
  long address; //函数地址
  size_t paranmeter_count; //参数个数
  size_t local_variable_count;
  Analysis_Instruct ins;
  std::stack <All_Analysis_Instruct> virtual_stack;
  Virtual_Register virtual_register;
}Analysis_Fuc,*pAnalysis_Fuc;


class AdvancedAnalysis : public Analysis
{
public:
  AdvancedAnalysis();
  virtual ~AdvancedAnalysis();
private:
  std::vector<Analysis_Fuc> fuc_vec;
};

#endif /* _ADVANCEDANALYSIS_H_ */
