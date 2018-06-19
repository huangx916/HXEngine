#include "HXInspectorWidget.h"
#include <QLabel.h>
//#include <QSpinBox.h>
#include <QBoxLayout.h>
#include <QFormLayout>

HXInspectorWidget::HXInspectorWidget(QWidget* parent) : QWidget(parent)
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
}

HXInspectorWidget::~HXInspectorWidget()
{

}

void HXInspectorWidget::SetGameObjectInfo(HXGameObject* pGameObject)
{
	if (pGameObject == NULL)
	{
		SetGameObjectTransform(NULL); 
		SetGameObjectName("");
	}
	else
	{
		SetGameObjectTransform(pGameObject->GetTransform());
		SetGameObjectName(pGameObject->GetName().c_str());
	}
}

void HXInspectorWidget::SetGameObjectName(QString name)
{
	editGameObjectName->setText(name);
}

void HXInspectorWidget::SetGameObjectTransform(HXITransform* pTransform)
{
	if (pTransform)
	{
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
	
}