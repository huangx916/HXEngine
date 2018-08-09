#include "HXEditorWin.h"
#include "HXGameWidget.h"
#include "HXHierarchyWidget.h"
#include "HXInspectorWidget.h"
#include <QFileDialog.h>
#include <QMessageBox.h>
#include "HXSceneManager.h"
#include "HXFogLinear.h"
#include "title_bar.h"

HXEditorWin* HXEditorWin::m_pInstance = NULL;
HXEditorWin::HXEditorWin(QWidget *parent)
	: QMainWindow(parent)
	, m_pMainLayout(NULL)
	, m_pGameWidget(NULL)
	, m_pHierarchyWidget(NULL)
	, m_pInspectorWidget(NULL)
	, m_pCoordArrowGO(NULL)
{
	ui.setupUi(this);
	m_pGameWidget = new HXGameWidget();
	m_pHierarchyWidget = new HXHierarchyWidget(HXEditorWin::updateGameObject, HXEditorWin::updateLight, HXEditorWin::updateCamera);
	m_pInspectorWidget = new HXInspectorWidget();

	m_pMainLayout = new QHBoxLayout();
	m_pMainLayout->addWidget(m_pHierarchyWidget,2);
	m_pMainLayout->addWidget(m_pInspectorWidget, 2);
	m_pMainLayout->addWidget(m_pGameWidget,6);
	ui.centralWidget->setLayout(m_pMainLayout);

	connect(ui.actionLoadScene, &QAction::triggered, this, &HXEditorWin::loadScene);
	connect(ui.actionSaveScene, &QAction::triggered, this, &HXEditorWin::saveScene);
	connect(ui.actionNewScene, &QAction::triggered, this, &HXEditorWin::newScene);
	connect(ui.actionCreateEmptyGO, &QAction::triggered, this, &HXEditorWin::createEmpty);
	connect(ui.actionLoadGameObject, &QAction::triggered, this, &HXEditorWin::loadGameObject);
	connect(ui.actionDeleteGameObject, &QAction::triggered, this, &HXEditorWin::deleteGameObject);
	connect(ui.actionExportGameObject, &QAction::triggered, this, &HXEditorWin::exportGameObject);
	connect(ui.actionDirectionLight, &QAction::triggered, this, &HXEditorWin::createDirectionLight);
	connect(ui.actionPointLight, &QAction::triggered, this, &HXEditorWin::createPointLight);
	connect(ui.actionSpotLight, &QAction::triggered, this, &HXEditorWin::createSpotLight);
	connect(ui.actionDeleteLight, &QAction::triggered, this, &HXEditorWin::deleteLight);

	/* set background color */
	//QPalette palette(palette());
	//palette.setColor(QPalette::Background, Qt::black);
	//setPalette(palette);

	setWindowFlags(Qt::FramelessWindowHint | windowFlags());
}

HXEditorWin::~HXEditorWin()
{
	if (m_pMainLayout)
	{
		delete m_pMainLayout;
		m_pMainLayout = NULL;
	}
	if (m_pGameWidget)
	{
		delete m_pGameWidget;
		m_pGameWidget = NULL;
	}
	if (m_pHierarchyWidget)
	{
		delete m_pHierarchyWidget;
		m_pHierarchyWidget = NULL;
	}
	if (m_pInspectorWidget)
	{
		delete m_pInspectorWidget;
		m_pInspectorWidget = NULL;
	}
}

HXEditorWin* HXEditorWin::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new HXEditorWin();
	}
	return m_pInstance;
}

void HXEditorWin::loadScene()
{
	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.scene)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		//QTextStream in(&file);
		//textEdit->setText(in.readAll());
		setWindowTitle(path);
		m_pGameWidget->LoadScene(path, HXEditorWin::loadSceneCallBack, HXEditorWin::updateCallBack, HXEditorWin::createGoCallBack);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void HXEditorWin::saveScene()
{
	QString path = QFileDialog::getSaveFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.scene)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		serializeScene(out);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void HXEditorWin::newScene()
{
	m_pGameWidget->LoadScene("./scene/empty.scene", HXEditorWin::loadSceneCallBack, HXEditorWin::updateCallBack, HXEditorWin::createGoCallBack);
}

