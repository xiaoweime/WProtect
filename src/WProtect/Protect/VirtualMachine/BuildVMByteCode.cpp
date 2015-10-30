/************************************************************
 *                                                         *
 *                                                        *
 *                2015年7月31日                          *
 *                             By:XiaoWei               *
 *                                                     *
 *                                                    *
 *****************************************************/

#include "BuildVMByteCode.hpp"
#include "VirtualMachine.h"
#include "CombosVMCode.hpp"
#include "VMAddressTable.hpp"
#include "VMCodeBuffer.hpp"
#include "PCode.hpp"
#include <WProtectConfig.h>
#include <Analysis.hpp>
#include <list>
#include <map>
#include <vector>
#include "OutDetailedInformation.hpp"
#include <string.h>
#include <fstream>


#ifndef LUA_H
#define LUA_H
extern "C"{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#endif


BuildVMByteCode * ptr_build_vm_bytecode;
VCombosVMCode * ptr_combos_vm_code;
ud_t * ptr_ud;
lua_State * build_vm_code_lua;
RandomEngender random_engender_lua;

#define get_operand1_type(x) x.operand[0].type
#define get_operand2_type(x) x.operand[1].type
#define get_operand1(x) x.operand[0]
#define get_operand2(x) x.operand[1]
#define read_mem(x) if(x.type == UD_OP_MEM)\
        {\
              switch (x.size)\
              {\
                 case 0:\
                    break;\
                 case 8:\
                    var_combos_vm_code.b_read_mem();\
                    break;\
                 case 16:\
                    var_combos_vm_code.w_read_mem();\
                    break;\
                 case 32:\
                    var_combos_vm_code.d_read_mem();\
                    break;\
                 case 64:\
                    int low_tmp_addr = var_combos_vm_code.get_tmp_vmregister();\
                    var_combos_vm_code.push_vsp();\
                    var_combos_vm_code.d_read_mem();\
                    var_combos_vm_code.pop(low_tmp_addr);\
                    var_combos_vm_code.b_push_imm_zx(4);\
                    var_combos_vm_code.d_add();\
                    var_combos_vm_code.pop(T_INVALID);\
                    var_combos_vm_code.d_read_mem();\
                    var_combos_vm_code.push(low_tmp_addr | T_E32X);\
                    var_combos_vm_code.d_read_mem();\
                    var_combos_vm_code.unlock_tmp_vmregister(low_tmp_addr);\
                    break;\
              }\
        }


#define write_mem(x) if(x.type == UD_OP_MEM)\
        {\
              switch (x.size)\
              {\
                 case 8:\
                    var_combos_vm_code.b_write_mem();\
                    break;\
                 case 16:\
                    var_combos_vm_code.w_write_mem();\
                    break;\
                 case 32:\
                    var_combos_vm_code.d_write_mem();\
                    break;\
                 case 64:\
                    int higt_tmp_addr = var_combos_vm_code.get_tmp_vmregister();\
                    var_combos_vm_code.push_vsp();\
                    var_combos_vm_code.d_read_mem();\
                    var_combos_vm_code.b_push_imm_zx(4);\
                    var_combos_vm_code.d_add();\
                    var_combos_vm_code.pop(T_INVALID);\
                    var_combos_vm_code.pop(higt_tmp_addr| T_E32X);\
                    var_combos_vm_code.d_write_mem();\
                    var_combos_vm_code.push(higt_tmp_addr | T_E32X);\
                    var_combos_vm_code.d_write_mem();\
                    var_combos_vm_code.unlock_tmp_vmregister(higt_tmp_addr);\
                    break;\
              }\
        }
#define set_imm_operand_size(dst,src) if (dst.type == UD_OP_IMM)\
        {\
            switch (src.size)\
            {\
            case 8:\
                break;\
            case 16:\
                if (dst.size == 8)\
                dst.lval.sword = (signed short)dst.lval.sbyte;\
                break;\
            case 32:\
                if (dst.size == 8)\
                {\
                    dst.lval.sdword = (signed int)dst.lval.sbyte;\
                }\
                else if (dst.size == 16)\
                {\
                    dst.lval.sdword = (signed int)dst.lval.sword;\
                }\
                break;\
            }\
            dst.size = src.size;\
        }


#define luai_def(name) \
static int luai_ ##name(lua_State * L)\
{\
    ptr_combos_vm_code->impact_vmregister(false);\
    ptr_combos_vm_code->name();\
    ptr_combos_vm_code->impact_vmregister(true);\
    return 0;\
}\

#define luai_def1(name)\
static int luai_ ##name(lua_State * L)\
{\
    ptr_combos_vm_code->impact_vmregister(false);\
    int count = lua_gettop(build_vm_code_lua);\
    if (count == 1)\
    {\
        if (!lua_isnumber(build_vm_code_lua,1))\
        {\
            lua_pushstring(build_vm_code_lua," is not an Integer\n");\
            lua_error(build_vm_code_lua);\
        }\
        else\
            ptr_combos_vm_code->name(lua_tonumber(build_vm_code_lua,1));\
    }\
    else\
    {\
        printf("%s Need a parameter\n",#name);\
    }\
    ptr_combos_vm_code->impact_vmregister(true);\
    return 0;\
};\

static int lua_randomseed(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    if (count == 1)
    {
        if (!lua_isnumber(build_vm_code_lua,1))
        {
            lua_pushstring(build_vm_code_lua, " is not an Interget\n");
            lua_error(build_vm_code_lua);
        }
        random_engender_lua.randomseed(lua_tonumber(build_vm_code_lua,1));
    }
    else
    {
        printf("randseed Need a parameter\n");
    }
    return 0;
}

static int lua_random(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    switch (count)
    {
    case 0:
        {
            lua_pushnumber(L,random_engender_lua.random());
        }
        break;
    case 1:
        {
            if (!lua_isnumber(L,1))
            {
                lua_pushstring(build_vm_code_lua, " is not an Interget\n");
                lua_error(L);
            }
            int n = (lua_tonumber(L,1));
            long rn = random_engender_lua.random() ;
            if (n == 0)
                lua_pushnumber(L,rn);
            else
                lua_pushnumber(L,(rn % n));
        }
        break;
    default:
        lua_pushstring(build_vm_code_lua, "random Need 1 or 2 parameter\\n");
        lua_error(build_vm_code_lua);
        break;
    }
    return 1;
}

/*
static int luai_b_push_imm(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    if (count == 1)
    {
        if (!lua_isnumber(build_vm_code_lua,1))
        {
            lua_pushstring(build_vm_code_lua, "不是一个整型\n");
            lua_error(build_vm_code_lua);
        }
        ptr_combos_vm_code->b_push_imm(lua_tonumber(build_vm_code_lua,1));
    }
    else
    {
        printf("函数需要一个参数\n");
    }
}*/

luai_def(run_stack)
luai_def(pushf)
luai_def(popf)

luai_def(push_vsp)
luai_def(pop_vsp)

luai_def(set_pc)

luai_def(b_read_mem)
luai_def(w_read_mem)
luai_def(d_read_mem)
//luai_def(q_read_mem)

luai_def(b_write_mem)
luai_def(w_write_mem)
luai_def(d_write_mem)
//luai_def(q_write_mem)

luai_def(b_nand)
luai_def(w_nand)
luai_def(d_nand)
//luai_def(q_nand)

luai_def(b_not)
luai_def(w_not)
luai_def(d_not)
//luai_def(q_not)

luai_def(b_neg)
luai_def(w_neg)
luai_def(d_neg)
//luai_def(q_neg)

luai_def(b_and)
luai_def(w_and)
luai_def(d_and)
//luai_def(q_and)

luai_def(b_or)
luai_def(w_or)
luai_def(d_or)
//luai_def(q_or)

luai_def(b_xor)
luai_def(w_xor)
luai_def(d_xor)
//luai_def(q_xor)

luai_def(b_add)
luai_def(w_add)
luai_def(d_add)
//luai_def(q_add)

luai_def(b_sub)
luai_def(w_sub)
luai_def(d_sub)
//luai_def(q_sub)

luai_def(b_cmp)
luai_def(w_cmp)
luai_def(d_cmp)
//luai_def(q_cmp)

luai_def(b_test)
luai_def(w_test)
luai_def(d_test)
//luai_def(q_test)

/*
luai_def(b_div)
luai_def(w_div)
luai_def(d_div)
//luai_def(q_div)

luai_def(b_mult)
luai_def(w_mult)
luai_def(d_mult)
//luai_def(q_mult)
*/

luai_def(b_shr)
luai_def(w_shr)
luai_def(d_shr)
//luai_def(q_shr)

luai_def(b_shl)
luai_def(w_shl)
luai_def(d_shl)
//luai_def(q_shl)

luai_def(b_sar)
luai_def(w_sar)
luai_def(d_sar)
//luai_def(q_sar)

luai_def(ret)

luai_def(fstsw)
luai_def(get_cf)
luai_def(get_pf)
luai_def(get_af)
luai_def(get_zf)
luai_def(get_sf)
luai_def(get_of)
luai_def(get_df)
#ifdef DEBUG
luai_def(int3)
#endif
luai_def(get_string_ins_diff)

luai_def1(b_push_imm)
luai_def1(w_push_imm)
luai_def1(d_push_imm)

luai_def1(b_push_imm_zx)
luai_def1(w_push_imm_zx)
luai_def1(b_push_imm_sx)
luai_def1(w_push_imm_sx)

luai_def1(push)
luai_def1(pop)

static int luai_read_vm_operand(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    if (count == 1)
    {
        if (!lua_isnumber(build_vm_code_lua,1))
        {
            lua_pushstring(build_vm_code_lua, "Is Not An Integer\n");
            lua_error(build_vm_code_lua);
        }
        int o = lua_tonumber(build_vm_code_lua,1);
        switch (o)
        {
        case 1:
            ptr_build_vm_bytecode->read_vm_operand(*ptr_combos_vm_code,get_operand1((*ptr_ud)));
            break;
        case 2:
            ptr_build_vm_bytecode->read_vm_operand(*ptr_combos_vm_code,get_operand2((*ptr_ud)));
            break;
        case 3:
            ptr_build_vm_bytecode->read_vm_operand(*ptr_combos_vm_code,ptr_ud->operand[2]);
            break;
        }
    }
    else if(count == 2)
    {
        int o = lua_tonumber(build_vm_code_lua,1);
        bool b = lua_tonumber(build_vm_code_lua,2);
        if (b)
        {
            /* ReadAddress */
            switch (o)
            {
            case 1:
                ptr_build_vm_bytecode->vm_operand(*ptr_combos_vm_code,get_operand1((*ptr_ud)));
                break;
            case 2:
                ptr_build_vm_bytecode->vm_operand(*ptr_combos_vm_code,get_operand2((*ptr_ud)));
                break;
            case 3:
                ptr_build_vm_bytecode->vm_operand(*ptr_combos_vm_code,ptr_ud->operand[2]);
                break;
            }
        }else
        {
            switch (o)
            {
            case 1:
                ptr_build_vm_bytecode->read_vm_operand(*ptr_combos_vm_code,get_operand1((*ptr_ud)));
                break;
            case 2:
                ptr_build_vm_bytecode->read_vm_operand(*ptr_combos_vm_code,get_operand2((*ptr_ud)));
                break;
            case 3:
                ptr_build_vm_bytecode->read_vm_operand(*ptr_combos_vm_code,ptr_ud->operand[2]);
                break;
            }
        }
    }
    else
    {
        printf("pop_operand Need 1 parameter\n");
        debugbreakpoint();
    }
	return 0;
}

static int luai_write_vm_operand(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    if (count == 1)
    {
        if (!lua_isnumber(build_vm_code_lua,1))
        {
            lua_pushstring(build_vm_code_lua, "is not an integer\n");
            lua_error(build_vm_code_lua);
        }
        int o = lua_tonumber(build_vm_code_lua,1);
        switch (o)
        {
        case 1:
            ptr_build_vm_bytecode->write_vm_operand(*ptr_combos_vm_code,get_operand1((*ptr_ud)));
            break;
        case 2:
            ptr_build_vm_bytecode->write_vm_operand(*ptr_combos_vm_code,get_operand2((*ptr_ud)));
            break;
        case 3:
            ptr_build_vm_bytecode->write_vm_operand(*ptr_combos_vm_code,ptr_ud->operand[2]);
            break;
        }
    }
    else
    {
        ptr_build_vm_bytecode->error("push_operand need 1 parameter\n");
        debugbreakpoint();
    }
}

static int luai_resize_imm_operand(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    ud_operand new_op;
    new_op.size = 32; //默认用32位                         
    if (count == 1)
    {
        if (!lua_isnumber(build_vm_code_lua,1))
        {
            lua_pushstring(build_vm_code_lua, "is not an integer\n");
            lua_error(build_vm_code_lua);
        }
        int o = lua_tonumber(build_vm_code_lua,1);    
        switch (o)
        {
        case 1:
            set_imm_operand_size(get_operand1((*ptr_ud)),new_op);    
            break;
        case 2:
            set_imm_operand_size(get_operand2((*ptr_ud)),new_op);     
            break;
        case 3:
            set_imm_operand_size(ptr_ud->operand[2],new_op);      
            break;
        }
    }
    else if(count == 2)
    {
        for (int i = 1; i <= 2;i++)
        {
           if (!lua_isnumber(build_vm_code_lua,i))
           {
              lua_pushstring(build_vm_code_lua, "is not an integer\n");
              lua_error(build_vm_code_lua);
           }                                           
        }

        int o = lua_tonumber(build_vm_code_lua,1);
        int size = lua_tonumber(build_vm_code_lua,2);

        new_op.size = size;
        switch (o)
        {
        case 1:
            set_imm_operand_size(get_operand1((*ptr_ud)),new_op);    
            break;
        case 2:
            set_imm_operand_size(get_operand2((*ptr_ud)),new_op);     
            break;
        case 3:
            set_imm_operand_size(ptr_ud->operand[2],new_op);      
            break;
        }
    }
    else
    {
        ptr_build_vm_bytecode->error("push_operand need 1 parameter\n");
        debugbreakpoint();
    } 
}


static int luai_get_operand_size(lua_State * L)
{
    int count = lua_gettop(build_vm_code_lua);
    int size = 0;
    if (count == 1)
    {
        if (!lua_isnumber(build_vm_code_lua,1))
        {
            lua_pushstring(build_vm_code_lua, "is not an integer\n");
            lua_error(build_vm_code_lua);
        }
        int o = lua_tonumber(build_vm_code_lua,1);
        switch (o)
        {
            case 1:
            size = get_operand1((*ptr_ud)).size;
            break;
            case 2:
            size = get_operand2((*ptr_ud)).size;
            break;
            case 3:
            size = ptr_ud->operand[2].size;
            break;
        }
    }
    else
    {
        printf("push_operand need 1 parameter\n");
        debugbreakpoint();
    } 
    lua_pushnumber(build_vm_code_lua,size);
    return 1;
}

#define luai_reg(name) lua_register(build_vm_code_lua,#name,luai_##name);

void lua_printError()
{
    const char* error = lua_tostring(build_vm_code_lua, -1);//打印错误结果  
    ptr_build_vm_bytecode->error("%s\n",error);
    lua_pop(build_vm_code_lua, 1);   
}

void lua_printError(const char * sz)
{
    const char* error = lua_tostring(build_vm_code_lua, -1);//打印错误结果
    ptr_build_vm_bytecode->error("%s,%s\n",sz,error);
    lua_pop(build_vm_code_lua, 1);
}

void register_build_vm_bytecode_lua()
{
    if (build_vm_code_lua == NULL)
    {
         build_vm_code_lua = luaL_newstate();
         luaL_openlibs(build_vm_code_lua);
         //lua_register(build_vm_code_lua,"b_not",luai_b_not);
         //luai_reg(b_not);

         lua_register(build_vm_code_lua,"randomseed",lua_randomseed);
         lua_register(build_vm_code_lua,"random",lua_random);

         luai_reg(run_stack)
         luai_reg(pushf)
         luai_reg(popf)

         luai_reg(push_vsp)
         luai_reg(pop_vsp)

         luai_reg(set_pc)

         luai_reg(b_read_mem)
         luai_reg(w_read_mem)
         luai_reg(d_read_mem)
         //luai_reg(q_read_mem)

         luai_reg(b_write_mem)
         luai_reg(w_write_mem)
         luai_reg(d_write_mem)
         //luai_reg(q_write_mem)

         luai_reg(b_nand)
         luai_reg(w_nand)
         luai_reg(d_nand)
         //luai_reg(q_nand)

         luai_reg(b_not)
         luai_reg(w_not)
         luai_reg(d_not)
         //luai_reg(q_not)

         luai_reg(b_neg)
         luai_reg(w_neg)
         luai_reg(d_neg)
         //luai_reg(q_neg)

         luai_reg(b_and)
         luai_reg(w_and)
         luai_reg(d_and)
         //luai_reg(q_and)

         luai_reg(b_or)
         luai_reg(w_or)
         luai_reg(d_or)
         //luai_reg(q_or)

         luai_reg(b_xor)
         luai_reg(w_xor)
         luai_reg(d_xor)
         //luai_reg(q_xor)

         luai_reg(b_add)
         luai_reg(w_add)
         luai_reg(d_add)
         //luai_reg(q_add)

         luai_reg(b_sub)
         luai_reg(w_sub)
         luai_reg(d_sub)
         //luai_reg(q_sub)

         luai_reg(b_cmp)
         luai_reg(w_cmp)
         luai_reg(d_cmp)
         //luai_reg(q_cmp)

         luai_reg(b_test)
         luai_reg(w_test)
         luai_reg(d_test)
         //luai_reg(q_test)

         /*
         luai_reg(b_div)
         luai_reg(w_div)
         luai_reg(d_div)
         //luai_reg(q_div)

         luai_reg(b_mult)
         luai_reg(w_mult)
         luai_reg(d_mult)
         //luai_reg(q_mult)
         */

         luai_reg(b_shr)
         luai_reg(w_shr)
         luai_reg(d_shr)
         //luai_reg(q_shr)

         luai_reg(b_shl)
         luai_reg(w_shl)
         luai_reg(d_shl)
         //luai_reg(q_shl)

         luai_reg(b_sar)
         luai_reg(w_sar)
         luai_reg(d_sar)
         //luai_reg(q_sar)


         luai_reg(ret)

         luai_reg(fstsw)
         luai_reg(get_cf)
         luai_reg(get_pf)
         luai_reg(get_af)
         luai_reg(get_zf)
         luai_reg(get_sf)
         luai_reg(get_of)
         luai_reg(get_df)
#ifdef DEBUG
         luai_reg(int3)
#endif
         luai_reg(get_string_ins_diff)

         luai_reg(b_push_imm)
         luai_reg(w_push_imm)
         luai_reg(d_push_imm)

         luai_reg(b_push_imm_zx)
         luai_reg(w_push_imm_zx)
         luai_reg(b_push_imm_sx)
         luai_reg(w_push_imm_sx)

         luai_reg(push)
         luai_reg(pop)
         lua_register(build_vm_code_lua,"push_operand",luai_read_vm_operand);
         lua_register(build_vm_code_lua,"pop_operand",luai_write_vm_operand);
         lua_register(build_vm_code_lua,"get_operand_size",luai_get_operand_size);
         lua_register(build_vm_code_lua,"resize_imm_operand",luai_resize_imm_operand);

 
#define luai_setglobalnumber(name) lua_pushnumber(build_vm_code_lua,T_##name);\
    lua_setglobal(build_vm_code_lua,#name);

         luai_setglobalnumber(AL);
         luai_setglobalnumber(BL);
         luai_setglobalnumber(CL);
         luai_setglobalnumber(DL);
         luai_setglobalnumber(AH);
         luai_setglobalnumber(BH);
         luai_setglobalnumber(CH);
         luai_setglobalnumber(DH);
         luai_setglobalnumber(AX);
         luai_setglobalnumber(BX);
         luai_setglobalnumber(CX);
         luai_setglobalnumber(DX);
         luai_setglobalnumber(SP);
         luai_setglobalnumber(BP);
         luai_setglobalnumber(SI);
         luai_setglobalnumber(DI);
         luai_setglobalnumber(EAX);
         luai_setglobalnumber(EBX);
         luai_setglobalnumber(ECX);
         luai_setglobalnumber(EDX);
         luai_setglobalnumber(ESP);
         luai_setglobalnumber(EBP);
         luai_setglobalnumber(ESI);
         luai_setglobalnumber(EDI);
         luai_setglobalnumber(RAX);
         luai_setglobalnumber(RBX);
         luai_setglobalnumber(RCX);
         luai_setglobalnumber(RDX);
         luai_setglobalnumber(RSP);
         luai_setglobalnumber(RBP);
         luai_setglobalnumber(RSI);
         luai_setglobalnumber(RDI);
         lua_pushnumber(build_vm_code_lua,T_FLAG);
         lua_setglobal(build_vm_code_lua,"T_FLAG");
         lua_pushnumber(build_vm_code_lua,T_INVALID);
         lua_setglobal(build_vm_code_lua,"T_INVALID");
         lua_pushnumber(build_vm_code_lua,T_8L);
         lua_setglobal(build_vm_code_lua,"T_8L");
         lua_pushnumber(build_vm_code_lua,T_8H);
         lua_setglobal(build_vm_code_lua,"T_8H");
         lua_pushnumber(build_vm_code_lua,T_16X);
         lua_setglobal(build_vm_code_lua,"T_16X");
         lua_pushnumber(build_vm_code_lua,T_E32X);
         lua_setglobal(build_vm_code_lua,"T_E32X");
         lua_pushnumber(build_vm_code_lua,T_NEXTINSADDR);
         lua_setglobal(build_vm_code_lua,"T_NEXTINSADDR");
         lua_pushnumber(build_vm_code_lua,T_JMPINSADDR);
         lua_setglobal(build_vm_code_lua,"T_JMPINSADDR");         


         //lua_pushnumber(build_vm_code_lua,T_AL);
         //lua_setglobal(build_vm_code_lua,"al");
         switch (luaL_loadfile(build_vm_code_lua,"./build_vm_handle.lua"))
         {
         case LUA_ERRSYNTAX:
             lua_printError("Lua ErrSyntax\n");
             ptr_build_vm_bytecode->error("Lua ErrSyntax\n");
             lua_close(build_vm_code_lua);
             build_vm_code_lua = NULL;
             break;
         case LUA_ERRMEM:
             lua_printError("Lua ErrMem\n");
             ptr_build_vm_bytecode->error("Lua ErrMem\n");
             lua_close(build_vm_code_lua);
             build_vm_code_lua = NULL;
             break;
         case LUA_ERRGCMM:
             lua_printError("Lua ErrGCMM.\n");
             ptr_build_vm_bytecode->error("Lua ErrGCMM.\n");
             lua_close(build_vm_code_lua);
             build_vm_code_lua = NULL;
             break;
         case LUA_OK:
             ptr_build_vm_bytecode->pass("Lua OK\n");
             lua_pcall(build_vm_code_lua, 0, LUA_MULTRET, 0);
             break;
         default:
             //ptr_build_vm_bytecode->warn("aa");
             //ptr_build_vm_bytecode->error("Can not find build_vm_handle.lua!\n");
             ptr_build_vm_bytecode->warn("Can not find build_vm_handle.lua!\n");
             lua_close(build_vm_code_lua);
             build_vm_code_lua = NULL;
             break;
         }
    }
}

/*
static int luai_b_not(lua_State * L)
{
    ptr_combos_vm_code->b_not();
    return 0;
}

static int luai_b_and(lua_State * L)
{
    ptr_combos_vm_code->b_and();
    return 0;
}*/



 
void printf_map_register_store(std::map<int,RegisterStore> & _p_map_in,
        std::map<int,RegisterStore> & _p_map_out)
{
#ifdef DEBUG
    int i = 0;
    while (_p_map_in.find(i) != _p_map_in.end())
    {
        printf("Label :%x\n",i);
        printf("In Key:%08x\n",_p_map_in[i].get_key());
        OutDI di;
        di.set_begin_text("");
        di.set_end_text(" ");

        di.print_vmregister_information(_p_map_in[i]);

        printf("\nOut Key:%08x\n",_p_map_out[i].get_key());
        di.set_begin_text("");
        di.set_end_text(" ");
        di.print_vmregister_information(_p_map_out[i]);
        i++;
        printf("\n");
    }
#endif
}

void printf_map_register_store(std::map<int,RegisterStore> & _p_map,
        char *sz)
{/*{{{*/
    std::map<int,RegisterStore>::iterator iter = _p_map.begin();
    for (iter; iter!=_p_map.end();iter++)
    {
        printf("Label :%x\n",iter->first);
        printf("%s Key:%08x\n\n",sz,iter->second.get_key());
        OutDI di;
        di.set_begin_text(sz);
        di.set_end_text("\n");
        di.print_vmregister_information(iter->second);
    }
}/*}}}*/

long BuildVMByteCode::get_vmcode_address(int _label_index)
{
    long result = 0;
    if (var_map_label_vmcode_addr.find(_label_index) !=
            var_map_label_vmcode_addr.end())
    {
       result = var_map_label_vmcode_addr[_label_index];
    }
    return result;
}


long BuildVMByteCode::create_vm_entry(int _piece_label)
{
    long opcode_addr = get_vmcode_address(_piece_label);
    long init_de_key = 0x12345678;
    bool t_sign = ptr_addr_table->get_sign();
    ptr_addr_table->set_sign(true);
    long head_address = ptr_addr_table->assign_address(0x70);
    ptr_addr_table->set_sign(t_sign);
    VMCodeBufferManage * buffer_manage = var_map_label_vmbuffer_manage[_piece_label];

    ppcode_block_info info = ptr_vm->create_function_head(
                            head_address,
                            opcode_addr,
                            &(buffer_manage->get_pcode()),
                            123,
                            123456,
                            init_de_key); //pcode位置有问题
    ptr_addr_table->copy(head_address,info->buf,info->size);
#ifdef DEBUG
    printf("VM EntryAddress:%x\n",head_address);
#endif
    return head_address;
}


long BuildVMByteCode::build_vmcode(bool b_allocator)
{
    long vm_byte_code_head  = 0;
    newlabel_count = 0;
    for (std::vector<CodePiece>::iterator iter = var_list_code_piece.begin();
         iter != var_list_code_piece.end();iter++)
    {
        int var_cur_label = iter->get_label();
        VMCodeBufferManage * cur_vmbuffer_manage = NULL;
        if (b_allocator)
        {
            cur_vmbuffer_manage = new VMCodeBufferManage(ptr_vm);
            cur_vmbuffer_manage->set_vmcode_label(var_cur_label);
            var_vmcode_manager_list.push_back(cur_vmbuffer_manage);
            var_map_label_vmbuffer_manage.insert(
                                    std::make_pair(
                                            var_cur_label,cur_vmbuffer_manage));
        }
        else
        {
            if (var_map_label_vmbuffer_manage.find(var_cur_label)
                            != var_map_label_vmbuffer_manage.end())
            {
                cur_vmbuffer_manage = var_map_label_vmbuffer_manage[var_cur_label];
            }
            else
            {
                debugbreakpoint();
            }
        }


        PCode & var_pcode = cur_vmbuffer_manage->get_pcode();
        VCombosVMCode & var_combos_vm_code = cur_vmbuffer_manage->get_generator();
        VTable var_vmcode_info;
        if (b_allocator)
        {
            var_vmcode_info.key = var_pcode.get_original_key();
            var_vmcode_info.v = &var_combos_vm_code;
            var_pcode.count_vmcode_begin();
            var_pcode.set_key(0x12345678);
        }
        else
        {
#ifdef DEBUG
            char file_name[256];
            memset(&file_name,0,256);
            if (vmdebug_out_file_directory == false)
            {
                vmdebug_out_file_directory = true;
                //system("rm -r ./virtual_machine_assembly");
                //system("mkdir virtual_machine_assembly");
            }
            //_mkdir("virtual_machine_assembly");
            sprintf(file_name,"virtual_machine_assembly/Label%d,%08x\n", iter->get_label(),var_map_label_vmcode_addr[iter->get_label()]);
            var_pcode.out_log_file(file_name);
#endif
        }


        var_pcode.register_store_in = var_map_label_vmreg_store_in[iter->get_label()];
        var_pcode.register_store_out = var_map_label_vmreg_store_out[iter->get_label()];
        var_combos_vm_code.save_vm_context();



        for (std::list<ud_t>::iterator uiter = iter->get_piece().begin();
             uiter != iter->get_piece().end();uiter++)
        {
            if (b_allocator == false)
            for (std::vector<long*>::iterator entry_iter = var_entry_address.begin();
                 entry_iter != var_entry_address.end();entry_iter++)
            {
                long * addr = *entry_iter;
                if (uiter->insn_offset == *addr)
                {
                    if (get_vmcode_address(var_cur_label))
                        *addr = create_vm_entry(var_cur_label);
                    else
                    {
                        debugbreakpoint();
                        printf("Address Not Found%x\n",*addr);
                    }
                }
            }
            std::list<ud_t>::iterator uiter_check_end = uiter;
            if (++uiter_check_end == iter->get_piece().end()) //是否是最后一条指令
            {
                long next_addr = 0;
                long jmp_addr = 0;
                bool test_find_addr_next = var_map_label_vmreg_store_in.find(iter->get_label() + 1) !=
                                var_map_label_vmreg_store_in.end();
                bool test_find_addr_jmp = var_map_label_vmreg_store_in.find(iter->get_jmplabel()) !=
                                var_map_label_vmreg_store_in.end();
                if (test_find_addr_next)
                    next_addr = get_vmcode_address(iter->get_label() + 1);
                if (test_find_addr_jmp)
                    jmp_addr = get_vmcode_address(iter->get_jmplabel());

                 long ignore_build_code_addr = 0;
                 ignore_build_code_addr = iter->get_jmplabel();

                switch (iter->get_opcode_attribute())
                {
                case OPCODE_ATTRIBUTE_JCC: //虚拟机内部条件跳转
                {
                    var_combos_vm_code.d_push_imm(jmp_addr);
                    var_combos_vm_code.d_push_imm(next_addr);
                    var_combos_vm_code.pop(T_NEXTINSADDR);
                    var_combos_vm_code.pop(T_JMPINSADDR);
                    build(var_combos_vm_code,*uiter);
                    var_combos_vm_code.recover_vm_context();
                    var_combos_vm_code.push(T_NEXTINSADDR);
                    var_combos_vm_code.set_pc(0x12345678);
                }
                    break;
                case OPCODE_ATTRIBUTE_JMP: //虚拟机内部跳转
                {
                    var_combos_vm_code.recover_vm_context();
                    var_combos_vm_code.d_push_imm(jmp_addr);
                    var_combos_vm_code.set_pc(0x12345678);
                }
                    break;
                case OPCODE_ATTRIBUTE_CALL: //虚拟机内部call
                {
                    debugbreakpoint();
                }
                    break;
                case OPCODE_ATTRIBUTE_EXTERNAL_JMP: //跳转到虚拟机外部
                {
                    if (iter->get_jmplabel() != PC_NONE)
                    {
                       var_combos_vm_code.d_push_imm(ignore_build_code_addr);
                    }
                    else
                    {
                        read_vm_operand(var_combos_vm_code,uiter->operand[0]);
                    }
                    //var_combos_vm_code.recover_vm_context();
                    var_combos_vm_code.ret();
                }
                    break;
                case OPCODE_ATTRIBUTE_EXTERNAL_CALL:
                {
                    int next_pcode_addr = 0;
                    if (get_vmcode_address(iter->get_label() + 1))
                         next_pcode_addr = create_vm_entry(iter->get_label() + 1);
                    else
                         next_pcode_addr = uiter->pc;
                    var_combos_vm_code.d_push_imm(next_pcode_addr);
                    if (iter->get_jmplabel() != PC_NONE)
                    {
                        var_combos_vm_code.d_push_imm(ignore_build_code_addr);
                    }
                    else
                    {
                        read_vm_operand(var_combos_vm_code,uiter->operand[0]);
                    }
                    //var_combos_vm_code.recover_vm_context();
                    var_combos_vm_code.ret();
//                    printf("处理OPCODE_ATTRIBUTE_EXTERNAL_CALL\n");
                }
                    break;
                case OPCODE_ATTRIBUTE_EXTERNAL_JCC:
                {
                   printf("jcc to out of VM\n");
                   debugbreakpoint();
                }
                    break;
                case OPCODE_ATTRIBUTE_NORMAL:
                {
                    build(var_combos_vm_code,*uiter);
                    var_combos_vm_code.recover_vm_context();
                    //var_combos_vm_code.push(T_NEXTINSADDR);
                    var_combos_vm_code.d_push_imm(next_addr);
                    var_combos_vm_code.set_pc(0x12345678);
                }
                    break;
                case OPCODE_ATTRIBUTE_RET:
                {
                    build(var_combos_vm_code,*uiter);
                }
                    break;
                case OPCODE_ATTRIBUTE_EXIT:
                {
                    build(var_combos_vm_code,*uiter);
                    var_combos_vm_code.d_push_imm(ignore_build_code_addr);
                    //var_combos_vm_code.recover_vm_context();
                    var_combos_vm_code.ret();
                }
                    break;
                default:
                    break;
                }


            }
            else { //不是最后一条指令
                build(var_combos_vm_code,*uiter);
            }
#ifdef DEBUG
            if (b_allocator == false ){
            fprintf(var_pcode.get_log(),"\nbuild %-30s\n\n",uiter->insn_buffer);
            printf("build %-30s ...done\n",uiter->insn_buffer);
            }
#endif
        }

        if (b_allocator)
        {
            size_t vm_piece_size = var_pcode.count_vmcode_end();
#ifdef DEBUG
            printf("Label %d,Size:%d\n",iter->get_label(),vm_piece_size);
#endif
            long t_byte_code_addr = ptr_addr_table->assign_address(vm_piece_size,var_vmcode_info);
            //long t_byte_code_addr = ptr_addr_table->assign_address(vm_piece_size);
            if(vm_byte_code_head == 0)
                vm_byte_code_head = t_byte_code_addr;
#ifdef DEBUG
            if (ptr_addr_table->get_sign())
                printf("Alloced PCODE Address %08x - %08x Flags:%d\n",
                       t_byte_code_addr,
                       t_byte_code_addr + vm_piece_size,
                       ptr_addr_table->get_sign());
            else
                printf("Alloced PCODE Address %08x - %08x Flags:%d\n",
                       t_byte_code_addr - vm_piece_size,
                       t_byte_code_addr,
                       ptr_addr_table->get_sign());
#endif
            var_map_label_vmcode_addr.insert(std::make_pair(iter->get_label(),t_byte_code_addr));
        }

    }
    return vm_byte_code_head;

}


void BuildVMByteCode::register_mapped_init()
{
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RAX,T_RAX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RBX,T_RBX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RCX,T_RCX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RDX,T_RDX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RSP,T_RSP));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RBP,T_RBP));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RSI,T_RSI));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_RDI,T_RDI));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_EAX,T_EAX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_EBX,T_EBX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_ECX,T_ECX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_EDX,T_EDX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_ESP,T_ESP));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_EBP,T_EBP));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_ESI,T_ESI));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_EDI,T_EDI));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_AX,T_AX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_BX,T_BX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_CX,T_CX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_DX,T_DX));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_SP,T_SP));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_BP,T_BP));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_SI,T_SI));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_DI,T_DI));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_AL,T_AL));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_AH,T_AH));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_BL,T_BL));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_CL,T_CL));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_DL,T_DL));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_BH,T_BH));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_CH,T_CH));
    mapped_vm_register.insert(make_pair<ud_type,long>(UD_R_DH,T_DH));

}


