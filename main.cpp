#include "priorityQueue.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

void printMenu()
{
    std::cout << "Select an option (1-4):\n1. N random generated elements and serialize queue into given file.\n";
    std::cout << "2.Input stable priority queue from file.\n3. Show all queue elements on screen.\n4.Exit\n";
}

void task1()
{
    priority_queue<int> pq;
    std::cout << "Please enter an integer and a path to a file in this format -> N path\n";

    int N;
    std::string path;
    std::cin >> N >> path;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < N; ++i)
    {
        int value = rand() % 100 + 1;
        int priority = rand() % 35 + 1;
        pq.enqueue(value, priority);
    }

    std::ofstream ofs(path);
    if (!ofs.is_open())
    {
        std::cerr << "Could not open file for writing: " << path << '\n';
        return;
    }

    pq.serialize(ofs);
}

void task2(priority_queue<int> &pq)
{
    priority_queue<int> copyPq;
    std::cout << "Please enter path to file:\n";
    std::string path;
    std::cin >> path;
    std::ifstream ifs(path);

    if (!ifs.is_open())
    {
        std::cerr << "Could not open file for reading: " << path << '\n';
        return;
    }

    copyPq.deserialize(ifs);

    pq.swap(copyPq);
}

void task3(priority_queue<int> pq)
{
    std::cout<< "Elements in priority_queue: " << pq.size();
    while(pq.size() != 0)
    {
        std::cout<< pq.head() << '\n';
        pq.dequeue();
    }
}

int main(int argc, char *argv[])
{
    printMenu();
    priority_queue<int> pqMain;

    int options = -1;
    std::cin >> options;
    while (options != 4)
    {
        std::cout << "\n\n";

        switch (options)
        {
        case 1:
            task1();
            break;

        case 2:
            task2(pqMain);
            break;

        case 3:
            task3(pqMain);
            break;
        }
        printMenu();
        std::cin >> options;
    }

    std::cout << "Bye bye!\n";
}