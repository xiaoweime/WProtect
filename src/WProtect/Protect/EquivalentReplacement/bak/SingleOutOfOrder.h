typedef struct _COMPLICATED_OPTION_
{
	bool bChangeStack; //是否改变堆栈
	
}Option,*pOption;

typedef struct _INSTRUCTIONS_INFO
{
	void * code_buf;          //代码的缓冲区
	unsigned long code_size;  //代码大小
	int stack_change;  //堆栈变化多少
}InstructionsInfo,*pInstructionsInfo;

typedef struct _STACK_REGISTER_
{
	int nax;
	int nbx;
	int ncx;
	int ndx;
	int nsp;
	int nbp;
	int nsi;
	int ndi;
	int eflag;
}StackRegister,*pStackRegister;
	
class CSingleCodeComplicated
{
 public:
	CSingleCodeComplicated();
 public:
	Option m_code_option;
    template <class T>  T * disordering(T * t,int nSize);
	StackRegister SREG; //堆栈保存的寄存器
};
