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
	m_aRenderers.clear();
};

void SBrush::EndStroke(void)
{
	
	for (QMap<Mesh *, MeshChange *>::iterator it = m_aMeshChanges.begin();
		it != m_aMeshChanges.end(); ++it)
	{
		it.key()->EndChange(); 
	} 
	m_aMeshChanges.clear(); 
	m_aRenderers.clear();

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

		// 
		unsigned int i = 0;
		MeshRenderer *p;
		while ( p = ((const Mesh *)pPoint->Mesh())->ChildByClass<MeshRenderer>( i++ ) )
			m_aRenderers.push_back( p );
	}

	const unsigned int fIdx = pPoint->FaceIndex();
	QVector<unsigned int> vIndices;
	if (pPoint->Mesh()->Type() == Topology::typeQuadric)
	{
		for (unsigned int c = 0; c < 4; ++c)
		{
			const unsigned int vIdx = pPoint->Mesh()->QuadIndex(fIdx, c);  
			MeshChange::VertexChange &vc = m_aMeshChanges[pPoint->Mesh()]->Add(vIdx, fIdx);

			const Vector vOldPos = vc.m_vPosition;
			Vector vDelta = Vector(0, 10, 0);
			pPoint->Mesh()->VertexPosition(vIdx) = vOldPos + vDelta;

			vIndices.push_back(vIdx);
		}
	}
	else
	{
		for (unsigned int c = 0; c < 3; ++c)
		{
			const unsigned int vIdx = pPoint->Mesh()->TriangleIndex(fIdx, c); 
			MeshChange::VertexChange &vc = m_aMeshChanges[pPoint->Mesh()]->Add(vIdx, fIdx);

			const Vector vOldPos = vc.m_vPosition;
			Vector vDelta = Vector(0, 10, 0);
			pPoint->Mesh()->VertexPosition(vIdx) = vOldPos + vDelta;
			
			vIndices.push_back(vIdx);
		}
	} 

	// 
	for ( int r = 0; r < m_aRenderers.size(); r++ )
	{
		MeshRenderer *pR = m_aRenderers[r];
		for ( int i = 0; i < vIndices.size(); i++ )
			pR->OnVertexPositionChange( vIndices[i], fIdx );
	};
	Kernel()->ViewPort()->Redraw();
};
 