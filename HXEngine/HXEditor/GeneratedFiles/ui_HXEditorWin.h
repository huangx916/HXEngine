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
    QAction *actionLoadScene;
    QAction *actionLoadGameObject;
    QAction *actionSaveScene;
    QAction *actionDeleteGameObject;
    QAction *actionExportGameObject;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuGameObject;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HXEditorWinClass)
    {
        if (HXEditorWinClass->objectName().isEmpty())
            HXEditorWinClass->setObjectName(QStringLiteral("HXEditorWinClass"));
        HXEditorWinClass->resize(1000, 600);
        actionLoadScene = new QAction(HXEditorWinClass);
        actionLoadScene->setObjectName(QStringLiteral("actionLoadScene"));
        actionLoadGameObject = new QAction(HXEditorWinClass);
        actionLoadGameObject->setObjectName(QStringLiteral("actionLoadGameObject"));
        actionSaveScene = new QAction(HXEditorWinClass);
        actionSaveScene->setObjectName(QStringLiteral("actionSaveScene"));
        actionDeleteGameObject = new QAction(HXEditorWinClass);
        actionDeleteGameObject->setObjectName(QStringLiteral("actionDeleteGameObject"));
        actionExportGameObject = new QAction(HXEditorWinClass);
        actionExportGameObject->setObjectName(QStringLiteral("actionExportGameObject"));
        centralWidget = new QWidget(HXEditorWinClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        HXEditorWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HXEditorWinClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuGameObject = new QMenu(menuBar);
        menuGameObject->setObjectName(QStringLiteral("menuGameObject"));
        HXEditorWinClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HXEditorWinClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HXEditorWinClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HXEditorWinClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HXEditorWinClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuGameObject->menuAction());
        menuFile->addAction(actionLoadScene);
        menuFile->addAction(actionSaveScene);
        menuGameObject->addAction(actionLoadGameObject);
        menuGameObject->addAction(actionDeleteGameObject);
        menuGameObject->addSeparator();
        menuGameObject->addAction(actionExportGameObject);

        retranslateUi(HXEditorWinClass);

        QMetaObject::connectSlotsByName(HXEditorWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *HXEditorWinClass)
    {
        HXEditorWinClass->setWindowTitle(QApplication::translate("HXEditorWinClass", "HXEditorWin", nullptr));
        actionLoadScene->setText(QApplication::translate("HXEditorWinClass", "Load...", nullptr));
        actionLoadGameObject->setText(QApplication::translate("HXEditorWinClass", "Create...", nullptr));
        actionSaveScene->setText(QApplication::translate("HXEditorWinClass", "Save as...", nullptr));
        actionDeleteGameObject->setText(QApplication::translate("HXEditorWinClass", "Delete...", nullptr));
        actionExportGameObject->setText(QApplication::translate("HXEditorWinClass", "Export...", nullptr));
        menuFile->setTitle(QApplication::translate("HXEditorWinClass", "Scene", nullptr));
        menuGameObject->setTitle(QApplication::translate("HXEditorWinClass", "GameObject", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HXEditorWinClass: public Ui_HXEditorWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HXEDITORWIN_H
