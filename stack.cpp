#include "stack.h"
template <class T>
Stack<T>::Stack()
{
    top = NULL;
    count=0;
}
template <class T>
void Stack<T>::empty()
{
    stackNode<T> *p;
    while (!isEmpty())
    {
        p = top;
        top = top->next;
        delete p;
    }
    top = NULL;
    count = 0;
}
template <class T>
Stack<T>::~Stack()
{
    empty();
}
template <class T>
void Stack<T>::push(T item)
{
    stackNode<T> *p = new (std::nothrow) stackNode<T>;
    if (p)
    {
        p->data = item;
        p->next = top;
        top = p;
        count++;
    }
    else
        throw MemoryException();
}
template <class T>
T Stack<T>::pop()
{
    stackNode<T> *p;
    if (isEmpty())
        throw EmptyStackException();
    T item = top->data;
    p = top;
    top = top->next;
    count--;
    delete p;
    return item;
}
template <class T>
T Stack<T>::peep()
{
    if (isEmpty())
        throw EmptyStackException();
    return top->data;
}
