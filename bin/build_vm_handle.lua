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
function nop()
    push_operand(1)
    pop_operand(1)
end

function mov()
    push_operand(2)
    pop_operand(1)
end

function xchg()
    push_operand(2)
    push_operand(1)
    pop_operand(2)
    pop_operand(1)
end

function lea()
    push_operand(2,true)
    pop_operand(1)
end

function push()
    resize_imm_operand(1)
    push_operand(1)
end

function pop()
    resize_imm_operand(1)
    pop_operand(1)
end

function cmp()
    push_operand(2)
    push_operand(1)
    size_func(1, b_sub, w_sub, d_sub)
    popf()
    size_pop_invalid(1)
end

function test()
    resize_imm_operand(2, get_operand_size(1))
    push_operand(1)
    push_operand(2)
    size_func(1, b_and, w_and, d_and)
    popf()
    size_pop_invalid(1)   
end

function add()
    resize_imm_operand(2, get_operand_size(1))
    push_operand(2)
    push_operand(1)
    size_func(1, b_add, w_add, d_add)
    popf()
    pop_operand(1)
end

function sub()
    resize_imm_operand(2,get_operand_size(1))
    push_operand(2)
    push_operand(1)
    size_func(1, b_sub, w_sub, d_sub)
    popf()
    pop_operand(1)
end

function inc()
    push_operand(1)
    size_func1(1, b_push_imm, w_push_imm, d_push_imm, i)
    --to be added

end

function dec()
    --TODO:   
end

function xor()
    push_operand(1)
    size_func(1, b_xor, w_xor, d_xor)   
    popf()
    pop_operand(1)    
end

function shl()
    push_operand(1) 
    push_operand(2)
    size_func1(1, b_shl, w_shl, d_shl, 1)
    popf()
    pop_operand(1)       
end

function shr()
    push_operand(1) 
    push_operand(2)
    size_func1(1, b_shr, w_shr, d_shr, 1)
    popf()
    pop_operand(1)   
end

function sar()
    push_operand(1)
    push_operand(2)
    size_func1(1, b_sar, w_sar, d_sar, 1)
    popf()
    pop_operand(1)
end

function cdq()
    push(T_EAX)
    b_push_imm(31)
    d_sar()
    pop(T_INVALID)
    pop(T_EDX)
end

function cwd()
    push(T_AX)
    b_push_imm(15)
    w_sar()
    pop(T_INVALID)
    pop(T_EDX)
end

function scasb()
    push(T_EDI)
    b_read_mem()
    push(T_AL)
    b_cmp()
    popf()

    get_string_ins_diff()
    b_push_imm(0)
    d_shl()
    pop(T_INVALID)
end

function scasb()
    push(T_EDI)
    b_read_mem()
    push(T_AL)
    b_cmp()
    popf()

    get_string_ins_diff()
    b_push_imm(0)
    d_shl()
    pop(T_INVALID)
end

function setz()
    pushf();
    get_zf();
    b_push_imm(2);
    d_shr();
    pop(T_INVALID); 
    pop_operand(1);
    pop(T_INVALID | T_8L );
    pop(T_INVALID | T_16X);     
end               