void HXEditorWin::serializeGameObjectRecursive(QTextStream& out, std::vector<HX3D::HXGameObject*>& list, int level)
{
	for (std::vector<HXGameObject*>::iterator itr = list.begin(); itr != list.end(); ++itr)
	{
		for (int i = 0; i < level + 2; ++i)
		{
			out << "	";
		}
		out << "<GameObj Name=\"";
		out << (*itr)->GetName().c_str();
		out << "\" Activity=\"";
		out << (*itr)->GetActivity();
		out << "\" Static=\"";
		out << (*itr)->GetStatic();
		out << "\" Model=\"";
		out << (*itr)->m_strModelFile.c_str();
		out << "\" CastShadow=\"";
		out << (*itr)->GetCastShadow();
		out << "\">\n";

		for (int i = 0; i < level + 3; ++i)
		{
			out << "	";
		}
		out << "<Position Px=\"";
		out << (*itr)->GetTransform()->GetPosition().x;
		out << "\" Py=\"";
		out << (*itr)->GetTransform()->GetPosition().y;
		out << "\" Pz=\"";
		out << (*itr)->GetTransform()->GetPosition().z;
		out << "\"/>\n";

		for (int i = 0; i < level + 3; ++i)
		{
			out << "	";
		}
		out << "<Rotation Rx=\"";
		out << (*itr)->GetTransform()->GetRotation().x;
		out << "\" Ry=\"";
		out << (*itr)->GetTransform()->GetRotation().y;
		out << "\" Rz=\"";
		out << (*itr)->GetTransform()->GetRotation().z;
		out << "\"/>\n";

		for (int i = 0; i < level + 3; ++i)
		{
			out << "	";
		}
		out << "<Scale Sx=\"";
		out << (*itr)->GetTransform()->GetScale().x;
		out << "\" Sy=\"";
		out << (*itr)->GetTransform()->GetScale().y;
		out << "\" Sz=\"";
		out << (*itr)->GetTransform()->GetScale().z;
		out << "\"/>\n";

		serializeGameObjectRecursive(out, (*itr)->GetChildren(), level+1);

		for (int i = 0; i < level + 2; ++i)
		{
			out << "	";
		}
		out << "</GameObj>\n";
	}
}

