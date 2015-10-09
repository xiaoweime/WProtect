#ifdef  __GNUC__
#define WProtectBegin() __asm__(".byte 0xEB\n\t.byte 0xf\n\t.string \"WProtect Begin\"\n\t");   
#define WProtectEnd() __asm__(".byte 0xEB\n\t.byte 0xd\n\t.string \"WProtect End\"\n\t"); 
#endif

#ifdef _MSC_VER           //by kido 
#define WProtectBegin() \
	__asm __emit 0xEB \
	__asm __emit 0x0F \
	__asm __emit 'W'  \
	__asm __emit 'P'  \
	__asm __emit 'r'  \
	__asm __emit 'o'  \
	__asm __emit 't'  \
	__asm __emit 'e'  \
	__asm __emit 'c'  \
	__asm __emit 't'  \
	__asm __emit ' '  \
	__asm __emit 'B'  \
	__asm __emit 'e'  \
	__asm __emit 'g'  \
	__asm __emit 'i'  \
	__asm __emit 'n'  \
	__asm __emit 00  
#define WProtectEnd() \
	__asm __emit 0xEB \
	__asm __emit 0x0D \
	__asm __emit 'W'  \
	__asm __emit 'P'  \
	__asm __emit 'r'  \
	__asm __emit 'o'  \
	__asm __emit 't'  \
	__asm __emit 'e'  \
	__asm __emit 'c'  \
	__asm __emit 't'  \
	__asm __emit ' '  \
	__asm __emit 'E'  \
	__asm __emit 'n'  \
	__asm __emit 'd'  \
	__asm __emit 00  
#endif                  
