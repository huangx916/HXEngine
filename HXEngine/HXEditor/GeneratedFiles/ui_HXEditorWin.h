/********************************************************************************
** Form generated from reading UI file 'HXEditorWin.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HXEDITORWIN_H
#define UI_HXEDITORWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HXEditorWinClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpinBox *spinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QDoubleSpinBox *doubleSpinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HXEditorWinClass)
    {
        if (HXEditorWinClass->objectName().isEmpty())
            HXEditorWinClass->setObjectName(QStringLiteral("HXEditorWinClass"));
        HXEditorWinClass->resize(600, 400);
        centralWidget = new QWidget(HXEditorWinClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 160, 321));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        spinBox = new QSpinBox(verticalLayoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        verticalLayout->addWidget(spinBox);

        doubleSpinBox_2 = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        verticalLayout->addWidget(doubleSpinBox_2);

        doubleSpinBox = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        verticalLayout->addWidget(doubleSpinBox);

        HXEditorWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HXEditorWinClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        HXEditorWinClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HXEditorWinClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HXEditorWinClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HXEditorWinClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HXEditorWinClass->setStatusBar(statusBar);

        retranslateUi(HXEditorWinClass);

        QMetaObject::connectSlotsByName(HXEditorWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *HXEditorWinClass)
    {
        HXEditorWinClass->setWindowTitle(QApplication::translate("HXEditorWinClass", "HXEditorWin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HXEditorWinClass: public Ui_HXEditorWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HXEDITORWIN_H
