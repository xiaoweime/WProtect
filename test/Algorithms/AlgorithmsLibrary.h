#include <AsmJit.h>

class AlgorithmsLib
{
 public:
  AlgorithmsLib(  );
  ~AlgorithmsLib(  );
  
  int ( *enfuc )( int );
  int ( *defuc )( int );
  unsigned char encode_buf[ 10 ]; //代码
  unsigned char encode_size;
  unsigned char decode_buf[ 10 ];
  unsigned char decode_size;

  void rand_encryption();
  long wrand( long start,long end );
 private:
  AsmJit::Compiler en;
  AsmJit::Compiler de;
  void _shr(  );
  void _shl(  );
  void _ror(  );
  void _rol(  );
  void _add(  );
  //  void _sub(  );
  void _not(  );
  void _neg(  );
  
};
