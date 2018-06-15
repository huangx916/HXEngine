#include "HXEditorWin.h"
#include "GameWidget.h"
#include <QFileDialog.h>
#include <QMessageBox.h>

HXEditorWin::HXEditorWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pGameWidget = new GameWidget();
	m_pCentralLayout = new QVBoxLayout();
	m_pCentralLayout->addWidget(m_pGameWidget);
	//ui.centralWidget->setLayout(m_pCentralLayout);
	ui.gameWidget->setLayout(m_pCentralLayout);

	connect(ui.actionOpenScene, &QAction::triggered, this, &HXEditorWin::openScene);
}

HXEditorWin::~HXEditorWin()
{
	if (m_pGameWidget)
	{
		delete m_pGameWidget;
		m_pGameWidget = NULL;
	}
	if (m_pCentralLayout)
	{
		delete m_pCentralLayout;
		m_pCentralLayout = NULL;
	}
}


void HXEditorWin::openScene()
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
		//ui.label->setText(path);
		//ui.label->adjustSize();
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}