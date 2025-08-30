#include "TaskManager.h"
#include "sqlite3.h"
#include <iostream>



int TaskManager::CreateTable(){
	const char* sql =
		"CREATE TABLE IF NOT EXISTS tasks("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"description TEXT NOT NULL,"
		"due_date TEXT NOT NULL,"
		"is_complete INTEGER NOT NULL DEFAULT 0);";

	char* errMsg = 0;
	int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return 1;
	}
	std::cout << "Tasks table created successfully." << std::endl;
	return 0;
}

bool TaskManager::FindTaskID(int userTaskID)
{
	const char* sql = "SELECT id FROM tasks WHERE id = ?;";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during prepare: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	rc = sqlite3_bind_int(stmt, 1, userTaskID);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during bind: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_finalize(stmt);
		return false;
	}

	rc = sqlite3_step(stmt);
	bool taskFound = (rc == SQLITE_ROW);

	sqlite3_finalize(stmt);

	return taskFound;
}

TaskManager::TaskManager() {
	int rc = sqlite3_open("tasks.db", &db);

	if (rc != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		db = nullptr;
	}
	else {
		std::cout << "Database opened successfully." << std::endl;
		if (CreateTable() != 0) {
			std::cerr << "Failed to create tasks table." << std::endl;
		}
	}
}

TaskManager::~TaskManager() {
	if (db)
		sqlite3_close(db);
}

void TaskManager::AddTask(const std::string& userDesc, const std::string& userDueDate){
	const char* sql = "INSERT INTO tasks (description, due_date, is_complete) VALUES (?, ?, ?);";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during prepare: " << sqlite3_errmsg(db) << std::endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, userDesc.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, userDueDate.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, 0);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "SQL error during step: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "\n------------------------------------\nTask added!\n------------------------------------" << std::endl;
	}

	sqlite3_finalize(stmt);
}


void TaskManager::UpdateTask(int userTaskId, const std::string& userDesc, const std::string& userDueDate)
{
	if (!FindTaskID(userTaskId)) {
		std::cout << "\n------------------------------------\nTask not found.\n------------------------------------" << std::endl;
		return;
	}

	const char* sql = "UPDATE tasks SET description = ?, due_date = ? WHERE id = ?;";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during prepare: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	sqlite3_bind_text(stmt, 1, userDesc.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, userDueDate.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, userTaskId);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "SQL error during step: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "\n------------------------------------\nTask updated successfully!\n------------------------------------" << std::endl;
	}

	sqlite3_finalize(stmt);
}

void TaskManager::CompleteTask(int userTaskId)
{
	if (!FindTaskID(userTaskId)) {
		std::cout << "\n------------------------------------\nTask not found.\n------------------------------------" << std::endl;
		return;
	}

	const char* sql = "UPDATE tasks SET is_complete = 1 WHERE id = ?;";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during prepare: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	sqlite3_bind_int(stmt, 1, userTaskId);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "SQL error during step: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "\n------------------------------------\nTask Completed!\n------------------------------------" << std::endl;
	}

	sqlite3_finalize(stmt);
}

void TaskManager::DeleteTask(int userTaskId)
{
	if (!FindTaskID(userTaskId)) {
		std::cout << "\n------------------------------------\nTask not found.\n------------------------------------" << std::endl;
		return;
	}

	const char* sql = "DELETE FROM tasks WHERE id = ?;";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during prepare: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	sqlite3_bind_int(stmt, 1, userTaskId);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "SQL error during step: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "\n------------------------------------\nTask Deleted!\n------------------------------------" << std::endl;
	}

	sqlite3_finalize(stmt);
}

void TaskManager::EmptyCompletedTasks() {
	const char* sql = "DELETE FROM tasks WHERE is_complete = 1;";
	char* errMsg = 0;

	int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else {
		std::cout << "\n------------------------------------\nCompleted tasks list cleared!\n------------------------------------" << std::endl;
	}
}

void TaskManager::PrintAllTasks(bool isComplete) const {
	const char* sql = "SELECT id, description, due_date FROM tasks WHERE is_complete = ?;";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error during prepare: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	sqlite3_bind_int(stmt, 1, isComplete ? 1 : 0);

	std::cout << (isComplete ? "\n--- Completed Tasks ---" : "\n--- Current Tasks ---") << std::endl;

	int rowCount = 0;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		rowCount++;
		int taskId = sqlite3_column_int(stmt, 0);
		const unsigned char* description = sqlite3_column_text(stmt, 1);
		const unsigned char* dueDate = sqlite3_column_text(stmt, 2);

		std::cout << taskId << ". " << "Description: " << description << ", Due Date:" << dueDate << std::endl;
	}

	if (rowCount == 0) {
		std::cout << "No tasks in this list.\n" << std::endl;
	}
	else {
		std::cout << "------------------------------------" << std::endl;
	}

	sqlite3_finalize(stmt);
}

bool TaskManager::ListEmpty(bool isComplete) {
	const char* sql = "SELECT COUNT(*) FROM tasks WHERE is_complete = ?;";
	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		return true;
	}

	sqlite3_bind_int(stmt, 1, isComplete ? 1 : 0);
	sqlite3_step(stmt);

	int count = sqlite3_column_int(stmt, 0);

	sqlite3_finalize(stmt);

	return (count == 0);
}


