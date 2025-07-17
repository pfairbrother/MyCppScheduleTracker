#pragma once
#include <string>

struct Task {
	int taskID;
	std::string description;
	std::string dueDate;
	bool isComplete;
};
