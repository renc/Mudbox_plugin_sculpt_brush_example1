#ifndef MUDBOXPLUGIN_EXAMPLE_SCULPTBRUSH1 
#define MUDBOXPLUGIN_EXAMPLE_SCULPTBRUSH1 
#include <QtCore/QObject> // include this before mudbox headers.
#include <Mudbox\mudbox.h>

using namespace mudbox;

class SBrush : public BrushOperation
{
	DECLARE_CLASS;
	SBrush(void);
	virtual void BeginStroke(Mesh *pMesh, Modifier, TriggerType);
	virtual void EndStroke(void);
	virtual void AddPatch(const SurfacePoint *pPoint, const Vector &vPatchCenter, float fSize, float fPressure, float fStrength, AxisAlignedBoundingBox &cDirtyWorldArea);
	 
public:


private:
	QMap<Mesh *, MeshChange *> m_aMeshChanges; 
};

#endif //MUDBOXPLUGIN_EXAMPLE_SCULPTBRUSH1  