#ifndef WPROTECT_USE_QT
#define WPROTECT_USE_QT
#endif

#ifndef WPROTECTGUI_H
#define WPROTECTGUI_H   

#include <QWidget>
#include <QMap>
#include <logfunctions.h>
//#include "ui_WProtectDialog.h"
namespace Ui{
    class WProtectDialog;
}

class QMessageBox;

class WProtectGui : public QWidget , public logfunctions
{
    Q_OBJECT
    public:
        explicit WProtectGui(QWidget * parent = 0);
        ~WProtectGui();
    private slots:
        void  on_pushButton_openFile_clicked();
        void  on_pushButton_protect_clicked();

        void on_listWidget_logOut_doubleClicked(const QModelIndex &index);

        void on_pushButton_addProtectAddress_clicked();

        void on_pushButton_about_clicked();

    private:
        Ui::WProtectDialog * ui;
        QMap<long,long>user_protect_address;
};
 
#endif /* end of include guard: WPROTECTGUI_H */
