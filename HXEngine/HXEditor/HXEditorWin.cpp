#include "HXEditorWin.h"
#include "GameWidget.h"

HXEditorWin::HXEditorWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pGameWidget = new GameWidget();
	m_pCentralLayout = new QVBoxLayout();
	m_pCentralLayout->addWidget(m_pGameWidget);
	ui.centralWidget->setLayout(m_pCentralLayout);
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
