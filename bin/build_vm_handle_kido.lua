--Junks
jfunc_count = 10
max_junc_count = 10
math.randomseed = randomseed
math.random = random
function on_pre_compile()
 r_key = os.time()
 math.randomseed(0)
end

function on_compile()
 math.randomseed(0)
end

function on_after_compile()
 math.randomseed(os.time())
end
function push_random_reg( ... )
	local index = math.random(8)
	if (index == 1) then
		push(T_EAX)
	elseif(index == 2) then
		push(T_ECX)
	elseif(index == 3) then
		push(T_EDX)
	elseif(index == 4) then
		push(T_EBX)
	elseif(index == 5) then
		push(T_ESP)
	elseif(index == 6) then
		push(T_EBP)
	elseif(index == 7) then
		push(T_ESI)
	elseif(index == 8) then
		push(T_EDI)
	end	
end

function GetJunkFunc1( index )
	local jfunc = pushf

	if (index == 1) then
		jfunc = push_random_reg
--	elseif(index == 2) then
--	elseif(index == 3) then
--	elseif(index == 4) then
--	elseif(index == 5) then
--	elseif(index == 6) then
--	elseif(index == 7) then
--	elseif(index == 8) then
--	elseif(index == 9) then
	else
		jfunc = pushf
	end
	return jfunc
end
function GetJunkFunc2( index )
	local jfunc = popf
	if (index == 1) then
		jfunc = pop_operand(T_INVALID)
--	elseif(index == 2) then
--	elseif(index == 3) then
--	elseif(index == 4) then
--	elseif(index == 5) then
--	elseif(index == 6) then
--	elseif(index == 7) then
--	elseif(index == 8) then
--	elseif(index == 9) then
	else
		jfunc = popf
	end
	return jfunc
end

function DoSomeJunk(  )
	local index = math.random(5)
	if (index == 1) then
		local d = math.random(max_junc_count)
		local j = math.random(jfunc_count)
		LoopDoFunc0(GetJunkFunc1(j), d)
		LoopDoFunc0(GetJunkFunc2(j), d)
	elseif(index == 2) then
	elseif(index == 3) then
	elseif(index == 4) then
	elseif(index == 5) then
	elseif(index == 6) then
	elseif(index == 7) then
	elseif(index == 8) then
	elseif(index == 9) then
	elseif(index == 10) then
	end
end

function AddJunk0( func )
	local rand = math.random(10)
	if (rand == 1) then
		DoSomeJunk()
		func()
		DoSomeJunk()
	elseif(rand == 2) then
		DoSomeJunk()
		DoSomeJunk()
		func()
	elseif(rand == 3) then
		DoSomeJunk()
		func()
	elseif(rand == 4) then
		func()
		DoSomeJunk()
	elseif(rand == 5) then
		func()
		DoSomeJunk()
		DoSomeJunk()
	elseif(rand == 6) then
		func()
	elseif(rand == 7) then
		func()
	elseif(rand == 8) then
		func()
	elseif(rand == 9) then
		func()
	elseif(rand == 10) then
		func()
	end
end

function AddJunk1( func, par )
	--push_operand
	--pop_operand
	local rand = math.random(10)
	if (rand == 1) then
		DoSomeJunk()
		func(par)
		DoSomeJunk()
	elseif(rand == 2) then
		DoSomeJunk()
		DoSomeJunk()
		func(par)
	elseif(rand == 3) then
		DoSomeJunk()
		func(par)
	elseif(rand == 4) then
		func(par)
		DoSomeJunk()
	elseif(rand == 5) then
		func(par)
		DoSomeJunk()
		DoSomeJunk()
	elseif(rand == 6) then
		func(par)
	elseif(rand == 7) then
		func(par)
	elseif(rand == 8) then
		func(par)
	elseif(rand == 9) then
		func(par)
	elseif(rand == 10) then
		func(par)
	end
end

--Detailed JunkCode

--utilities
function LoopDoFunc0( func, looptime )
	for i=1,looptime do
		func()
	end	
end

function size_func( op, b_func, w_func, d_func)
    local i = get_operand_size(op)
    if (i == 8) then
        AddJunk0(b_func)
    elseif(i == 16) then
        AddJunk0(w_func)
    elseif(i == 32) then
        AddJunk0(d_func)      
    end
end

