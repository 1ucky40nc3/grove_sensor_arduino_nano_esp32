#pragma once

#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class AbstractQueue
{
protected:
    vector<T> queue;
    AbstractQueue(vector<T> queue) : queue(queue) {};

public:
    virtual void add(T item) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() = 0;
    virtual ~AbstractQueue() = default;
};

template <typename T>
class SequencedQueue : public AbstractQueue<T>
{
public:
    SequencedQueue() : AbstractQueue<T>({}) {} // Initialize with empty vector

    void add(T item) override
    {
        this->queue.push_back(item);
    }

    T pop() override
    {
        if (isEmpty())
        {
            throw out_of_range("Queue is empty!");
        }
        T item = this->queue.front();
        this->queue.erase(this->queue.begin());
        return item;
    }

    bool isEmpty() override
    {
        return this->queue.empty();
    }
};