--Common Instructions
function nop()
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
    push_operand(1)
end

function cmp()
    push_operand(2)
    push_operand(1)
    local i = get_operand_size(1)
    if (i == 8) then
        b_sub()
        popf()
        pop(T_INVALID | T_E32X | T_16X | T_8L)
    elseif(i == 16) then
        w_sub()
        popf()
        pop(T_INVALID | T_E32X | T_16X)
    elseif(i == 32) then
        d_sub()
        popf()
        pop(T_INVALID | T_E32X)       
    end
end

function ret()
    ret()
end

function add()
    push_operand(2)
    push_operand(1)
    local i = get_operand_size(1)
    if (i == 8) then
        b_add()
    elseif(i == 16) then
        w_add()
    elseif(i == 32) then
        d_add()     
    end
    popf()
    pop_operand(1)
end
--setCC
function stc()
    pushf();
    b_push_imm_zx(1);
    d_or();
    pop(T_INVALID);
    popf();
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
function setnz()
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
    pop(T_INVALID | T_8L )
    pop(T_INVALID | T_16X)
end

function sets()
    pushf();
    get_sf();
    b_push_imm(2);
    d_shr();
    pop(T_INVALID); 
    pop_operand(1);
    pop(T_INVALID | T_8L );
    pop(T_INVALID | T_16X);    
end
function setns()
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
    pop(T_INVALID | T_8L )
    pop(T_INVALID | T_16X)
end

function setp()
    pushf();
    get_pf();
    b_push_imm(2);
    d_shr();
    pop(T_INVALID); 
    pop_operand(1);
    pop(T_INVALID | T_8L );
    pop(T_INVALID | T_16X);     
end               
function setnp()
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
    pop(T_INVALID | T_8L )
    pop(T_INVALID | T_16X)
end

function seto()
    pushf();
    get_of();
    b_push_imm(2);
    d_shr();
    pop(T_INVALID); 
    pop_operand(1);
    pop(T_INVALID | T_8L );
    pop(T_INVALID | T_16X);     
end               
function setno()
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
    pop(T_INVALID | T_8L )
    pop(T_INVALID | T_16X)
end
