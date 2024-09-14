#ifndef CIRCULARQUEUETESTS_H
#define CIRCULARQUEUETESTS_H

#include "circularqueue.h"
#include <stdexcept>

#define TEST(function) \
if(!function()) \
    throw std::runtime_error(std::string(#function) + "() failed!");

class CircularQueueTests
{
public:
    bool testAll() const;
    bool testPush() const;
    bool testPop() const;
    bool testSize() const;
    bool testEmpty() const;
private:
    bool testPushToFullQueue() const;
    bool testPushFewTimes() const;
    bool testPopFromEmptyQueue() const;
    bool testPopFewTimes() const;
};

bool CircularQueueTests::testAll() const
{
    TEST(testPush);
    TEST(testPop);
    TEST(testSize);
    TEST(testEmpty);
    return true;
}

bool CircularQueueTests::testPush() const
{
    TEST(testPushToFullQueue);
    TEST(testPushFewTimes);
    return true;
}

bool CircularQueueTests::testPushToFullQueue() const
{
    CircularQueue<int, 0> queue;
    try
    {
        queue.push(1);
    }
    catch(std::runtime_error& error)
    {
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}

bool CircularQueueTests::testPushFewTimes() const
{
    CircularQueue<int, 2> queue;
    queue.push(1);
    queue.push(2);
    if(queue.back() != 2)
        return false;
    queue.pop();
    queue.push(3);
    if(queue.back() != 3)
        return false;
    queue.pop();
    queue.pop();
    queue.push(4);
    if(queue.back() != 4)
        return false;
    return true;
}


bool CircularQueueTests::testPop() const
{
    TEST(testPopFromEmptyQueue);
    TEST(testPopFewTimes);
    return true;
}

bool CircularQueueTests::testPopFromEmptyQueue() const
{
    CircularQueue<int, 0> queue;
    try
    {
        queue.pop();
    }
    catch(std::runtime_error& error)
    {
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}

bool CircularQueueTests::testPopFewTimes() const
{
    CircularQueue<int, 2> queue;
    queue.push(1);
    queue.push(2);
    queue.pop();
    if(queue.front() != 2)
        return false;
    queue.push(3);
    queue.pop();
    queue.pop();
    if(!queue.empty())
        return false;
    return true;
}

bool CircularQueueTests::testSize() const
{
    CircularQueue<int, 5> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    if(queue.size() != 3)
        return false;
    queue.push(4);
    queue.push(5);
    if(queue.size() != 5)
        return false;
    queue.pop();
    queue.pop();
    queue.push(6);
    queue.pop();
    queue.push(7);
    if(queue.size() != 4)
        return false;
    return true;
}

bool CircularQueueTests::testEmpty() const
{
    CircularQueue<int, 2> queue;
    if(!queue.empty())
        return false;
    queue.push(1);
    if(queue.empty())
        return false;
    queue.pop();
    if(!queue.empty())
        return false;
    queue.push(2);
    queue.push(3);
    queue.pop();
    queue.push(4);
    queue.pop();
    queue.pop();
    return queue.empty();
}

#endif
