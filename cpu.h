#pragma once
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

class core
{
private: 
	int computing_resource;           //���������ļ�����Դ
	int state;                        //����������״̬:0 - �޸��أ�1 - ��ȸ��أ� 2 - �жȸ��أ� 3 - �ضȸ���
	int comput_res_re;                //���������ļ�����Դʣ��
	int comput_res_use;               //���������ļ�����Դʹ��
	double L_state;                   //��ȸ����ж��õĺ��ļ�����Դ��������
	double M_state;                   //�ж�
	double H_state;	                  //�ض�
	ttask* p_task_start;              //���������ʼָ��
	ttask* p_task_end;                //������ж�βָ��
	int task_num;                     //�����������
	int task_num_limit;               //���������������
public:
	core();
	core(int num, double L, double M, double H);
	int set_core();
	int release_one_res();               //ģ���ͷŴ��������ļ�����Դ
	int use_one_res();                   //ģ�����Ĵ��������ļ�����Դ
	int release_res(int n);              //����ʣ��δ�ͷŵ���
	int use_res(int n);                  //����ʣ��δʹ�õ���
	int check_state();                   //���״̬
	int set_state_ratio(double L, double M, double H);               //����״̬����
	int set_state();
	int add_one_task(task t, int core_no);
	int add_task(task* p, int n, int core_no);
	int add_task_p(task** p, int n, int core_no);
	int get_one_task(int no, task* p_return);
	int get_task(int start_no, int num, task** q);
	int get_all_task(task** q, int* re_task_num);
	int remove_one_task(int model);         //modelΪ1ɾ������ռ���ڴ�,0��ɾ��
	int remove_task(int n, int model);
	int remove_all_task(int model);
	ttask* get_p_task_start();
	ttask* get_p_task_end();
	int get_task_num();
	int get_state();
	int get_com_res_re();
};

class multi_core                     //core���ܳ���2��10����
{
private:
	int core_num;               //��˴�������������
	int state;					//��˴�����״̬: 0 - ���ؾ��⣻1 - �Ǹ��ؾ���
	core** p_core;
public:
	multi_core();
	multi_core(int num, double L, double M, double H);
	int set_multi_core_state_ratio(double L, double M, double H);     //Ŀǰ���ܽ������к�����ͬ����״̬�ж�����
	int set_multi_core();
	int set_core(int num, core** p);
	int release_one_core_res(int no, int num);
	int use_one_core_res(int no, int num);
	int release_res();               //ģ���ͷŴ��������ļ�����Դ
	int use_res();                   //ģ�����Ĵ��������ļ�����Դ
	int check_state();               //�˺����о������˲���ϵͳ�ͼ������ɣ��Ȳ��ã�
	int add_one_core_task(int no, task* p, int n);
	int add_task(int start_core_no, task** p, int core_num, int* n);
	int remove_one_core_task(int no, int n);
	int remove_core_task();
	int remove_one_core_all_task();
	int remove_core_all_task(int* core_no, int get_core_num);
	int get_one_core_task(int core_no, int task_start_no, task** p, int num);
	int get_one_core_all_task(int core_no, task** q,int* re_task_num);
	int get_core_task(int core_start_no, int core_num, task*** p, int* task_start_no, int* num);
	int get_core_all_task(int* core_no, int get_core_num, task*** q, int** task_num);
	int get_all_core_all_task(int* re_core_num, task*** q, int** task_num);
	int get_one_core_task_num(int no, int* num);
	int get_core_task_num(int no_start, int num, int** n);
	ttask* get_one_core_p_task_start(int no);
	ttask* get_one_core_p_task_end(int no);
	ttask** get_p_task_start();
	ttask** get_p_task_end();
	core** get_p_core();
	int get_core_num();
	int get_multi_core_res_re();
};