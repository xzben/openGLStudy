#pragma once

#define BEGIN_EDITOR_NAMESPACE namespace OGS_EDITOR{
#define END_EDITOR_NAMESPACE }
#define USING_EDITOR_NAMESPACE  using namespace OGS_EDITOR

#define DECLARE_EDITOR_CLASS_BASE(CLS) \
public: \
	typedef CLS ThisType; \
private:

#define DECLARE_EDITOR_CLASS(CLS) \
public: \
	typedef ThisType Super; \
	typedef CLS ThisType; \
	static SharePtr<CLS> create(){ \
		auto obj = makeShare<CLS>(new CLS()); \
		obj->handleInit(); \
		return obj; \
	}\
private: