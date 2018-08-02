#pragma once
#include <QWidget>

class HXWinWrap : public QWidget {
	Q_OBJECT

public:
	HXWinWrap(QWidget * parent = Q_NULLPTR);
	~HXWinWrap();

	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	//bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
	bool m_bPressed;
	QPoint m_point;

	//int m_nBorder;
};
