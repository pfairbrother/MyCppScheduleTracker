// CLITracker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>
#include "Task.h"

int main()
{
    std::vector<Task> tasks;
    std::vector<Task> completeTasks;
    int nextTaskId = 1;

    char select;

    do {
        std::cout << "\n------------------------------------\n";
        std::cout << "Welcome to the Task Tracker!\n------------------------------------\n\nPress 1 to view current tasks.\nPress 2 to view completed tasks\nPress 3 to add tasks.\nPress 4 to quit." << std::endl;
        std::cin >> select;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (select == '1') {

                if (tasks.empty()) {
                    std::cout << std::endl << "------------------------------------\nNo tasks currently in list\n------------------------------------" << std::endl;
                }
                else {
                    int mark;
                    do {
                        std::cout << "\n--- Current Tasks ---" << std::endl;
                        for (size_t i = 0; i < tasks.size(); ++i) {
                            std::cout << tasks[i].taskID << ". " << "Description: " << tasks[i].description << ", Due Date:" << tasks[i].dueDate << std::endl;
                        }
                        std::cout << "------------------------------------" << std::endl;
                        std::cout << "\nInput task ID to select task. 0 to exit." << std::endl;
                        std::cin >> mark;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (mark != 0) {
                            size_t foundIndex = (size_t)-1;
                            for (size_t i = 0; i < tasks.size(); ++i) {
                                if (tasks[i].taskID == mark) {
                                    foundIndex = i;
                                    break;
                                }
                            }
                            if (foundIndex == (size_t)-1) {
                                std::cout << std::endl << "------------------------------------\nTask not found.\n------------------------------------" << std::endl;
                            }
                            else {
                                char action;
                                std::cout << std::endl << "Task " << mark << " selected. Press M to mark complete, D to delete, U to update or R to return to selection." << std::endl;
                                std::cin >> action;
                                if (action == 'm' || action == 'M') {
                                    completeTasks.push_back(tasks[foundIndex]);
                                    tasks.erase(tasks.begin() + foundIndex);
                                    std::cout << "\n------------------------------------\nTask Completed!\n------------------------------------" << std::endl;
                                }
                                else if (action == 'd' || action == 'D') {
                                    tasks.erase(tasks.begin() + foundIndex);
                                    std::cout << "\n------------------------------------\nTask Deleted!\n------------------------------------" << std::endl;
                                }
                                else if (action == 'u' || action == 'U') {
                                    //ADD UPDATE ACTION HERE!!!!
                                }
                            }
                        }
                    } while (mark != 0 && tasks.size() > 0);
                }
        }
        else if (select == '2') {
            char choice;
            if (completeTasks.empty()) {
                std::cout << "\n------------------------------------\nNo tasks completed.\n------------------------------------\n";
            }
            else {
                std::cout << "\n--- Completed Tasks ---" << std::endl;
                for (size_t i = 0; i < completeTasks.size(); ++i) {
                    std::cout << completeTasks[i].taskID << ". " << "Description: " << completeTasks[i].description << ", Due Date:" << completeTasks[i].dueDate << std::endl;
                }
                std::cout << "------------------------------------" << std::endl;
            }
        }
        else if (select == '3') {
            char choice;
            do {
                std::string tempDescription;
                std::string tempDueDate;

                std::cout << std::endl << "Please enter a task description: " << std::endl;
                std::getline(std::cin, tempDescription);

                std::cout << "\nPlease enter a due date (use YYYY-MM-DD): " << std::endl;
                std::cin >> tempDueDate;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Task newTask;
                newTask.taskID = nextTaskId++;
                newTask.description = tempDescription;
                newTask.dueDate = tempDueDate;
                newTask.isComplete = false;


                tasks.push_back(newTask);
                std::cout << "\nTask added! Add another? (Y/N): ";
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            } while (choice == 'y' || choice == 'Y');
        }

    } while (select != '4');

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
