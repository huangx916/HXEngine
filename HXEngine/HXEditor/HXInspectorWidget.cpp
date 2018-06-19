#include "HXInspectorWidget.h"
#include <QLabel.h>
//#include <QSpinBox.h>
#include <QBoxLayout.h>
#include <QFormLayout>

HXInspectorWidget::HXInspectorWidget(QWidget* parent) : QWidget(parent), selectedGameObject(NULL)
{
	editGameObjectName = new QLineEdit();

	spinboxPositionX = new QDoubleSpinBox();
	spinboxPositionX->setRange(MIN, MAX);

	spinboxPositionY = new QDoubleSpinBox();
	spinboxPositionY->setRange(MIN, MAX);

	spinboxPositionZ = new QDoubleSpinBox();
	spinboxPositionZ->setRange(MIN, MAX);

	spinboxRotationX = new QDoubleSpinBox();
	spinboxRotationX->setRange(MIN, MAX);

	spinboxRotationY = new QDoubleSpinBox();
	spinboxRotationY->setRange(MIN, MAX);

	spinboxRotationZ = new QDoubleSpinBox();
	spinboxRotationZ->setRange(MIN, MAX);

	spinboxScaleX = new QDoubleSpinBox();
	spinboxScaleX->setRange(MIN, MAX);

	spinboxScaleY = new QDoubleSpinBox();
	spinboxScaleY->setRange(MIN, MAX);

	spinboxScaleZ = new QDoubleSpinBox();
	spinboxScaleZ->setRange(MIN, MAX);

	QFormLayout* inspectorLayout = new QFormLayout();
	QFont font("Microsoft YaHei", 10, 75);

	QLabel* gameobject = new QLabel(tr("GameObject"));
	gameobject->setFont(font);
	inspectorLayout->addRow(gameobject);
	inspectorLayout->addRow(editGameObjectName);

	inspectorLayout->addRow(new QLabel(tr("-----------------------------")));

	QLabel* transform = new QLabel(tr("Transform"));
	transform->setFont(font);
	inspectorLayout->addRow(transform);
	inspectorLayout->addRow(QStringLiteral("Position X"), spinboxPositionX);
	inspectorLayout->addRow(QStringLiteral("Position Y"), spinboxPositionY);
	inspectorLayout->addRow(QStringLiteral("Position Z"), spinboxPositionZ);
	inspectorLayout->addRow(new QLabel(tr("")));
	inspectorLayout->addRow(QStringLiteral("Rotation X"), spinboxRotationX);
	inspectorLayout->addRow(QStringLiteral("Rotation Y"), spinboxRotationY);
	inspectorLayout->addRow(QStringLiteral("Rotation Z"), spinboxRotationZ);
	inspectorLayout->addRow(new QLabel(tr("")));
	inspectorLayout->addRow(QStringLiteral("Scale X"), spinboxScaleX);
	inspectorLayout->addRow(QStringLiteral("Scale Y"), spinboxScaleY);
	inspectorLayout->addRow(QStringLiteral("Scale Z"), spinboxScaleZ);
	inspectorLayout->addRow(new QLabel(tr("-----------------------------")));

	setLayout(inspectorLayout);


	connect(editGameObjectName, &QLineEdit::textChanged, this, &HXInspectorWidget::GameObjectNameChanged);
	connect(spinboxPositionX, SIGNAL(valueChanged(double)), this, SLOT(PositionXValueChanged(double)));
	connect(spinboxPositionY, SIGNAL(valueChanged(double)), this, SLOT(PositionYValueChanged(double)));
	connect(spinboxPositionZ, SIGNAL(valueChanged(double)), this, SLOT(PositionZValueChanged(double)));

	connect(spinboxRotationX, SIGNAL(valueChanged(double)), this, SLOT(RotationXValueChanged(double)));
	connect(spinboxRotationY, SIGNAL(valueChanged(double)), this, SLOT(RotationYValueChanged(double)));
	connect(spinboxRotationZ, SIGNAL(valueChanged(double)), this, SLOT(RotationZValueChanged(double)));

	connect(spinboxScaleX, SIGNAL(valueChanged(double)), this, SLOT(ScaleXValueChanged(double)));
	connect(spinboxScaleY, SIGNAL(valueChanged(double)), this, SLOT(ScaleYValueChanged(double)));
	connect(spinboxScaleZ, SIGNAL(valueChanged(double)), this, SLOT(ScaleZValueChanged(double)));
}

