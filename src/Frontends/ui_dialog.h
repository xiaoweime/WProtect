/********************************************************************************
** Form generated from reading UI file 'untitled.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_fileName;
    QPushButton *pushButton_openFile;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_log;
    QListView *listView_log;
    QWidget *horizontalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_beginAddress;
    QLineEdit *lineEdit_beginAddress;
    QLabel *label_endAddress;
    QLineEdit *lineEdit_endAddress;
    QPushButton *pushButton_addAddress;
    QPushButton *pushButton_deleteAddress;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_protectAddress;
    QListView *listView_protectAddress;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1008, 699);
        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 20, 911, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_fileName = new QLineEdit(horizontalLayoutWidget);
        lineEdit_fileName->setObjectName(QStringLiteral("lineEdit_fileName"));

        horizontalLayout->addWidget(lineEdit_fileName);

        pushButton_openFile = new QPushButton(horizontalLayoutWidget);
        pushButton_openFile->setObjectName(QStringLiteral("pushButton_openFile"));

        horizontalLayout->addWidget(pushButton_openFile);

        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 470, 941, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_log = new QLabel(verticalLayoutWidget);
        label_log->setObjectName(QStringLiteral("label_log"));

        verticalLayout->addWidget(label_log);

        listView_log = new QListView(verticalLayoutWidget);
        listView_log->setObjectName(QStringLiteral("listView_log"));

        verticalLayout->addWidget(listView_log);

        horizontalLayoutWidget_2 = new QWidget(Dialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(800, 80, 148, 211));
        verticalLayout_2 = new QVBoxLayout(horizontalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_beginAddress = new QLabel(horizontalLayoutWidget_2);
        label_beginAddress->setObjectName(QStringLiteral("label_beginAddress"));

        verticalLayout_2->addWidget(label_beginAddress);

        lineEdit_beginAddress = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_beginAddress->setObjectName(QStringLiteral("lineEdit_beginAddress"));

        verticalLayout_2->addWidget(lineEdit_beginAddress);

        label_endAddress = new QLabel(horizontalLayoutWidget_2);
        label_endAddress->setObjectName(QStringLiteral("label_endAddress"));

        verticalLayout_2->addWidget(label_endAddress);

        lineEdit_endAddress = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_endAddress->setObjectName(QStringLiteral("lineEdit_endAddress"));

        verticalLayout_2->addWidget(lineEdit_endAddress);

        pushButton_addAddress = new QPushButton(horizontalLayoutWidget_2);
        pushButton_addAddress->setObjectName(QStringLiteral("pushButton_addAddress"));

        verticalLayout_2->addWidget(pushButton_addAddress);

        pushButton_deleteAddress = new QPushButton(horizontalLayoutWidget_2);
        pushButton_deleteAddress->setObjectName(QStringLiteral("pushButton_deleteAddress"));

        verticalLayout_2->addWidget(pushButton_deleteAddress);

        verticalLayoutWidget_2 = new QWidget(Dialog);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(540, 80, 241, 211));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_protectAddress = new QLabel(verticalLayoutWidget_2);
        label_protectAddress->setObjectName(QStringLiteral("label_protectAddress"));

        verticalLayout_3->addWidget(label_protectAddress);

        listView_protectAddress = new QListView(verticalLayoutWidget_2);
        listView_protectAddress->setObjectName(QStringLiteral("listView_protectAddress"));

        verticalLayout_3->addWidget(listView_protectAddress);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        pushButton_openFile->setText(QApplication::translate("Dialog", "\346\265\217\350\247\210\346\226\207\344\273\266", 0));
        label_log->setText(QApplication::translate("Dialog", "\346\227\245\345\277\227\350\276\223\345\207\272\357\274\232", 0));
        label_beginAddress->setText(QApplication::translate("Dialog", "\345\274\200\345\247\213\345\234\260\345\235\200\357\274\232", 0));
        label_endAddress->setText(QApplication::translate("Dialog", "\347\273\223\346\235\237\345\234\260\345\235\200\357\274\232", 0));
        pushButton_addAddress->setText(QApplication::translate("Dialog", "\346\267\273\345\212\240\345\234\260\345\235\200", 0));
        pushButton_deleteAddress->setText(QApplication::translate("Dialog", "\345\210\240\351\231\244\345\234\260\345\235\200", 0));
        label_protectAddress->setText(QApplication::translate("Dialog", "\350\246\201\344\277\235\346\212\244\347\232\204\345\234\260\345\235\200\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
