#include "..\include\HXRenderable.h"
#include "HXVector.h"
#include "HXMesh.h"

namespace HX3D
{
	HXRenderable::HXRenderable()
	{
	}

	HXRenderable::~HXRenderable()
	{
	}

	void HXRenderable::GenerateArguments(HXSubMesh* pSubMesh)
	{
		m_pSubMesh = pSubMesh;
		m_pSubMesh->renderable = this;
	}
}