void HXEditorWin::serializeScene(QTextStream& out)
{
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	out << "<Scene>\n";
	
	// Camera
	HXGLCamera* camera = (HXGLCamera*)HXSceneManager::GetInstance()->GetMainCamera();
	out << "	<Camera NearZ=\"";
	out << camera->mNear;
	out << "\" FarZ=\"";
	out << camera->mFar;
	out << "\">\n";
	out << "		<Position Px=\"";
	out << camera->transform->mPostion.x;
	out << "\" Py=\"";
	out << camera->transform->mPostion.y;
	out << "\" Pz=\"";
	out << camera->transform->mPostion.z;
	out << "\"/>\n";
	out << "		<Rotation Rx=\"";
	out << camera->transform->mEulerDegree.x;
	out << "\" Ry=\"";
	out << camera->transform->mEulerDegree.y;
	out << "\" Rz=\"";
	out << camera->transform->mEulerDegree.z;
	out << "\"/>\n";
	out << "	</Camera>\n";

	// Fog
	HXFogBase* fogBase = HXSceneManager::GetInstance()->fog;
	out << "	<Fog Use=\"";
	if (fogBase->useFog)
	{
		out << 1;
	}
	else
	{
		out << 0;
	}
	out << "\" Type=\"";
	out << fogBase->fogType;
	out << "\" R=\"";
	out << fogBase->fogColor.r;
	out << "\" G=\"";
	out << fogBase->fogColor.g;
	out << "\" B=\"";
	out << fogBase->fogColor.b;
	if (fogBase->fogType == HXFogType::FOG_Linear)
	{
		out << "\" Start=\"";
		HXFogLinear* fogLinear = (HXFogLinear*)fogBase;
		out << fogLinear->fogStart;
		out << "\" End=\"";
		out << fogLinear->fogEnd;
	}
	else
	{
		out << "\" Start=\"";
		out << 0;
		out << "\" End=\"";
		out << 0;
	}
	out << "\"/>\n";

	// Ambient
	HXCOLOR* Ambient = &(HXSceneManager::GetInstance()->ambient);
	out << "	<Ambient R=\"";
	out << Ambient->r;
	out << "\" G=\"";
	out << Ambient->g;
	out << "\" B=\"";
	out << Ambient->b;
	out << "\"/>\n";

	// Lights
	out << "	<Lights>\n";
	std::vector<HXLight*> lightVct = HXSceneManager::GetInstance()->lightVct;
	for (std::vector<HXLight*>::iterator itr = lightVct.begin(); itr != lightVct.end(); ++itr)
	{
		out << "		<Light Name=\"";
		out << (*itr)->name.c_str();
		out << "\" Enable=\"";
		int enable = (*itr)->enable ? 1 : 0;
		out << enable;
		out << "\" LightType=\"";
		out << (*itr)->lightType;
		out << "\" Shininess=\"";
		out << (*itr)->shininess;
		out << "\" Strength=\"";
		out << (*itr)->strength;
		out << "\" constantAttenuation=\"";
		out << (*itr)->constantAttenuation;
		out << "\" LinearAttenuation=\"";
		out << (*itr)->LinearAttenuation;
		out << "\" QuadraticAttenuation=\"";
		out << (*itr)->QuadraticAttenuation;
		out << "\" SpotCosCutoff=\"";
		out << (*itr)->SpotCosCutoff;
		out << "\" SpotExponent=\"";
		out << (*itr)->SpotExponent;
		out << "\">\n";

		out << "			<Color Cr=\"";
		out << (*itr)->color.r;
		out << "\" Cg=\"";
		out << (*itr)->color.g;
		out << "\" Cb=\"";
		out << (*itr)->color.b;
		out << "\"/>\n";

		out << "			<Position Px=\"";
		out << (*itr)->position.x;
		out << "\" Py=\"";
		out << (*itr)->position.y;
		out << "\" Pz=\"";
		out << (*itr)->position.z;
		out << "\"/>\n";

		out << "			<Direct Dx=\"";
		out << (*itr)->direct.x;
		out << "\" Dy=\"";
		out << (*itr)->direct.y;
		out << "\" Dz=\"";
		out << (*itr)->direct.z;
		out << "\"/>\n";

		out << "			<ConeDirection Cx=\"";
		out << (*itr)->ConeDirection.x;
		out << "\" Cy=\"";
		out << (*itr)->ConeDirection.y;
		out << "\" Cz=\"";
		out << (*itr)->ConeDirection.z;
		out << "\"/>\n";

		out << "		</Light>\n";
	}
	out << "	</Lights>\n";

	// GameObjects
	out << "	<GameObjects>\n";
	HXGameObject* gameObjectTreeRoot = HXSceneManager::GetInstance()->GetGameObjectTreeRoot();
	serializeGameObjectRecursive(out, gameObjectTreeRoot->GetChildren(), 0);
	out << "	</GameObjects>\n";

	out << "</Scene>";
}

void HXEditorWin::serializePrefab(QTextStream& out)
{
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	out << "<Scene>\n";

	std::vector<HX3D::HXGameObject*> list;
	list.push_back(m_pInspectorWidget->selectedGameObject);
	serializeGameObjectRecursive(out, list, -1);

	out << "</Scene>";
}

void HXEditorWin::createEmpty()
{
	QString scene = m_pGameWidget->GetCurScene();
	if (scene.isEmpty())
	{
		QMessageBox::warning(this, tr("Read File"),
			tr("Please load or new a scene first"));
		return;
	}
	m_pGameWidget->LoadGameObject(m_pInspectorWidget->selectedGameObject, "./prefab/Empty/Empty.prefab");
}

