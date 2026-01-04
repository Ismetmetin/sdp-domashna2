#include "priorityQueue.h"
#include <iostream>
#include <random>

void printMenu()
{
    std::cout << "Select an option (1-4):\n1. N random generated elements and serialize queue into given file.\n";
    std::cout << "2.Input stable priority queue from file.\n3. Show all queue elements on screen.\n4.Exit\n";
}

void task1()
{
    
}

void task2()
{

}

void task3()
{

}

int main(int argc, char *argv[])
{
    printMenu();

    int options = -1;
    std::cin >> options;
    while (options != 4)
    {
        std::cout << "\n\n";
        printMenu();
        std::cin >> options;

        switch (options)
        {
        case 1:
            task1();
            break;

        case 2:
            task2();
            break;

        case 3:
            task3();
            break;
        }
    }

    std::cout << "Bye bye!\n"
}