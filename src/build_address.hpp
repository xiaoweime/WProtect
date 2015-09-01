#ifndef BUILD_INFO_HPP
#define BUILD_INFO_HPP




#include <iostream>
#include <list>

struct build_piece
{
  //char * build_exec_name;
  long build_exec_addr;
  long build_exec_size;
}; 

class BuildCodeInfo{
    char * build_exec_name;
    std::list<build_piece> list_build_exec_info;
  public:
    BuildCodeInfo(char * _filename)
    {
        build_exec_name = _filename;
    }
    ~BuildCodeInfo()
    {}
    typedef std::list<build_piece>::iterator iterator;
    iterator begin()
    {
        return list_build_exec_info.begin();
    }
    iterator end()
    {
        return list_build_exec_info.end();
    }
    void push_back(build_piece & _piece)
    {
      list_build_exec_info.push_back(_piece);
    }
    void for_each(void (*fuc)(iterator _iter))
    {
        for (iterator i = begin(); i != end();i++)
        {
            fuc(i);
        }
    }
    char * get_filename()
    {
      return build_exec_name;
    }
};






//#define build_code_info build_mov_test
//char * build_exec_name = ;
//long build_exec_addr =  0x401008;
//long build_exec_size = 5;

 #endif /* end of include guard: BUILD_INFO_HPP */     
