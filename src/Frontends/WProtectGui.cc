#define WPROTECT_USE_QT

#include "../vm_protect.h" 
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemModel>
#include "ui_WProtectDialog.h"
#include "WProtectGui.h"
#include <list>

QListWidget * ptr_log_list;
QTreeWidget * ptr_protect_address_tree;


#define about_info "\
\
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
    ptr_log_list = ui->listWidget_logOut;
    ptr_protect_address_tree = ui->treeWidget_protectAddress;
    ui->treeWidget_protectAddress->setColumnCount(1);
    ui->treeWidget_protectAddress->setHeaderLabel(tr("Protect Address"));

    QMessageBox::about(this,"WProtect By XiaoWei",about_info);
}

WProtectGui::~WProtectGui()
{
    delete ui;
}

void  WProtectGui::on_pushButton_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("EXECUTABLE File(*.exe)"));
    if (fileName != "")
    {
    ui->lineEdit_filePath->setText(fileName);
    vm_protect vm;
    std::map<long,long> xxx = user_protect_address.toStdMap();
    vm.protect_address_disas(fileName.toStdString().c_str(),xxx);
    }
}

void  WProtectGui::on_pushButton_protect_clicked()
{
    if (ui->lineEdit_beginAddress->text() == "")
    {
        QMessageBox::warning(this,"警告","请选择一个要保护的文件");
        return;
    }
    ui->listWidget_logOut->clear();
    vm_protect vm;
    QString fileName = ui->lineEdit_filePath->text();
        std::map<long,long> xxx = user_protect_address.toStdMap();
    vm.protect_code(fileName.toStdString().c_str(),xxx);
    //QMessageBox::information(this,tr("fuck"),tr("build"));
    //QMessageBox::information()
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
        QMessageBox::warning(this,"警告","请输入正确地址");
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
