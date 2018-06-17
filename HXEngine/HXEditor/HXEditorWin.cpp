#include "HXEditorWin.h"
#include "GameWidget.h"
#include <QFileDialog.h>
#include <QMessageBox.h>

HXEditorWin::HXEditorWin(QWidget *parent)
	: QMainWindow(parent), m_pGameWidget(NULL), m_pGameLayout(NULL)
{
	ui.setupUi(this);
	m_pGameWidget = new GameWidget();
	m_pGameLayout = new QVBoxLayout();
	m_pGameLayout->setContentsMargins(QMargins(200, 0, 0, 0));
	m_pGameLayout->addWidget(m_pGameWidget);
	ui.centralWidget->setLayout(m_pGameLayout);

	connect(ui.actionLoadScene, &QAction::triggered, this, &HXEditorWin::loadScene);
	connect(ui.actionLoadGameObject, &QAction::triggered, this, &HXEditorWin::loadGameObject);
}

HXEditorWin::~HXEditorWin()
{
	if (m_pGameWidget)
	{
		delete m_pGameWidget;
		m_pGameWidget = NULL;
	}
	if (m_pGameLayout)
	{
		delete m_pGameLayout;
		m_pGameLayout = NULL;
	}
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
		m_pGameWidget->LoadScene(path);
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