#pragma once
#include<QWidget>
#include "HXGameObject.h"
#include "HXITransform.h"
#include <QSpinBox>

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
	void SetGameObjectTransform(HXITransform* pTransform);

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
