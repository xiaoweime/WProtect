/*
 *
 *   Copyright (C) Tue Jul  2 05:16:49 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _VOPERAND_H_
#define _VOPERAND_H_


enum 
{
  T_RAX = 1 << 0,
  T_RBX = 1 << 1,//2,
  T_RCX = 1 << 2,//4,
  T_RDX = 1 << 3,//8,
  T_RSP = 1 << 4,//16,
  T_RBP = 1 << 5,//32,
  T_RSI = 1 << 6,//64,
  T_RDI = 1 << 7,//128,
  T_EFLAG_ = 1 << 8,//256,
  T_TMP_R64_1 = 1 << 9,//512,
  T_TMP_R64_2 = 1 << 10,//1024,
  T_TMP_R64_3 = 1 << 11,//2048,
  T_TMP_R64_4 = 1 << 12,//4096,

  T_TMP_R64_5 = 1 << 13,//32768, //保留
  T_TMP_R64_6 = 1 << 14,//65536,
  T_TMP_R64_7 = 1 << 15,//131072,
  T_TMP_R64_8 = 1 << 16,//262144, //跳转寄存器

  T_KEY64 = 1 << 17,//8192,
  T_RET64 = 1 << 18,//16384,   

  T_JMPINSADDR64 =  1 << 19,
  T_NEXTINSADDR64 = 1 << 20,

  T_ALL_TMPREGISTER = 0x1FE00,
  T_ALL_REGISTER = 0x1FFFFF,    //上面所有的寄存器

  T_XXX5 = 1 << 23,//524288,

  T_INVALID = 1 << 24,//1048576,

  T_E32X = 1 << 25,//16777216, //只有64位程序时才有  
  T_16X  = (1 << 26),//2097152, //AX
  T_8H =  (1 << 27),//4194304, //AH
  T_8L =  (1 << 28),//8388608,

  T_RN = 1 << 29,//33554432,       //R8 - R15

  disable = 1 << 30,
  enable = 1 << 31,
  T_KEY32 = (T_KEY64 | T_E32X),
  T_RET32 = (T_RET64 | T_E32X),

  T_TMP_R32_1 = (T_TMP_R64_1 | T_E32X),
  T_TMP_R32_2 = (T_TMP_R64_2 | T_E32X),
  T_TMP_R32_3 = (T_TMP_R64_3 | T_E32X),
  T_TMP_R32_4 = (T_TMP_R64_4 | T_E32X),
  T_TMP_R32_5 = (T_TMP_R64_5 | T_E32X),
  T_TMP_R32_6 = (T_TMP_R64_6 | T_E32X),
  T_TMP_R32_7 = (T_TMP_R64_7 | T_E32X),
  T_TMP_R32_8 = (T_TMP_R64_8 | T_E32X),
  T_INVALID_R32 = (T_INVALID | T_E32X),

  T_TMP_R16_1 = (T_TMP_R32_1 | T_16X),
  T_TMP_R16_2 = (T_TMP_R32_2 | T_16X),
  T_TMP_R16_3 = (T_TMP_R32_3 | T_16X),
  T_TMP_R16_4 = (T_TMP_R32_4 | T_16X),
  T_TMP_R16_5 = (T_TMP_R32_5 | T_16X),
  T_TMP_R16_6 = (T_TMP_R32_6 | T_16X),
  T_TMP_R16_7 = (T_TMP_R32_7 | T_16X),
  T_TMP_R16_8 = (T_TMP_R32_8 | T_16X),
  T_INVALID_R16 = (T_INVALID_R32 | T_16X),

  T_TMP_R8_1H = (T_TMP_R16_1 | T_8H),
  T_TMP_R8_2H = (T_TMP_R16_2 | T_8H),
  T_TMP_R8_3H = (T_TMP_R16_3 | T_8H),
  T_TMP_R8_4H = (T_TMP_R16_4 | T_8H),
  T_TMP_R8_5H = (T_TMP_R16_5 | T_8H),
  T_TMP_R8_6H = (T_TMP_R16_6 | T_8H),
  T_TMP_R8_7H = (T_TMP_R16_7 | T_8H),
  T_TMP_R8_8H = (T_TMP_R16_8 | T_8H),
  T_INVALID_R8 = (T_INVALID_R16 | T_8H),

  T_TMP_R8_1L = (T_TMP_R16_1 | T_8L),
  T_TMP_R8_2L = (T_TMP_R16_2 | T_8L),
  T_TMP_R8_3L = (T_TMP_R16_3 | T_8L),
  T_TMP_R8_4L = (T_TMP_R16_4 | T_8L),
  T_TMP_R8_5L = (T_TMP_R16_5 | T_8L),
  T_TMP_R8_6L = (T_TMP_R16_6 | T_8L),
  T_TMP_R8_7L = (T_TMP_R16_7 | T_8L),
  T_TMP_R8_8L = (T_TMP_R16_8 | T_8L),

  T_INVALID32 = (T_INVALID | T_E32X),
  T_INVALID16 = (T_INVALID | T_16X),
  T_INVALID8L  = (T_INVALID | T_8L),
  T_INVALID8H  = (T_INVALID | T_8H),

  T_R8 = (T_RAX | T_RN),
  T_R9 = (T_RBX | T_RN),
  T_R10 = (T_RCX | T_RN),
  T_R11 = (T_RDX | T_RN),
  T_R12 = (T_RSP | T_RN),
  T_R13 = (T_RBP | T_RN),
  T_R14 = (T_RSI | T_RN),
  T_R15 = (T_RDI | T_RN),

  T_EAX = (T_RAX | T_E32X),
  T_EBX = (T_RBX | T_E32X),
  T_ECX = (T_RCX | T_E32X),
  T_EDX = (T_RDX | T_E32X),
  T_ESP = (T_RSP | T_E32X),
  T_EBP = (T_RBP | T_E32X),
  T_ESI = (T_RSI | T_E32X),
  T_EDI = (T_RDI | T_E32X),

  T_AX = (T_EAX | T_16X),
  T_BX = (T_EBX | T_16X),
  T_CX = (T_ECX | T_16X),
  T_DX = (T_EDX | T_16X),
  T_SP = (T_ESP | T_16X),
  T_BP = (T_EBP | T_16X),
  T_SI = (T_ESI | T_16X),
  T_DI = (T_EDI | T_16X),

  T_AH = (T_AX | T_8H),
  T_AL = (T_AX | T_8L),
  T_CH = (T_CX | T_8H),
  T_CL = (T_CX | T_8L),
  T_DH = (T_DX | T_8H),
  T_DL = (T_DX | T_8L),
  T_BH = (T_BX | T_8H),
  T_BL = (T_BX | T_8L),

  T_EFLAG8H = (T_EFLAG_ | T_8H),
  T_EFLAG8L = (T_EFLAG_ | T_8L),
  T_EFLAG16 = (T_EFLAG_ | T_16X),
  T_EFLAG32 = (T_EFLAG_ | T_E32X)
  //disable = 67108864,
  //enable = 134217728  
};
/*
  

#define T_RAX 1
#define T_RBX 2
#define T_RCX 4
#define T_RDX 8
#define T_RSP 16
#define T_RBP 32
#define T_RSI 64
#define T_RDI 128

#define T_EFLAG_ 256

#define T_TMP_R64_1 512
#define T_TMP_R64_2 1024
#define T_TMP_R64_3 2048
#define T_TMP_R64_4 4096

#define T_KEY64  8192
#define T_RET64  16384

#define T_TMP_R64_5 32768 //保留
#define T_TMP_R64_6 65536
#define T_TMP_R64_7 131072
#define T_TMP_R64_8 262144
#define T_XXX5 524288


#define T_INVALID 1048576

#define T_16X  2097152 //AX
#define T_8H 4194304 //AH
#define T_8L 8388608
#define T_E32X  16777216 //只有64位程序时才有
#define T_RN 33554432       //R8 - R15

#define  disable 67108864
#define  enable 134217728

#define T_KEY32 (T_KEY64 | T_E32X)
#define T_RET32 (T_RET64 | T_E32X)

#define T_TMP_R32_1 (T_TMP_R64_1 | T_E32X)
#define T_TMP_R32_2 (T_TMP_R64_2 | T_E32X)
#define T_TMP_R32_3 (T_TMP_R64_3 | T_E32X)
#define T_TMP_R32_4 (T_TMP_R64_4 | T_E32X)
#define T_TMP_R32_5 (T_TMP_R64_5 | T_E32X)
#define T_TMP_R32_6 (T_TMP_R64_6 | T_E32X)
#define T_TMP_R32_7 (T_TMP_R64_7 | T_E32X)
#define T_TMP_R32_8 (T_TMP_R64_8 | T_E32X)
#define T_INVALID_R32 (T_INVALID | T_E32X)

#define T_TMP_R16_1 (T_TMP_R32_1 | T_16X)
#define T_TMP_R16_2 (T_TMP_R32_2 | T_16X)
#define T_TMP_R16_3 (T_TMP_R32_3 | T_16X)
#define T_TMP_R16_4 (T_TMP_R32_4 | T_16X)
#define T_TMP_R16_5 (T_TMP_R32_5 | T_16X)
#define T_TMP_R16_6 (T_TMP_R32_6 | T_16X)
#define T_TMP_R16_7 (T_TMP_R32_7 | T_16X)
#define T_TMP_R16_8 (T_TMP_R32_8 | T_16X)
#define T_INVALID_R16 (T_INVALID_R32 | T_16X)

#define T_TMP_R8_1H (T_TMP_R16_1 | T_8H)
#define T_TMP_R8_2H (T_TMP_R16_2 | T_8H)
#define T_TMP_R8_3H (T_TMP_R16_3 | T_8H)
#define T_TMP_R8_4H (T_TMP_R16_4 | T_8H)
#define T_TMP_R8_5H (T_TMP_R16_5 | T_8H)
#define T_TMP_R8_6H (T_TMP_R16_6 | T_8H)
#define T_TMP_R8_7H (T_TMP_R16_7 | T_8H)
#define T_TMP_R8_8H (T_TMP_R16_8 | T_8H)
#define T_INVALID_R8 (T_INVALID_R16 | T_8H)

#define T_TMP_R8_1L (T_TMP_R16_1 | T_8L)
#define T_TMP_R8_2L (T_TMP_R16_2 | T_8L)
#define T_TMP_R8_3L (T_TMP_R16_3 | T_8L)
#define T_TMP_R8_4L (T_TMP_R16_4 | T_8L)
#define T_TMP_R8_5L (T_TMP_R16_5 | T_8L)
#define T_TMP_R8_6L (T_TMP_R16_6 | T_8L)
#define T_TMP_R8_7L (T_TMP_R16_7 | T_8L)
#define T_TMP_R8_8L (T_TMP_R16_8 | T_8L)

#define T_INVALID32 (T_INVALID | T_E32X)
#define T_INVALID16 (T_INVALID | T_16X)
#define T_INVALID8L  (T_INVALID | T_8L)
#define T_INVALID8H  (T_INVALID | T_8H)

#define T_R8 (T_RAX | T_RN)
#define T_R9 (T_RBX | T_RN)
#define T_R10 (T_RCX | T_RN)
#define T_R11 (T_RDX | T_RN)
#define T_R12 (T_RSP | T_RN)
#define T_R13 (T_RBP | T_RN)
#define T_R14 (T_RSI | T_RN)
#define T_R15 (T_RDI | T_RN)

#define T_EAX (T_RAX | T_E32X)
#define T_EBX (T_RBX | T_E32X)
#define T_ECX (T_RCX | T_E32X)
#define T_EDX (T_RDX | T_E32X)
#define T_ESP (T_RSP | T_E32X)
#define T_EBP (T_RBP | T_E32X)
#define T_ESI (T_RSI | T_E32X)
#define T_EDI (T_RDI | T_E32X)

#define T_AX (T_EAX | T_16X)
#define T_BX (T_EBX | T_16X)
#define T_CX (T_ECX | T_16X)
#define T_DX (T_EDX | T_16X)
#define T_SP (T_ESP | T_16X)
#define T_BP (T_EBP | T_16X)
#define T_SI (T_ESI | T_16X)
#define T_DI (T_EDI | T_16X)

#define T_AH (T_AX | T_8H)
#define T_AL (T_AX | T_8L)
#define T_CH (T_CX | T_8H)
#define T_CL (T_CX | T_8L)
#define T_DH (T_DX | T_8H)
#define T_DL (T_DX | T_8L)
#define T_BH (T_BX | T_8H)
#define T_BL (T_BX | T_8L)

#define T_EFLAG8H (T_EFLAG_ | T_8H)
#define T_EFLAG8L (T_EFLAG_ | T_8L)
#define T_EFLAG16 (T_EFLAG_ | T_16X)
#define T_EFLAG32 (T_EFLAG_ | T_E32X)
*/
#ifdef PROTECT_X64
#define T_FLAG T_EFLAG_
#define T_EFLAG T_EFLAG_
#define T_KEY T_KEY64
#define T_RET T_RET64
#define T_NEXTINSADDR T_NEXTINSADDR64
#define T_JMPINSADDR T_JMPINSADDR64
#define T_TMP_REGISTER1 T_TMP_R64_1
#define T_TMP_REGISTER2 T_TMP_R64_2
#define T_TMP_REGISTER3 T_TMP_R64_3
#define T_TMP_REGISTER4 T_TMP_R64_4
#define T_TMP_REGISTER5 T_TMP_R64_5
#define T_TMP_REGISTER6 T_TMP_R64_6
#define T_TMP_REGISTER7 T_TMP_R64_7
#define T_TMP_REGISTER8 T_TMP_R64_8
#define T_NAX T_RAX
#define T_NBX T_RBX
#define T_NCX T_RCX
#define T_NDX T_RDX
#define T_NSP T_RSP
#define T_NBP T_RBP
#define T_NSI T_RSI
#define T_NDI T_RDI
#else
#define T_FLAG (T_EFLAG32)
#define T_EFLAG (T_EFLAG32)
#define T_NEXTINSADDR (T_NEXTINSADDR64 | T_E32X)
#define T_JMPINSADDR (T_JMPINSADDR64 | T_E32X)
#define T_KEY (T_KEY32)
#define T_RET (T_RET32)
#define T_TMP_REGISTER1 T_TMP_R32_1
#define T_TMP_REGISTER2 T_TMP_R32_2
#define T_TMP_REGISTER3 T_TMP_R32_3
#define T_TMP_REGISTER4 T_TMP_R32_4
#define T_TMP_REGISTER5 T_TMP_R32_5
#define T_TMP_REGISTER6 T_TMP_R32_6
#define T_TMP_REGISTER7 T_TMP_R32_7
#define T_TMP_REGISTER8 T_TMP_R32_8
#define T_NAX T_EAX
#define T_NBX T_EBX
#define T_NCX T_ECX
#define T_NDX T_EDX
#define T_NSP T_ESP
#define T_NBP T_EBP
#define T_NSI T_ESI
#define T_NDI T_EDI
#endif

