#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <string>
#include "sqlite3.h"

class TaskManager {
private:                    
	int CreateTable();
	bool FindTaskID(int userTaskID);
	sqlite3* db;

	

public:
	TaskManager();
	~TaskManager();
	void AddTask(const std::string& userDesc, const std::string& userDueDate);
	void UpdateTask(int userTaskId, const std::string& userDesc, const std::string& userDueDate);
	void CompleteTask(int userTaskId);
	void DeleteTask(int userTaskId);
	void EmptyCompletedTasks();
	void PrintAllTasks(bool isComplete) const;
	bool ListEmpty(bool isComplete);
	
};

#endif // !TASKMANAGER_H



