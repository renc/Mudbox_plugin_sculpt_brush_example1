#include "SBrush.h"
 
#include <QtCore/QVector>
#include <math.h>


#include <float.h>

IMPLEMENT_CLASS(SBrush, BrushOperation, "SBrush");
  
SBrush::SBrush() 
{
};

void SBrush::BeginStroke(Mesh *pMesh, Modifier, TriggerType)
{ 
	m_aMeshChanges.clear(); 
};

void SBrush::EndStroke(void)
{	
	for (QMap<Mesh *, MeshChange *>::iterator it = m_aMeshChanges.begin();
		it != m_aMeshChanges.end(); ++it)
	{
		it.key()->EndChange(); 
	} 
	m_aMeshChanges.clear(); 

	Kernel()->Redraw();
};

void SBrush::AddPatch(const SurfacePoint *pPoint, const Vector &vPatchCenter, float fSize, float fPressure, float fStrength, AxisAlignedBoundingBox &cDirtyWorldArea)
{
	if (!pPoint || !pPoint->Mesh())
		return;

	if (m_aMeshChanges.find(pPoint->Mesh()) == m_aMeshChanges.end())
	{
		// map a mesh to a meshchange;
		// this supports sculpting on multi meshes. 
		m_aMeshChanges[pPoint->Mesh()] = pPoint->Mesh()->StartChange();
	}

	const unsigned int fIdx = pPoint->FaceIndex();
	const unsigned int vIdx = pPoint->Mesh()->Type() == Topology::typeQuadric ? pPoint->Mesh()->QuadIndex(fIdx, 0) : pPoint->Mesh()->TriangleIndex(fIdx, 0); 
	MeshChange::VertexChange &vc = m_aMeshChanges[pPoint->Mesh()]->Add(vIdx, fIdx);

	const Vector vOldPos = vc.m_vPosition;
	Vector vDelta = Vector(0, 10, 0);
	pPoint->Mesh()->VertexPosition(vIdx) = vOldPos + vDelta;
};
 