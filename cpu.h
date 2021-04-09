#pragma once
#include "task.h"

class core
{
private: 
	int computing_resource;           //���������ļ�����Դ
	int state;                        //����������״̬:0 - �޸��أ�1 - ��ȸ��أ� 2 - �жȸ��أ� 3 - �ضȸ���
	int comput_res_re;                //���������ļ�����Դʣ��
	int comput_res_use;               //���������ļ�����Դʹ��

public:
	core();
	core(int num);
	int release_res();               //ģ���ͷŴ��������ļ�����Դ
	int use_res();                   //ģ�����Ĵ��������ļ�����Դ
};

class multi_core
{
private:
	int core_num;               //��˴�������������
	int state;					//��˴�����״̬: 0 - ���ؾ��⣻1 - �Ǹ��ؾ���
	core* p_core;
public:
	multi_core();
	multi_core(int num);
};