function size_func1( op, b_func, w_func, d_func, param)
    local i = get_operand_size(op)
    if (i == 8) then
        AddJunk1(b_func, param)
    elseif(i == 16) then
        AddJunk1(w_func, param)
    elseif(i == 32) then
        AddJunk1(d_func, param)      
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
  AddJunk1(push_operand, 2)
  AddJunk1(pop_operand, 1)
end

function vm_xchg()
  AddJunk1(push_operand, 2)
  AddJunk1(push_operand, 1)
  AddJunk1(pop_operand, 2)
  AddJunk1(pop_operand, 1)
end
function vm_lea()
  push_operand(2,true)
  AddJunk1(pop_operand, 1)
end
function vm_push()
  resize_imm_operand(1)
  AddJunk1(push_operand, 1)
end 
function vm_cmp()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 2)
  AddJunk1(push_operand, 1)
  size_func(1, b_sub, w_sub, d_sub)
  AddJunk0(popf)
  size_pop_invalid(1)
end 
function vm_AddJunk0(ret)
  AddJunk0(ret)
end
function vm_add()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 2)
  AddJunk1(push_operand, 1)
  size_func(1, b_add, w_add, d_add)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)
end
function vm_sub()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 2)
  AddJunk1(push_operand, 1)
  size_func(1, b_sub, w_sub, d_sub)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)
end
function vm_not()
  AddJunk1(push_operand, 1)
  size_func(1, b_not, w_not, d_not)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)
end
function vm_and()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 2)
  AddJunk1(push_operand, 1)
  size_func(1, b_and, w_and, d_and)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)
end
function vm_or()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 1)
  AddJunk1(push_operand, 2)
  size_func(1, b_or, w_or, d_or)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1) 
end
function vm_xor()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 1)
  AddJunk1(push_operand, 2)
  size_func(1, b_xor, w_xor, d_xor)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1) 
end
function vm_test()
  resize_imm_operand(2, get_operand_size(1))
  AddJunk1(push_operand, 1)
  AddJunk1(push_operand, 2)
  size_func(1, b_and, w_and, d_and)
  AddJunk0(popf)
  size_pop_invalid(1)
end
function vm_pop()
  resize_imm_operand(1)
  AddJunk1(pop_operand, 1)
end
function vm_inc()
  AddJunk1(push_operand, 1)
  size_func1(1, b_push_imm, w_push_imm, d_push_imm,1)
  size_func(1, b_add, w_add, d_add)
  d_push_imm(~((1 << 0) | (1 << 10)))
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk0(pushf)
  d_push_imm((1 << 0) | (1 << 10))
  AddJunk0(d_and)
  pop(T_INVALID) 
  AddJunk0(d_or)
  pop(T_INVALID)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)
end
function vm_dec()
  size_func1(1, b_push_imm, w_push_imm, d_push_imm,1)
  AddJunk1(push_operand, 1)
  size_func(1, b_sub, w_sub, d_sub)
  d_push_imm(~((1 << 0) | (1 << 10)))
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk0(pushf)
  d_push_imm((1 << 0) | (1 << 10))
  AddJunk0(d_and)
  pop(T_INVALID) 
  AddJunk0(d_or)
  pop(T_INVALID)
  AddJunk0(popf) 
  AddJunk1(pop_operand, 1)
end
function vm_shl()
  AddJunk1(push_operand, 1) 
  AddJunk1(push_operand, 2)
  size_func(1, b_shl, w_shl, d_shl)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)   
end
function vm_shr()
  AddJunk1(push_operand, 1) 
  AddJunk1(push_operand, 2)
  size_func(1, b_shr, w_shr, d_shr)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)   
end
function vm_sar()
  AddJunk1(push_operand, 1) 
  AddJunk1(push_operand, 2)
  size_func(1, b_sar, w_sar, d_sar)
  AddJunk0(popf)
  AddJunk1(pop_operand, 1)   
end
function vm_cdq()
  push(T_EAX)
  b_push_imm(31)
  AddJunk0(d_sar)
  pop(T_INVALID)
  pop(T_EDX)
end
function vm_cwd()
  push(T_AX)
  b_push_imm(15)
  AddJunk0(w_sar)
  pop(T_INVALID)
  pop(T_DX)
