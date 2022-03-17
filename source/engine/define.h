#ifndef __2022_01_06_DEFINE_H__
#define __2022_01_06_DEFINE_H__

enum class ResolutionFit
{
	FIXED_WIDTH,  //�̶����
	FIXED_HEIGHT, //�̶��߶�
	AUTO_FIT,		  //�Զ����ݿ�Ⱥ͸߶ȱ�������Ʒֱ��ʿ�߱ȣ��Զ�ѡ������߶Ȼ��߿�ȣ���֤������Ʒֱ���
};

#define DELETE_OBJ( pointer ) do{ if(pointer != nullptr) delete pointer; pointer = nullptr; }while(false);
#define DELETE_ARRAY_OBJ( pointer ) do{ if(pointer != nullptr) delete[] pointer; pointer = nullptr; }while(false);


#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_EPSILON                0.000001f

#endif//__2022_01_06_DEFINE_H__