#include "HXInspectorWidget.h"
#include <QLabel.h>
//#include <QSpinBox.h>
#include <QBoxLayout.h>
#include <QFormLayout>

HXInspectorWidget::HXInspectorWidget(QWidget* parent) : QWidget(parent)
{
	//QLabel* labelPositionX = new QLabel(tr("Position X"));
	spinboxPositionX = new QDoubleSpinBox();
	spinboxPositionX->setRange(MIN, MAX);

	//QLabel* labelPositionY = new QLabel(tr("Position Y"));
	spinboxPositionY = new QDoubleSpinBox();
	spinboxPositionY->setRange(MIN, MAX);

	//QLabel* labelPositionZ = new QLabel(tr("Position Z"));
	spinboxPositionZ = new QDoubleSpinBox();
	spinboxPositionZ->setRange(MIN, MAX);

	//QLabel* labelRotationX = new QLabel(tr("Rotation X"));
	spinboxRotationX = new QDoubleSpinBox();
	spinboxRotationX->setRange(MIN, MAX);

	//QLabel* labelRotationY = new QLabel(tr("Rotation Y"));
	spinboxRotationY = new QDoubleSpinBox();
	spinboxRotationY->setRange(MIN, MAX);

	//QLabel* labelRotationZ = new QLabel(tr("Rotation Z"));
	spinboxRotationZ = new QDoubleSpinBox();
	spinboxRotationZ->setRange(MIN, MAX);

	//QLabel* labelScaleX = new QLabel(tr("Scale X"));
	spinboxScaleX = new QDoubleSpinBox();
	spinboxScaleX->setRange(MIN, MAX);

	//QLabel* labelScaleY = new QLabel(tr("Scale Y"));
	spinboxScaleY = new QDoubleSpinBox();
	spinboxScaleY->setRange(MIN, MAX);

	//QLabel* labelScaleZ = new QLabel(tr("Scale Z"));
	spinboxScaleZ = new QDoubleSpinBox();
	spinboxScaleZ->setRange(MIN, MAX);


	/*QGridLayout* inspectorLayout = new QGridLayout();

	inspectorLayout->addWidget(labelPositionX, 0, 0);
	inspectorLayout->addWidget(spinboxPositionX, 0, 1);

	inspectorLayout->addWidget(labelPositionY, 1, 0);
	inspectorLayout->addWidget(spinboxPositionY, 1, 1);

	inspectorLayout->addWidget(labelPositionZ, 2, 0);
	inspectorLayout->addWidget(spinboxPositionZ, 2, 1);

	inspectorLayout->addWidget(labelRotationX, 3, 0);
	inspectorLayout->addWidget(spinboxRotationX, 3, 1);

	inspectorLayout->addWidget(labelRotationY, 4, 0);
	inspectorLayout->addWidget(spinboxRotationY, 4, 1);

	inspectorLayout->addWidget(labelRotationZ, 5, 0);
	inspectorLayout->addWidget(spinboxRotationZ, 5, 1);

	inspectorLayout->addWidget(labelScaleX, 6, 0);
	inspectorLayout->addWidget(spinboxScaleX, 6, 1);

	inspectorLayout->addWidget(labelScaleY, 7, 0);
	inspectorLayout->addWidget(spinboxScaleY, 7, 1);

	inspectorLayout->addWidget(labelScaleZ, 8, 0);
	inspectorLayout->addWidget(spinboxScaleZ, 8, 1);*/


	QFormLayout* inspectorLayout = new QFormLayout();
	QLabel* title = new QLabel(tr("Transform"));
	QFont font("Microsoft YaHei", 10, 75);
	title->setFont(font);
	inspectorLayout->addRow(title);
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
}

HXInspectorWidget::~HXInspectorWidget()
{

}

void HXInspectorWidget::SetGameObjectInfo(HXGameObject* pGameObject)
{
	if (pGameObject == NULL)
	{
		SetGameObjectTransform(NULL);
	}
	else
	{
		SetGameObjectTransform(pGameObject->GetTransform());
	}
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