HXInspectorWidget::~HXInspectorWidget()
{

}

void HXInspectorWidget::SetGameObjectInfo(HXGameObject* pGameObject)
{
	selectedGameObject = pGameObject;
	SetGameObjectName();
	SetGameObjectTransform();
}

void HXInspectorWidget::SetGameObjectName()
{
	if (selectedGameObject)
	{
		editGameObjectName->setText(selectedGameObject->GetName().c_str());
	}
	else
	{
		editGameObjectName->setText("");
	}
}

void HXInspectorWidget::SetGameObjectTransform()
{
	if (selectedGameObject && selectedGameObject->GetTransform())
	{
		HXITransform* pTransform = selectedGameObject->GetTransform();

		spinboxPositionX->setValue(pTransform->GetPosition().x);
		spinboxPositionY->setValue(pTransform->GetPosition().y);
		spinboxPositionZ->setValue(pTransform->GetPosition().z);

		spinboxRotationX->setValue(pTransform->GetRotation().x);
		spinboxRotationY->setValue(pTransform->GetRotation().y);
		spinboxRotationZ->setValue(pTransform->GetRotation().z);

		spinboxScaleX->setValue(pTransform->GetScale().x);
		spinboxScaleY->setValue(pTransform->GetScale().y);
		spinboxScaleZ->setValue(pTransform->GetScale().z);
	}
	else
	{
		spinboxPositionX->setValue(0);
		spinboxPositionY->setValue(0);
		spinboxPositionZ->setValue(0);

		spinboxRotationX->setValue(0);
		spinboxRotationY->setValue(0);
		spinboxRotationZ->setValue(0);

		spinboxScaleX->setValue(0);
		spinboxScaleY->setValue(0);
		spinboxScaleZ->setValue(0);
	}
}

void HXInspectorWidget::GameObjectNameChanged(const QString& name)
{
	if (selectedGameObject)
	{
		selectedGameObject->SetName(name.toStdString());
	}
}

void HXInspectorWidget::PositionXValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D pos = selectedGameObject->GetTransform()->GetPosition();
		selectedGameObject->GetTransform()->SetPosition(HXVector3D(value, pos.y, pos.z));
	}
}
void HXInspectorWidget::PositionYValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D pos = selectedGameObject->GetTransform()->GetPosition();
		selectedGameObject->GetTransform()->SetPosition(HXVector3D(pos.x, value, pos.z));
	}
}
void HXInspectorWidget::PositionZValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D pos = selectedGameObject->GetTransform()->GetPosition();
		selectedGameObject->GetTransform()->SetPosition(HXVector3D(pos.x, pos.y, value));
	}
}

void HXInspectorWidget::RotationXValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D rotate = selectedGameObject->GetTransform()->GetRotation();
		selectedGameObject->GetTransform()->SetRotation(HXVector3D(value, rotate.y, rotate.z));
	}
}
void HXInspectorWidget::RotationYValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D rotate = selectedGameObject->GetTransform()->GetRotation();
		selectedGameObject->GetTransform()->SetRotation(HXVector3D(rotate.x, value, rotate.z));
	}
}
void HXInspectorWidget::RotationZValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D rotate = selectedGameObject->GetTransform()->GetRotation();
		selectedGameObject->GetTransform()->SetRotation(HXVector3D(rotate.x, rotate.y, value));
	}
}

void HXInspectorWidget::ScaleXValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D scale = selectedGameObject->GetTransform()->GetScale();
		selectedGameObject->GetTransform()->SetScale(HXVector3D(value, scale.y, scale.z));
	}
}
void HXInspectorWidget::ScaleYValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D scale = selectedGameObject->GetTransform()->GetScale();
		selectedGameObject->GetTransform()->SetScale(HXVector3D(scale.x, value, scale.z));
	}
}
void HXInspectorWidget::ScaleZValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D scale = selectedGameObject->GetTransform()->GetScale();
		selectedGameObject->GetTransform()->SetScale(HXVector3D(scale.x, scale.y, value));
	}
}