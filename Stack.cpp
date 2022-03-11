/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 7, 2022                                               */
/* Purpose: Implementation of Stack class                            */
/*********************************************************************/

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

    if(!isEmpty())                          // if Stack is empty, don't pop anything
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
    if(!isEmpty())                          // if the Stack is empty, return nothing
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

template <class T>
void Stack<T>::copy(const Stack<T> & other)
{
    /**
     * @CasesToConsider
     * 1. Other Stack is empty
     * 2. Other Stack has item
     */

    if (other.top == nullptr)                   // when the other Stack is empty
        top == nullptr;
    else                                        // when the other Stack is not empty
    {
        top = new Node<T>;                      // these 3 lines copy the first node
        top->next = nullptr;
        top->info = other.top->info;

        Node<T>* p = other.top->next;           // p will walk the other Stack
        Node<T>* q = top;                       // q will walk, create node and copy info to this Stack

        while (p != nullptr)                    // only if p is not NULL, q take action
        {
            q->next = new Node<T>;              // q create a new node
            q->next->next = nullptr;            // set "next" of new node to NULL for safety
            q->next->info = p->info;            // copy info to the new node

            q = q->next;                        // q and p both walks to the next location
            p = p->next;
        }

        p = nullptr;                            // for safety, set both p and q to NULL after use
        q = nullptr;
    }
}

template <class T>
void Stack<T>::printStack()
{
    while (!isEmpty())                           // while the stack is not empty
    {
        T temp;
        Top(temp);                            // save the value of top item of stack to a variable
        pop();                                   // remove the top item from stack
        cout << temp << endl;                    // print the value of top item
    }
    cout << endl;
}

