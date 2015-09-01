#ifndef OUTDETAILEDINFORMATION_HPP_D54GBQU3
#define OUTDETAILEDINFORMATION_HPP_D54GBQU3

#include <iostream>
#include "VOperand.hpp"
#include "PCode.hpp"
using namespace std;

class OutDI{
    public:
    OutDI();
    ~OutDI();

    enum Out_Type { Out_Text = 0, Out_Characters = 1 };
    void print_vmregister_information(long _register);

    void print_vmregister_information(RegisterStore & store);
    //void out_information(RegisterStore & store)
    void set_begin_text(char * _text);
    void set_end_text(char * _text);
    private:
    char * _begin_text;
    char * _end_text;
    int default_out_type;
};


#endif /* end of include guard: OUTDETAILEDINFORMATION_HPP_D54GBQU3 */
