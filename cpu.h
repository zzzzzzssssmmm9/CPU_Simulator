#pragma once
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

class core
{
private: 
	int computing_resource;           //处理器核心计算资源
	int state;                        //处理器核心状态:0 - 无负载；1 - 轻度负载； 2 - 中度负载； 3 - 重度负载
	int comput_res_re;                //处理器核心计算资源剩余
	int comput_res_use;               //处理器核心计算资源使用
	double L_state;                   //轻度负载判断用的核心计算资源用量比例
	double M_state;                   //中度
	double H_state;	                  //重度
	ttask* p_task_start;              //任务队列起始指针
	ttask* p_task_end;                //任务队列队尾指针
	int task_num;                     //任务队列容量
	int task_num_limit;               //任务队列容量限制
public:
	core();
	core(int num, double L, double M, double H);
	int set_core();
	int release_one_res();               //模拟释放处理器核心计算资源
	int use_one_res();                   //模拟消耗处理器核心计算资源
	int release_res(int n);              //返回剩余未释放的量
	int use_res(int n);                  //返回剩余未使用的量
	int check_state();                   //检查状态
	int set_state_ratio(double L, double M, double H);               //设置状态比例
	int set_state();
	int add_one_task(task t, int core_no);
	int add_task(task* p, int n, int core_no);
	int add_task_p(task** p, int n, int core_no);
	int get_one_task(int no, task* p_return);
	int get_task(int start_no, int num, task** q);
	int get_all_task(task** q, int* re_task_num);
	int remove_one_task(int model);         //model为1删除任务占用内存,0不删除
	int remove_task(int n, int model);
	int remove_all_task(int model);
	ttask* get_p_task_start();
	ttask* get_p_task_end();
	int get_task_num();
	int get_state();
	int get_com_res_re();
};

class multi_core                     //core不能超过2的10次幂
{
private:
	int core_num;               //多核处理器核心数量
	int state;					//多核处理器状态: 0 - 负载均衡；1 - 非负载均衡
	core** p_core;
public:
	multi_core();
	multi_core(int num, double L, double M, double H);
	int set_multi_core_state_ratio(double L, double M, double H);     //目前仅能进行所有核心相同负载状态判断设置
	int set_multi_core();
	int set_core(int num, core** p);
	int release_one_core_res(int no, int num);
	int use_one_core_res(int no, int num);
	int release_res();               //模拟释放处理器核心计算资源
	int use_res();                   //模拟消耗处理器核心计算资源
	int check_state();               //此函数感觉混淆了操作系统和计算机组成（先不用）
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