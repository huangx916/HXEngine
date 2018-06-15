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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HXEditorWinClass
{
public:
    QAction *actionOpenScene;
    QWidget *centralWidget;
    QWidget *gameWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HXEditorWinClass)
    {
        if (HXEditorWinClass->objectName().isEmpty())
            HXEditorWinClass->setObjectName(QStringLiteral("HXEditorWinClass"));
        HXEditorWinClass->resize(600, 400);
        actionOpenScene = new QAction(HXEditorWinClass);
        actionOpenScene->setObjectName(QStringLiteral("actionOpenScene"));
        centralWidget = new QWidget(HXEditorWinClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gameWidget = new QWidget(centralWidget);
        gameWidget->setObjectName(QStringLiteral("gameWidget"));
        gameWidget->setGeometry(QRect(180, 0, 411, 341));
        HXEditorWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HXEditorWinClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        HXEditorWinClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HXEditorWinClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HXEditorWinClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HXEditorWinClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HXEditorWinClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenScene);

        retranslateUi(HXEditorWinClass);

        QMetaObject::connectSlotsByName(HXEditorWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *HXEditorWinClass)
    {
        HXEditorWinClass->setWindowTitle(QApplication::translate("HXEditorWinClass", "HXEditorWin", nullptr));
        actionOpenScene->setText(QApplication::translate("HXEditorWinClass", "OpenScene", nullptr));
        menuFile->setTitle(QApplication::translate("HXEditorWinClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HXEditorWinClass: public Ui_HXEditorWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HXEDITORWIN_H
