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
#include "HXGLCamera.h"
#include "QPushButton.h"

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
	void SetAmbientInfo(HXCOLOR* pAmbient);
	void SetCameraInfo(HXICamera* pCamera);

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

	// ambient
	QSpinBox* spinboxAmbientColorR;
	QSpinBox* spinboxAmbientColorG;
	QSpinBox* spinboxAmbientColorB;

	// camera
	QDoubleSpinBox* spinboxCameraNear;
	QDoubleSpinBox* spinboxCameraFar;
	QPushButton* pushbuttonCameraTransSync;
	QDoubleSpinBox* spinboxCameraPositionX;
	QDoubleSpinBox* spinboxCameraPositionY;
	QDoubleSpinBox* spinboxCameraPositionZ;
	QDoubleSpinBox* spinboxCameraRotationX;
	QDoubleSpinBox* spinboxCameraRotationY;
	QDoubleSpinBox* spinboxCameraRotationZ;

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
	HXCOLOR* ambient;
	HXGLCamera* camera;

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

	void AmbientColorRChanged(int value);
	void AmbientColorGChanged(int value);
	void AmbientColorBChanged(int value);

	void CameraNearChanged(double value);
	void CameraFarChanged(double value);

	void TransSyncOnClick();

	void CameraPositionXValueChanged(double value);
	void CameraPositionYValueChanged(double value);
	void CameraPositionZValueChanged(double value);

	void CameraRotationXValueChanged(double value);
	void CameraRotationYValueChanged(double value);
	void CameraRotationZValueChanged(double value);
};
