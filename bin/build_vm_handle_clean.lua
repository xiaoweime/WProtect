--Junks
math.randomseed = randomseed
math.random = random

function on_pre_compile()
 math.randomseed(0)
end

function on_compile()
 math.randomseed(0)
end

function on_after_compile()
 math.randomseed(os.time())
end 

--utilities
function size_func( op, b_func, w_func, d_func)
    local i = get_operand_size(op)
    if (i == 8) then
        b_func()
    elseif(i == 16) then
        w_func()
    elseif(i == 32) then
        d_func()      
    end
end

function size_func1( op, b_func, w_func, d_func, param)
    local i = get_operand_size(op)
    if (i == 8) then
        b_func(param)
    elseif(i == 16) then
        w_func(param)
    elseif(i == 32) then
        d_func(param)      
    end
end

function size_pop_invalid( op )
    local i = get_operand_size(op)
    if (i == 8) then
        pop(T_INVALID | T_E32X | T_16X | T_8L)
    elseif(i == 16) then
        pop(T_INVALID | T_E32X | T_16X)
    elseif(i == 32) then
        pop(T_INVALID | T_E32X)       
    end
end

--Template
function vm_nop()
end
function vm_mov()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(2)
  pop_operand(1)
end

function vm_xchg()
  push_operand(2)
  push_operand(1)
  pop_operand(2)
  pop_operand(1)
end
function vm_lea()
  push_operand(2,true)
  pop_operand(1)
end
function vm_push()
  resize_imm_operand(1)
  push_operand(1)
end 
function vm_cmp()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(2)
  push_operand(1)
  size_func(1, b_sub, w_sub, d_sub)
  popf()
  size_pop_invalid(1)
end 
function vm_ret()
  ret()
end
function vm_add()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(2)
  push_operand(1)
  size_func(1, b_add, w_add, d_add)
  popf()
  pop_operand(1)
end
function vm_sub()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(2)
  push_operand(1)
  size_func(1, b_sub, w_sub, d_sub)
  popf()
  pop_operand(1)
end
function vm_not()
  push_operand(1)
  size_func(1, b_not, w_not, d_not)
  popf()
  pop_operand(1)
end
function vm_and()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(2)
  push_operand(1)
  size_func(1, b_and, w_and, d_and)
  popf()
  pop_operand(1)
end
function vm_or()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(1)
  push_operand(2)
  size_func(1, b_or, w_or, d_or)
  popf()
  pop_operand(1) 
end
function vm_xor()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(1)
  push_operand(2)
  size_func(1, b_xor, w_xor, d_xor)
  popf()
  pop_operand(1) 
end
function vm_test()
  resize_imm_operand(2, get_operand_size(1))
  push_operand(1)
  push_operand(2)
  size_func(1, b_and, w_and, d_and)
  popf()
  size_pop_invalid(1)
end
function vm_pop()
  resize_imm_operand(1)
  pop_operand(1)
end
function vm_inc()
  push_operand(1)
  size_func1(1, b_push_imm, w_push_imm, d_push_imm,1)
  size_func(1, b_add, w_add, d_add)
  d_push_imm(~((1 << 0) | (1 << 10)))
  d_and()
  pop(T_INVALID)
  pushf()
  d_push_imm((1 << 0) | (1 << 10))
  d_and()
  pop(T_INVALID) 
  d_or()
  pop(T_INVALID)
  popf()
  pop_operand(1)
end
function vm_dec()
  size_func1(1, b_push_imm, w_push_imm, d_push_imm,1)
  push_operand(1)
  size_func(1, b_sub, w_sub, d_sub)
  d_push_imm(~((1 << 0) | (1 << 10)))
  d_and()
  pop(T_INVALID)
  pushf()
  d_push_imm((1 << 0) | (1 << 10))
  d_and()
  pop(T_INVALID) 
  d_or()
  pop(T_INVALID)
  popf() 
  pop_operand(1)
end
function vm_shl()
  push_operand(1) 
  push_operand(2)
  size_func(1, b_shl, w_shl, d_shl)
  popf()
  pop_operand(1)   
end
function vm_shr()
  push_operand(1) 
  push_operand(2)
  size_func(1, b_shr, w_shr, d_shr)
  popf()
  pop_operand(1)   
end
function vm_sar()
  push_operand(1) 
  push_operand(2)
  size_func(1, b_sar, w_sar, d_sar)
  popf()
  pop_operand(1)   
end
function vm_cdq()
  push(T_EAX)
  b_push_imm(31)
  d_sar()
  pop(T_INVALID)
  pop(T_EDX)
