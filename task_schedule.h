#pragma once
#include "cpu.h"
#include "task.h"

int task_sche_on_one_core(core* C, task* T);

int task_sche_on_multi_core(core* C, task* T);

int DLBQ_sche(int type, core* C, task* T);

int Base_sche(int type, core* C, task* T);

int Linux_sche(int type, core* C, task* T);

int Windows_sche(int type, core* C, task* T);