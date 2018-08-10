#pragma once
#include<QWidget>
#include "HXGameObject.h"
#include "HXLight.h"
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
	void SetLightInfo(HXLight* pLight);
	void SetFogInfo(HXFogBase* pFog);
	void SetAmbientInfo(HXCOLOR* pAmbient);
	void SetCameraInfo(HXICamera* pCamera);

	void OnDeleteGameObject();
	void OnDeleteLight();

	// data
	HXGameObject* selectedGameObject;
	HXLight* selectedLight;
	HXGLCamera* selectedCamera;
	HXFogBase* fogData;
	HXCOLOR* ambientData;

private:

	// fog
	QTreeWidgetItem *fog;
	QCheckBox* checkboxFog;
	QComboBox* comboboxFogType;
	QSpinBox* spinboxFogColorR;
	QSpinBox* spinboxFogColorG;
	QSpinBox* spinboxFogColorB;
	QDoubleSpinBox* spinboxFogStart;
	QDoubleSpinBox* spinboxFogEnd;

	// ambient
	QTreeWidgetItem *ambient;
	QSpinBox* spinboxAmbientColorR;
	QSpinBox* spinboxAmbientColorG;
	QSpinBox* spinboxAmbientColorB;

	// camera
	QTreeWidgetItem *camera;
	QLineEdit* editCameraName;
	QCheckBox* checkboxCamera;
	QComboBox* comboboxClearFlag;
	QSpinBox* spinboxBGColorR;
	QSpinBox* spinboxBGColorG;
	QSpinBox* spinboxBGColorB;
	QDoubleSpinBox* spinboxCameraNear;
	QDoubleSpinBox* spinboxCameraFar;
	QComboBox* comboboxCullingMask;
	QComboBox* comboboxProjection;
	QSpinBox* spinboxDepth;
	QPushButton* pushbuttonCameraTransSync;
	QDoubleSpinBox* spinboxCameraPositionX;
	QDoubleSpinBox* spinboxCameraPositionY;
	QDoubleSpinBox* spinboxCameraPositionZ;
	QDoubleSpinBox* spinboxCameraRotationX;
	QDoubleSpinBox* spinboxCameraRotationY;
	QDoubleSpinBox* spinboxCameraRotationZ;

	// gameobject
	QTreeWidgetItem *gameobject;
	QCheckBox* checkboxActivity;
	QCheckBox* checkboxStatic;
	QLineEdit* editGameObjectName;
	QCheckBox* checkboxCastShadow;
	QComboBox* comboboxLayer;
	QDoubleSpinBox* spinboxPositionX;
	QDoubleSpinBox* spinboxPositionY;
	QDoubleSpinBox* spinboxPositionZ;
	QDoubleSpinBox* spinboxRotationX;
	QDoubleSpinBox* spinboxRotationY;
	QDoubleSpinBox* spinboxRotationZ;
	QDoubleSpinBox* spinboxScaleX;
	QDoubleSpinBox* spinboxScaleY;
	QDoubleSpinBox* spinboxScaleZ;

	// light
	QTreeWidgetItem *light;
	QLineEdit* editLightName;
	QCheckBox* checkboxLight;
	QComboBox* comboboxLightType;
	QDoubleSpinBox* spinboxShininess;
	QDoubleSpinBox* spinboxStrength;
	QDoubleSpinBox* spinboxConstantAttenuation;
	QDoubleSpinBox* spinboxLinearAttenuation;
	QDoubleSpinBox* spinboxQuadraticAttenuation;
	QDoubleSpinBox* spinboxSpotCosCutoff;
	QDoubleSpinBox* spinboxSpotExponent;
	QSpinBox* spinboxLightColorR;
	QSpinBox* spinboxLightColorG;
	QSpinBox* spinboxLightColorB;
	QDoubleSpinBox* spinboxLightPositionX;
	QDoubleSpinBox* spinboxLightPositionY;
	QDoubleSpinBox* spinboxLightPositionZ;
	QDoubleSpinBox* spinboxLightDirectionX;
	QDoubleSpinBox* spinboxLightDirectionY;
	QDoubleSpinBox* spinboxLightDirectionZ;
	QDoubleSpinBox* spinboxConeDirX;
	QDoubleSpinBox* spinboxConeDirY;
	QDoubleSpinBox* spinboxConeDirZ;

	void GameObjectNameChanged(const QString& name);
	void LightNameChanged(const QString& name);
	void CameraNameChanged(const QString& name);
	public Q_SLOTS:
	// gameobject
	void ActivityToggled(bool activity);
	void StaticToggled(bool bStatic);
	void CastShadowToggled(bool castShadow);
	void LayerActivated(int index);

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

	void CameraToggled(bool useCamera);
	void CameraNearChanged(double value);
	void CameraFarChanged(double value);

	void ClearFlagActivated(int index);

	void BGColorRChanged(int value);
	void BGColorGChanged(int value);
	void BGColorBChanged(int value);

	void CullingMaskActivated(int index);

	void ProjectionActivated(int index);

	void DepthChanged(int value);

	void TransSyncOnClick();

	void CameraPositionXValueChanged(double value);
	void CameraPositionYValueChanged(double value);
	void CameraPositionZValueChanged(double value);

	void CameraRotationXValueChanged(double value);
	void CameraRotationYValueChanged(double value);
	void CameraRotationZValueChanged(double value);


	void LightToggled(bool useLight);
	void LightTypeActivated(int index);
	void ShininessValueChanged(double value);
	void StrengthValueChanged(double value);
	void ConstantAttenuationValueChanged(double value);
	void LinearAttenuationValueChanged(double value);
	void QuadraticAttenuationValueChanged(double value);
	void SpotCosCutoffValueChanged(double value);
	void SpotExponentValueChanged(double value);
	void LightColorRChanged(int value);
	void LightColorGChanged(int value);
	void LightColorBChanged(int value);
	void LightPositionXValueChanged(double value);
	void LightPositionYValueChanged(double value);
	void LightPositionZValueChanged(double value);
	void LightDirectionXValueChanged(double value);
	void LightDirectionYValueChanged(double value);
	void LightDirectionZValueChanged(double value);
	void ConeDirXValueChanged(double value);
	void ConeDirYValueChanged(double value);
	void ConeDirZValueChanged(double value);
};