#ifdef PROTECT_X64
#define  T_JCC_REGISTER  T_TMP_R64_8
#define  T_MEM_REGISTER  T_TMP_R64_7
#define  T_DATA_REGISTER T_TMP_R64_6
#else
#define  T_JCC_REGISTER  T_TMP_R32_8
#define  T_MEM_REGISTER  T_TMP_R32_7
#define  T_DATA_REGISTER T_TMP_R32_6
#endif

enum V_OPERAND_TYPE
{
  VOPERAND_NONE = 0x00,
  VOPERAND_REG  = 0x01,
  VOPERAND_IMM  = 0x02,
  VOPERAND_MEM  = 0x04,
  VOPERAND_JIMM = 0x08
};


typedef struct _V_Operand
{
  typedef struct _BASE_DATA
  {
	 long id;
    char op;
    char size;
  }BaseData;
  
  typedef struct _MEM_DATA
  {
    char op;
    char size;  //指的是内存大小 比如dword_ptr为4    
    long id;
    long base;
    long index;
    long scale;
    long lval;
  }MemData;
  typedef struct _REG_DATA
  {
    char op;
    char size;    
    long id;    
    long base;
  }RegData;
  typedef struct _IMM_DATA
  {
    char op;
    char size;    
    long id;    
    long value;
  }ImmData;
  
  union
  {
    BaseData _base;
    MemData _mem;
    RegData _reg;
    ImmData _imm;
  };

  inline size_t get_size(  ) const {
    return _base.size;
  }
  inline long get_id(  ) const {
    return _base.id;
  }
  inline bool is_mem(  ) const {
    return ( _base.op == VOPERAND_MEM );
  }
  inline bool is_reg(  ) const {
    return ( _base.op == VOPERAND_REG );
  }
  inline bool is_imm(  ) const {
    return ( _base.op == VOPERAND_IMM );
  }
  inline bool is_none(  ) const {
    return ( _base.op == VOPERAND_NONE );
  }
  inline bool isGPD(  ) const {
    if (_reg.base == T_EAX ||
        _reg.base == T_EBX ||
        _reg.base == T_ECX ||
        _reg.base == T_EDX ||
        _reg.base == T_ESP ||
        _reg.base == T_EBP ||
        _reg.base == T_ESI ||
        _reg.base == T_EDI
#ifndef PROTECT_X64
        ||_reg.base == T_EFLAG
#endif
        )
    {
      return true;
    } else return false;
  }
  inline bool isGPW(  ) const {
    if (_reg.base == T_AX||
        _reg.base == T_BX||
        _reg.base == T_CX||
        _reg.base == T_DX||
        _reg.base == T_SP||
        _reg.base == T_BP||
        _reg.base == T_SI||
        _reg.base == T_DI)
    {
      return true;
    } else return false;
  }
  inline bool isGPBLo(  ) const {
    if (_reg.base == T_AL||
        _reg.base == T_BL||
        _reg.base == T_CL||
        _reg.base == T_DL)
    {
      return true;
    } else return false;
  }
  inline bool isGPBHi(  ) const {
    if (_reg.base == T_AH||
        _reg.base == T_BH||
        _reg.base == T_CH||
        _reg.base == T_DH)
    {
      return true;
    } else return false;    
  }
  inline bool isGPB(  ) const {
    return ( isGPBHi(  ) || isGPBLo(  ) );
  }
  inline bool isGPQ(  ) const {
    if (_reg.base == T_NAX ||
        _reg.base == T_NBX ||
        _reg.base == T_NCX ||
        _reg.base == T_NDX ||
        _reg.base == T_NSP ||
        _reg.base == T_NBP ||
        _reg.base == T_NSI ||
        _reg.base == T_NDI
#ifdef PROTECT_X64
        ||_reg.base == T_EFLAG
#endif        
        )
    {
      return true;
    } else return false;    
  }
}VOperand,*pVOperand;


