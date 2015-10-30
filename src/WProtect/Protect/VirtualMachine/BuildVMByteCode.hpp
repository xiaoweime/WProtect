
#ifndef BUILDVMBYTECODE_HPP_PTATXLUJ
#define BUILDVMBYTECODE_HPP_PTATXLUJ
#include "CombosVMCode.hpp"
#include "VirtualMachineManage.hpp"
#include "VMAddressTable.hpp"
#include "VMCodeBuffer.hpp"
#include <Analysis.hpp>
#include <vector>
#include <logfunctions.h>
#include <random.hpp>

class BuildVMByteCode : public logfunctions{
  public:
    enum ProtectType{
        ComplexIns, //Complex Instruction Set Computer
        ReducudIns, //Reduced Instruction Set Computer
        //超级精简指令没有数字运算
        UntimateReducedIns //Ultimate Reduced Instruction Set Computer
    };

  std::map<int,RegisterStore> var_map_label_vmreg_store;
  std::map<int,RegisterStore> var_map_label_vmreg_store_in;  
  std::map<int,RegisterStore> var_map_label_vmreg_store_out;  
  std::map<int,long> var_map_label_vmkey;           //标签对应的vmkey
  std::map<int,long>  var_map_label_vmcode_addr;    //标签对应的分配的vmcode地址 
  std::map<int,long>  var_map_newlabel_vmcode_addr;
  std::map<int,VMCodeBufferManage *> var_map_label_vmbuffer_manage;
  std::map<int,VMCodeBufferManage *> var_map_newlabel_vmbuffer_manage;
  std::vector<long*> var_entry_address;
  std::vector<CodePiece> var_list_code_piece;  
  std::vector<VMCodeBufferManage *> var_vmcode_manager_list; 
  int newlabel_count;
  long get_newvm_cur_label();
  VMCodeBufferManage * get_newvm_piece();

  VMCodeBufferManage * create_newvm_piece();
  VirtualMachine * ptr_vm;
  VMAddressTable * ptr_addr_table;
  void build_pfx(VCombosVMCode & var_combos_vm_code,ud_t &var_ud,CodePiece &var_cur_piece,bool b_allocator) ;
  BuildVMByteCode(VirtualMachineManage *ptr_vmmanage,
          pCodeBufferInfo ptr_info,
          VMAddressTable * ptr_address_table);
  BuildVMByteCode(VirtualMachineManage * ptr_vmmanage,
        pCodeBufferInfo ptr_info,
        VMAddressTable *ptr_address_table,
        std::vector<long *> & entry_address);

  ~BuildVMByteCode();
  void build(VCombosVMCode & var_combos_vm_code,ud_t & var_ud);
  long create_vm_entry(int _label);
  long get_vmcode_address(int _label_index);
  //void build(VCombosVMCode & var_combos_vm_code,ud_t & var_ud,long var_jmp_addr);
  void set_lastpiece_register_store(std::vector<CodePiece> &var_list_code_piece,std::map<int,RegisterStore> & var_map_label_vmreg_store); 
  void set_register_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_out,
        std::map<int,RegisterStore> & var_map_lastpiece_vmreg_store);   
  void full_register_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_out);    
  void set_vmregister_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_out,
        int var_cur_label); 
  void full_vmregister_store(std::vector<CodePiece> &var_list_code_piece,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_in,
        std::map<int,RegisterStore> & var_map_label_vmreg_store_out);
  void vm_operand(VCombosVMCode & var_combos_vm_code,ud_operand & var_operand);
  void write_vm_operand(VCombosVMCode & var_combos_vm_code,ud_operand & var_operand); 
  void read_vm_operand(VCombosVMCode & var_combos_vm_code,ud_operand & var_operand);
  void build_fpu(VCombosVMCode & var_combos_vm_code,ud_t &var_ud);
  void copy_exec_code_to_stack(VCombosVMCode & var_combos_vm_code,
                                              const uint8_t * var_code_buffer,
                                              size_t var_code_size);
  void register_mapped_init();
  void call_lua_functions(const char * lua_fuc_name);
  long build_vmcode(bool b_allocator);
  std::map<ud_type,long> mapped_vm_register;
  long get_vm_register(ud_type _register);
#ifdef DEBUG
  bool vmdebug_out_file_directory;
#endif
  RandomEngender random_engender;
  //lua interface 
};

extern BuildVMByteCode * ptr_build_vm_bytecode;

extern VCombosVMCode * ptr_combos_vm_code;

extern ud_t  * ptr_ud;



#endif /* end of include guard: BUILDVMBYTECODE_HPP_PTATXLUJ */