end
function vm_cwd()
  push(T_AX)
  b_push_imm(15)
  w_sar()
  pop(T_INVALID)
  pop(T_DX)
end
function vm_scasb()
  push(T_EDI)
  b_read_mem()
  push(T_AL)
  b_cmp()
  popf()
  get_string_ins_diff()
  b_push_imm(0)
  d_shl()
  pop(T_INVALID)
  push(T_EDI)
  d_add()
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_scasw() --edi - ~df + df
  push(T_EDI)
  w_read_mem()
  push(T_AX)
  w_cmp()
  popf()
  get_string_ins_diff()
  b_push_imm(1)
  d_shl()
  pop(T_INVALID)
  push(T_EDI)
  d_add()
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_scasd() --edi - ~df + df
  push(T_EDI)
  d_read_mem()
  push(T_EAX)
  d_cmp()
  popf()
  get_string_ins_diff()
  b_push_imm(2)
  d_shl()
  pop(T_INVALID)
  push(T_EDI)
  d_add()
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_movsb()
  push(T_ESI)
  b_read_mem()
  push(T_EDI)
  b_write_mem()
  get_string_ins_diff()
  push_vsp()
  d_read_mem()
  push(T_ESI)
  d_add()
  pop(T_INVALID)
  pop(T_ESI)
  push(T_EDI)
  d_add()
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_movsd()
  push(T_ESI)
  d_read_mem()
  push(T_EDI)
  d_write_mem()
  get_string_ins_diff()
  b_push_imm(2)
  d_shl()
  pop(T_INVALID)
  push_vsp()
  d_read_mem()
  push(T_ESI)
  d_add()
  pop(T_INVALID)
  pop(T_ESI)
  push(T_EDI)
  d_add()
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_setz() -- zf = 1
  pushf()
  get_zf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setnz() -- zf = 0
  pushf()
  get_zf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_not()
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_sets() -- sf = 1
  pushf()
  get_sf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setns() -- sf = 0
  pushf()
  get_sf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_not()
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setnp() -- pf = 0
  pushf()
  get_pf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_not() 
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setp() -- pf = 1
  pushf()
  get_pf()--这里获取一个dword的zf标志位 zf=1的时候 数据为4(二进制100) zf=0的时候 数据为0
  b_push_imm(2) --这里把刚刚获取的那个数据右移三位
  d_shr()--右移
  pop(T_INVALID)--删除shr那个eflag我们并不需要
  pop_operand(1) --把刚刚那个数据写入第一个操作数,因为第一个操作数只会是8位 
  pop(T_INVALID | T_16X)--上面用了8位还剩24位(这24位都为0)先删除16位
  pop(T_INVALID | T_8H)--在删除8位 
end 
function vm_seto() -- of = 1
  pushf()
  get_of()--这里获取一个dword的zf标志位 zf=1的时候 数据为4(二进制100) zf=0的时候 数据为0
  b_push_imm(2) --这里把刚刚获取的那个数据右移三位
  d_shr()--右移
  pop(T_INVALID)--删除shr那个eflag我们并不需要
  pop_operand(1) --把刚刚那个数据写入第一个操作数,因为第一个操作数只会是8位
  pop(T_INVALID | T_16X)--上面用了8位还剩24位(这24位都为0)先删除16位
  pop(T_INVALID | T_8H)--在删除8位
