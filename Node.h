/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 7, 2022                                               */
/* Purpose: Definition of Node Struct                                */
/*********************************************************************/

#ifndef STACKARITHMETICEVALUATION_NODE_H
#define STACKARITHMETICEVALUATION_NODE_H

template <class T>
struct Node {
    T info;
    Node<T>* next;
};


#endif //STACKARITHMETICEVALUATION_NODE_H