void BuildVMByteCode::call_lua_functions(const char * lua_fuc_name)
{
    lua_getglobal(build_vm_code_lua,lua_fuc_name);
    if (lua_isfunction(build_vm_code_lua,1) == 0)
    {
        ptr_build_vm_bytecode->error("Lua Has Not Declare Function %s\n",lua_fuc_name);
        lua_printError();

    }
    else
    {
        switch (lua_pcall(build_vm_code_lua,0,0,0))
        {
        case LUA_ERRRUN:
            ptr_build_vm_bytecode->error("Lua ErrRun\n");
            lua_printError();
            break;
        case LUA_ERRMEM:
            lua_printError();
            ptr_build_vm_bytecode->error("Lua ErrMem\n");
            break;
        case LUA_ERRERR:
            lua_printError();
            ptr_build_vm_bytecode->error("Lua Not Functions:%s\n",lua_fuc_name);
            break;
        default:
            //printf("运行成功\n");
            break;
        }
    }


}



BuildVMByteCode::BuildVMByteCode(VirtualMachineManage * ptr_vmmanage,
        pCodeBufferInfo ptr_info,
        VMAddressTable *ptr_address_table,
        std::vector<long*> & entry_address)
    :newlabel_count(0)
#ifdef DEBUG
     ,vmdebug_out_file_directory(false)
