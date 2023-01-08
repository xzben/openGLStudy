#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "core/math/math.h"

BEGIN_OGS_NAMESPACE

using namespace Gfx;

class Transform;
class Renderable;
class RenderWindow;

enum class CameraProjection{
	ORTHO,
	PERSPECTIVE,
};

class CameraComponent : public Component
{
	DECLARE_CLASS(CameraComponent)
	DECLARE_REFLEX_CLASS_FIELD(CameraComponent)
public:
	friend class RenderSystem;
	CameraComponent();
	~CameraComponent();

	void initPerspective(float fieldOfView, float aspectRation, float nearPlane, float farPlane);
	void initOrthographic(float zoomx, float zoomy, float nearPlane, float farplane);

	void lookAt(Vector3 pos, Vector3 targetpos, Vector3 up);
	void setFov(float fieldOfView);
	void setAspect(float width, float height);
	int getPriority() { return m_priority; }
	void setRenderWindow(RenderWindow* m_window);
	void clear();
	void setClearColor(const Color& color) { m_clearColor = color; }
	void setClearType(ClearFlagBit type) { m_cleartype = type; }
protected:
	void handleViewportChange(const Rect& viewport);
	virtual void onLoad() override;
	virtual void onStart() override;
	virtual void onStop() override;


	void render(std::vector<Renderable*> renders);
protected:
	Transform* m_transform{ nullptr };
	ClearFlagBit m_cleartype{ ClearFlagBit::ALL };
	Color	m_clearColor{ Color::BLACK };
	float   m_clearDepth{0};
	uint8    m_clearStenicl{0};
	int		m_priority{0};
	CameraProjection m_projection{CameraProjection::PERSPECTIVE};
	uint32  m_visibility{ CAMERA_DEFAUK_MASK };
	Matrix4 m_matProj;
	Matrix4 m_matView;
	Matrix4 m_matViewInverse;
	Matrix4 m_matViewProj;
	Vector3 m_up;
	float m_fieldOfView{45};
	float m_zoom[2]{0,0};
	float m_aspectRatio{1.f};
	float m_nearPlane{1.f};
	float m_farPlane{1000.f};

	bool m_projectDirty{ false };
	bool m_viewDirty{ false };
	bool m_frusumDirty{ false };
	WeakRef<RenderWindow> m_renderWindow;
};

END_OGS_NAMESPACE