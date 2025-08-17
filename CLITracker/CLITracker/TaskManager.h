#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include "Task.h"
#include <vector>
#include <string>

class TaskManager {
private:
	std::vector<Task> tasks;
	std::vector<Task> completedTasks;
	int nextTaskId;
	size_t FindTaskID(int userTaskId, bool isComplete);

public:
	TaskManager();
	void AddTask(const std::string& userDesc, const std::string& userDueDate);
	void UpdateTask(int userTaskId, const std::string& userDesc, const std::string& userDueDate);
	void CompleteTask(int userTaskId);
	void DeleteTask(int userTaskId);
	void EmptyCompletedTasks();
	void PrintAllTasks(bool isComplete) const;
	bool ListEmpty(bool isComplete);
	
};

#endif // !TASKMANAGER_H



