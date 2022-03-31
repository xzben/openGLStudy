#ifndef __2022_03_31_NONCOPYABLE_H__
#define __2022_03_31_NONCOPYABLE_H__

class NonCopyable
{
public:
	NonCopyable(){}
	virtual ~NonCopyable(){}
private:
	NonCopyable(const NonCopyable&) = delete;
	void operator=(const NonCopyable&) = delete;
};

#endif//__2022_03_31_NONCOPYABLE_H__