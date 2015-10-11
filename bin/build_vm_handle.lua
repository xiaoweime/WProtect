function stc()
    pushf();
    b_push_imm_zx(1);
    d_or();
    pop(INVALID);
    popf();
end
