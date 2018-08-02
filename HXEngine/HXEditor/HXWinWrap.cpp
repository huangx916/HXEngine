#include "HXWinWrap.h"
#include "title_bar.h"
#include "HXEditorWin.h"
#include <QIcon>
#include <QBoxLayout>
#include <QMouseEvent>
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif

HXWinWrap::HXWinWrap(QWidget * parent) : QWidget(parent)
, m_bPressed(false)
//, m_nBorder(5)
{
	setWindowFlags(Qt::FramelessWindowHint | windowFlags());
	//setAttribute(Qt::WA_TranslucentBackground, true);

	TitleBar *pTitleBar = new TitleBar(this);
	installEventFilter(pTitleBar);

	resize(1000, 600);
	setWindowTitle("HXEngine Editor");
	setWindowIcon(QIcon(":/icon"));

	/*QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(50, 50, 50));
	setAutoFillBackground(true);
	setPalette(pal);*/

	QVBoxLayout *pLayout = new QVBoxLayout();
	pLayout->addWidget(pTitleBar,0);
	//pLayout->setSpacing(0);
	pLayout->addWidget(HXEditorWin::GetInstance(),10);
	//pLayout->addStretch();
	//pLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(pLayout);
}

HXWinWrap::~HXWinWrap() 
{
	
}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void HXWinWrap::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bPressed = true;
		m_point = event->pos();
	}
}

// 若鼠标左键被按下，移动窗体位置
void HXWinWrap::mouseMoveEvent(QMouseEvent *event)
{
	if (m_bPressed)
		move(event->pos() - m_point + pos());
}

// 设置鼠标未被按下
void HXWinWrap::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

	m_bPressed = false;
}

//bool HXWinWrap::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//	Q_UNUSED(eventType)
//
//		MSG *param = static_cast<MSG *>(message);
//
//	switch (param->message)
//	{
//	case WM_NCHITTEST:
//	{
//		int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
//		int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();
//
//		// 如果鼠标位于子控件上，则不进行处理
//		if (childAt(nX, nY) != NULL)
//			return QWidget::nativeEvent(eventType, message, result);
//
//		*result = HTCAPTION;
//
//		// 鼠标区域位于窗体边框，进行缩放
//		if ((nX > 0) && (nX < m_nBorder))
//			*result = HTLEFT;
//
//		if ((nX > this->width() - m_nBorder) && (nX < this->width()))
//			*result = HTRIGHT;
//
//		if ((nY > 0) && (nY < m_nBorder))
//			*result = HTTOP;
//
//		if ((nY > this->height() - m_nBorder) && (nY < this->height()))
//			*result = HTBOTTOM;
//
//		if ((nX > 0) && (nX < m_nBorder) && (nY > 0)
//			&& (nY < m_nBorder))
//			*result = HTTOPLEFT;
//
//		if ((nX > this->width() - m_nBorder) && (nX < this->width())
//			&& (nY > 0) && (nY < m_nBorder))
//			*result = HTTOPRIGHT;
//
//		if ((nX > 0) && (nX < m_nBorder)
//			&& (nY > this->height() - m_nBorder) && (nY < this->height()))
//			*result = HTBOTTOMLEFT;
//
//		if ((nX > this->width() - m_nBorder) && (nX < this->width())
//			&& (nY > this->height() - m_nBorder) && (nY < this->height()))
//			*result = HTBOTTOMRIGHT;
//
//		return true;
//	}
//	}
//
//	return QWidget::nativeEvent(eventType, message, result);
//}