// CLITracker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>
#include <regex>
#include "Task.h"
#include "TaskManager.h"

int main()
{
    TaskManager taskManager;
    char select;

    do {
        std::cout << "\n------------------------------------\n";
        std::cout << "Welcome to the Task Tracker!\n------------------------------------\n\nPress 1 to view current tasks.\nPress 2 to view completed tasks\nPress 3 to add tasks.\nPress 4 to quit." << std::endl;
        std::cin >> select;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (select == '1') {
            int taskId;

            do {
                taskManager.PrintAllTasks(false);
                if (!taskManager.ListEmpty(false)) {
                    std::cout << "\nInput task ID to select a task. Enter 0 to return to the main menu.\n" << std::endl;
                    std::cin >> taskId;

                    if (std::cin.fail()) {
                        std::cout << "\n------------------------------------\nInvalid input. Please enter a number.\n------------------------------------\n" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (taskId != 0) {
                        char subSelect;
                        std::cout << "\nTask " << taskId << " selected. Press 'M' to mark complete, 'D' to delete, 'U' to update or 'R' to return to selection.\n" << std::endl;
                        std::cin >> subSelect;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (subSelect == 'm' || subSelect == 'M') {
                            taskManager.CompleteTask(taskId);
                        }
                        else if (subSelect == 'd' || subSelect == 'D') {
                            taskManager.DeleteTask(taskId);
                        }
                        else if (subSelect == 'u' || subSelect == 'U') {
                            std::string tempDescription;
                            std::string tempDueDate;

                            std::cout << "\nUpdate Description: " << std::endl;
                            std::getline(std::cin, tempDescription);

                            const std::regex datePattern("\\d{4}-\\d{2}-\\d{2}");
                            do {
                                std::cout << "\nUpdate due date (use YYYY-MM-DD): " << std::endl;
                                std::cin >> tempDueDate;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                                if (!std::regex_match(tempDueDate, datePattern)) {
                                    std::cout << "\n------------------------------------\nInvalid date format. Please use YYYY-MM-DD.\n------------------------------------\n" << std::endl;
                                }
                            } while (!std::regex_match(tempDueDate, datePattern));

                            taskManager.UpdateTask(taskId, tempDescription, tempDueDate);
                        }
                    }
                }
                else
                    taskId = 0;
            } while (taskId != 0);
        }
        else if (select == '2') {
            char choice;
            do {
                taskManager.PrintAllTasks(true);
                if (!taskManager.ListEmpty(true)) {
                    std::cout << "\nPress C to clear list, R to return\n";
                    std::cin >> choice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (choice == 'c' || choice == 'C')
                        taskManager.EmptyCompletedTasks();
                }
                else
                    choice = 'r';
            } while (choice != 'r' && choice != 'R');
        }
        else if (select == '3') {
            char choice;
            do {
                std::string tempDescription;
                std::string tempDueDate;

                std::cout << std::endl << "Please enter a task description: " << std::endl;
                std::getline(std::cin, tempDescription);

                const std::regex datePattern("\\d{4}-\\d{2}-\\d{2}");
                do {
                    std::cout << "\nPlease enter a due date (use YYYY-MM-DD): " << std::endl;
                    std::cin >> tempDueDate;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (!std::regex_match(tempDueDate, datePattern)) {
                        std::cout << "\n------------------------------------\nInvalid date format. Please use YYYY-MM-DD.\n------------------------------------\n" << std::endl;
                    }
                } while (!std::regex_match(tempDueDate, datePattern));

                taskManager.AddTask(tempDescription, tempDueDate);

                std::cout << "\nTask added! Add another? (Y/N): ";
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            } while (choice == 'y' || choice == 'Y');
        }
        else if (select == '4') {
            return 0;
        }
        else {
            std::cout << "\nInvalid input. please enter 1, 2, 3 or 4\n";
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
