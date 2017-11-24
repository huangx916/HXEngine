//#include "..\include\HXFBXMaterial.h"
//#include "HXResourceManager.h"
//#include "HXFBXLoader.h"
//
//namespace HX3D
//{
//	HXFBXMaterial::HXFBXMaterial()
//	{
//	}
//
//
//	HXFBXMaterial::~HXFBXMaterial()
//	{
//	}
//
//	bool HXFBXMaterial::Initialize(const FbxSurfaceMaterial* pMaterial)
//	{
//		// TODO: 暂时只支持一张漫反射贴图
//		FbxProperty lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
//		if (lProperty.IsValid())
//		{
//			const int lTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();
//			if (lTextureCount)
//			{
//				const FbxFileTexture* lFileTexture = lProperty.GetSrcObject<FbxFileTexture>();
//				if (lFileTexture)
//				{
//					std::string strTextureFileName = lFileTexture->GetFileName();
//					// 贴图路径处理，改为FBX同目录下
//					size_t index = strTextureFileName.find_last_of("\\");
//					if (index != -1)
//					{
//						strTextureFileName = strTextureFileName.substr(index+1, strTextureFileName.length());
//					}
//					
//					index = HXFBXLoader::gCurPathFileName.find_last_of("\\");
//					std::string strPath;
//					if (index != -1)
//					{
//						strPath = HXFBXLoader::gCurPathFileName.substr(0, index);
//						strTextureFileName = strPath + "\\" + strTextureFileName;
//					}
//					else
//					{
//						strPath = "";
//					}
//					 
//					mBitmap = HXResourceManager::GetInstance()->GetBitmap(strTextureFileName);
//				}
//			}
//		}
//
//		FbxPropertyT<FbxDouble3> lKFbxDouble3;
//		FbxPropertyT<FbxDouble> lKFbxDouble1;
//		if (pMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
//		{
//			shadingModel = MAT_SHADING_MODEL::Phong;
//
//			lKFbxDouble3 = ((FbxSurfacePhong *)pMaterial)->Ambient;
//			ambient.r = lKFbxDouble3.Get()[0];
//			ambient.g = lKFbxDouble3.Get()[1];
//			ambient.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble3 = ((FbxSurfacePhong *)pMaterial)->Diffuse;
//			diffuse.r = lKFbxDouble3.Get()[0];
//			diffuse.g = lKFbxDouble3.Get()[1];
//			diffuse.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble3 = ((FbxSurfacePhong *)pMaterial)->Specular;
//			specular.r = lKFbxDouble3.Get()[0];
//			specular.g = lKFbxDouble3.Get()[1];
//			specular.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble3 = ((FbxSurfacePhong *)pMaterial)->Emissive;
//			emissive.r = lKFbxDouble3.Get()[0];
//			emissive.g = lKFbxDouble3.Get()[1];
//			emissive.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble1 = ((FbxSurfacePhong *)pMaterial)->TransparencyFactor;
//			transparencyfactor = lKFbxDouble1;
//
//			lKFbxDouble1 = ((FbxSurfacePhong *)pMaterial)->Shininess;
//			shininess = lKFbxDouble1;
//
//			lKFbxDouble1 = ((FbxSurfacePhong *)pMaterial)->ReflectionFactor;
//			reflectionfactor = lKFbxDouble1;
//		}
//		else if (pMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
//		{
//			shadingModel = MAT_SHADING_MODEL::Lambert;
//
//			lKFbxDouble3 = ((FbxSurfaceLambert *)pMaterial)->Ambient;
//			ambient.r = lKFbxDouble3.Get()[0];
//			ambient.g = lKFbxDouble3.Get()[1];
//			ambient.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble3 = ((FbxSurfaceLambert *)pMaterial)->Diffuse;
//			diffuse.r = lKFbxDouble3.Get()[0];
//			diffuse.g = lKFbxDouble3.Get()[1];
//			diffuse.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble3 = ((FbxSurfaceLambert *)pMaterial)->Emissive;
//			emissive.r = lKFbxDouble3.Get()[0];
//			emissive.g = lKFbxDouble3.Get()[1];
//			emissive.b = lKFbxDouble3.Get()[2];
//
//			lKFbxDouble1 = ((FbxSurfaceLambert *)pMaterial)->TransparencyFactor;
//			transparencyfactor = lKFbxDouble1;
//		}
//		return true;
//	}
//}