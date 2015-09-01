#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QMessageBox>
#include <QModelIndex>
#include <QFileDialog>
#include <QDialog>


#include <WProtect/Protect/EquivalentReplacement/LuaEquivalentReplacement.h>
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

//#include <AsmJit.h>

#include <PESection.h>
#ifndef LUA_H
#define LUA_H
extern "C"{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#endif


void MainWindow::Protect(char *file_name)
{

    CPESection test;
    if (!test.LoadPEFile(file_name))
		{
			fprintf(stdout,"file not found.");
			return;
		}
	if (test.IsPEFile())
	{
		//fprintf(stdout,"the is pe");
		unsigned char * asmbuf = new unsigned char [0xFFF];
		unsigned long asmsize = 0;
		unsigned long asmmaxsize = 0;
		unsigned long newsectionbase = test.GetNewSectionBase();
		QStringList strList;

        for (int i = 0; i < listcount ; i++)
        {
			
              QStandardItem *item = listmodel->takeItem(i);
              QString strAddr = item->text();
              item = listmodel->takeItem(i,1);
              QString strSize = item->text();

			  strList.push_back(strAddr);
			  strList.push_back(strSize);

			  
			  CodeInformation info;
			  info.size = strtoul(qPrintable(strSize),NULL,16);
			  info.base = strtoul(qPrintable(strAddr),NULL,16);
			  
			  info.buf = (unsigned char*)test.VaToPtr(info.base );
			 // info.size = 4;
			  info.base = info.base ;
			  OutOfOrder code;
			  LuaInterface lua;
			  info = *lua.lua_equivalent_replacement(&info,newsectionbase + asmsize);

			  if (asmsize + info.size >= asmmaxsize)
			  {
				  unsigned char * newasmbuf = new unsigned char [asmmaxsize+0xFFF];
				  memcpy(newasmbuf,asmbuf,asmsize);
				  delete [] asmbuf;
				  asmbuf = newasmbuf;
			  }
			  memcpy(&asmbuf[asmsize],info.buf,info.size);
			  asmsize += info.size;
			  
        }
		//reloc_jcc_addr();
		listmodel->removeRows(0,listmodel->rowCount());
		listcount = 0;
		int strlistcount = strList.count();
		for (int i=0;i<strlistcount;i+=2)
		{
			listmodel->setItem(listcount,0,new QStandardItem(strList.first()));
			strList.pop_front();
			listmodel->setItem(listcount++,1,new QStandardItem(strList.first()));
			strList.pop_front();
		}

		//FILE *pFile = fopen("testcode","wb");
		//if (pFile)
		//{
		//	fwrite(asmbuf,asmsize,1,pFile);
		//	fclose(pFile);
		//}

		//delete [] asmbuf;

		CodeInformation info;
		info.buf = asmbuf;//(unsigned char*)test.VaToPtr(0x401000);
		info.size = asmsize;
		info.base = newsectionbase;
		OutOfOrder code;
		info = *code.code_out_of_order(&info,newsectionbase);
		unsigned long add_section_size = info.size;



		for (int i = 0; i < listcount ; i++)
		{

			QStandardItem *item = listmodel->takeItem(i);
			QString strAddr = item->text();
			item = listmodel->takeItem(i,1);
			QString strSize = item->text();

			strList.push_back(strAddr);
			strList.push_back(strSize);

			int usercodesize = strtoul(qPrintable(strSize),NULL,16);
			int usercodebase = strtoul(qPrintable(strAddr),NULL,16);
			unsigned char* usercodebuf;
			usercodebuf = (unsigned char*)test.VaToPtr(usercodebase );
			for (int j = 0; j < usercodesize; j++)
			{
				*usercodebuf++ = rand()%0xff;
			}
			usercodebuf = (unsigned char*)test.VaToPtr(usercodebase );
			*usercodebuf = 0xE9;
			unsigned long old_addr;// = get_old_addr(usercodebase);
			*(unsigned long*)(usercodebuf + 1) = code.get_old_addr_to_new_addr(old_addr) - usercodebase - 5;
		} 

		listmodel->removeRows(0,listmodel->rowCount());
		listcount = 0;
		strlistcount = strList.count();
		for (int i=0;i<strlistcount;i+=2)
		{
			listmodel->setItem(listcount,0,new QStandardItem(strList.first()));
			strList.pop_front();
			listmodel->setItem(listcount++,1,new QStandardItem(strList.first()));
			strList.pop_front();
		}
		//clean_addr_table();

		test.AddSection("WProtect",add_section_size,0x20000000|0x40000000|0x80000000);//代码可读可写可执行
		test.WriteSectionData(test.GetSectionCount()-1,0,info.buf,&info.size);
		test.SavePEFile("test.wp.exe");
		*strrchr(file_name,'.') = '\0';
		char save_file_name[256];
		strcat(save_file_name,file_name);
		sprintf(save_file_name,"%s.wp.exe",file_name);
		delete [] asmbuf;
		//FILE*pFile = fopen("testcode","wb");
		//if (pFile)
		//{
		//	fwrite(info.buf,info.size,1,pFile);
		//	fclose(pFile);
		//}

		//CodeInformation info;
		//info.buf = (unsigned char*)test.VaToPtr(0x401000);
		//info.size = 4;
		//info.base = 0x401000;
		//OutOfOrder code;
		//info = *lua_equivalent_replacement(&info,0x401000);
		//FILE *pFile = fopen("testcode","wb");
		//if (pFile)
		//{
		//	fwrite(info.buf,info.size,1,pFile);
		//	fclose(pFile);
		//}
	}
	else
		fprintf(stdout,"the not pe");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    listmodel = new QStandardItemModel();
    listmodel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("Address")));
    listmodel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("Size")));
    ui->ProtectTableView->setModel(listmodel);
    ui->ProtectTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    listcount = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete listmodel;
}

