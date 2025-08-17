#include "TaskManager.h"
#include <iostream>

TaskManager::TaskManager() : nextTaskId(1) {}

size_t TaskManager::FindTaskID(int userTaskId, bool isComplete){
	std::vector<Task>* taskListToSearch;
	if (!isComplete)
		taskListToSearch = &tasks;
	else
		taskListToSearch = &completedTasks;

	for (size_t i = 0; i < taskListToSearch->size(); ++i){
		if (taskListToSearch->at(i).taskID == userTaskId)
			return i;
	}

	return (size_t)-1;
}

void TaskManager::AddTask(const std::string& userDesc, const std::string& userDueDate){
	Task newTask;
	newTask.taskID = nextTaskId++;
	newTask.description = userDesc;
	newTask.dueDate = userDueDate;
	newTask.isComplete = false;
	tasks.push_back(newTask);
}

void TaskManager::UpdateTask(int userTaskId, const std::string& userDesc, const std::string& userDueDate){

	size_t foundIndex = FindTaskID(userTaskId, false);

	if (foundIndex != (size_t)-1) {
		Task& taskToUpdate = tasks.at(foundIndex);
		taskToUpdate.description = userDesc;
		taskToUpdate.dueDate = userDueDate;
		std::cout << "\n------------------------------------\nTask updated successfully!\n------------------------------------" << std::endl;
	}
	else
		std::cout << "\n------------------------------------\nTask not found.\n------------------------------------" << std::endl;
}

void TaskManager::CompleteTask(int userTaskId)
{
	size_t foundIndex = FindTaskID(userTaskId, false);

	if (foundIndex != (size_t)-1) {
		completedTasks.push_back(tasks.at(foundIndex));
		tasks.erase(tasks.begin() + foundIndex);
		std::cout << "\n------------------------------------\nTask Completed!\n------------------------------------" << std::endl;
	}
	else
		std::cout << "\n------------------------------------\nTask not found.\n------------------------------------" << std::endl;
}

void TaskManager::DeleteTask(int userTaskId){

	size_t foundIndex = FindTaskID(userTaskId, false);

	if (foundIndex != (size_t)-1) {
		tasks.erase(tasks.begin() + foundIndex);
		std::cout << "\n------------------------------------\nTask Deleted!\n------------------------------------" << std::endl;
	}
	else
		std::cout << "\n------------------------------------\nTask not found.\n------------------------------------" << std::endl;

	
}

void TaskManager::EmptyCompletedTasks(){
	completedTasks.clear();
}

void TaskManager::PrintAllTasks(bool isComplete) const{
	const std::vector<Task>* taskList;
	if (!isComplete) {
		taskList = &tasks;
		std::cout << "\n--- Current Tasks ---" << std::endl;
	}
	else {
		taskList = &completedTasks;
		std::cout << "\n--- Completed Tasks ---" << std::endl;
	}
	if(taskList->empty())
		std::cout << "No tasks in this list.\n" << std::endl;
	else {
		for (const Task& task : *taskList) {
			std::cout << task.taskID << ". " << "Description: " << task.description << ", Due Date:" << task.dueDate << std::endl;
		}
		std::cout << "------------------------------------" << std::endl;
	}
}

bool TaskManager::ListEmpty(bool isComplete)
{
	const std::vector<Task>* listChecked;
	if (!isComplete)
		listChecked = &tasks;
	else
		listChecked = &completedTasks;
	if (listChecked->empty())
		return true;
	else
		return false;
}


