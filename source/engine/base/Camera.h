#ifndef __2022_03_18_CAMERA_H__
#define __2022_03_18_CAMERA_H__

#include "base/Node.h"
#include "common.h"
#include "math/Mat4.h"

class Camera : public Node
{
protected:
	uint m_visibility; //可见分组
	fMat4 m_matProjection;
	fMat4 m_matView;
public:
	CREATE_FUNC(Camera);
	static Camera* createFrustum();
	static Camera* createPerspective();
	
	Camera();
	virtual ~Camera();

	
	bool isCameraVisible(uint group);
	void setMask(uint mask);
	void addGroup(uint mask);
};

#endif//__2022_03_18_CAMERA_H__
