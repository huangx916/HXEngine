#pragma once
#include<QWidget>
#include "HXGameObject.h"
#include "HXITransform.h"
#include "HXFogBase.h"
#include <QSpinBox>
#include <QLineEdit.h>
#include <QCheckBox.h>
#include <QComboBox.h>
#include <QTreeWidget.h>

using namespace HX3D;
class HXInspectorWidget : public QTreeWidget
{
	Q_OBJECT

	const double MIN = -100000;
	const double MAX = 100000;
	const int COLOR_MIN = 0;
	const int COLOR_MAX = 255;
public:
	HXInspectorWidget(QWidget * parent = 0);
	~HXInspectorWidget();

	void SetGameObjectInfo(HXGameObject* pGameObject);
	void SetFogInfo(HXFogBase* pFog);

private:
	void SetGameObjectName();
	void SetGameObjectTransform();

	// fog
	QCheckBox* checkboxFog;
	QComboBox* comboboxFogType;

	QSpinBox* spinboxFogColorR;
	QSpinBox* spinboxFogColorG;
	QSpinBox* spinboxFogColorB;

	QDoubleSpinBox* spinboxFogStart;
	QDoubleSpinBox* spinboxFogEnd;

	// gameobject
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
	HXFogBase* fog;

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

	void FogToggled(bool useFog);
	void FogTypeActivated(int index);

	void FogColorRChanged(int value);
	void FogColorGChanged(int value);
	void FogColorBChanged(int value);

	void FogStartChanged(double value);
	void FogEndChanged(double value);
};
