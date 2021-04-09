#pragma once
#include "task.h"

class core
{
private: 
	int computing_resource;           //处理器核心计算资源
	int state;                        //处理器核心状态:0 - 无负载；1 - 轻度负载； 2 - 中度负载； 3 - 重度负载
	int comput_res_re;                //处理器核心计算资源剩余
	int comput_res_use;               //处理器核心计算资源使用

public:
	core();
	core(int num);
	int release_res();               //模拟释放处理器核心计算资源
	int use_res();                   //模拟消耗处理器核心计算资源
};

class multi_core
{
private:
	int core_num;               //多核处理器核心数量
	int state;					//多核处理器状态: 0 - 负载均衡；1 - 非负载均衡
	core* p_core;
public:
	multi_core();
	multi_core(int num);
};