#endif
{
    /*
    random_engender.randomseed(123456);
    for (int i = 0;i < 10;i++)
    {
        std::cout << random_engender.random() << std::endl;
    }
    std::cout << "-------------" << std::endl;
    random_engender.randomseed(123456);
    for (int i = 0;i < 10;i++)
    {
        std::cout << random_engender.random() << std::endl;
    }
    debugbreakpoint();*/
   register_build_vm_bytecode_lua();
   var_entry_address = entry_address;
   if (!ptr_info->size)
        return;
    register_mapped_init();
    Analysis var_analysis;

    var_analysis.disasm(ptr_info,var_list_code_piece);

    var_analysis.printf_piece(var_list_code_piece);
    VirtualMachine *ptr_rand_vm = ptr_vmmanage->rand_virtual_machine();
    ptr_vm = ptr_rand_vm;
    ptr_addr_table = ptr_address_table;

    //printf_map_register_store(var_map_label_vmreg_store,"var_map_label_vmreg_store");

    full_register_store(var_list_code_piece,var_map_label_vmreg_store_in,var_map_label_vmreg_store_out);
    //printf_map_register_store(var_map_label_vmreg_store_in,"In  ");
    //printf_map_register_store(var_map_label_vmreg_store_out,"Out ");
    printf_map_register_store(var_map_label_vmreg_store_in,var_map_label_vmreg_store_out);

    long vm_byte_code_head  = 0;

    call_lua_functions("on_pre_compile");
    vm_byte_code_head = build_vmcode(true);
    call_lua_functions("on_compile");
    build_vmcode(false);
    call_lua_functions("on_after_compile");

    ptr_address_table->copy();
    long init_vm_key = 0x12345678;
    bool t_sign = ptr_address_table->get_sign();
    ptr_address_table->set_sign(true);
    long head_address = ptr_address_table->assign_address(0x70);
    ptr_address_table->set_sign(t_sign);
    ppcode_block_info info = ptr_rand_vm->create_function_head(head_address,
          vm_byte_code_head,
          &(var_vmcode_manager_list[0]->get_pcode()),
          1,//ptr_info->addr + ptr_info->size,
          123456,
          init_vm_key); //pcode位置有问题

    ptr_address_table->copy(head_address,info->buf,info->size);

    ptr_info->addr = head_address;

}

BuildVMByteCode::BuildVMByteCode(VirtualMachineManage * ptr_vmmanage,
        pCodeBufferInfo ptr_info,
        VMAddressTable *ptr_address_table)
    :newlabel_count(0)
#ifdef DEBUG
     ,vmdebug_out_file_directory(false)
#endif

{

    register_build_vm_bytecode_lua();

    if (!ptr_info->size)
        return;
    register_mapped_init();
    Analysis var_analysis;

    var_analysis.disasm(ptr_info,var_list_code_piece);

    var_analysis.printf_piece(var_list_code_piece);
    VirtualMachine *ptr_rand_vm = ptr_vmmanage->rand_virtual_machine();
    ptr_vm = ptr_rand_vm;
    ptr_addr_table = ptr_address_table;

    //printf_map_register_store(var_map_label_vmreg_store,"var_map_label_vmreg_store");

    full_register_store(var_list_code_piece,var_map_label_vmreg_store_in,var_map_label_vmreg_store_out);
    //printf_map_register_store(var_map_label_vmreg_store_in,"In  ");
    //printf_map_register_store(var_map_label_vmreg_store_out,"Out ");
    printf_map_register_store(var_map_label_vmreg_store_in,var_map_label_vmreg_store_out);
    
    long vm_byte_code_head  = 0;

    call_lua_functions("on_pre_compile");
    vm_byte_code_head = build_vmcode(true);
    call_lua_functions("on_compile");
    build_vmcode(false);
    call_lua_functions("on_after_compile");
    ptr_address_table->copy();  
    long init_vm_key = 0x12345678;
    bool t_sign = ptr_address_table->get_sign();
    ptr_address_table->set_sign(true);
    long head_address = ptr_address_table->assign_address(0x70);
    ptr_address_table->set_sign(t_sign);
    ppcode_block_info info = ptr_rand_vm->create_function_head(head_address,
          vm_byte_code_head,
          &(var_vmcode_manager_list[0]->get_pcode()),
          1,//ptr_info->addr + ptr_info->size,
          123456,
          init_vm_key); //pcode位置有问题

    ptr_address_table->copy(head_address,info->buf,info->size);
    
    ptr_info->addr = head_address; 
}



BuildVMByteCode::~BuildVMByteCode()
{
   for (std::vector<VMCodeBufferManage*>::iterator iter = var_vmcode_manager_list.begin();
         iter != var_vmcode_manager_list.end();iter++) 
   {
      delete *iter;
   }
}

void BuildVMByteCode::vm_operand(
      VCombosVMCode & var_combos_vm_code,
      ud_operand & var_operand)
{/*{{{*/
   var_combos_vm_code.impact_vmregister(false);
   switch (var_operand.type)
   {
      case UD_OP_MEM:
         {
            int count = 0;
            if (mapped_vm_register.find(var_operand.base) == mapped_vm_register.end())
            {
                 //printf("没有base\n");
            }
            else
            {
               long base = mapped_vm_register[var_operand.base];
               var_combos_vm_code.push(base); 
               count++;
            }
            if (mapped_vm_register.find(var_operand.index) == mapped_vm_register.end())
            {
               //printf("没有index\n");
            }
            else
            {
               long index = mapped_vm_register[var_operand.index];
               var_combos_vm_code.push(index);
               switch (var_operand.scale)
               {
               case 1:
                   var_combos_vm_code.b_push_imm(0);
                   break;
               case 2:
                   var_combos_vm_code.b_push_imm(1);
                   break;
               case 4:
                   var_combos_vm_code.b_push_imm(2);
                   break;
               case 8:
                   var_combos_vm_code.b_push_imm(3);
                   break;
               }
               if(var_operand.scale != 0)
               {
                   var_combos_vm_code.d_shl();
                   var_combos_vm_code.pop(T_INVALID);
               }
               count++;
            }
            if (var_operand.lval.sdword)
            {
               count++;
               if (var_operand.offset == 8)
               {
                  signed char lval = var_operand.lval.sbyte;
                  var_combos_vm_code.b_push_imm_sx(lval);
               }
               else
               {
                  long lval = var_operand.lval.sdword;
                  var_combos_vm_code.d_push_imm(lval);
               }
            }
            for (int i = 1; i < count ; i++)
            {
               var_combos_vm_code.d_add();
               var_combos_vm_code.pop(T_INVALID);
            }
            /*switch (var_operand.size)
            {
               case 8:
                  var_combos_vm_code.b_read_mem();
                  break;
               case 16:
                  var_combos_vm_code.w_read_mem();
                  break;
               case 32:
                  var_combos_vm_code.d_read_mem();
                  break;
            } */
              
         }
         break;
      case UD_OP_IMM:
         {
            switch (var_operand.size)
            {
               case 8:
                  {
                     signed char lval = var_operand.lval.sbyte; 
                     var_combos_vm_code.b_push_imm(lval);
                  }
                  break;
               case 16:
                  {
                     signed short lval = var_operand.lval.sword;
                     var_combos_vm_code.w_push_imm(lval); 
                  }
                  break;
               case 32:
                  {
                     int lval = var_operand.lval.sdword;
                     var_combos_vm_code.d_push_imm(lval);  
                  }
                  break;
            }
         }
         break;
      case UD_OP_REG:
         {
            if (mapped_vm_register.find(var_operand.base) == mapped_vm_register.end())
            {
                 printf("No Register\n");
                 debugbreakpoint();
            }
            else
            {
               long base = mapped_vm_register[var_operand.base];
               var_combos_vm_code.push(base); 
            } 
         }
         break;
   }
   var_combos_vm_code.impact_vmregister(true);
}/*}}}*/

long BuildVMByteCode::get_vm_register(ud_type _register)
{/*{{{*/
   long result = T_INVALID;
   if (mapped_vm_register.find(_register) == mapped_vm_register.end())
   {
      printf("Can not identify Register\n");
   }
   else
   {
      result = mapped_vm_register[_register];
   }
   return result;
}/*}}}*/



/*
void BuildVMByteCode::build(VCombosVMCode & var_combos_vm_code,ud_t &var_ud)
{
  build(var_combos_vm_code,var_ud,0);
} 
*/

void BuildVMByteCode::copy_exec_code_to_stack(VCombosVMCode & var_combos_vm_code,
                                              const uint8_t * var_code_buffer,
                                              size_t var_code_size)
{
    var_combos_vm_code.b_push_imm(0xc3);
    for (int i = var_code_size - 1; i >= 0; i--)
    {
       //printf("%x ",code_addr[i]);
       //code_addr++;
       var_combos_vm_code.b_push_imm(var_code_buffer[i]);
    }
    var_combos_vm_code.b_push_imm(var_code_size + 1);
#ifdef DEBUG
    var_combos_vm_code.int3();
#endif
    var_combos_vm_code.run_stack();
}

