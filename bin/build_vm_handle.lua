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
        pop(T_INVALID + T_E32X + T_16X + T_8L)
    elseif(i == 16) then
        pop(T_INVALID + T_E32X + T_16X)
    elseif(i == 32) then
        pop(T_INVALID + T_E32X)       
    end
end

--Common Instructions
function vm_nop()
    push_operand(1)
    pop_operand(1)
end

function vm_mov()
    push_operand(2)
    pop_operand(1)
end

function vm_movzx()
    for i =  get_operand_size(2), get_operand_size(1)-1, 8 do
        b_push_imm(0)
    end
    push_operand(2)
    pop_operand(1)
end

function vm_movsx()
    push_operand(2)
    for i =  get_operand_size(2), get_operand_size(1)-1, 8 do
        b_push_imm(0)
    end
    b_push_imm(get_operand_size(1) - get_operand_size(2))
    d_sar()
    pop(T_INVALID)
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

function vm_pop()
    resize_imm_operand(1)
    pop_operand(1)
end

function vm_cmp()
    push_operand(2)
    push_operand(1)
    size_func(1, b_sub, w_sub, d_sub)
    popf()
    size_pop_invalid(1)
end

function vm_test()
    resize_imm_operand(2, get_operand_size(1))
    push_operand(1)
    push_operand(2)
    size_func(1, b_and, w_and, d_and)
    popf()
    size_pop_invalid(1)   
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
    resize_imm_operand(2,get_operand_size(1))
    push_operand(2)
    push_operand(1)
    size_func(1, b_sub, w_sub, d_sub)
    popf()
    pop_operand(1)
end

function vm_inc()
    push_operand(1)
    size_func1(1, b_push_imm, w_push_imm, d_push_imm, 1)
    d_add()
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
    push_operand(1)
    size_func1(1, b_push_imm, w_push_imm, d_push_imm, 1)
    d_sub()
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

function vm_not()
    push_operand(1)
    size_func(1, b_not, w_not, d_not)
    popf()
    pop_operand(1)    
end

function vm_and()
    push_operand(1)
    size_func(1, b_and, w_and, d_and)
    popf()
    pop_operand(1)    
end

function vm_or()
    push_operand(1)
    size_func(1, b_or, w_or, d_or)
    popf()
    pop_operand(1)    
end

function vm_xor()
    push_operand(1)
    size_func(1, b_xor, w_xor, d_xor)   
    popf()
    pop_operand(1)    
end

function vm_shl()
    push_operand(1) 
    push_operand(2)
    size_func1(1, b_shl, w_shl, d_shl, 1)
    popf()
    pop_operand(1)       
end

function vm_shr()
    push_operand(1) 
    push_operand(2)
    size_func1(1, b_shr, w_shr, d_shr, 1)
    popf()
    pop_operand(1)   
end

function vm_sar()
    push_operand(1)
    push_operand(2)
    size_func1(1, b_sar, w_sar, d_sar, 1)
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
    pop(T_EDX)
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

function vm_scasw()
    push(T_EDI)
    b_read_mem()
    push(T_AX)
    b_cmp()
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

function vm_scasd()
    push(T_EDI)
    b_read_mem()
    push(T_EAX)
    b_cmp()
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
    b_write_men()

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
    b_read_mem()
    push(T_EDI)
    b_write_men()

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

--jcc
function vm_jnz()
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

function vm_jz()
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

function vm_ja()
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

function vm_jae()
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

function vm_jb( ... )
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

function vm_jbe()
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

function vm_jcxz()
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

function vm_jg()
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

function vm_jge()
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

function vm_jl()
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

function vm_jle()
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

function vm_jo()
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

function vm_jno()
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

function vm_jp()
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

function vm_jnp()
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

function vm_jns()
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

function vm_jmp()
end

--setcc
function vm_setz()
    pushf()
    get_zf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID) 
    pop_operand(1)
    pop(T_INVALID | T_8L )
    pop(T_INVALID | T_16X)     
end               

function vm_setnz()
    pushf()
    get_zf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    b_push_imm_zx(1)
    d_and()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_sets()
    pushf()
    get_sf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_setns()
    pushf()
    get_sf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    b_push_imm_zx(1)
    d_and()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_setp()
    pushf()
    get_pf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_setnp()
    pushf()
    get_pf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    b_push_imm_zx(1)
    d_and()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_seto()
    pushf()
    get_of()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_setno()
    pushf()
    get_of()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    b_push_imm_zx(1)
    d_and()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_setb()
    pushf()
    get_cf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X) 
end

function vm_setae()
    pushf()
    get_cf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    b_push_imm_zx(1)
    d_and()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)
end

function vm_seta()
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
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X) 
end

function vm_setbe()
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
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)    
end

function vm_setg()
    pushf()
    get_zf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    pushf()
    get_sf()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pushf()
    get_of()
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    d_xor()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    d_and()
    pop(T_INVALID)
    b_push_imm_zx(1)
    d_and()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)  
end

function vm_setge()
    pushf()
    get_sf()
    pushf()
    get_of()
    d_xor()
    pop(T_INVALID)
    d_not()
    pop(T_INVALID)
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)  
end

function vm_setle()
    pushf()
    get_sf()
    pushf()
    get_of()
    d_xor()
    pop(T_INVALID)
    pushf()
    get_zf()
    d_and()
    pop(T_INVALID)
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)   
end

function vm_setl()
    pushf()
    get_sf()
    pushf()
    get_of()
    d_xor()
    pop(T_INVALID)
    b_push_imm(2)
    d_shr()
    pop(T_INVALID)
    pop_operand(1)
    pop(T_INVALID | T_8L)
    pop(T_INVALID | T_16X)       
end