#pragma once
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>

template <typename T>
class priority_queue
{
private:
    struct Node
    {
        int priority;
        std::list<T> values;
    };

    int heapSize;
    int elementCount;
    std::vector<Node> binaryHeap;
    std::map<int, int> priorityToNodeIndex;

    int parentIndex(int i) const { return (i == 0) ? 0 : (i - 1) / 2; }
    int leftChildIndex(int i) const { return 2 * i + 1; }
    int rightChildIndex(int i) const { return 2 * i + 2; }

    void shiftUp(int i);
    void shiftDown(int i);

public:
    
    priority_queue();
    priority_queue(const priority_queue &src);
    priority_queue &operator=(const priority_queue &rhs);
    ~priority_queue() = default;

    
    size_t size() const;
    T &head();

    void enqueue(const T &element, int priority);
    void dequeue();
    void clear();
    void swap(priority_queue &other) noexcept;

    void serialize(std::ofstream &str) const;
    void deserialize(std::ifstream &out);
};