#ifdef WINDOWS

const unsigned int instruction_table_count = 575;
const char * instruction_table[575] =
{
	"ADC",           // X86/X64
	"ADD",           // X86/X64
	"ADDPD",         // SSE2
	"ADDPS",         // SSE
	"ADDSD",         // SSE2
	"ADDSS",         // SSE
	"ADDSUBPD",      // SSE3
	"ADDSUBPS",      // SSE3
	"AMD_PREFETCH",
	"AMD_PREFETCHW",
	"AND",           // X86/X64
	"ANDNPD",        // SSE2
	"ANDNPS",        // SSE
	"ANDPD",         // SSE2
	"ANDPS",         // SSE
	"BLENDPD",       // SSE4.1
	"BLENDPS",       // SSE4.1
	"BLENDVPD",      // SSE4.1
	"BLENDVPS",      // SSE4.1
	"BSF",           // X86/X64
	"BSR",           // X86/X64
	"BSWAP",         // X86/X64 (i486)
	"BT",            // X86/X64
	"BTC",           // X86/X64
	"BTR",           // X86/X64
	"BTS",           // X86/X64
	"CALL",          // X86/X64
	"CBW",           // X86/X64
	"CDQE",          // X64 only
	"CLC",           // X86/X64
	"CLD",           // X86/X64
	"CLFLUSH",       // SSE2
	"CMC",           // X86/X64
	"CMOVA",         //X86/X64 (cmovcc) (i586)
	"CMOVAE",        // X86/X64 (cmovcc) (i586)
	"CMOVB",         // X86/X64 (cmovcc) (i586)
	"CMOVBE",        // X86/X64 (cmovcc) (i586)
	"CMOVC",         // X86/X64 (cmovcc) (i586)
	"CMOVE",         // X86/X64 (cmovcc) (i586)
	"CMOVG",         // X86/X64 (cmovcc) (i586)
	"CMOVGE",        // X86/X64 (cmovcc) (i586)
	"CMOVL",         // X86/X64 (cmovcc) (i586)
	"CMOVLE",        // X86/X64 (cmovcc) (i586)
	"CMOVNA",        // X86/X64 (cmovcc) (i586)
	"CMOVNAE",       // X86/X64 (cmovcc) (i586)
	"CMOVNB",        // X86/X64 (cmovcc) (i586)
	"CMOVNBE",       // X86/X64 (cmovcc) (i586)
	"CMOVNC",        // X86/X64 (cmovcc) (i586)
	"CMOVNE",        // X86/X64 (cmovcc) (i586)
	"CMOVNG",        // X86/X64 (cmovcc) (i586)
	"CMOVNGE",       // X86/X64 (cmovcc) (i586)
	"CMOVNL",        // X86/X64 (cmovcc) (i586)
	"CMOVNLE",       // X86/X64 (cmovcc) (i586)
	"CMOVNO",        // X86/X64 (cmovcc) (i586)
	"CMOVNP",        // X86/X64 (cmovcc) (i586)
	"CMOVNS",        // X86/X64 (cmovcc) (i586)
	"CMOVNZ",        // X86/X64 (cmovcc) (i586)
	"CMOVO",         // X86/X64 (cmovcc) (i586)
	"CMOVP",         // X86/X64 (cmovcc) (i586)
	"CMOVPE",        // X86/X64 (cmovcc) (i586)
	"CMOVPO",        // X86/X64 (cmovcc) (i586)
	"CMOVS",         // X86/X64 (cmovcc) (i586)
	"CMOVZ",         // X86/X64 (cmovcc) (i586)

	"CMP",           // X86/X64
	"CMPPD",         // SSE2
	"CMPPS",         // SSE
	"CMPSD",         // SSE2
	"CMPSS",         // SSE
	"CMPXCHG",       // X86/X64 (i486)
	"CMPXCHG16B",    // X64 only
	"CMPXCHG8B",     // X86/X64 (i586)
	"COMISD",        // SSE2
	"COMISS",        // SSE
	"CPUID",         // X86/X64 (i486)
	"CRC32",         // SSE4.2
	"CVTDQ2PD",      // SSE2
	"CVTDQ2PS",      // SSE2
	"CVTPD2DQ",      // SSE2
	"CVTPD2PI",      // SSE2
	"CVTPD2PS",      // SSE2
	"CVTPI2PD",      // SSE2
	"CVTPI2PS",      // SSE
	"CVTPS2DQ",      // SSE2
	"CVTPS2PD",      // SSE2
	"CVTPS2PI",      // SSE
	"CVTSD2SI",      // SSE2
	"CVTSD2SS",      // SSE2
	"CVTSI2SD",      // SSE2
	"CVTSI2SS",      // SSE
	"CVTSS2SD",      // SSE2
	"CVTSS2SI",      // SSE
	"CVTTPD2DQ",     // SSE2
	"CVTTPD2PI",     // SSE2
	"CVTTPS2DQ",     // SSE2
	"CVTTPS2PI",     // SSE
	"CVTTSD2SI",     // SSE2
	"CVTTSS2SI",     // SSE
	"CWDE",          // X86/X64
	"DAA",           // X86 only
	"DAS",           // X86 only
	"DEC",           // X86/X64
	"DIV",           // X86/X64
	"DIVPD",         // SSE2
	"DIVPS",         // SSE
	"DIVSD",         // SSE2
	"DIVSS",         // SSE
	"DPPD",          // SSE4.1
	"DPPS",          // SSE4.1
	"EMMS",          // MMX
	"ENTER",         // X86/X64
	"EXTRACTPS",     // SSE4.1
	"F2XM1",         // X87
	"FABS",          // X87
	"FADD",          // X87
	"FADDP",         // X87
	"FBLD",          // X87
	"FBSTP",         // X87
	"FCHS",          // X87
	"FCLEX",         // X87
	"FCMOVB",        // X87
	"FCMOVBE",       // X87
	"FCMOVE",        // X87
	"FCMOVNB",       // X87
	"FCMOVNBE",      // X87
	"FCMOVNE",       // X87
	"FCMOVNU",       // X87
	"FCMOVU",        // X87
	"FCOM",          // X87
	"FCOMI",         // X87
	"FCOMIP",        // X87
	"FCOMP",         // X87
	"FCOMPP",        // X87
	"FCOS",          // X87
	"FDECSTP",       // X87
	"FDIV",          // X87
	"FDIVP",         // X87
	"FDIVR",         // X87
	"FDIVRP",        // X87
	"FEMMS",         // 3dNow!
	"FFREE",         // X87
	"FIADD",         // X87
	"FICOM",         // X87
	"FICOMP",        // X87
	"FIDIV",         // X87
	"FIDIVR",        // X87
	"FILD",          // X87
	"FIMUL",         // X87
	"FINCSTP",       // X87
	"FINIT",         // X87
	"FIST",          // X87
	"FISTP",         // X87
	"FISTTP",        // SSE3
	"FISUB",         // X87
	"FISUBR",        // X87
	"FLD",           // X87
	"FLD1",          // X87
	"FLDCW",         // X87
	"FLDENV",        // X87
	"FLDL2E",        // X87
	"FLDL2T",        // X87
	"FLDLG2",        // X87
	"FLDLN2",        // X87
	"FLDPI",         // X87
	"FLDZ",          // X87
	"FMUL",          // X87
	"FMULP",         // X87
	"FNCLEX",        // X87
	"FNINIT",        // X87
	"FNOP",          // X87
	"FNSAVE",        // X87
	"FNSTCW",        // X87
	"FNSTENV",       // X87
	"FNSTSW",        // X87
	"FPATAN",        // X87
	"FPREM",         // X87
	"FPREM1",        // X87
	"FPTAN",         // X87
	"FRNDINT",       // X87
	"FRSTOR",        // X87
	"FSAVE",         // X87
	"FSCALE",        // X87
	"FSIN",          // X87
	"FSINCOS",       // X87
	"FSQRT",         // X87
	"FST",           // X87
	"FSTCW",         // X87
	"FSTENV",        // X87
	"FSTP",          // X87
	"FSTSW",         // X87
	"FSUB",          // X87
	"FSUBP",         // X87
	"FSUBR",         // X87
	"FSUBRP",        // X87
	"FTST",          // X87
	"FUCOM",         // X87
	"FUCOMI",        // X87
	"FUCOMIP",       // X87
	"FUCOMP",        // X87
	"FUCOMPP",       // X87
	"FWAIT",         // X87
	"FXAM",          // X87
	"FXCH",          // X87
	"FXRSTOR",       // X87
	"FXSAVE",        // X87
	"FXTRACT",       // X87
	"FYL2X",         // X87
	"FYL2XP1",       // X87
	"HADDPD",        // SSE3
	"HADDPS",        // SSE3
	"HSUBPD",        // SSE3
	"HSUBPS",        // SSE3
	"IDIV",          // X86/X64
	"IMUL",          // X86/X64
	"INC",           // X86/X64
	"INT3",          // X86/X64
	"JA",             // Begin (jcc)
	"JAE",           // X86/X64 (jcc)
	"JB",            // X86/X64 (jcc)
	"JBE",           // X86/X64 (jcc)
	"JC",            // X86/X64 (jcc)
	"JE",            // X86/X64 (jcc)
	"JG",            // X86/X64 (jcc)
	"JGE",           // X86/X64 (jcc)
	"JL",            // X86/X64 (jcc)
	"JLE",           // X86/X64 (jcc)
	"JNA",           // X86/X64 (jcc)
	"JNAE",          // X86/X64 (jcc)
	"JNB",           // X86/X64 (jcc)
	"JNBE",          // X86/X64 (jcc)
	"JNC",           // X86/X64 (jcc)
	"JNE",           // X86/X64 (jcc)
	"JNG",           // X86/X64 (jcc)
	"JNGE",          // X86/X64 (jcc)
	"JNL",           // X86/X64 (jcc)
	"JNLE",          // X86/X64 (jcc)
	"JNO",           // X86/X64 (jcc)
	"JNP",           // X86/X64 (jcc)
	"JNS",           // X86/X64 (jcc)
	"JNZ",           // X86/X64 (jcc)
	"JO",            // X86/X64 (jcc)
	"JP",            // X86/X64 (jcc)
	"JPE",           // X86/X64 (jcc)
	"JPO",           // X86/X64 (jcc)
	"JS",            // X86/X64 (jcc)
	"JZ",            // X86/X64 (jcc)
	"JMP",           // X86/X64 (jmp)
	"LDDQU",         // SSE3
	"LDMXCSR",       // SSE
	"LAHF",          // X86/X64 (CPUID NEEDED)
	"LEA",           // X86/X64
	"LEAVE",         // X86/X64
	"LFENCE",        // SSE2
	"MASKMOVDQU",    // SSE2
	"MASKMOVQ",      // MMX-Ext
	"MAXPD",         // SSE2
	"MAXPS",         // SSE
	"MAXSD",         // SSE2
	"MAXSS",         // SSE
	"MFENCE",        // SSE2
	"MINPD",         // SSE2
	"MINPS",         // SSE
	"MINSD",         // SSE2
	"MINSS",         // SSE
	"MONITOR",       // SSE3
	"MOV",           // X86/X64
	"MOVAPD",        // SSE2
	"MOVAPS",        // SSE
	"MOVBE",         // SSE3 - Intel-Atom
	"MOVD",          // MMX/SSE2
	"MOVDDUP",       // SSE3
	"MOVDQ2Q",       // SSE2
	"MOVDQA",        // SSE2
	"MOVDQU",        // SSE2
	"MOVHLPS",       // SSE
	"MOVHPD",        // SSE2
	"MOVHPS",        // SSE
	"MOVLHPS",       // SSE
	"MOVLPD",        // SSE2
	"MOVLPS",        // SSE
	"MOVMSKPD",      // SSE2
	"MOVMSKPS",      // SSE2
	"MOVNTDQ",       // SSE2
	"MOVNTDQA",      // SSE4.1
	"MOVNTI",        // SSE2
	"MOVNTPD",       // SSE2
	"MOVNTPS",       // SSE
	"MOVNTQ",        // MMX-Ext
	"MOVQ",          // MMX/SSE/SSE2
	"MOVQ2DQ",       // SSE2
	"MOVSD",         // SSE2
	"MOVSHDUP",      // SSE3
	"MOVSLDUP",      // SSE3
	"MOVSS",         // SSE
	"MOVSX",         // X86/X64
	"MOVSXD",        // X86/X64
	"MOVUPD",        // SSE2
	"MOVUPS",        // SSE
	"MOVZX",         // X86/X64
	"MOV_PTR",       // X86/X64
	"MPSADBW",       // SSE4.1
	"MUL",           // X86/X64
	"MULPD",         // SSE2
	"MULPS",         // SSE
	"MULSD",         // SSE2
	"MULSS",         // SSE
	"MWAIT",         // SSE3
	"NEG",           // X86/X64
	"NOP",           // X86/X64
	"NOT",           // X86/X64
	"OR",            // X86/X64
	"ORPD",          // SSE2
	"ORPS",          // SSE
	"PABSB",         // SSSE3
	"PABSD",         // SSSE3
	"PABSW",         // SSSE3
	"PACKSSDW",      // MMX/SSE2
	"PACKSSWB",      // MMX/SSE2
	"PACKUSDW",      // SSE4.1
	"PACKUSWB",      // MMX/SSE2
	"PADDB",         // MMX/SSE2
	"PADDD",         // MMX/SSE2
	"PADDQ",         // SSE2
	"PADDSB",        // MMX/SSE2
	"PADDSW",        // MMX/SSE2
	"PADDUSB",       // MMX/SSE2
	"PADDUSW",       // MMX/SSE2
	"PADDW",         // MMX/SSE2
	"PALIGNR",       // SSSE3
	"PAND",          // MMX/SSE2
	"PANDN",         // MMX/SSE2
	"PAUSE",         // SSE2.
	"PAVGB",         // MMX-Ext
	"PAVGW",         // MMX-Ext
	"PBLENDVB",      // SSE4.1
	"PBLENDW",       // SSE4.1
	"PCMPEQB",       // MMX/SSE2
	"PCMPEQD",       // MMX/SSE2
	"PCMPEQQ",       // SSE4.1
	"PCMPEQW",       // MMX/SSE2    
	"PCMPESTRI",     // SSE4.2
	"PCMPESTRM",     // SSE4.2
	"PCMPGTB",       // MMX/SSE2
	"PCMPGTD",       // MMX/SSE2
	"PCMPGTQ",       // SSE4.2
	"PCMPGTW",       // MMX/SSE2
	"PCMPISTRI",     // SSE4.2
	"PCMPISTRM",     // SSE4.2
	"PEXTRB",        // SSE4.1
	"PEXTRD",        // SSE4.1        
	"PEXTRQ",        // SSE4.1
	"PEXTRW",        // MMX-Ext/SSE2
	"PF2ID",         // 3dNow!
	"PF2IW",         // Enhanced 3dNow!
	"PFACC",         // 3dNow!
	"PFADD",         // 3dNow!
	"PFCMPEQ",       // 3dNow!
	"PFCMPGE",       // 3dNow!
	"PFCMPGT",       // 3dNow!
	"PFMAX",         // 3dNow!
	"PFMIN",         // 3dNow!
	"PFMUL",         // 3dNow!
	"PFNACC",        // Enhanced 3dNow!
	"PFPNACC",       // Enhanced 3dNow!
	"PFRCP",         // 3dNow!
	"PFRCPIT1",      // 3dNow!
	"PFRCPIT2",      // 3dNow!
	"PFRSQIT1",      // 3dNow!
	"PFRSQRT",       // 3dNow!
	"PFSUB",         // 3dNow!
	"PFSUBR",        // 3dNow!
	"PHADDD",        // SSSE3
	"PHADDSW",       // SSSE3
	"PHADDW",        // SSSE3
	"PHMINPOSUW",    // SSE4.1
	"PHSUBD",        // SSSE3
	"PHSUBSW",       // SSSE3
	"PHSUBW",        // SSSE3
	"PI2FD",         // 3dNow!
	"PI2FW",         // Enhanced 3dNow!
	"PINSRB",        // SSE4.1
	"PINSRD",        // SSE4.1
	"PINSRQ",        // SSE4.1
	"PINSRW",        // MMX-Ext
	"PMADDUBSW",     // SSSE3
	"PMADDWD",       // MMX/SSE2
	"PMAXSB",        // SSE4.1
	"PMAXSD",        // SSE4.1
	"PMAXSW",        // MMX-Ext
	"PMAXUB",        // MMX-Ext
	"PMAXUD",        // SSE4.1
	"PMAXUW",        // SSE4.1
	"PMINSB",        // SSE4.1
	"PMINSD",        // SSE4.1
	"PMINSW",        // MMX-Ext
	"PMINUB",        // MMX-Ext
	"PMINUD",        // SSE4.1
	"PMINUW",        // SSE4.1
	"PMOVMSKB",      // MMX-Ext
	"PMOVSXBD",      // SSE4.1
	"PMOVSXBQ",      // SSE4.1
	"PMOVSXBW",      // SSE4.1
	"PMOVSXDQ",      // SSE4.1
	"PMOVSXWD",      // SSE4.1
	"PMOVSXWQ",      // SSE4.1
	"PMOVZXBD",      // SSE4.1
	"PMOVZXBQ",      // SSE4.1
	"PMOVZXBW",      // SSE4.1
	"PMOVZXDQ",      // SSE4.1
	"PMOVZXWD",      // SSE4.1
	"PMOVZXWQ",      // SSE4.1
	"PMULDQ",        // SSE4.1
	"PMULHRSW",      // SSSE3
	"PMULHUW",       // MMX-Ext
	"PMULHW",        // MMX/SSE2
	"PMULLD",        // SSE4.1
	"PMULLW",        // MMX/SSE2
	"PMULUDQ",       // SSE2
	"POP",           // X86/X64
	"POPAD",         // X86 only
	"POPCNT",        // SSE4.2
	"POPFD",         // X86 only
	"POPFQ",         // X64 only
	"POR",           // MMX/SSE2
	"PREFETCH",      // MMX-Ext
	"PSADBW",        // MMX-Ext
	"PSHUFB",        // SSSE3
	"PSHUFD",        // SSE2
	"PSHUFW",        // MMX-Ext
	"PSHUFHW",       // SSE2
	"PSHUFLW",       // SSE2
	"PSIGNB",        // SSSE3
	"PSIGND",        // SSSE3
	"PSIGNW",        // SSSE3
	"PSLLD",         // MMX/SSE2
	"PSLLDQ",        // SSE2
	"PSLLQ",         // MMX/SSE2
	"PSLLW",         // MMX/SSE2
	"PSRAD",         // MMX/SSE2
	"PSRAW",         // MMX/SSE2
	"PSRLD",         // MMX/SSE2
	"PSRLDQ",        // SSE2
	"PSRLQ",         // MMX/SSE2
	"PSRLW",         // MMX/SSE2
	"PSUBB",         // MMX/SSE2
	"PSUBD",         // MMX/SSE2
	"PSUBQ",         // SSE2
	"PSUBSB",        // MMX/SSE2
	"PSUBSW",        // MMX/SSE2
	"PSUBUSB",       // MMX/SSE2
	"PSUBUSW",       // MMX/SSE2
	"PSUBW",         // MMX/SSE2
	"PSWAPD",        // Enhanced 3dNow!
	"PTEST",         // SSE4.1
	"PUNPCKHBW",     // MMX/SSE2
	"PUNPCKHDQ",     // MMX/SSE2
	"PUNPCKHQDQ",    // SSE2
	"PUNPCKHWD",     // MMX/SSE2
	"PUNPCKLBW",     // MMX/SSE2
	"PUNPCKLDQ",     // MMX/SSE2
	"PUNPCKLQDQ",    // SSE2
	"PUNPCKLWD",     // MMX/SSE2
	"PUSH",          // X86/X64
	"PUSHAD",        // X86 only
	"PUSHFD",        // X86 only
	"PUSHFQ",        // X64 only
	"PXOR",          // MMX/SSE2
	"RCL",           // X86/X64
	"RCPPS",         // SSE
	"RCPSS",         // SSE
	"RCR",           // X86/X64
	"RDTSC",         // X86/X64
	"RDTSCP",        // X86/X64
	"REP_LODSB",     // X86/X64 (REP)
	"REP_LODSD",     // X86/X64 (REP)
	"REP_LODSQ",     // X64 only (REP)
	"REP_LODSW",     // X86/X64 (REP)
	"REP_MOVSB",     // X86/X64 (REP)
	"REP_MOVSD",     // X86/X64 (REP)
	"REP_MOVSQ",     // X64 only (REP)
	"REP_MOVSW",     // X86/X64 (REP)
	"REP_STOSB",     // X86/X64 (REP)
	"REP_STOSD",     // X86/X64 (REP)
	"REP_STOSQ",     // X64 only (REP)
	"REP_STOSW",     // X86/X64 (REP)
	"REPE_CMPSB",    // X86/X64 (REP)
	"REPE_CMPSD",    // X86/X64 (REP)
	"REPE_CMPSQ",    // X64 only (REP)
	"REPE_CMPSW",    // X86/X64 (REP)
	"REPE_SCASB",    // X86/X64 (REP)
	"REPE_SCASD",    // X86/X64 (REP)
	"REPE_SCASQ",    // X64 only (REP)
	"REPE_SCASW",    // X86/X64 (REP)
	"REPNE_CMPSB",   // X86/X64 (REP)
	"REPNE_CMPSD",   // X86/X64 (REP)
	"REPNE_CMPSQ",   // X64 only (REP)
	"REPNE_CMPSW",   // X86/X64 (REP)
	"REPNE_SCASB",   // X86/X64 (REP)
	"REPNE_SCASD",   // X86/X64 (REP)
	"REPNE_SCASQ",   // X64 only (REP)
	"REPNE_SCASW",   // X86/X64 (REP)
	"RET",           // X86/X64
	"ROL",           // X86/X64
	"ROR",           // X86/X64
	"ROUNDPD",       // SSE4.1
	"ROUNDPS",       // SSE4.1
	"ROUNDSD",       // SSE4.1
	"ROUNDSS",       // SSE4.1
	"RSQRTPS",       // SSE
	"RSQRTSS",       // SSE
	"SAHF",          // X86/X64 (CPUID NEEDED)
	"SAL",           // X86/X64
	"SAR",           // X86/X64
	"SBB",           // X86/X64
	"SETA",           // Begin (setcc)
	// X86/X64 (setcc)
	"SETAE",         // X86/X64 (setcc)
	"SETB",          // X86/X64 (setcc)
	"SETBE",         // X86/X64 (setcc)
	"SETC",          // X86/X64 (setcc)
	"SETE",          // X86/X64 (setcc)
	"SETG",          // X86/X64 (setcc)
	"SETGE",         // X86/X64 (setcc)
	"SETL",          // X86/X64 (setcc)
	"SETLE",         // X86/X64 (setcc)
	"SETNA",         // X86/X64 (setcc)
	"SETNAE",        // X86/X64 (setcc)
	"SETNB",         // X86/X64 (setcc)
	"SETNBE",        // X86/X64 (setcc)
	"SETNC",         // X86/X64 (setcc)
	"SETNE",         // X86/X64 (setcc)
	"SETNG",         // X86/X64 (setcc)
	"SETNGE",        // X86/X64 (setcc)
	"SETNL",         // X86/X64 (setcc)
	"SETNLE",        // X86/X64 (setcc)
	"SETNO",         // X86/X64 (setcc)
	"SETNP",         // X86/X64 (setcc)
	"SETNS",         // X86/X64 (setcc)
	"SETNZ",         // X86/X64 (setcc)
	"SETO",          // X86/X64 (setcc)
	"SETP",          // X86/X64 (setcc)
	"SETPE",         // X86/X64 (setcc)
	"SETPO",         // X86/X64 (setcc)
	"SETS",          // X86/X64 (setcc)
	"SETZ",          // X86/X64 (setcc)
	"SFENCE",        // MMX-Ext/SSE
	"SHL",           // X86/X64
	"SHLD",          // X86/X64
	"SHR",           // X86/X64
	"SHRD",          // X86/X64
	"SHUFPD",        // SSE2
	"SHUFPS",        // SSE
	"SQRTPD",        // SSE2
	"SQRTPS",        // SSE
	"SQRTSD",        // SSE2
	"SQRTSS",        // SSE
	"STC",           // X86/X64
	"STD",           // X86/X64
	"STMXCSR",       // SSE
	"SUB",           // X86/X64
	"SUBPD",         // SSE2
	"SUBPS",         // SSE
	"SUBSD",         // SSE2
	"SUBSS",         // SSE
	"TEST",          // X86/X64
	"UCOMISD",       // SSE2
	"UCOMISS",       // SSE
	"UD2",           // X86/X64
	"UNPCKHPD",      // SSE2
	"UNPCKHPS",      // SSE
	"UNPCKLPD",      // SSE2
	"UNPCKLPS",      // SSE
	"XADD",          // X86/X64 (i486)
	"XCHG",          // X86/X64 (i386)
	"XOR",           // X86/X64
	"XORPD",         // SSE2
	"XORPS",         // SSE
};
#endif

