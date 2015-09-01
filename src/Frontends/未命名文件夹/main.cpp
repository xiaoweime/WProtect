#include "mainwindow.h"
#include <QApplication>

//#include <WProtect.h>
#ifndef WPROTECT_CONFIG_H
#define WPROTECT_CONFIG_H
#include <WProtectConfig.h>
#endif



//#ifndef UDIS86_H
//#define UDIS86_H
#include <udis86.h>
//#endif
//#include <udis86.h>

#include <OutOfOrder.h>
// This is type of functionwe will generate
typedef int (*MyFn)();

#include <PEFile.h>

#ifndef LUA_H
#define LUA_H
extern "C"{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
