//
// Created by Xinpeng Liu on 3/4/22.
//

#include "Stack.h"

template <class T>
Stack<T>::Stack()
{
    top = nullptr;
}

template <class T>
Stack<T>::~Stack()
{
    destroy();
}

template <class T>
Stack<T>::Stack(const Stack<T>& other)
{
    copy(other);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    // avoid self-copy
    if (this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return top == nullptr;
}

template <class T>
void Stack<T>::push(T item)
{
    /**
     * @CasesToConsider
     * 1. Stack is empty
     * 2. Stack has item
     */

    Node<T>* temp = top;        // let pointer "temp" points to where "top" points to

    top = new Node<T>;          // "top" create a new node
    top->info = item;           // assign value to the new node
    top->next = temp;           // build access from "new node" to "previous node" or "nullptr"

    temp = nullptr;             // for safety, set "temp" pointer to NULL
}

template <class T>
void Stack<T>::pop()
{
    /**
     * @CasesToConsider
     * 1. Stack is empty
     * 2. Stack has item
     */

    if (isEmpty())                           // if Stack is empty, don't pop anything
        cout << "Stack is empty, "
                "nothing to pop." << endl;
    else
    {
        Node<T>* temp = top;                // let "temp" pointer points to where top points to
        top = top->next;                    // move "top" to the next, it could be a node or nullptr
        temp->next = nullptr;               // for safety, removing access from current node to next node
        delete temp;                        // delete the current node

        temp = nullptr;                     // for safety, set the "temp" pointer to nullptr
    }
}

template <class T>
void Stack<T>::Top(T& container) const
{
    container = top->info;
}

template <class T>
void Stack<T>::destroy()
{
    Node<T>* temp = nullptr;
    while (!isEmpty())
    {
        temp = top;
        top = top->next;

        temp->next = nullptr;
        delete temp;
    }
    temp = nullptr;
}