void MainWindow::on_AddAddressButton_clicked()
{
    QString strAddr = ui->AddrEdit->text();
    QString strSize = ui->SizeEdit->text();
    //int addr = strAddr.toInt();
    //int size = strSize.toInt();
    //QStringList user;
    //user += strAddr;
   // user += strSize;
    //QStringListModel *model =  new QStringListModel(user);
    //ui->ProtectView->setModel(model);
   // QAbstractItemModel model = new QAbstractItemModel(,)
    int addr = strAddr.toInt();
    int size = strSize.toInt();
    if (addr != 0 && size != 0 )
    {
        listmodel->setItem(listcount,0,new QStandardItem(strAddr));
        listmodel->setItem(listcount++,1,new QStandardItem(strSize));

    }
    else
    {
        QMessageBox * msgbox = new QMessageBox;
        msgbox->setWindowTitle("error");
        msgbox->setText("Please enter a number");
        msgbox->exec();
        delete msgbox;
    }
}

void MainWindow::on_ProtectButton_clicked()
{
 /*   for (int i = 0; i < listcount ; i++)
    {
        QStandardItem *item = listmodel->takeItem(i);
        QString strAddr = item->text();
        item = listmodel->takeItem(i,1);
        QString strSize = item->text();
    }
    listmodel->removeRows(0,listcount);
    //listmodel->deleteLater();
    listcount = 0;*/
    Protect(ui->PatchEdit->text().toLatin1().data());
}

void MainWindow::on_pushButton_clicked()
{
    QModelIndex index = ui->ProtectTableView->currentIndex();
    listmodel->removeRow(index.row());
    listcount -- ;
}

void MainWindow::on_OpenFileButton_clicked()
{
    QFileDialog *fd = new QFileDialog(this);
    fd->resize(1000,500);
    //fd->setFilter("AllFile(*.*)");
    fd->setViewMode(QFileDialog::List);
    if (fd->exec() == QDialog::Accepted)
    {
        QStringList fileNameList;
        fileNameList = fd->selectedFiles();
        QString filepath = fileNameList[0];
        ui->PatchEdit->setText(filepath);
    }
    fd->close();
    delete fd;
}