end
function vm_scasb()
  push(T_EDI)
  b_read_mem()
  push(T_AL)
  AddJunk0(b_cmp)
  AddJunk0(popf)
  get_string_ins_diff()
  b_push_imm(0)
  AddJunk0(d_shl)
  pop(T_INVALID)
  push(T_EDI)
  AddJunk0(d_add)
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_scasw() --edi - ~df + df
  push(T_EDI)
  w_read_mem()
  push(T_AX)
  AddJunk0(w_cmp)
  AddJunk0(popf)
  get_string_ins_diff()
  b_push_imm(1)
  AddJunk0(d_shl)
  pop(T_INVALID)
  push(T_EDI)
  AddJunk0(d_add)
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_scasd() --edi - ~df + df
  push(T_EDI)
  d_read_mem()
  push(T_EAX)
  AddJunk0(d_cmp)
  AddJunk0(popf)
  get_string_ins_diff()
  b_push_imm(2)
  AddJunk0(d_shl)
  pop(T_INVALID)
  push(T_EDI)
  AddJunk0(d_add)
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
  AddJunk0(d_add)
  pop(T_INVALID)
  pop(T_ESI)
  push(T_EDI)
  AddJunk0(d_add)
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
  AddJunk0(d_shl)
  pop(T_INVALID)
  push_vsp()
  d_read_mem()
  push(T_ESI)
  AddJunk0(d_add)
  pop(T_INVALID)
  pop(T_ESI)
  push(T_EDI)
  AddJunk0(d_add)
  pop(T_INVALID)
  pop(T_EDI)
end
function vm_setz() -- zf = 1
  AddJunk0(pushf)
  get_zf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setnz() -- zf = 0
  AddJunk0(pushf)
  get_zf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_not)
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_sets() -- sf = 1
  AddJunk0(pushf)
  get_sf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setns() -- sf = 0
  AddJunk0(pushf)
  get_sf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_not)
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setnp() -- pf = 0
  AddJunk0(pushf)
  get_pf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_not) 
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setp() -- pf = 1
  AddJunk0(pushf)
  get_pf()
  b_push_imm(2) 
  AddJunk0(d_shr)--右移
  pop(T_INVALID)--删除shr那个eflag我们并不需要
  AddJunk1(pop_operand, 1) --把刚刚那个数据写入第一个操作数,因为第一个操作数只会是8位 
  pop(T_INVALID | T_16X)--上面用了8位还剩24位(这24位都为0)先删除16位
  pop(T_INVALID | T_8H)--在删除8位 
end 
function vm_seto() -- of = 1
  AddJunk0(pushf)
  get_of()--这里获取一个dword的zf标志位 zf=1的时候 数据为4(二进制100) zf=0的时候 数据为0
  b_push_imm(2) --这里把刚刚获取的那个数据右移三位
  AddJunk0(d_shr)--右移
  pop(T_INVALID)--删除shr那个eflag我们并不需要
  AddJunk1(pop_operand, 1) --把刚刚那个数据写入第一个操作数,因为第一个操作数只会是8位
  pop(T_INVALID | T_16X)--上面用了8位还剩24位(这24位都为0)先删除16位
  pop(T_INVALID | T_8H)--在删除8位