void BuildVMByteCode::build_fpu(VCombosVMCode & var_combos_vm_code,ud_t &var_ud)
{
   // printf ("instruction_table size %d\n",sizeof(instruction_table));
    switch (get_operand1_type(var_ud))
    {
    case UD_OP_IMM:
        copy_exec_code_to_stack(var_combos_vm_code,ud_insn_ptr(&var_ud),ud_insn_len(&var_ud));
        break;
    case UD_OP_MEM:
        if (get_operand1(var_ud).base == UD_NONE &&
                get_operand1(var_ud).index == UD_NONE &&
                get_operand1(var_ud).scale == 0) //like mnemonic [addr]
        {
            copy_exec_code_to_stack(var_combos_vm_code,ud_insn_ptr(&var_ud),ud_insn_len(&var_ud));
        }
        else{
            const char * mnemonic_name = ud_lookup_mnemonic(ud_insn_mnemonic(&var_ud));
            int index = 0;
            bool find = false;
            //printf ("mnemonic :%s\n",mnemonic_name);
			for (index = 0; index < instruction_table_count; index++)
            {
#ifdef _MSC_VER
				if (stricmp(instruction_table[index], mnemonic_name) == 0)
#else
                if (strcasecmp(instruction_table[index], mnemonic_name) == 0)
#endif
                {
                    read_vm_operand(var_combos_vm_code,get_operand1(var_ud));

                    find = true;
                    //read_vm_operand(var_combos_vm_code,var_ud);
                    AsmJit::Assembler a;
                    AsmJit::Operand o1;
                    switch (get_operand1(var_ud).size) {
                    case 32:
                        o1 = AsmJit::dword_ptr(AsmJit::nbp);
                        break;
                    case 64:
                        o1 = AsmJit::qword_ptr(AsmJit::nbp);
                        break;
                    default:
#ifdef DEBUG
                        printf("Unknown FPU OP Size%d\n",get_operand1(var_ud).size);
#endif
                        break;
                    }
                    a._emitInstruction(index,&o1);
                    copy_exec_code_to_stack(var_combos_vm_code,
                                            a.getCode(),
                                            a.getCodeSize());
                    break;
                }
            }
            if (find == false)
                ptr_build_vm_bytecode->error("Instruction Not Found: %s\n",mnemonic_name);
            else
                write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
        }
        break;
    case UD_OP_REG:
        if (mapped_vm_register.find(get_operand1(var_ud).base) == mapped_vm_register.end()) //like mnemonic st1,st2
            copy_exec_code_to_stack(var_combos_vm_code,ud_insn_ptr(&var_ud),ud_insn_len(&var_ud));
        break;
    case UD_NONE:
        copy_exec_code_to_stack(var_combos_vm_code,ud_insn_ptr(&var_ud),ud_insn_len(&var_ud));
        break;
    }
}

 //编译前缀
