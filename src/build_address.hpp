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
    const char * build_exec_name;
    std::list<build_piece> list_build_exec_info;
  public:
    BuildCodeInfo()
    {
    }
    BuildCodeInfo(const char * _filename)
    {
        build_exec_name = _filename;
    }
    ~BuildCodeInfo()
    {}
    void set_filename(const char * _filename)
    {
      build_exec_name = _filename;
    }
    typedef std::list<build_piece>::iterator iterator;
    typedef build_piece data_type;
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
    const char * get_filename()
    {
      return build_exec_name;
    }
};






//#define build_code_info build_mov_test
//char * build_exec_name = ;
//long build_exec_addr =  0x401008;
//long build_exec_size = 5;

 #endif /* end of include guard: BUILD_INFO_HPP */     