void HXEditorWin::loadGameObject()
{
	QString scene = m_pGameWidget->GetCurScene();
	if (scene.isEmpty())
	{
		QMessageBox::warning(this, tr("Read File"),
			tr("Please load or new a scene first"));
		return;
	}

	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.prefab)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		//QTextStream in(&file);
		//textEdit->setText(in.readAll());
		m_pGameWidget->LoadGameObject(m_pInspectorWidget->selectedGameObject, path);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void HXEditorWin::deleteGameObject()
{
	if (NULL == m_pInspectorWidget->selectedGameObject)
	{
		QMessageBox::warning(this, tr("GameObject"),
			tr("You did not select any gameobject."));
		return;
	}

	if (QMessageBox::Yes == QMessageBox::question(this,
		tr("GameObject"),
		tr("Delete this GameObject ?"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::Yes)) {
		if (HXSceneManager::GetInstance()->DeleteGameObject(m_pInspectorWidget->selectedGameObject))
		{
			m_pHierarchyWidget->OnDeleteGameObject();
		}
	}
	/*else {
		QMessageBox::information(this, tr("Hmmm..."), tr("I'm sorry!"));
	}*/
}

void HXEditorWin::exportGameObject()
{
	if (NULL == m_pInspectorWidget->selectedGameObject)
	{
		QMessageBox::warning(this, tr("GameObject"),
			tr("You did not select any gameobject."));
		return;
	}

	QString path = QFileDialog::getSaveFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.prefab)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		serializePrefab(out);
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void HXEditorWin::createDirectionLight()
{
	QString scene = m_pGameWidget->GetCurScene();
	if (scene.isEmpty())
	{
		QMessageBox::warning(this, tr("Read File"),
			tr("Please load or new a scene first"));
		return;
	}
	HXLight* light = HXSceneManager::GetInstance()->CreateLight(LIGHT_DIRECTION);
	if (light)
	{
		m_pHierarchyWidget->OnCreateLight(light);
	}
}

void HXEditorWin::createPointLight()
{
	QString scene = m_pGameWidget->GetCurScene();
	if (scene.isEmpty())
	{
		QMessageBox::warning(this, tr("Read File"),
			tr("Please load or new a scene first"));
		return;
	}
	HXLight* light = HXSceneManager::GetInstance()->CreateLight(LIGHT_POINT);
	if (light)
	{
		m_pHierarchyWidget->OnCreateLight(light);
	}
}

void HXEditorWin::createSpotLight()
{
	QString scene = m_pGameWidget->GetCurScene();
	if (scene.isEmpty())
	{
		QMessageBox::warning(this, tr("Read File"),
			tr("Please load or new a scene first"));
		return;
	}
	HXLight* light = HXSceneManager::GetInstance()->CreateLight(LIGHT_SPOT);
	if (light)
	{
		m_pHierarchyWidget->OnCreateLight(light);
	}
}

void HXEditorWin::deleteLight()
{
	if (NULL == m_pInspectorWidget->selectedLight)
	{
		QMessageBox::warning(this, tr("Light"),
			tr("You did not select any light."));
		return;
	}

	if (QMessageBox::Yes == QMessageBox::question(this,
		tr("Light"),
		tr("Delete this light ?"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::Yes)) {
		if (HXSceneManager::GetInstance()->DeleteLight(m_pInspectorWidget->selectedLight))
		{
			m_pHierarchyWidget->OnDeleteLight();
		}
	}
}

void HXEditorWin::loadSceneCallBack()
{
	HXEditorWin::GetInstance()->m_pCoordArrowGO = HXSceneManager::GetInstance()->CreateGameObjectFromPrefab(NULL, "./prefab/CoordArrow/CoordArrow.prefab");
	HXEditorWin::GetInstance()->m_pHierarchyWidget->UpdateSceneTree();
	HXEditorWin::GetInstance()->m_pInspectorWidget->SetFogInfo(HXSceneManager::GetInstance()->fog);
	HXEditorWin::GetInstance()->m_pInspectorWidget->SetAmbientInfo(&(HXSceneManager::GetInstance()->ambient));
	//HXEditorWin::GetInstance()->m_pInspectorWidget->SetCameraInfo(HXSceneManager::GetInstance()->GetMainCamera());
}

void HXEditorWin::updateCallBack()
{
	// 影响帧率，改用按钮同步数据
	//HXEditorWin::GetInstance()->m_pInspectorWidget->SetCameraInfo(HXSceneManager::GetInstance()->mainCamera);
}

void HXEditorWin::createGoCallBack(HX3D::HXGameObject* gameObject)
{
	HXEditorWin::GetInstance()->m_pHierarchyWidget->OnCreateGameObject(gameObject);
}

void HXEditorWin::updateGameObject(HX3D::HXGameObject* gameObject)
{
	HXEditorWin::GetInstance()->m_pInspectorWidget->SetGameObjectInfo(gameObject);
}

void HXEditorWin::updateLight(HX3D::HXLight* light)
{
	HXEditorWin::GetInstance()->m_pInspectorWidget->SetLightInfo(light);
}

void HXEditorWin::updateCamera(HX3D::HXICamera* camera)
{
	HXEditorWin::GetInstance()->m_pInspectorWidget->SetCameraInfo(camera);
}