void BuildVMByteCode::build_pfx(VCombosVMCode & var_combos_vm_code,ud_t &var_ud,CodePiece & var_cur_piece,bool b_allocator)
{
   VMCodeBufferManage * code_buf = NULL;

   if (b_allocator)
   {
      code_buf = create_newvm_piece();
   }
   else
   {
      /*if (var_map_newlabel_vmbuffer_manage.find(newlabel_count) !=
            var_map_newlabel_vmbuffer_manage.end())
      {
         code_buf = var_map_newlabel_vmbuffer_manage[newlabel_count];
      }*/
       code_buf = get_newvm_piece();
   }

   VCombosVMCode & new_combos_vm_code = code_buf->get_generator();
   PCode & new_pcode = code_buf->get_pcode();

   if (b_allocator)
   {
       new_pcode.count_vmcode_begin();
       //cur_vmcode -> new_combos or next
       //new_combos -> cur_vmcode

       RegisterStore t_store;
       new_combos_vm_code.upset_register_array(t_store);

       new_combos_vm_code.set_vmregister_store_in(t_store);
       new_combos_vm_code.set_vmregister_store_out(t_store);
       new_pcode.set_key(0x12345678);
   }
   else
   {
       new_combos_vm_code.set_vmregister_store_in(
                   var_map_label_vmreg_store_out[var_cur_piece.get_label()]);
       new_combos_vm_code.set_vmregister_store_out(
                   var_map_label_vmreg_store_in[var_cur_piece.get_label()]);
#ifdef DEBUG
           char file_name[256];
           memset(&file_name,0,256);
           sprintf(file_name,"virtual_machine_assembly/NewLabel%d,%08x\n", get_newvm_cur_label(),var_map_newlabel_vmcode_addr[get_newvm_cur_label()]);
           new_pcode.out_log_file(file_name);
#endif


   }
   new_combos_vm_code.save_vm_context();
   build(new_combos_vm_code,var_ud); 
   
   //new_combos_vm_code.d_push_imm(0);
   //new_combos_vm_code.set_key(0);


   if (var_ud.pfx_rep)
   {
      if (b_allocator)
      {
       var_combos_vm_code.d_push_imm(0);
       var_combos_vm_code.d_push_imm(0);
      } else {
         long jmp_addr = var_map_label_vmcode_addr[var_cur_piece.get_jmplabel()];
         long next_addr = var_map_newlabel_vmcode_addr[get_newvm_cur_label()];
         //var_combos_vm_code.d_push_imm(next_addr);
         //var_combos_vm_code.d_push_imm(jmp_addr);
         var_combos_vm_code.d_push_imm(jmp_addr);
         var_combos_vm_code.d_push_imm(next_addr);
      }
      //var_combos_vm_code.ptr_pcode->out_info("cmp ecx,0 \njz store\n");
      var_combos_vm_code.impact_vmregister(false);
      var_combos_vm_code.push_vsp();

      var_combos_vm_code.push(T_ECX); //cmp ecx,0
      var_combos_vm_code.d_push_imm(0);
      var_combos_vm_code.d_cmp();
      var_combos_vm_code.get_zf();

      var_combos_vm_code.d_add();
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.d_read_mem(); //读取地址
      var_combos_vm_code.pop(T_NEXTINSADDR);
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.pop(T_INVALID);

      //用这个的话计算到最后ecx会少一个
      /*
      var_combos_vm_code.d_push_imm(1) ;
      var_combos_vm_code.push(T_ECX); //sub ecx,1
      var_combos_vm_code.d_sub();
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.pop(T_ECX);

      */
      new_combos_vm_code.d_push_imm(1);
      new_combos_vm_code.push(T_ECX); //sub ecx,1
      new_combos_vm_code.d_sub();
      new_combos_vm_code.pop(T_INVALID);
      new_combos_vm_code.pop(T_ECX);



      //var_combos_vm_code.set_pc(0x12345678);

      new_combos_vm_code.recover_vm_context();
      if (b_allocator)
      {
          new_combos_vm_code.d_push_imm(0);
          //new_combos_vm_code.d_push_imm(0);
      }
      else
      {
          int next_addr = get_vmcode_address(var_cur_piece.get_label());//var_map_label_vmcode_addr[var_cur_piece.get_label()];
          new_combos_vm_code.d_push_imm(next_addr);
      }
      new_combos_vm_code.set_pc(0x12345678);

   }
   else if (var_ud.pfx_repe)
   {
      //while (ecx != 0)
      //{
      //   oldcode();
      //}
      if (b_allocator)
      {
       var_combos_vm_code.d_push_imm(0);
       var_combos_vm_code.d_push_imm(0);
      } else {
         long jmp_addr = var_map_label_vmcode_addr[var_cur_piece.get_jmplabel()];
         long next_addr = var_map_newlabel_vmcode_addr[get_newvm_cur_label()];
         var_combos_vm_code.d_push_imm(next_addr);
         var_combos_vm_code.d_push_imm(jmp_addr);
         //var_combos_vm_code.d_push_imm(jmp_addr);
         //var_combos_vm_code.d_push_imm(next_addr);
      }
      //var_combos_vm_code.ptr_pcode->out_info("cmp ecx,0 \njz store\n");
      var_combos_vm_code.impact_vmregister(false);
      var_combos_vm_code.push_vsp();

      var_combos_vm_code.push(T_ECX); //cmp ecx,0
      var_combos_vm_code.d_push_imm(0);
      var_combos_vm_code.d_cmp();
      var_combos_vm_code.get_zf();

      var_combos_vm_code.pushf();
      var_combos_vm_code.impact_vmregister(true);
      var_combos_vm_code.get_zf();
      var_combos_vm_code.d_or();
      var_combos_vm_code.pop(T_INVALID);

      var_combos_vm_code.d_add();
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.d_read_mem(); //读取地址
      //var_combos_vm_code.int3();
      var_combos_vm_code.pop(T_NEXTINSADDR);
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.pop(T_INVALID);

      //用这个的话计算到最后ecx会少一个
      /*
      var_combos_vm_code.d_push_imm(1) ;
      var_combos_vm_code.push(T_ECX); //sub ecx,1
      var_combos_vm_code.d_sub();
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.pop(T_ECX);

      */
      new_combos_vm_code.d_push_imm(1);
      new_combos_vm_code.push(T_ECX); //sub ecx,1
      new_combos_vm_code.d_sub();
      new_combos_vm_code.pop(T_INVALID);
      new_combos_vm_code.pop(T_ECX);


      //var_combos_vm_code.set_pc(0x12345678);

      new_combos_vm_code.recover_vm_context();
      if (b_allocator)
      {
          new_combos_vm_code.d_push_imm(0);
          //new_combos_vm_code.d_push_imm(0);
      }
      else
      {
          int next_addr = get_vmcode_address(var_cur_piece.get_label());//var_map_label_vmcode_addr[var_cur_piece.get_label()];
          new_combos_vm_code.d_push_imm(next_addr);
      }
      new_combos_vm_code.set_pc(0x12345678);

   }
   else if (var_ud.pfx_repne)
   {
      
      //while (ecx != 0)
      //{
      //   oldcode();
      //}
      if (b_allocator)
      {
       var_combos_vm_code.d_push_imm(0);
       var_combos_vm_code.d_push_imm(0);
      } else {
         long jmp_addr = var_map_label_vmcode_addr[var_cur_piece.get_jmplabel()];
         long next_addr = var_map_newlabel_vmcode_addr[get_newvm_cur_label()];
         //var_combos_vm_code.d_push_imm(next_addr);
         //var_combos_vm_code.d_push_imm(jmp_addr);
         var_combos_vm_code.d_push_imm(jmp_addr);
         var_combos_vm_code.d_push_imm(next_addr);
      } 
      //var_combos_vm_code.ptr_pcode->out_info("cmp ecx,0 \njz store\n");
      var_combos_vm_code.impact_vmregister(false);
      var_combos_vm_code.push_vsp();

      var_combos_vm_code.push(T_ECX); //cmp ecx,0
      var_combos_vm_code.d_push_imm(0);
      var_combos_vm_code.d_cmp();
      var_combos_vm_code.get_zf();

      var_combos_vm_code.pushf();
      var_combos_vm_code.impact_vmregister(true);
      var_combos_vm_code.get_zf();
      var_combos_vm_code.d_or();
      var_combos_vm_code.pop(T_INVALID);

      var_combos_vm_code.d_add();
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.d_read_mem(); //读取地址
      //var_combos_vm_code.int3();
      var_combos_vm_code.pop(T_NEXTINSADDR);
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.pop(T_INVALID);

      //用这个的话计算到最后ecx会少一个
      /*
      var_combos_vm_code.d_push_imm(1) ;
      var_combos_vm_code.push(T_ECX); //sub ecx,1
      var_combos_vm_code.d_sub();
      var_combos_vm_code.pop(T_INVALID);
      var_combos_vm_code.pop(T_ECX);

      */
      new_combos_vm_code.d_push_imm(1);
      new_combos_vm_code.push(T_ECX); //sub ecx,1
      new_combos_vm_code.d_sub();
      new_combos_vm_code.pop(T_INVALID);
      new_combos_vm_code.pop(T_ECX);


      //var_combos_vm_code.set_pc(0x12345678);

      new_combos_vm_code.recover_vm_context();
      if (b_allocator)
      {
          new_combos_vm_code.d_push_imm(0);
          //new_combos_vm_code.d_push_imm(0);
      }
      else
      {
          int next_addr = get_vmcode_address(var_cur_piece.get_label());//var_map_label_vmcode_addr[var_cur_piece.get_label()];
          new_combos_vm_code.d_push_imm(next_addr);
      }
      new_combos_vm_code.set_pc(0x12345678);

      //var_combos_vm_code.push()
      //var_combos_vm_code
   }
   if (b_allocator)
   {
      int new_pcode_size = new_pcode.count_vmcode_end();
      VTable table;
      table.v = &new_combos_vm_code;
      long new_pcode_addr = ptr_addr_table->assign_address(new_pcode_size,table);
      var_map_newlabel_vmcode_addr.insert(std::make_pair(get_newvm_cur_label(),new_pcode_addr));
      //printf("NewLabel分配到PCODE地址:%x - %x\n",new_pcode_addr - new_pcode_size,new_pcode_addr);
           if (ptr_addr_table->get_sign())
               printf("NEWPCODE Address:%08x - %08x, Flags:%d\n",
                  new_pcode_addr,
                  new_pcode_addr + new_pcode_size,
                  ptr_addr_table->get_sign());
           else
               printf("NEWPCODE Address:%08x - %08x, Flags:%d\n",
                  new_pcode_addr - new_pcode_size,
                  new_pcode_addr,
                  ptr_addr_table->get_sign());

   }
   else
   {
       //ptr_addr_table->copy();
       //int a = new_combos_vm_code.get_code_size();
       //printf("代码大小%d\n",a);
   }


   //newlabel_count++;
}

VMCodeBufferManage * BuildVMByteCode::create_newvm_piece()
{
   var_vmcode_manager_list.push_back(new VMCodeBufferManage(ptr_vm));
   var_map_newlabel_vmbuffer_manage.insert(
         std::make_pair(newlabel_count,var_vmcode_manager_list.back()));
   newlabel_count++;
   return var_vmcode_manager_list.back();
} 

VMCodeBufferManage * BuildVMByteCode::get_newvm_piece()
{
    VMCodeBufferManage * result = NULL;
   if (var_map_newlabel_vmbuffer_manage.find(newlabel_count) !=
           var_map_newlabel_vmbuffer_manage.end())
   {
       result = var_map_newlabel_vmbuffer_manage[newlabel_count];

   }
   newlabel_count++;
   return result;
}

long BuildVMByteCode::get_newvm_cur_label()
{
    return newlabel_count;
}

void BuildVMByteCode::write_vm_operand(VCombosVMCode & var_combos_vm_code,ud_operand & var_operand)
{
        switch (var_operand.type)
        {
           case UD_OP_MEM:
              vm_operand(var_combos_vm_code,var_operand);
              write_mem(var_operand);
              break;
           case UD_OP_REG:
              if (var_operand.base == UD_R_ESP)
              {
                  var_combos_vm_code.pop_vsp();
                  //var_combos_vm_code.int3();
              }
              else
                  var_combos_vm_code.pop(get_vm_register(var_operand.base));
              break;
        }    
}

void BuildVMByteCode::read_vm_operand(VCombosVMCode & var_combos_vm_code,ud_operand & var_operand)
{
     vm_operand(var_combos_vm_code,var_operand);
     read_mem(var_operand);
}

