// min binary heap based priority queue
#include "priorityQueue.h"

template <typename T>
class priority_queue
{
    struct Node
    {
        int priority;
        std::list<T> values;
    }

    int heapSize;
    int elementCount;
    std::vector<Node> binaryHeap;           // tuk shte pazq prioritetite
    std::map<int, int> priorityToNodeIndex; // self explanatory

    int parent(int i)
    {
        if (i != 0)
        {
            return (i - 1) / 2;
        }
        else
        {
            std::cout << "Already at root, returning 0";
            return 0;
        }
    }

    int leftChild(int i) { return (2 * i + 1); }

    int rightChild(int i) { return (2 * i + 2); }

    void shiftUp(int i)
    {
        while (i > 0 && binaryHeap[parent[i]].priority > binaryHeap[i].priority)
        {
            std::swap(priorityToNodeIndex.at(binaryHeap[parent[i]].priority),
                      priorityToNodeIndex.at(binaryHeap[i].priority));
            std::swap(binaryHeap[parent[i]], binaryHeap[i]);
            i = parent(i);
        }
    }

    void shiftDown(int i)
    {
        int maxIndex = i;
        int l = leftChild(i);
        if (l < this->heapSize && this->binaryHeap[l].priority < this->binaryHeap[maxIndex].priority)
            maxIndex = l;

        int r = rightChild(i);
        if (r < this->heapSize && this->binaryHeap[r].priority < this->binaryHeap[maxIndex].priority)
            maxIndex = r;

        if (maxIndex != i)
        {
            std::swap(priorityToNodeIndex.at(binaryHeap[maxIndex].priority),
                      priorityToNodeIndex.at(binaryHeap[i].priority));
            std::swap(binaryHeap[maxIndex], binaryHeap[i]);

            shiftDown(maxIndex);
        }
    }

public:
    priority_queue() : elementCount(0), heapSize(0) {}

    priority_queue(const priority_queue &src)
    {
        this->binaryHeap = src.binaryHeap;
        this->priorityToNodeIndex = src.priorityToNodeIndex;
        this->heapSize = src.heapSize;
        this->elementCount = src.elementCount;
    }

    priority_queue<T> &operator=(const priority_queue<T> &rhs)
    {
        std::map<int, int> safeMapCopy(rhs.priorityToNodeIndex);
        std::vector<Node> safeHeapCopy(rhs.binaryHeap);
        int elements = rhs.elementCount;
        int nodes = rhs.heapSize;

        std::swap(this->priorityToNodeIndex, safeMapCopy);
        std::swap(this->binaryHeap, safeHeapCopy);
        std::swap(this->elementCount, elements);
        std::swap(this->heapSize, nodes);

        return *this;
    }

    ~priority_queue() {}

    size_t size() const // O log 1
    {
        return this->elementCount;
    }

    T &head() // мисля че го показва само O(1)
    {
        return binaryHeap[0].values.front();
    }

    void enqueue(const T &element, int priority) // O log (n)
    {
        if (this->priorityToNodeIndex.contains(priority))
        {
            this->binaryHeap[priorityToNodeIndex.at(priority)].values.push_back(element);
            ++elementCount;
        }
        else
        {
            Node newNode;
            newNode.priority = priority;
            newNode.values.push_back(element);

            binaryHeap.push_back(newNode);
            priorityToNodeIndex[priority] = heapSize;
            
            shiftUp(heapSize);
            ++elementCount;
            ++heapSize;
        }
    }

    void dequeue() // маха главата на опашката O (log n)
    {
        --elementCount;
        binaryHeap[0].values.pop_front();
        
        if(binaryHeap[0].values.size() == 0)
        {
            
            priorityToNodeIndex.erase(binaryHeap[0].priority);
            binaryHeap[0] = binaryHeap.back();
            binaryHeap.pop_back();

            --heapSize;
            shiftDown(0);
        }
    }

    void clear() // изпразва опашката
    {
        binaryHeap.clear();
        priorityToNodeIndex.clear();
        heapSize = 0;
        elementCount = 0;
    }

    void swap(priority_queue &other) noexcept
    { // разменя съдържанието на два обекта за време O(1), nothrow
        std::swap(this->binaryHeap, other.binaryHeap);
        std::swap(this->priorityToNodeIndex, other.priorityToNodeIndex);
        std::swap(this->heapSize, other.heapSize);
        std::swap(this->elementCount, other.elementCount);
    }

    void serialize(ofstream &str) const // опашка-> поток
    // времева О(N). хващат се всички възможни грешки, ако не успее операцията да се хвърли изключение
    // не променя опашката по никакъв начинrhs
    {   
        str.exceptions(std::ios::failbit | std::ios::badbit);
        
        str<< this->heapSize << ' ' << this->elementCount << '\n';
        for(const Node& node: binaryHeap)
        {
            str << node.priority << ' ' << node.values.size() << ' ';

            for(const T& value: node.values)
            {
                str<< value << ' ';
            }
            
            str << '\n';
        }
    }

    void deserialize(ifstream &out) // поток -> опашка
    // ако вече има елементи, да се съхранят новите прочетени.
    // времева О(N)
    // хващат се всички грешки и ако не успее, се хвърля изглюючение.
    // strong exception safety
    {
        if(!out.is_open()) {std::cerr << "IFSTREAM ISN'T OPEN, RETURNING. NO CHANGES!"; return;}
        int copyHeapSize = 0;
        int copyElementCount = 0;
        std::vector<Node> copyHeap;
        std::map<int,int>copyToNodeIndex;

        out >> copyHeapSize >> copyElementCount;
        int priority = -1;
        int count = -1;
        int currentIndex = 0;
        while(out >> priority >> count)
        {
            Node newNode;
            newNode.priority = priority;

            for (int i = 0; i < count; ++i)
            {
                T temp;
                out >> temp;
                newNode.values.push_back(temp);
                ++copyElementCount;
            }

            copyHeap.push_back(newNode);
            copyToNodeIndex[priority] = currentIndex++;
            ++copyHeapSize;
        }
    
        swap(this->binaryHeap, copyHeap); 
        swap(this->priorityToNodeIndex,copyToNodeIndex);
        swap(this->elementCount,copyElementCount);
        swap(this->heapSize, copyHeapSize);
    }
};