end
function vm_setno() -- of = 0
  AddJunk0(pushf)
  get_of()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_not)
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setb() -- cf = 1
  AddJunk0(pushf)
  get_cf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setae() -- cf = 0
  AddJunk0(pushf)
  get_cf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_not)
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_seta() -- cf = 0 && zf = 0
  AddJunk0(pushf)
  get_cf()
  b_push_imm(2)
  AddJunk0(d_shr)
  pop(T_INVALID)
  AddJunk0(d_not)
  pop(T_INVALID)
  AddJunk0(pushf)
  get_zf()
  b_push_imm(2)
  AddJunk0(d_shr)
  pop(T_INVALID)
  AddJunk0(d_not)
  pop(T_INVALID)
  AddJunk0(d_and)
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setbe() -- cf = 1 && zf = 1
  AddJunk0(pushf)
  get_cf()
  b_push_imm(2)
  AddJunk0(d_shr)
  pop(T_INVALID)
  AddJunk0(d_not)
  pop(T_INVALID)
  AddJunk0(pushf)
  get_zf()
  b_push_imm(2)
  AddJunk0(d_shr)
  pop(T_INVALID)
  AddJunk0(d_not)
  pop(T_INVALID)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk0(d_not)
  pop(T_INVALID)
  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setg()-- zf = 0 && sf = of
  AddJunk0(pushf)
  get_zf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_not)
  pop(T_INVALID)

  AddJunk0(pushf)
  get_sf()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(pushf)
  get_of()--
  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk0(d_xor)
  pop(T_INVALID)
  AddJunk0(d_not)
  pop(T_INVALID)

  AddJunk0(d_and)
  pop(T_INVALID)

  b_push_imm_zx(1)
  AddJunk0(d_and)
  pop(T_INVALID)

  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
 function vm_setle() -- zf = 1 && sf != of
  AddJunk0(pushf)
  get_sf()--

  AddJunk0(pushf)
  get_of()

  AddJunk0(d_xor)
  pop(T_INVALID)

  AddJunk0(pushf)
  get_zf()

  AddJunk0(d_and)
  pop(T_INVALID)

  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setl() -- sf != of
  AddJunk0(pushf)
  get_sf()--

  AddJunk0(pushf)
  get_of()

  AddJunk0(d_xor)
  pop(T_INVALID)

  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_setge() -- sf = OF
  AddJunk0(pushf)
  get_sf()--

  AddJunk0(pushf)
  get_of()

  AddJunk0(d_xor)
  pop(T_INVALID)

  AddJunk0(d_not)
  pop(T_INVALID)

  b_push_imm(2) --
  AddJunk0(d_shr)--
  pop(T_INVALID)--
  AddJunk1(pop_operand, 1) --
  pop(T_INVALID | T_16X)--
  pop(T_INVALID | T_8H)--
end
function vm_jnz() --ZF = 0
 

push(T_NEXTINSADDR)
push(T_JMPINSADDR)

push_vsp()

AddJunk0(pushf)
d_push_imm(0x40)
AddJunk0(d_and)
pop(T_INVALID)

b_push_imm(4)
AddJunk0(d_shr)
pop(T_INVALID)
AddJunk0(d_add)
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

AddJunk0(pushf)
d_push_imm(0x40)
AddJunk0(d_and)
pop(T_INVALID)

b_push_imm(4)
AddJunk0(d_shr)
pop(T_INVALID)
AddJunk0(d_add)
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

AddJunk0(pushf)
get_cf()
AddJunk0(pushf)
get_zf()
AddJunk0(d_or)
pop(T_INVALID)

AddJunk0(d_add)
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

AddJunk0(pushf)
get_cf()

AddJunk0(d_add)
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

AddJunk0(pushf)
get_cf()

AddJunk0(d_add)
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

AddJunk0(pushf)
get_cf()

AddJunk0(pushf)
get_zf()

AddJunk0(d_or)
pop(T_INVALID)

AddJunk0(d_add)
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
AddJunk0(w_cmp)
get_zf()

AddJunk0(d_add)
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

AddJunk0(pushf)
get_zf()

AddJunk0(pushf)
get_sf()
AddJunk0(pushf)
get_of()
AddJunk0(d_xor)
pop(T_INVALID)

AddJunk0(d_or)
pop(T_INVALID)

AddJunk0(d_add)
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

AddJunk0(pushf)
get_sf()
AddJunk0(pushf)
get_of()
AddJunk0(d_xor)
pop(T_INVALID)

AddJunk0(d_add)
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

AddJunk0(pushf)
get_of()
AddJunk0(pushf)
get_sf()
AddJunk0(d_xor)
pop(T_INVALID)

AddJunk0(d_add)
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

AddJunk0(pushf)
get_zf()

AddJunk0(pushf)
get_sf()
AddJunk0(pushf)
get_of()
AddJunk0(d_xor)
pop(T_INVALID)

AddJunk0(d_or)
pop(T_INVALID)

AddJunk0(d_add)
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

AddJunk0(pushf)
get_of()

AddJunk0(d_add)
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

AddJunk0(pushf)
get_pf()

AddJunk0(d_add)
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

  AddJunk0(pushf)
  get_sf()

  AddJunk0(d_add)
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
  AddJunk0(pushf)
  get_of()
  AddJunk0(d_add)
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
  AddJunk0(pushf)
  get_pf()
  AddJunk0(d_add)
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
  AddJunk0(pushf)
  get_sf()
  AddJunk0(d_add)
  pop(T_INVALID)
  d_read_mem()
  pop(T_NEXTINSADDR)
  pop(T_INVALID)
  pop(T_INVALID)
end

function vm_jmp()
end