end
function vm_setno() -- of = 0
  pushf()
  get_of()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_not()
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setb() -- cf = 1
  pushf()
  get_cf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setae() -- cf = 0
  pushf()
  get_cf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_not()
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_seta() -- cf = 0 && zf = 0
  pushf()
  get_cf()
  b_push_imm(2)
  d_shr()
  pop(T_INVALID)
  d_not()
  pop(T_INVALID)
  pushf()
  get_zf()
  b_push_imm(2)
  d_shr()
  pop(T_INVALID)
  d_not()
  pop(T_INVALID)
  d_and()
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setbe() -- cf = 1 && zf = 1
  pushf()
  get_cf()
  b_push_imm(2)
  d_shr()
  pop(T_INVALID)
  d_not()
  pop(T_INVALID)
  pushf()
  get_zf()
  b_push_imm(2)
  d_shr()
  pop(T_INVALID)
  d_not()
  pop(T_INVALID)
  d_and()
  pop(T_INVALID)
  d_not()
  pop(T_INVALID)
  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setg()-- zf = 0 && sf = of
  pushf()
  get_zf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_not()
  pop(T_INVALID)

  pushf()
  get_sf()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pushf()
  get_of()--
  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  d_xor()
  pop(T_INVALID)
  d_not()
  pop(T_INVALID)

  d_and()
  pop(T_INVALID)

  b_push_imm_zx(1)
  d_and()
  pop(T_INVALID)

  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
 function vm_setle() -- zf = 1 && sf != of
  pushf()
  get_sf()--

  pushf()
  get_of()

  d_xor()
  pop(T_INVALID)

  pushf()
  get_zf()

  d_and()
  pop(T_INVALID)

  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setl() -- sf != of
  pushf()
  get_sf()--

  pushf()
  get_of()

  d_xor()
  pop(T_INVALID)

  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setge() -- sf = OF
  pushf()
  get_sf()--

  pushf()
  get_of()

  d_xor()
  pop(T_INVALID)

  d_not()
  pop(T_INVALID)

  b_push_imm(2) --
  d_shr()--
  pop(T_INVALID)--
  pop_operand(1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_jnz() --ZF = 0
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
d_push_imm(0x40)
d_and()
pop(T_INVALID)

b_push_imm(4)
d_shr()
pop(T_INVALID)
d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jz()--ZF != 0
 

push(T_JMPINSADDR)
push(T_NEXTINSADDR)

push_vsp()

pushf()
d_push_imm(0x40)
d_and()
pop(T_INVALID)

b_push_imm(4)
d_shr()
pop(T_INVALID)
d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_ja() --CF = 0 && ZF = 0
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
get_cf()
pushf()
get_zf()
d_or()
pop(T_INVALID)

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jae()-- CF = 0
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
get_cf()

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)
 
 
end
function vm_jb()--CF = 1
 

push(T_JMPINSADDR)
push(T_NEXTINSADDR)

push_vsp()

pushf()
get_cf()

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jbe() --CF = 1 || ZF = 1
 

push(T_JMPINSADDR)
push(T_NEXTINSADDR)

push_vsp()

pushf()
get_cf()

pushf()
get_zf()

d_or()
pop(T_INVALID)

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)
 
 
end
function vm_jcxz()--CX = 0
 

push(T_JMPINSADDR)

push(T_NEXTINSADDR)

push_vsp()
w_push_imm(0)
push(T_CX)
w_cmp()
get_zf()

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jg()--ZF = 0 && SF = OF
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
get_zf()

pushf()
get_sf()
pushf()
get_of()
d_xor()
pop(T_INVALID)

d_or()
pop(T_INVALID)

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)
 
 
end
function vm_jge() --SF = OF
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
get_sf()
pushf()
get_of()
d_xor()
pop(T_INVALID)

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jl()-- OF != SF
 


push(T_JMPINSADDR)
push(T_NEXTINSADDR) 

push_vsp()

pushf()
get_of()
pushf()
get_sf()
d_xor()
pop(T_INVALID)

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)
 
 
end
function vm_jle()-- ZF = 1 || SF != OF
 


push(T_JMPINSADDR)
push(T_NEXTINSADDR) 

push_vsp()

pushf()
get_zf()

pushf()
get_sf()
pushf()
get_of()
d_xor()
pop(T_INVALID)

d_or()
pop(T_INVALID)

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jno() -- OF = 0
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
get_of()

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)
 
 
end
function vm_jnp() -- PF = 0
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

pushf()
get_pf()

d_add()
pop(T_INVALID)
d_read_mem()
pop(T_NEXTINSADDR)
pop(T_INVALID)
pop(T_INVALID)

 
end
function vm_jns() -- SF = 0
  push(T_NEXTINSADDR)
  push(T_JMPINSADDR)

  push_vsp()

  pushf()
  get_sf()

  d_add()
  pop(T_INVALID)
  d_read_mem()
  pop(T_NEXTINSADDR)
  pop(T_INVALID)
  pop(T_INVALID)
end
function vm_jo()-- OF = 1
  push(T_JMPINSADDR)
  push(T_NEXTINSADDR)
  push_vsp()
  pushf()
  get_of()
  d_add()
  pop(T_INVALID)
  d_read_mem()
  pop(T_NEXTINSADDR)
  pop(T_INVALID)
  pop(T_INVALID)
end
function vm_jp()-- PF = 1
  push(T_JMPINSADDR)
  push(T_NEXTINSADDR) 
  push_vsp()
  pushf()
  get_pf()
  d_add()
  pop(T_INVALID)
  d_read_mem()
  pop(T_NEXTINSADDR)
  pop(T_INVALID)
  pop(T_INVALID)
end
function vm_js()
  push(T_JMPINSADDR)
  push(T_NEXTINSADDR) 
  push_vsp()
  pushf()
  get_sf()
  d_add()
  pop(T_INVALID)
  d_read_mem()
  pop(T_NEXTINSADDR)
  pop(T_INVALID)
  pop(T_INVALID)
end

function vm_jmp()
end
