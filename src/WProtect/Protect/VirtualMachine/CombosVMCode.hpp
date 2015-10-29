#ifndef COMBOSVMCODE_CPP_VKZFE2VQ
#define COMBOSVMCODE_CPP_VKZFE2VQ


#include "VMHandle.h"
#include "PCode.hpp"
#include <VOperand.hpp>
#include <logfunctions.h>
#include <opcode_table.h>
class VCombosVMCode : public logfunctions{
    public:
    enum ProtectFlag{
        EncryConst = 1 << 0,//
        EncryRegister = 1 << 1,//
        EncryInstruction = 1 << 2,
        Normal = 0
    };
        //variable area
        PCode *ptr_pcode;
        bool super_protect;          //模拟所有运算
        int  protect_flag;
        bool change_vmregister_flag;
        bool tmp_vmregister_status[8];

        //
        //
        //
        //
        //
        //
        //variable area
        //
        //function area
        //
        //
        //
        VCombosVMCode();
        VCombosVMCode(PCode * p);
        ~VCombosVMCode();
        
        void *get_code_buf();
        long get_code_size();

        void impact_vmregister(bool _change_vmregister)
        {
            change_vmregister_flag = _change_vmregister;
		};

        long get_tmp_vmregister()
        {
            for (int i = 0; i < sizeof(tmp_vmregister_status);i++)
            {
                if (tmp_vmregister_status[i] == false)
                {
                    tmp_vmregister_status[i] = true;
#ifdef PROTECT_X64
                    return T_TMP_REGISTER1 << i;
#else
                    return ((T_TMP_REGISTER1 & T_ALL_TMPREGISTER) << i) | T_E32X;
#endif
                }
            }
            printf("没有可用的临时寄存器\n");
            //__asm("int3");
        }
        void unlock_tmp_vmregister(long _tmp_register)
        {
            bool free = false;
            for (int i = 0;i < sizeof(tmp_vmregister_status);i++)
            {
#ifdef PROTECT_X64
                if ((_tmp_register & T_ALL_REGISTER) == (T_TMP_REGISTER1 << i))
#else
                if ((_tmp_register & T_ALL_TMPREGISTER) == ((T_TMP_REGISTER1 << i) & T_ALL_TMPREGISTER))
#endif
                {
                    tmp_vmregister_status[i] = false;
                    free = true;
                }
            } 
            if (free == false)
            {
                printf("没有找到需要释放临时寄存器\n");
            }
        }
        long get_tmp_vmregister_count()
        {
            int count = 0;
            for (int i = 0; i < sizeof(tmp_vmregister_status);i++)
            {
                if (tmp_vmregister_status[i] == false)
                {
                    count++;
                }
            }
            return count;
            //printf("没有可用的临时寄存器\n");
            //__asm("int3");       
        }
        void attach_pcode(PCode * p);
        
        void set_vmregister_store_in(RegisterStore & store_in);
        void set_vmregister_store_out(RegisterStore & store_out);

        void save_vm_context();
        void recover_vm_context();
        void upset_register_array(RegisterStore & r);

        void run_stack();
        void pushf();
        void popf();

        void push_vsp();
        void pop_vsp();
        void push(long _register,bool _disable);
        void push(long _register);
        void pop(long _register);
        
        void build_byte_code(unsigned char b);
        void build_word_code(unsigned short w);
        void build_dword_code(unsigned int d); 
        void build_qword_code(unsigned long q);
        
        void set_pc(long _key);
        void set_pc();

        void b_push_imm(char b);
        void w_push_imm(short w);
        void d_push_imm(int d);
        void q_push_imm(long q);

        void b_push_imm_sx(char b);
        void w_push_imm_sx(short w);
        void d_push_imm_sx(int d);
        void b_push_imm_zx(char b);
        void w_push_imm_zx(short w);
        void d_push_imm_zx(int d);
        
        void b_read_mem();
        void w_read_mem();
        void d_read_mem();
        void q_read_mem();
        
        void b_write_mem();
        void w_write_mem();
        void d_write_mem();
        void q_write_mem();
        
        void b_nand();
        void w_nand();
        void d_nand();
        void q_nand();

        void b_not();                        
        void w_not();
        void d_not();
        void q_not();

        void b_neg();
        void w_neg();
        void d_neg();
        void q_neg();
 
        void b_and();                        
        void w_and();
        void d_and();
        void q_and();  

        void b_or();                        
        void w_or();
        void d_or();
        void q_or();   
        
        void b_xor();                        
        void w_xor();
        void d_xor();
        void q_xor();   

        void b_add();
        void w_add();
        void d_add();
        void q_add();

        void b_sub();
        void w_sub();
        void d_sub();
        void q_sub();

        void b_cmp();
        void w_cmp();
        void d_cmp();
        void q_cmp();

        void b_test();
        void w_test();
        void d_test();
        void q_test();

        void b_div();
        void w_div();
        void d_div();
        void q_div();

        void b_mult();
        void w_mult();
        void d_mult();
        void q_mult();
        
        void b_shr();
        void w_shr();
        void d_shr();
        void q_shr();

        void b_shl();
        void w_shl();
        void d_shl();
        void q_shl(); 

        void b_sar();
        void w_sar();
        void d_sar();
        void q_sar();

        
        void ret();

        void fstsw();
        void get_cf();
        void get_pf();
        void get_af();
        void get_zf();
        void get_sf();
        void get_of();
        void get_df();
#ifdef DEBUG
        void int3();
#endif
        void get_string_ins_diff();
        //
        //
        //function area
};



#endif /* end of include guard: COMBOSVMCODE_CPP_VKZFE2VQ */
