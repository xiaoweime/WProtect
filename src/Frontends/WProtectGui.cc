#ifndef WPROTECT_USE_QT
#define WPROTECT_USE_QT
#endif

#include "../vm_protect.h" 
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QSettings>
#include <QTextCodec>
#include "ui_WProtectDialog.h"
#include "WProtectGui.h"
#include <list>
#include <fstream>

QListWidget * ptr_log_list;
QTreeWidget * ptr_protect_address_tree;


#define about_info "\
\
<font color=\"blue\">&#160;&#160;&#160;&#160;ReVerSe EnGiNeeR TeAm[R.E.T]<br>\
&#160;&#160;Name              -=TeaM RET Members=-        Comment <br>    \
<font color=\"red\">[ Kido....................<font color=\"red\">Founder/Admin ] <br>\
[ L4nce..................<font color=\"\">Unpacker/Coder ] <br>\
[ Rookietp...............<font color=\"\">Reverser/Coder ] <br>\
[ Sound...............<font color=\"\">Unpacker/Reverser ] <br>\
[ willj...........<font color=\"\">Vulnerability Digging ] <br>\
[ xiaoy.................<font color=\"\">Kernel Security ]<br>\
[ XiaoWei..............<font color=\"\">Reverser/Coder ]<br>\
[ yoza................<font color=\"\">Unpacker/Reverser ]<br>\
<font color=\"Gray\">Copyright &#169; 2001-2015 ReverseEngineer.Cn All Rights Reserved</font><br>\
<font color=\"Gray\"><a href=\"http://www.reverseengineer.cn/\" title=\"EnTer[R.E.T]Forum\"><b>FORUM</b></a> </font>\
\
"

WProtectGui::WProtectGui(QWidget * parent)
    :QWidget(parent),
    ui(new Ui::WProtectDialog)
{
    ui->setupUi(this);
#if defined(WIN32) || defined _WINDOWS_
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb2312"));
#endif

    ptr_log_list = ui->listWidget_logOut;
    ptr_protect_address_tree = ui->treeWidget_protectAddress;
    ui->treeWidget_protectAddress->setColumnCount(1);
    ui->treeWidget_protectAddress->setHeaderLabel(tr("保护地址"));

    QMessageBox::about(this,"WProtect By XiaoWei",about_info);
}

WProtectGui::~WProtectGui()
{
    delete ui;
}

void  WProtectGui::on_pushButton_openFile_clicked()
{
    ui->treeWidget_protectAddress->clear();
    ui->listWidget_logOut->clear();
    user_protect_address.clear();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("EXECUTABLE File(*.exe)"));

    if (fileName != "")
    {
        ui->lineEdit_filePath->setText(fileName);

        ifstream f;
        QString configFileName = fileName;
        configFileName.replace(tr(".exe"),tr(".wp"));
        f.open(configFileName.toStdString().c_str());
        if (f.is_open())
        {
            QMessageBox load_config_info(QMessageBox::Information,tr("配置文件"),tr("找到配置文件是否加载"),QMessageBox::Yes|QMessageBox::No,NULL) ;
            if (load_config_info.exec() != QMessageBox::No)
            {
                QSettings s(configFileName, QSettings::IniFormat);
                //s.setValue();
                info("load prject config file : %s",configFileName.toStdString().c_str());
                long key;
                long value;
                s.beginGroup("Procedure");
                QStringList key_list = s.allKeys();
                for(int i = 0; i < key_list.size(); ++i)
                {
                    QString str_key = key_list.at(i);
                    //warn("key : %s",str_key.toStdString().c_str());
                    key = str_key.toLong(NULL,16);
                    QString str_value = s.value(str_key).toString();
                    //warn("value : %s",str_value.toStdString().c_str());
                    value = str_value.toLong(NULL,16);
                    user_protect_address.insert(key,value);
                }
                s.endGroup();
            }
            f.close();
        }
        vm_protect vm;
        std::map<long,long> xxx = user_protect_address.toStdMap();
        vm.protect_address_disas(fileName.toStdString().c_str(),xxx);
    }
}

void  WProtectGui::on_pushButton_protect_clicked()
{
    if (ui->lineEdit_filePath->text() == "")
    {
        QMessageBox::warning(this,"Warning","Please Select One File TO Protect");
        return;
    }
    ui->listWidget_logOut->clear();
    vm_protect vm;
    QString fileName = ui->lineEdit_filePath->text();
    std::map<long,long> xxx = user_protect_address.toStdMap();
    vm.protect_code(fileName.toStdString().c_str(),xxx);
    if (user_protect_address.empty())
    {
        QMessageBox::information(this,tr("Protect Success"),tr("Protect Success, Check Log"));
        return;
    }
    QMessageBox save_config_info(QMessageBox::Information,tr("Protect Success"),tr("Protect Success, Do you want to save config files"),QMessageBox::Yes|QMessageBox::No,NULL);
    if (save_config_info.exec() == QMessageBox::Yes)
    {
        fileName.replace(tr(".exe"),tr(".wp"));
        QSettings *s = new QSettings(fileName,QSettings::IniFormat);
        s->beginGroup("Procedure");
        s->clear();
        for (QMap<long,long>::iterator iter = user_protect_address.begin();
             iter != user_protect_address.end();iter++)
        {
            s->setValue(QString::number(iter.key(),16).toStdString().c_str(), QString::number(iter.value(),16).toStdString().c_str());
        }
        s->endGroup();
        delete s;
    }
}


void WProtectGui::on_listWidget_logOut_doubleClicked(const QModelIndex &index)
{
    const QAbstractItemModel * model = index.model();
    QString text = model->data(index,Qt::DisplayRole).toString();
    QString title = text;

    title.remove(QRegExp(":.+"));
    text.remove(0,text.indexOf(":",0)+1);
    QMessageBox info_msg(QMessageBox::Information,title,text);
    info_msg.exec();
}

void WProtectGui::on_pushButton_addProtectAddress_clicked()
{
    QString beginAddress = ui->lineEdit_beginAddress->text();
    QString endAddress = ui->lineEdit_endAddress->text();
    if (beginAddress == "" || endAddress == "")
    {
        QMessageBox::warning(this,"Warning ","Please input correct address");
        return;
    }
    user_protect_address.insert(beginAddress.toLong(0,16),endAddress.toLong(0,16));
    vm_protect vm;
    std::map<long,long> xxx;
    xxx = user_protect_address.toStdMap();
    vm.protect_address_disas(ui->lineEdit_filePath->text().toStdString().c_str(),xxx);
}


void WProtectGui::on_pushButton_about_clicked()
{
    //QMessageBox::about(this,"WProtect","WProtect是一个虚拟机保护软件\n详情请关注 http://release.crack4r.cc/TeaM.RET.html");
    QMessageBox::about(this,"WProtect By XiaoWei",about_info);
}