void BuildVMByteCode::build(VCombosVMCode & var_combos_vm_code,ud_t &var_ud)
{
   if(get_operand1(var_ud).base == UD_R_ESP ||
         get_operand1(var_ud).index == UD_R_ESP ||
         get_operand2(var_ud).base == UD_R_ESP ||
         get_operand2(var_ud).index == UD_R_ESP)
   {
      var_combos_vm_code.push_vsp();
      var_combos_vm_code.pop(T_ESP);
   }
   switch(ud_insn_mnemonic(&var_ud))
   {
    //Comment ones are the ones processed by lua
    /*
    case UD_Inop:
       break;
    case UD_Imov:
        {
          set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
          read_vm_operand(var_combos_vm_code,get_operand2(var_ud));
          write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
        }
        break;

    case UD_Ixchg:
       {
         read_vm_operand(var_combos_vm_code,get_operand2(var_ud));
         read_vm_operand(var_combos_vm_code,get_operand1(var_ud));

         write_vm_operand(var_combos_vm_code,get_operand2(var_ud));
         write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
       }
       break;
    case UD_Ilea:
     {
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Ipush:
     {
        ud_operand o;
        o.size = 32; //默认用32位
        set_imm_operand_size(get_operand1(var_ud),o);
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
     }
     break;   
    case UD_Icmp:
     {
       set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
       read_vm_operand(var_combos_vm_code,get_operand2(var_ud));
       read_vm_operand(var_combos_vm_code,get_operand1(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_sub();
              var_combos_vm_code.popf();   
              var_combos_vm_code.pop(T_INVALID | T_E32X | T_16X | T_8L);
              break;
           case 16:
              var_combos_vm_code.w_sub();
              var_combos_vm_code.popf();
              var_combos_vm_code.pop(T_INVALID | T_E32X | T_16X);
              break;
           case 32:
              var_combos_vm_code.d_sub();
              var_combos_vm_code.popf();
              var_combos_vm_code.pop(T_INVALID | T_E32X);
              break;
        }
        
     }
     break;     
    case UD_Iret:
     {
        var_combos_vm_code.ret();
     }
     break;
    case UD_Iadd:
     {
        set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        read_mem(get_operand2(var_ud));
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_add();
              break;
           case 16:
              var_combos_vm_code.w_add();
              break;
           case 32:
              var_combos_vm_code.d_add();
              break;
        }
        var_combos_vm_code.popf();
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Isub:
        set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        read_mem(get_operand2(var_ud));
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_sub();
              break;
           case 16:
              var_combos_vm_code.w_sub();
              break;
           case 32:
              var_combos_vm_code.d_sub();
              break;
        }
        var_combos_vm_code.popf();
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
     
    case UD_Inot:
     {
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_not();
              break;
           case 16:
              var_combos_vm_code.w_not();
              break;
           case 32:
              var_combos_vm_code.d_not();
              break;
        }

        var_combos_vm_code.popf();
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Iand:
     {
        set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));

        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        read_mem(get_operand2(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_and();
              break;
           case 16:
              var_combos_vm_code.w_and();
              break;
           case 32:
              var_combos_vm_code.d_and();
              break;
        }
        var_combos_vm_code.popf();
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); 
     }
     break;
    case UD_Ior:
     {
        set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        read_mem(get_operand2(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_or();
              break;
           case 16:
              var_combos_vm_code.w_or();
              break;
           case 32:
              var_combos_vm_code.d_or();
              break;
        }
        var_combos_vm_code.popf();
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));   
     }
     break;
    
     case UD_Ixor:
     {
        set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        read_mem(get_operand2(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_xor();
              break;
           case 16:
              var_combos_vm_code.w_xor();
              break;
           case 32:
              var_combos_vm_code.d_xor();
              break;
        }
        var_combos_vm_code.popf();
 
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));  
     }
     break;
    case UD_Itest:
     {
        set_imm_operand_size(get_operand2(var_ud),get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        vm_operand(var_combos_vm_code,get_operand2(var_ud));
        read_mem(get_operand2(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.b_and();
              break;
           case 16:
              var_combos_vm_code.w_and();
              break;
           case 32:
              var_combos_vm_code.d_and();
              break;
        }
        var_combos_vm_code.popf();
        switch (get_operand1(var_ud).size)
        {
           case 8:
              var_combos_vm_code.pop(T_INVALID|T_E32X|T_16X|T_8H);
              break;
           case 16:
              var_combos_vm_code.pop(T_INVALID|T_E32X|T_16X);
              break;
           case 32:
              var_combos_vm_code.pop(T_INVALID|T_E32X);
              break;
        }
     }
     break;
    case UD_Ipop:
     {
        ud_operand o;
        o.size = 32;
        set_imm_operand_size(get_operand1(var_ud),o);
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Iinc:
     {
        vm_operand(var_combos_vm_code,get_operand1(var_ud));
        read_mem(get_operand1(var_ud));
        switch (get_operand1(var_ud).size)
        {
           case 8: 
              var_combos_vm_code.b_push_imm(1);
              var_combos_vm_code.b_add();
              break;
           case 16:
              var_combos_vm_code.w_push_imm(1);
              var_combos_vm_code.w_add();
              break;
           case 32:
              var_combos_vm_code.d_push_imm(1);
              var_combos_vm_code.d_add();
              break;
        }
        var_combos_vm_code.d_push_imm(~((1 << 0) | (1 << 10)));
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pushf();
        var_combos_vm_code.d_push_imm((1 << 0) | (1 << 10));
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);     
        var_combos_vm_code.d_or();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.popf();
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Idec:
     {
        switch (get_operand1(var_ud).size)
        {
           case 8: 
              var_combos_vm_code.b_push_imm(1);
              read_vm_operand(var_combos_vm_code,get_operand1(var_ud));
              var_combos_vm_code.b_sub();
              break;
           case 16:
              var_combos_vm_code.w_push_imm(1);
              read_vm_operand(var_combos_vm_code,get_operand1(var_ud));
              var_combos_vm_code.w_sub();
              break;
           case 32:
              var_combos_vm_code.b_push_imm_zx(1);
              read_vm_operand(var_combos_vm_code,get_operand1(var_ud));
              var_combos_vm_code.d_sub();
              break;
        }
        var_combos_vm_code.d_push_imm(~((1 << 0) | (1 << 10)));
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);
              
        var_combos_vm_code.pushf();
        var_combos_vm_code.d_push_imm((1 << 0) | (1 << 10));
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);     
        var_combos_vm_code.d_or();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.popf(); 
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Ishl:
     {
         vm_operand(var_combos_vm_code, get_operand1(var_ud));
         read_mem(get_operand1(var_ud));
         vm_operand(var_combos_vm_code, get_operand2(var_ud));
         read_mem(get_operand2(var_ud));
         switch (get_operand1(var_ud).size) {
         case 8:
             var_combos_vm_code.b_shl();
             break;
         case 16:
             var_combos_vm_code.w_shl();
             break;
         case 32:
             var_combos_vm_code.d_shl();
             break;
         default:
             break;
         }
         var_combos_vm_code.popf();
         write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Ishr:
     {
         vm_operand(var_combos_vm_code, get_operand1(var_ud));
         read_mem(get_operand1(var_ud));
         vm_operand(var_combos_vm_code, get_operand2(var_ud));
         read_mem(get_operand2(var_ud));
         switch (get_operand1(var_ud).size) {
         case 8:
             var_combos_vm_code.b_shr();
             break;
         case 16:
             var_combos_vm_code.w_shr();
             break;
         case 32:
             var_combos_vm_code.d_shr();
             break;
         default:
             break;
         }
         var_combos_vm_code.popf();
         write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Isar:
     {
         var_combos_vm_code.impact_vmregister(false);
         read_vm_operand(var_combos_vm_code,get_operand1(var_ud));
         read_vm_operand(var_combos_vm_code,get_operand2(var_ud));
         switch (get_operand1(var_ud).size) {
         case 8:
             var_combos_vm_code.b_sar();
             break;
         case 16:
             var_combos_vm_code.w_sar();
             break;
         case 32:
             var_combos_vm_code.d_sar();
             break;
         default:
             printf("OP NotSupported\n");
             debugbreakpoint();
             break;
         }
         var_combos_vm_code.popf();
         write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
         var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Icdq:
     {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_EAX);
       var_combos_vm_code.b_push_imm(31);
       var_combos_vm_code.d_sar();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_EDX);
       var_combos_vm_code.impact_vmregister(true);
     }
       break;
    case UD_Icwd:
    {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_AX);
       var_combos_vm_code.b_push_imm(15);
       var_combos_vm_code.w_sar();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_DX);

       var_combos_vm_code.impact_vmregister(true);
    }
       break;
    case UD_Iscasb: //edi - ~df + df
     {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.b_read_mem();
       var_combos_vm_code.push(T_AL);
       var_combos_vm_code.b_cmp();
       var_combos_vm_code.popf();

       var_combos_vm_code.get_string_ins_diff();
       var_combos_vm_code.b_push_imm(0);
       var_combos_vm_code.d_shl();
       var_combos_vm_code.pop(T_INVALID);

       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_EDI);
       var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Iscasw: //edi - ~df + df
     {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.w_read_mem();
       var_combos_vm_code.push(T_AX);
       var_combos_vm_code.w_cmp();
       var_combos_vm_code.popf();

       var_combos_vm_code.get_string_ins_diff();
       var_combos_vm_code.b_push_imm(1);
       var_combos_vm_code.d_shl();
       var_combos_vm_code.pop(T_INVALID);

       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_EDI);
       var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Iscasd: //edi - ~df + df
     {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_EDI);

       var_combos_vm_code.d_read_mem();
       var_combos_vm_code.push(T_EAX);
       var_combos_vm_code.d_cmp();
       var_combos_vm_code.popf();

       var_combos_vm_code.get_string_ins_diff();
       var_combos_vm_code.b_push_imm(2);
       var_combos_vm_code.d_shl();
       var_combos_vm_code.pop(T_INVALID);

       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_EDI);
       var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Imovsb:
     {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_ESI);
       var_combos_vm_code.b_read_mem();
       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.b_write_mem();

       var_combos_vm_code.get_string_ins_diff();
       var_combos_vm_code.push_vsp();
       var_combos_vm_code.d_read_mem();

       var_combos_vm_code.push(T_ESI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_ESI);

       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_EDI);
       var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Imovsd:
     {
       var_combos_vm_code.impact_vmregister(false);
       var_combos_vm_code.push(T_ESI);
       var_combos_vm_code.d_read_mem();
       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.d_write_mem();

       var_combos_vm_code.get_string_ins_diff();
       var_combos_vm_code.b_push_imm(2);
       var_combos_vm_code.d_shl();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.push_vsp();
       var_combos_vm_code.d_read_mem();


       var_combos_vm_code.push(T_ESI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_ESI);

       var_combos_vm_code.push(T_EDI);
       var_combos_vm_code.d_add();
       var_combos_vm_code.pop(T_INVALID);
       var_combos_vm_code.pop(T_EDI);
       var_combos_vm_code.impact_vmregister(true);
     }
     break;
     case UD_Isetz: // zf = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();  //
        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetnz: // zf = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();  //

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//

        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isets: // sf = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();  //
        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetns: // sf = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();  //

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//

        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetnp: // pf = 0
     {
         var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_pf();  //

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//

        var_combos_vm_code.d_not();     
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetp: // pf = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_pf();  //这里获取一个dword的zf标志位 zf=1的时候 数据为4(二进制100) zf=0的时候 数据为0
        var_combos_vm_code.b_push_imm(2); //这里把刚刚获取的那个数据右移三位
        var_combos_vm_code.d_shr();    //右移
        var_combos_vm_code.pop(T_INVALID);//删除shr那个eflag我们并不需要
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //把刚刚那个数据写入第一个操作数,因为第一个操作数只会是8位 
        var_combos_vm_code.pop(T_INVALID | T_16X);//上面用了8位还剩24位(这24位都为0)先删除16位
        var_combos_vm_code.pop(T_INVALID | T_8H);//在删除8位 
        var_combos_vm_code.impact_vmregister(true);
     }
     break;                     
    case UD_Iseto: // of = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();  //这里获取一个dword的zf标志位 zf=1的时候 数据为4(二进制100) zf=0的时候 数据为0
        var_combos_vm_code.b_push_imm(2); //这里把刚刚获取的那个数据右移三位
        var_combos_vm_code.d_shr();    //右移
        var_combos_vm_code.pop(T_INVALID);//删除shr那个eflag我们并不需要
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //把刚刚那个数据写入第一个操作数,因为第一个操作数只会是8位
        var_combos_vm_code.pop(T_INVALID | T_16X);//上面用了8位还剩24位(这24位都为0)先删除16位
        var_combos_vm_code.pop(T_INVALID | T_8H);//在删除8位
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetno: // of = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();  //

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//

        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetb: // cf = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();  //
        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetae: // cf = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();  //

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//

        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Iseta: // cf = 0 && zf = 0
     {
        var_combos_vm_code.impact_vmregister(false);

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();
        var_combos_vm_code.b_push_imm(2);
        var_combos_vm_code.d_shr();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();
        var_combos_vm_code.b_push_imm(2);
        var_combos_vm_code.d_shr();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetbe: // cf = 1 && zf = 1
     {
        var_combos_vm_code.impact_vmregister(false);

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();
        var_combos_vm_code.b_push_imm(2);
        var_combos_vm_code.d_shr();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();
        var_combos_vm_code.b_push_imm(2);
        var_combos_vm_code.d_shr();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Isetg:  // zf = 0 && sf = of
    {
         var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();  //
        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();  //
        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();  //
        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.b_push_imm_zx(1);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
    }
       break;
   case UD_Isetle:   // zf = 1 && sf != of
       {
         var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();  //

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();

        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();

        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);

       }
       break;
    case UD_Isetl: // sf != of
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();  //

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();

        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
       break;
    case UD_Isetge: // sf = of
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();  //

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();

        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_not();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.b_push_imm(2); //
        var_combos_vm_code.d_shr();    //
        var_combos_vm_code.pop(T_INVALID);//
        write_vm_operand(var_combos_vm_code,get_operand1(var_ud)); //
        var_combos_vm_code.pop(T_INVALID | T_16X);//
        var_combos_vm_code.pop(T_INVALID | T_8H);//
        var_combos_vm_code.impact_vmregister(true);
     }
       break;
    case UD_Ijnz: //ZF = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.d_push_imm(0x40);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.b_push_imm(4);
        var_combos_vm_code.d_shr();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);
     }
     break;
    case UD_Ijz:  //ZF != 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.d_push_imm(0x40);
        var_combos_vm_code.d_and();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.b_push_imm(4);
        var_combos_vm_code.d_shr();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);
     }
     break;  
    case UD_Ija: //CF = 0 && ZF = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();
        var_combos_vm_code.d_or();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijae:  // CF = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true); 
     }
     break;
    case UD_Ijb://CF = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijbe: //CF = 1 || ZF = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_cf();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();

        var_combos_vm_code.d_or();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);   
     }
     break;
    case UD_Ijcxz:  //CX = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push(T_NEXTINSADDR);

        var_combos_vm_code.push_vsp();
        var_combos_vm_code.w_push_imm(0);
        var_combos_vm_code.push(T_CX);
        var_combos_vm_code.w_cmp();
        var_combos_vm_code.get_zf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijg:  //ZF = 0 && SF = OF
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();
        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_or();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true); 
     }
     break;
    case UD_Ijge: //SF = OF
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();
        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijl:  // OF != SF
     {
        var_combos_vm_code.impact_vmregister(false);
        
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR); 

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();
        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);   
     }
     break;
    case UD_Ijle:  // ZF = 1 || SF != OF
     {
        var_combos_vm_code.impact_vmregister(false);
        
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR); 

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_zf();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();
        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();
        var_combos_vm_code.d_xor();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_or();
        var_combos_vm_code.pop(T_INVALID);

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);    
     }
     break;
    case UD_Ijno: // OF = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true); 
     }
     break;
    case UD_Ijnp: // PF = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_pf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijns: // SF = 0
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_NEXTINSADDR);
        var_combos_vm_code.push(T_JMPINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijo:  // OF = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR);

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_of();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);  
     }
     break;
    case UD_Ijp:  // PF = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR); 

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_pf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);   
     }
     break;
    case UD_Ijs:  // SF = 1
     {
        var_combos_vm_code.impact_vmregister(false);
        
        var_combos_vm_code.push(T_JMPINSADDR);
        var_combos_vm_code.push(T_NEXTINSADDR); 

        var_combos_vm_code.push_vsp();

        var_combos_vm_code.pushf();
        var_combos_vm_code.get_sf();

        var_combos_vm_code.d_add();
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.d_read_mem();
        var_combos_vm_code.pop(T_NEXTINSADDR);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.pop(T_INVALID);
        var_combos_vm_code.impact_vmregister(true);   
     }
     break;
    case UD_Ijmp:
     {

     }
     break;
     */
    case UD_Imovzx:
     {
       for (int i = get_operand2(var_ud).size; i < get_operand1(var_ud).size;i+=8)
       {
           var_combos_vm_code.b_push_imm(0);
       }
       read_vm_operand(var_combos_vm_code,get_operand2(var_ud));

       write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
     
    case UD_Imovsx:
     {
       read_vm_operand(var_combos_vm_code,get_operand2(var_ud));

       for (int i = get_operand2(var_ud).size; i < get_operand1(var_ud).size;i+=8)
       {
           int r = rand();
           r = r ? r%0xff : 0;
           var_combos_vm_code.b_push_imm(r);
       }
       var_combos_vm_code.b_push_imm(get_operand1(var_ud).size - get_operand2(var_ud).size);
       var_combos_vm_code.d_sar();
       var_combos_vm_code.pop(T_INVALID);
       write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_If2xm1:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifabs:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifadd:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifaddp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifbld:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifbstp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifchs:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifclex:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovb:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmove:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovbe:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovu:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovnb:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovne:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovnbe:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcmovnu:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifucomi:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcom:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcom2:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcomp3:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcomi:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifucomip:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcomip:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcomp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcomp5:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcompp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifcos:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifdecstp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifdiv:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifdivp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifdivr:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifdivrp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifemms:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Iffree:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Iffreep:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ificom:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ificomp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifild:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifincstp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifninit:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifiadd:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifidivr:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifidiv:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifisub:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifisubr:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifist:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifistp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifisttp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifld:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifld1:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldl2t:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldl2e:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldpi:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldlg2:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldln2:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldz:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldcw:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifldenv:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifmul:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifmulp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifimul:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifnop:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifpatan:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifprem:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifprem1:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifptan:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifrndint:

     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifrstor:

     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifnsave:

     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifscale:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifsin:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifsincos:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifsqrt:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifstp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifstp1:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifstp8:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifstp9:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifst:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifnstcw:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifnstenv:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifnstsw:
     {
       var_combos_vm_code.fstsw();
       write_vm_operand(var_combos_vm_code,get_operand1(var_ud));
     }
     break;
    case UD_Ifsub:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifsubp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifsubr:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifsubrp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Iftst:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifucom:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifucomp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifucompp:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxam:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxch:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxch4:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxch7:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxrstor:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxsave:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifxtract:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifyl2x:
     build_fpu(var_combos_vm_code,var_ud);
     break;
    case UD_Ifyl2xp1:
     build_fpu(var_combos_vm_code,var_ud);
     break;

   default:
       {
           if (build_vm_code_lua)
           {
               ptr_build_vm_bytecode = this;
               ptr_combos_vm_code = &var_combos_vm_code;
               ptr_ud = &var_ud;
               char luafunc[255] = "vm_";
               strcat(luafunc, ud_lookup_mnemonic(var_ud.mnemonic));
               lua_getglobal(build_vm_code_lua,luafunc);
               if (lua_isfunction(build_vm_code_lua,1) == 0)
               {
                   ptr_build_vm_bytecode->warn("Lua Has Not Declare Function %s\n",luafunc);
                   ptr_build_vm_bytecode->error("Not Handle:%s\n",ud_lookup_mnemonic(var_ud.mnemonic));
                   debugbreakpoint();
               }
               else
               {
                   switch (lua_pcall(build_vm_code_lua,0,0,0))
                   {
                   case LUA_ERRRUN:
                       lua_printError("Lua ErrRun\n");
                       ptr_build_vm_bytecode->warn("Lua ErrRun\n");
                       ptr_build_vm_bytecode->error("Not Handle:%s\n",luafunc);
                       break;
                   case LUA_ERRMEM:
                       lua_printError("Lua ErrMem\n");
                       ptr_build_vm_bytecode->warn("Lua ErrMem\n");
                       ptr_build_vm_bytecode->error("Not Handle:%s\n",luafunc);
                       lua_printError();
                       break;
                   case LUA_ERRERR:
                       lua_printError("Lua ErrErr");
                       ptr_build_vm_bytecode->warn("Lua ErrErr\n");
                       ptr_build_vm_bytecode->error("Not Handle:%s\n",luafunc);
                       lua_printError();
                       break;
                   default:
                       //std::cout <<  luafunc << std::endl;
                       //printf("运行成功\n");
                       break;
                   }
               }
           }
           else
           {
               ptr_build_vm_bytecode->error("Not Handle:%s\n",ud_lookup_mnemonic(var_ud.mnemonic));
               debugbreakpoint();
           }
       }

       break;
   }
}


void BuildVMByteCode::full_vmregister_store(std::vector<CodePiece> & var_list_code_piece,
      std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
      std::map<int,RegisterStore> & var_map_label_vmreg_store_out)
{
   size_t var_list_size = var_list_code_piece.size();
   for (size_t i = 0; i < var_list_size; i++)
   {
      set_vmregister_store(var_list_code_piece,var_map_label_vmreg_store_in,var_map_label_vmreg_store_out,i);
   }
}

void BuildVMByteCode::set_vmregister_store(std::vector<CodePiece> & var_list_code_piece,
      std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
      std::map<int,RegisterStore> & var_map_label_vmreg_store_out, 
      int var_cur_label)
{/*{{{*/
    std::vector<CodePiece>::iterator iter = var_list_code_piece.begin();
    bool find_out = false;
    bool find_in = false;
    std::vector<int> var_label_in;
    std::vector<int> var_label_out;
    RegisterStore var_store_in;    
    RegisterStore var_store_out;
    for (iter;iter != var_list_code_piece.end();iter++)
    {
       //查找是否有指令跳转到这里
       if (iter->get_jmplabel() == var_cur_label)
       {
          if (var_map_label_vmreg_store_out.find(iter->get_label()) != var_map_label_vmreg_store_out.end()) 
          {
             if (var_store_in.get_key() != var_map_label_vmreg_store_out[iter->get_label()].get_key())
             {
                //asm("int3");
             }
             var_store_in = var_map_label_vmreg_store_out[iter->get_label()];
             var_map_label_vmreg_store_in.insert(std::make_pair(var_cur_label,
                      var_map_label_vmreg_store_out[iter->get_label()]));
             find_in = true;
          }
          else
          {
             //if (iter->get_jmplabel_type() == TYPE_LABEL)
                var_label_out.push_back(iter->get_label());
          }
       }
       //查找上条指令
       if (iter->get_label() + 1 == var_cur_label && iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_NORMAL)//iter->get_jmplabel_type() == TYPE_LABEL)
       {
              if (var_store_in.get_key() != var_map_label_vmreg_store_out[iter->get_label()].get_key())
             {
                //asm("int3");
             }                          
          if (var_map_label_vmreg_store_out.find(iter->get_label()) != var_map_label_vmreg_store_out.end())
          {
             var_store_in = var_map_label_vmreg_store_out[iter->get_label()]; 
             var_map_label_vmreg_store_in.insert(std::make_pair(var_cur_label,
                      var_map_label_vmreg_store_out[iter->get_label()]));
             find_in = true;
          } 
          else
          {
              //if (iter->get_jmplabel_type() == TYPE_LABEL) 
                 var_label_out.push_back(iter->get_label());
          }  
       }
       
       if (iter->get_label() == var_cur_label)
       {
               if (var_store_out.get_key() != var_map_label_vmreg_store_in[iter->get_label()].get_key())
             {
                //asm("int3");
             }                 
          if (var_map_label_vmreg_store_in.find(iter->get_jmplabel()) != var_map_label_vmreg_store_in.end())
          {
             
                var_store_out = var_map_label_vmreg_store_in[iter->get_jmplabel()]; 
                var_map_label_vmreg_store_out.insert(std::make_pair(var_cur_label,
                         var_store_out));
                find_out = true;
          }
          else{
                //if (iter->get_jmplabel_type() == TYPE_LABEL)
                if (iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_NORMAL)
                   var_label_in.push_back(iter->get_jmplabel());
          }
       }
       //
       if (iter->get_label() - 1 == var_cur_label)
       {
             if (var_store_out.get_key() != var_map_label_vmreg_store_in[iter->get_label()].get_key())
             {
               // asm("int3");
             }                                                            
          if (var_map_label_vmreg_store_in.find(iter->get_label()) != var_map_label_vmreg_store_in.end())
          {
             var_store_out = var_map_label_vmreg_store_in[iter->get_label()];
             var_map_label_vmreg_store_out.insert(std::make_pair(var_cur_label,
                      var_map_label_vmreg_store_in[iter->get_label()]));
             find_out = true;
          }
          else
          {
              //pe() == TYPE_LABEL)      
                 var_label_in.push_back(iter->get_label());
          }
       }
    }

    if (find_out == false)
    {
       VCombosVMCode var_t;
       
       var_t.upset_register_array(var_store_out);
       var_map_label_vmreg_store_in.insert(std::make_pair(var_cur_label,var_store_out));
    }
    for (std::vector<int>::iterator iter = var_label_out.begin();
          iter != var_label_out.end();iter++)
    {
         var_map_label_vmreg_store_out.insert(std::make_pair(*iter,var_store_out));
    }    

    if (find_in == false)
    {
       VCombosVMCode var_t;
       //RegisterStore var_store;
       var_t.upset_register_array(var_store_in);
       var_map_label_vmreg_store_out.insert(std::make_pair(var_cur_label,var_store_in)); 
    }
    for (std::vector<int>::iterator iter = var_label_in.begin();
          iter != var_label_in.end();iter++)
    {
         var_map_label_vmreg_store_in.insert(std::make_pair(*iter,var_store_in));
    }  
}/*}}}*/

void BuildVMByteCode::set_lastpiece_register_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store)
{/*{{{*/
    VCombosVMCode var_t;
    RegisterStore var_store;
    var_t.upset_register_array(var_store);

    std::vector<CodePiece>::iterator iter = var_list_code_piece.begin();
    for (iter;iter != var_list_code_piece.end();iter++)
    {
        //if ( iter->get_jmplabel_type() == TYPE_RET &&
        //        iter->get_is_jcc() == false)
        bool set_exit = false;
        /*for (std::vector<long*>::iterator entry_iter = var_entry_address.begin();
                 entry_iter != var_entry_address.end();entry_iter++)
            {
                long * addr = *entry_iter;
                if (iter->get_piece().front().insn_offset == *addr)
                {
                   set_exit = true;
                }
            }*/

        /*if (iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_RET ||
                iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_EXIT ||
                iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_EXTERNAL_CALL||
                iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_EXTERNAL_JMP||
                set_exit)*/
        if (iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_RET ||
                iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_EXIT)
        {
            printf("LastPieceLabel:%d\n",iter->get_label());

              var_map_label_vmreg_store.insert( std::make_pair(
                          iter->get_label(),
                          var_store));

        }
        /*if (iter->get_opcode_attribute() == OPCODE_ATTRIBUTE_EXIT)
        {
           var_map_label_vmreg_store_out.insert(std::make_pair<int,RegisterStore>(
                          iter->get_label(),
                          var_store));
        }*/
    }
}/*}}}*/
void BuildVMByteCode::full_register_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_out
        )   
{/*{{{*/
    std::map<int,RegisterStore> store;
    //set_lastpiece_register_store(var_list_code_piece,store);
    //set_register_store(var_list_code_piece,var_map_label_vmreg_store_in,var_map_label_vmreg_store_out,store);

    
    int code_piece_count = var_list_code_piece.size();
    int n = code_piece_count;
    VCombosVMCode combs;
    RegisterStore regstore;
    combs.upset_register_array(regstore);

    for (int i = 0; i < n; i++)
    {
    //    VCombosVMCode combs;
     //   RegisterStore regstore;
     //   combs.upset_register_array(regstore);

        var_map_label_vmreg_store_in.insert(std::make_pair(i,regstore));
        var_map_label_vmreg_store_out.insert(std::make_pair(i,regstore));
    }

    /*while (n)
    {
        VCombosVMCode combs;
        RegisterStore regstore;
        combs.upset_register_array(regstore);
        bool b  = var_map_label_vmreg_store_in.find(var_list_code_piece[--n].get_label()) == 
            var_map_label_vmreg_store_in.end();
        if (b)
        {
            store.insert(std::make_pair<int,RegisterStore>(var_list_code_piece[n].get_label(),regstore)); 
            set_register_store(var_list_code_piece,var_map_label_vmreg_store_in,var_map_label_vmreg_store_out,store);
        }
    } 
    if (var_map_label_vmreg_store_in.find(var_list_code_piece[0].get_label()) == 
      var_map_label_vmreg_store_in.end()) {
     VCombosVMCode combs;
     RegisterStore regstore;
     combs.upset_register_array(regstore);
     var_map_label_vmreg_store_in.insert(std::make_pair<int,RegisterStore>(
        var_list_code_piece[0].get_label(),
        regstore
        ));
    }*/
}/*}}}*/

