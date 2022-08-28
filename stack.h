#include <exception>
struct MemoryException: public std::exception{
    const char * what () {
        return "Unable to allocate memory for a stack node!";
    }
};
struct EmptyStackException: public std::exception{
    const char * what () {
        return "Popping an empty stack!";
    }
};
template <class T>
struct stackNode
{
    T data;
    stackNode<T> *next;
};
template <class T>
class Stack
{
public:
    Stack();
    virtual ~Stack();
    void push(T data);
    T pop();
    T peep();
    bool isEmpty() { return count == 0; }
    int getCount() { return count; }
    void empty();

private:
    stackNode<T> *top;
    int count;
};
