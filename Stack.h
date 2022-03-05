/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 4, 2022                                               */
/* Purpose:  Definition of Stack class                               */
/* Stack class is implemented by using LinkedList                    */
/*********************************************************************/

#ifndef STACKARITHMETICEVALUATION_STACK_H
#define STACKARITHMETICEVALUATION_STACK_H

#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class Stack {
private:
    Node<T>* top;

    /**
     * @Brief destroy all the nodes in an stack object
     * @Detail all the nodes will be deleted and pointer
     * "top" will be set to nullptr
     */
    void destroy();

    /**
     * @Brief copy the information of another stack to the current stack
     * @Input a reference of another instantiated Stack object, and
     * const means this object can't be modified within this function
     */
    void copy(const Stack<T>&);

public:

    /**
     * @Brief default constructor of Stack class
     * @Detail it will set the pointer "top" to null
     */
    Stack();

    /**
     * @Brief destructor of Stack class
     * @Detail will call the destroy() function to
     * delete all the nodes
     */
    ~Stack();

    /**
     * @Brief copy constructor of Stack class
     * @Input a reference of instantiated Stack object, and
     * const means this object can't be modified within this function
     */
    Stack(const Stack<T>&);

    /**
     * @Brief overloading the operator=
     * @Detail it enables copying the value from another stack to
     * overwrite the current Stack who calls this function. This function
     * will firstly destroy() the current Stack, then implement copy().
     * @Input a reference of another instantiated Stack object, and
     * const means this object can't be modified within this function
     * @Output a reference of the current Stack object. This return value
     * will enable cascade equal between multiple Stack objects
     */
    Stack<T>& operator=(const Stack<T>&);

    /**
     * @Brief a function for judging whether the Stack is empty or not
     * @Output if the Stack is empty, the function returns TRUE,
     * otherwise it returns FALSE
     */
     bool isEmpty() const;

    /**
     * @Brief a function put an item into the stack
     * @Input the item which user want to put into the stack
     */
     void push(T);

    /**
     * @Brief a function removes the top item from the stack
     */
    void pop();

    /**
     * @Brief this functions is used to return the top item to the client.
     * The client will pass a container of type T into the function by reference,
     * and the function will assign the value of top item to the container.
     * @Input an reference of container the user pass in, which is used
     * to store the information of the top item.
     */
    void Top(T&) const;

};


#endif //STACKARITHMETICEVALUATION_STACK_H