void BuildVMByteCode::set_register_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_out,
        std::map<int,RegisterStore> & var_map_lastpiece_vmreg_store)  
{/*{{{*/
    std::map<int,RegisterStore>::iterator lastpiece_iter =  var_map_lastpiece_vmreg_store.begin();
    std::map<int,RegisterStore>::iterator  store_in_iter = var_map_label_vmreg_store_in.begin();
    std::map<int,RegisterStore>::iterator store_out_iter = var_map_label_vmreg_store_out.begin(); 
    
    //printf_map_register_store(var_map_lastpiece_vmreg_store,"var_map_lastpiece_vmreg_store");
    int i = 0;
    // printf("var_map_lastpiece_vmreg_store大小:%d\n",var_map_lastpiece_vmreg_store.size());     
    //for (lastpiece_iter; lastpiece_iter != var_map_lastpiece_vmreg_store.end();)//lastpiece_iter++)
    while (!var_map_lastpiece_vmreg_store.empty())
    {
        printf("No.%d Entry Loop,var_map_lastpiece_vmreg_store Size:%d\n",i++,var_map_lastpiece_vmreg_store.size());
        std::map<int,RegisterStore>::iterator var_iter_map_t = lastpiece_iter;
        std::vector<CodePiece>::iterator codepiece_iter = var_list_code_piece.begin(); 
        /*if (i > 100)
        {
           break;
        } */
        for (codepiece_iter; codepiece_iter != var_list_code_piece.end(); codepiece_iter++)
        {
            if (lastpiece_iter->first == codepiece_iter->get_jmplabel() || 
                 (lastpiece_iter->first == (codepiece_iter->get_label() + 1 )) //&&
                  //codepiece_iter->get_jmplabel_type() != TYPE_MEM) 
                 ) {
                var_map_label_vmreg_store_out.insert(std::make_pair(
                            codepiece_iter->get_label(),
                            lastpiece_iter->second
                            ));
                var_map_label_vmreg_store_in.insert(std::make_pair(
                            codepiece_iter->get_label() + 1,
                            lastpiece_iter->second
                            ));
                if (var_map_label_vmreg_store_in.find(codepiece_iter->get_label()) !=
                        var_map_label_vmreg_store_in.end())
                {
                  
                   if (codepiece_iter->get_label() != codepiece_iter->get_jmplabel())
                      var_map_lastpiece_vmreg_store.insert(std::make_pair(
                            codepiece_iter->get_label() + 1,
                            lastpiece_iter->second
                            )); 
               //printf("aaaaaaaaaaaa %s,%x,%x\n" ,var_list_code_piece[codepiece_iter->get_label() + 1 ]
               //                    .get_piece().back().insn_buffer,codepiece_iter->get_label(),codepiece_iter->get_jmplabel());    
                }
                std::map<int,RegisterStore> var_out;
                std::vector<CodePiece> var_t_CodePiece;
                for (std::vector<CodePiece>::iterator iter_t_codepiece = var_list_code_piece.begin();
                        iter_t_codepiece!= var_list_code_piece.end();iter_t_codepiece++)
                {
                    if (var_map_label_vmreg_store_out.find(iter_t_codepiece->get_label()) != 
                            var_map_label_vmreg_store_out.end())
                    {
                        bool b1 =  (var_map_lastpiece_vmreg_store.find(iter_t_codepiece->get_jmplabel()) ==
                                 var_map_lastpiece_vmreg_store.end());
                        bool b2 = (var_map_label_vmreg_store_in.find(iter_t_codepiece->get_jmplabel()) ==
                                 var_map_label_vmreg_store_in.end()); 
                        bool b3 = iter_t_codepiece->get_opcode_attribute() == OPCODE_ATTRIBUTE_NORMAL; //iter_t_codepiece->get_jmplabel_type() == TYPE_LABEL;
                         if (b1 && b2 && b3)
                         {
                             //printf("标签是:%d\n",iter_t_codepiece->get_jmplabel());
                             //if (var_map_label_vmreg_store_in.find(iter_t_codepiece->get_jmplabel()) == 
                             //      var_map_label_vmreg_store_in.end())
                             {

                             
                             var_map_lastpiece_vmreg_store.insert(std::make_pair(
                                         iter_t_codepiece->get_jmplabel(),
                                         lastpiece_iter->second 
                                      ));
               
                             }
                             var_map_label_vmreg_store_in.insert(std::make_pair(
                                         iter_t_codepiece->get_jmplabel(),
                                         lastpiece_iter->second
                                         ));

                                                             
                         } //else if (var_map_label_vmreg_store_out.find(iter_t_codepiece-))
                    }
                }    
                //var_iter_map_t = lastpiece_iter;
                                               
            }
            
            
        }
        
        
        var_map_lastpiece_vmreg_store.erase(lastpiece_iter);
        lastpiece_iter = var_map_lastpiece_vmreg_store.begin();

        /*set_register_store(var_list_code_piece,
                    var_map_label_vmreg_store_in,
                    var_map_label_vmreg_store_out,
                    var_map_t);   */
             
    }
    
}/*}}}*/

/*
void BuildVMByteCode::full_label_vmkey(std::vector<CodePiece> &var_list_code_piece,
      std::map<int,long> & var_map_label_vmkey,
      int var_cur_label,
      int var_key       //代表的是进入时候的key
      )
{
   long firstkey = m_random() ;
   for (std::vector<CodePiece>::iterator xiter = var_list_code_piece.begin();
         xiter != var_list_code_piece.end();xiter++)
   {
      if (xiter->get_is_jcc())
      {
         for (std::vector<CodePiece>::iterator yiter = var_list_code_piece.begin();
            yiter != var_list_code_piece.end();yiter++)
         {
            if (yiter->get_jmplabel() == xiter->get_label())
            {
            var_map_label_vmkey.insert(std:: )
            }
         }  
      }

      var_map_label_vmkey.insert()
   }
} */
