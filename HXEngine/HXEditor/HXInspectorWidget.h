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
	void SetGameObjectName();
	void SetGameObjectTransform();

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

	HXGameObject* selectedGameObject;

	void GameObjectNameChanged(const QString& name);
	public Q_SLOTS:
	void PositionXValueChanged(double value);
	void PositionYValueChanged(double value);
	void PositionZValueChanged(double value);

	void RotationXValueChanged(double value);
	void RotationYValueChanged(double value);
	void RotationZValueChanged(double value);

	void ScaleXValueChanged(double value);
	void ScaleYValueChanged(double value);
	void ScaleZValueChanged(double value);
};
