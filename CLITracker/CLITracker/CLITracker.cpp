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

    char select;

    do {
        std::cout << "Welcome to the Task Tracker!\nPress 1 to view current tasks.\nPress 2 to view completed tasks\nPress 3 to add tasks.\nPress 4 to quit." << std::endl;
        std::cin >> select;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (select == '1') {
            char choice;
            do {
                if (tasks.empty()) {
                    std::cout << std::endl << "No tasks currently in list" << std::endl;
                }
                else {
                    char mark;
                    do {
                        std::cout << "\n--- Current Tasks ---" << std::endl;
                        for (size_t i = 0; i < tasks.size(); ++i) {
                            std::cout << (i + 1) << ". " << "Description: " << tasks[i].description << ", Due Date:" << tasks[i].dueDate << std::endl;
                        }
                        std::cout << "------------------------------------" << std::endl;
                        std::cout << "Input task number to mark complete. E to exit." << std::endl;
                        std::cin >> mark;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (mark >= '1' && mark <= '9') {
                            int taskNumber = static_cast<int>(mark - '0') - 1;
                            if (taskNumber >= 0 && taskNumber < tasks.size()) {
                                completeTasks.push_back(tasks[taskNumber]);
                                tasks.erase(tasks.begin() + taskNumber);
                                std::cout << "Task Completed!" << std::endl;
                            }
                            else {
                                std::cout << "Invalid Number. Try again." << std::endl;
                            }
                        }
                    } while (mark != 'e' && mark != 'E' && tasks.size() > 0);
                }
                std::cout << "Back to menu? (Y/N): " << std::endl;
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }while (choice == 'n' || choice == 'N');
        }
        else if (select == '2') {
            char choice;
            if (completeTasks.empty()) {
                std::cout << "No tasks completed.\n";
            }
            else {
                std::cout << "\n--- Completed Tasks ---" << std::endl;
                for (size_t i = 0; i < completeTasks.size(); ++i) {
                    std::cout << (i + 1) << ". " << "Description: " << completeTasks[i].description << ", Due Date:" << completeTasks[i].dueDate << std::endl;
                }
                std::cout << "------------------------------------" << std::endl;
            }
            std::cout << "Back to menu? (Y/N): " << std::endl;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (select == '3') {
            char choice;
            do {
                std::string tempDescription;
                std::string tempDueDate;

                std::cout << std::endl << "Please enter a task description: " << std::endl;
                std::getline(std::cin, tempDescription);

                std::cout << "Please enter a due date (use YYYY-MM-DD): " << std::endl;
                std::cin >> tempDueDate;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Task newTask;
                newTask.description = tempDescription;
                newTask.dueDate = tempDueDate;


                tasks.push_back(newTask);
                std::cout << "Task added! Add another? (Y/N): ";
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
