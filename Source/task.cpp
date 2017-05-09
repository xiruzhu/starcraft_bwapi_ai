#include "task.h"
task::task(std::vector<int> unit_group, task::action group_action, BWAPI::GameWrapper *broodwar){
	this->unit_list = unit_group;
	this->unit_group_action = group_action;
	this->broodwar = broodwar;
	this->condition = nullptr;
	this->condition_argument = nullptr;
}

task::task(std::vector<int>unit_group, task::action group_action, BWAPI::GameWrapper *broodwar, bool(*condition)(void *, std::vector<int>), void *cond_arg) {
	this->unit_list = unit_group;
	this->unit_group_action = group_action;
	this->broodwar = broodwar;
	this->condition = condition;
	this->condition_argument = cond_arg;
}

task::~task(){
	//Nothing to do here ... 
}

//Execute Task
int task::execute_task() {
	//First run condition
	if (this->condition(this->condition_argument, this->unit_list)) {
		for (int i = 0; i < unit_list.size; i++) {

		}
	}
	else {
		return this->unit_list.size;
	}
}
