#ifndef __2022_01_06_DEFINE_H__
#define __2022_01_06_DEFINE_H__

enum class ResolutionFit
{
	FIXED_WIDTH,  //�̶����
	FIXED_HEIGHT, //�̶��߶�
	AUTO_FIT,		  //�Զ����ݿ�Ⱥ͸߶ȱ�������Ʒֱ��ʿ�߱ȣ��Զ�ѡ������߶Ȼ��߿�ȣ���֤������Ʒֱ���
};

#define DELETE_OBJ( pointer ) do{ if(pointer != nullptr) delete pointer; pointer = nullptr; }while(false);
#endif//__2022_01_06_DEFINE_H__