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