typedef struct _VImm : public VOperand 
{
  _VImm( long _value , char _size) {
    _imm.op = VOPERAND_IMM;
    _imm.value = _value;
    _imm.size = _size;
  }
  _VImm( long _value ) {
    _imm.op = VOPERAND_IMM;    
    _imm.value = _value;
#ifdef PROTECT_X64
    _imm.size = 8;
#else
    _imm.size = 4;
#endif
  }
  ~_VImm(  ) {
    
  }
}VImm;

typedef struct _VReg : public VOperand
{
  _VReg( long _register,char _size )
  {
    _reg.op = VOPERAND_REG;
    _reg.base = _register;
    _reg.size = _size;
  }
  _VReg( long _register )
  {
    _reg.op = VOPERAND_REG;
    _reg.base = _register;
#ifdef PROTECT_X64
    long defsize = 8;
#else
    long defsize = 4;
#endif
    switch( _register )
    {
    case T_RAX:
      _reg.size = defsize;
      break;
    case T_RBX:
      _reg.size = defsize;
      break;
    case T_RCX:
      _reg.size = defsize;
      break;
    case T_RDX:
      _reg.size = defsize;
      break;
    case T_RSP:
      _reg.size = defsize;
      break;
    case T_RBP:
      _reg.size = defsize;
      break;
    case T_RSI:
      _reg.size = defsize;
      break;
    case T_RDI:
      _reg.size = defsize;
      break;
    case T_EAX:
      _reg.size = 4;
      break;
    case T_EBX:
      _reg.size = 4;
      break;
    case T_ECX:
      _reg.size = 4;
      break;
    case T_EDX:
      _reg.size = 4;
      break;
    case T_ESP:
      _reg.size = 4;
      break;
    case T_EBP:
      _reg.size = 4;
      break;
    case T_ESI:
      _reg.size = 4;
      break;
    case T_EDI:
      _reg.size = 4;
      break;      
    case T_AX:
      _reg.size = 2;
      break;
    case T_BX:
      _reg.size = 2;
      break;
    case T_CX:
      _reg.size = 2;
      break;
    case T_DX:
      _reg.size = 2;      
      break;
    case T_SI:
      _reg.size = 2;
      break;
    case T_DI:
      _reg.size = 2;
      break;
    case T_SP:
      _reg.size = 2;
      break;
    case T_BP:
      _reg.size = 2;
      break;
    case T_AL:
      _reg.size = 1;
      break;
    case T_BH:
      _reg.size = 1;
      break;
    case T_CL:
      _reg.size = 1;
      break;
    case T_CH:
      _reg.size = 1;
      break;
    case T_DL:
      _reg.size = 1;
      break;
    case T_AH:
      _reg.size = 1;
      break;
    case T_BL:
      _reg.size = 1;
      break;
    case T_DH:
      _reg.size = 1;
      break;
    }    
  }
  ~_VReg(  )
  {
    
  }
}VReg;

typedef struct _VMem : public VOperand
{
  _VMem( long base,long index,long scale,long lval,char _size){
    _mem.op = VOPERAND_MEM;
    _mem.base = base;
    _mem.index = index;
    _mem.scale = scale;
    _mem.lval = lval;
    _mem.size = _size;
  }
  ~_VMem(  ){
    
  }
}VMem;

  
VImm vimm( long _value );
VReg vreg( long _register );
VMem vmem( long _base,long _index,long _scale,long _lval,char _size );

#endif /* _VOPERAND_H_ */ 
