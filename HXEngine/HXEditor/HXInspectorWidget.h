#pragma once
#include<QWidget>
#include "HXGameObject.h"
#include "HXITransform.h"
#include <QSpinBox>
#include <QLineEdit.h>

using namespace HX3D;
class HXInspectorWidget : public QWidget
{
	Q_OBJECT

	const double MAX = 100000;
	const double MIN = -100000;
public:
	HXInspectorWidget(QWidget * parent = 0);
	~HXInspectorWidget();

	void SetGameObjectInfo(HXGameObject* pGameObject);
	

private:
	void SetGameObjectName(QString name);
	void SetGameObjectTransform(HXITransform* pTransform);

	void GameObjectNameChanged(const QString& name);

	QLineEdit* editGameObjectName;
	QDoubleSpinBox* spinboxPositionX;
	QDoubleSpinBox* spinboxPositionY;
	QDoubleSpinBox* spinboxPositionZ;
	QDoubleSpinBox* spinboxRotationX;
	QDoubleSpinBox* spinboxRotationY;
	QDoubleSpinBox* spinboxRotationZ;
	QDoubleSpinBox* spinboxScaleX;
	QDoubleSpinBox* spinboxScaleY;
	QDoubleSpinBox* spinboxScaleZ;
};
