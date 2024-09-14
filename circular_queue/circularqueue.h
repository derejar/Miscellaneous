#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <utility>
#include <iterator>
#include <stdexcept>

template <typename T, std::size_t MAX_SIZE>
class CircularQueue
{
public:
    void push(const T& value);
    void pop();
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    bool empty() const;
    std::size_t max_size() const;
    std::size_t size() const;
private:
    std::size_t m_front = 0;
    std::size_t m_back = 0;
    T m_queue[MAX_SIZE + 1]{};
};

template <typename T, std::size_t MAX_SIZE>
void CircularQueue<T, MAX_SIZE>::push(const T& value)
{
    if(size() == MAX_SIZE)
        throw std::runtime_error("Impossible to push element into full queue!");
    m_queue[m_back] = value;
    m_back = (m_back + 1) % (MAX_SIZE + 1);
}

template <typename T, std::size_t MAX_SIZE>
void CircularQueue<T, MAX_SIZE>::pop()
{
    if(empty())
        throw std::runtime_error("Impossible to extract element from empty queue!");
    m_front = (m_front + 1) % (MAX_SIZE + 1);
}

template <typename T, std::size_t MAX_SIZE>
T& CircularQueue<T, MAX_SIZE>::front()
{
    return m_queue[m_front];
}

template <typename T, std::size_t MAX_SIZE>
T& CircularQueue<T, MAX_SIZE>::back()
{
    if(m_back == 0)
        return m_queue[MAX_SIZE];
    return m_queue[m_back - 1];
}

template <typename T, std::size_t MAX_SIZE>
const T& CircularQueue<T, MAX_SIZE>::front() const
{
    return m_queue[m_front];
}

template <typename T, std::size_t MAX_SIZE>
const T& CircularQueue<T, MAX_SIZE>::back() const
{
    if(m_back == 0)
        return m_queue[MAX_SIZE];
    return m_queue[m_back - 1];
}

template <typename T, std::size_t MAX_SIZE>
bool CircularQueue<T, MAX_SIZE>::empty() const
{
    return m_front == m_back;
}

template <typename T, std::size_t MAX_SIZE>
std::size_t CircularQueue<T, MAX_SIZE>::max_size() const
{
    return MAX_SIZE;
}

template <typename T, std::size_t MAX_SIZE>
std::size_t CircularQueue<T, MAX_SIZE>::size() const
{
    if(m_back < m_front)
        return m_back + (MAX_SIZE + 1) - m_front;
    return m_back - m_front;
}

#endif
