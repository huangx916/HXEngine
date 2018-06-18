#include "HXEditorWin.h"
#include "HXGameWidget.h"
#include "HXHierarchyWidget.h"
#include "HXInspectorWidget.h"
#include <QFileDialog.h>
#include <QMessageBox.h>

HXEditorWin* HXEditorWin::m_pInstance = NULL;
HXEditorWin::HXEditorWin(QWidget *parent)
	: QMainWindow(parent)
	, m_pMainLayout(NULL)
	, m_pGameWidget(NULL)
	, m_pHierarchyWidget(NULL)
	, m_pInspectorWidget(NULL)
{
	ui.setupUi(this);
	m_pGameWidget = new HXGameWidget();
	m_pHierarchyWidget = new HXHierarchyWidget(HXEditorWin::updateInspector);
	m_pInspectorWidget = new HXInspectorWidget();

	m_pMainLayout = new QHBoxLayout();
	m_pMainLayout->addWidget(m_pHierarchyWidget,2);
	m_pMainLayout->addWidget(m_pInspectorWidget, 2);
	m_pMainLayout->addWidget(m_pGameWidget,6);
	ui.centralWidget->setLayout(m_pMainLayout);

	connect(ui.actionLoadScene, &QAction::triggered, this, &HXEditorWin::loadScene);
	connect(ui.actionLoadGameObject, &QAction::triggered, this, &HXEditorWin::loadGameObject);
}

HXEditorWin::~HXEditorWin()
{
	if (m_pMainLayout)
	{
		delete m_pMainLayout;
		m_pMainLayout = NULL;
	}
	if (m_pGameWidget)
	{
		delete m_pGameWidget;
		m_pGameWidget = NULL;
	}
	if (m_pHierarchyWidget)
	{
		delete m_pHierarchyWidget;
		m_pHierarchyWidget = NULL;
	}
	if (m_pInspectorWidget)
	{
		delete m_pInspectorWidget;
		m_pInspectorWidget = NULL;
	}
}

HXEditorWin* HXEditorWin::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new HXEditorWin();
	}
	return m_pInstance;
}

void HXEditorWin::loadScene()
{
	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.scene)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		//QTextStream in(&file);
		//textEdit->setText(in.readAll());
		setWindowTitle(path);
		m_pGameWidget->LoadScene(path, HXEditorWin::updateHierarchy);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void HXEditorWin::loadGameObject()
{
	QString scene = m_pGameWidget->GetCurScene();
	if (scene.isEmpty())
	{
		QMessageBox::warning(this, tr("Read File"),
			tr("Please load or new a scene first"));
		return;
	}

	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.prefab)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		//QTextStream in(&file);
		//textEdit->setText(in.readAll());
		m_pGameWidget->LoadGameObject(path);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void HXEditorWin::updateHierarchy()
{
	HXEditorWin::GetInstance()->m_pHierarchyWidget->UpdateGameObjectTree();
}

void HXEditorWin::updateInspector(HX3D::HXGameObject* gameObject)
{
	HXEditorWin::GetInstance()->m_pInspectorWidget->SetGameObjectInfo(gameObject);
}