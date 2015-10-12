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