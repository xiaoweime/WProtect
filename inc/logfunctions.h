/****************************************************************************
 *
 * Author: XiaoWei - handsomexiaowei@gmail.com
 *
 * QQ:125896239
 *
 * Last modified:	2015-09-18 19:59
 *
 * Filename:		logfuctions.h
 *
 * Description:  
 *
 ****************************************************************************/
#ifndef LOGFUCTION_H
#define LOGFUCTION_H

#include <iostream>
#include <cstdio>
#include <cstdarg>
#ifdef WPROTECT_USE_QT
#include <QListWidget>
#include <QString>
#include <QMessageBox>
extern QListWidget * ptr_log_list;
#endif

typedef class logfunctions {
    char * prefix;
    public:
    logfunctions(void){}
    ~logfunctions(void){}
    void warn(const char *fmt,...) {
        std::va_list arglist;
        va_start(arglist,fmt);
#ifndef WPROTECT_USE_QT
        vfprintf(stdout,fmt,arglist);
#else
        char sz[256];
        vsprintf(sz,fmt,arglist);
        QString s;
        s = "warn:";
        s = s + sz;
        s.replace("\n","");
        ptr_log_list->addItem(s);
        QMessageBox warn_info(QMessageBox::Warning,"warn",s,QMessageBox::Yes|QMessageBox::No,NULL);
        if (warn_info.exec() == QMessageBox::No)
        {
            exit(0);
        }
#endif
        va_end(arglist);
    }

    void info(const char *fmt,...) {
        std::va_list arglist;
        va_start(arglist,fmt); 
#ifndef WPROTECT_USE_QT
        vfprintf(stdout,fmt,arglist);
#else 
        char sz[256];
        vsprintf(sz,fmt,arglist); 
        QString s;
        s = "info:";
        s = s + sz;
        s.replace("\n","");   
        ptr_log_list->addItem(s);
#endif
        va_end(arglist);    
    }
    void error(const char *fmt,...) {
        std::va_list arglist;
        va_start(arglist,fmt); 
#ifndef WPROTECT_USE_QT
        vfprintf(stdout,fmt,arglist);
#else
        char sz[256];
        vsprintf(sz,fmt,arglist); 
        QString s;
        s = "error:";
        s = s + sz;
        s.replace("\n","");
        ptr_log_list->addItem(s);
        QMessageBox err(QMessageBox::Critical,"error",s);
        err.exec();
#endif
        va_end(arglist);         
        exit(0);
    }
    void panic(const char *fmt,...) {
        std::va_list arglist;
        va_start(arglist,fmt);
#ifndef WPROTECT_USE_QT
        vfprintf(stdout,fmt,arglist);
#else
        char sz[256];
        vsprintf(sz,fmt,arglist);
        QString s;
        s = "panic:";
        s = s + sz;
        s.replace("\n","");
        ptr_log_list->addItem(s);
        QMessageBox err(QMessageBox::Critical,"panic",s);
        err.exec();
#endif
        va_end(arglist);            //exit(0);
        exit(0);
    }
    void pass(const char *fmt,...) {
        std::va_list arglist;
        va_start(arglist,fmt);
#ifndef WPROTECT_USE_QT
        vfprintf(stdout,fmt,arglist);
#else
        char sz[256];
        vsprintf(sz,fmt,arglist);
        QString s;
        s = "pass:";
        s = s + sz;
        ptr_log_list->addItem(s);
#endif
        va_end(arglist);
    }
    void ldebug(const char *fmt,...) {
        std::va_list arglist;
        va_start(arglist,fmt);
        vfprintf(stdout,fmt,arglist);
        va_end(arglist);      
    }
    void fatal(const char * prefix,const char *fmt,...) {

    }
}logfunc_t;

#endif /* end of include guard: LOGFUCTION_H */
