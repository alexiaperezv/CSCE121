#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
class DoublyLinkedList
{
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList();
    DoublyLinkedList(T data);
    DoublyLinkedList(const DoublyLinkedList<T> &oldList);
    DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &oldList);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T &front() { return head->data; }
    const T &front() const { return head->data; }
    T &back() { return tail->data; }
    const T &back() const { return tail->data; }
    void push_back(T data);
    void push_front(T data);
    void pop_back();
    void pop_front();
    void erase(unsigned int idx);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream &operator<<(std::ostream &, DoublyLinkedList<T> const &);

template <typename T>
bool operator==(DoublyLinkedList<T> const &, DoublyLinkedList<T> const &);

template <typename T>
bool operator!=(DoublyLinkedList<T> const &, DoublyLinkedList<T> const &);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl
       << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" << std::setw(16) << "node.next" << std::endl;
    while (curr)
    {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0)
{
    //std::cout << "Default Constructor" << std::endl;
} // Default Constructor

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) : head(nullptr), tail(nullptr), sz(0)
{
    Node<T> *newNode = new Node<T>(data);
    head = newNode;
    tail = newNode;
    sz++;
} // Overloaded Constructor

/*
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &oldList) : head(oldList.head), tail(oldList.tail), sz(oldList.sz) {std::cout << "Copy Constructor" << std::endl;} // Copy Constructor
*/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &oldList) : head(nullptr), tail(nullptr), sz(0)
{
    //std::cout << "Copy Constructor" << std::endl;
    Node<T>* current = oldList.head;
    for(unsigned int i = 0; i < oldList.sz; i++)
    {
        push_back(current->data);
        current = current->next;
    }
} // Copy Constructor

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &oldList)
{
    //std::cout << "Copy Assignment" << std::endl;
    clear();
    Node<T>* current = oldList.head;
    for(unsigned int i = 0; i < oldList.sz; i++)
    {
        this->push_back(current->data);
        current = current->next;
    }
    return *this;
} // Copy Assignment Operator



template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
} // Destructor

template <typename T>
void DoublyLinkedList<T>::push_back(T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (tail != nullptr)
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }
    sz++;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (head != nullptr)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }
    sz++;
}

template <typename T>
void DoublyLinkedList<T>::pop_back()
{
    if(sz > 0){
        Node<T> *temp = tail;
        tail = tail->prev;
        if(tail == nullptr)
            head = nullptr;
        else
            tail->next = nullptr;
        delete temp;
        sz--;
    }
}

template <typename T>
void DoublyLinkedList<T>::pop_front()
{
    if(sz > 0){
        Node<T> *temp = head;
        head = head->next;
        if(head == nullptr)
            tail = nullptr;
        else
            head->prev = nullptr;
        delete temp;
        sz--;   
    }
}

template <typename T>
void DoublyLinkedList<T>::erase(unsigned int idx){
    if(idx < sz){
        if(idx == 0){
            pop_front();
        }
        else if(idx == sz-1){
            pop_back();
        }
        else{
            Node<T>* current = head;
            for(unsigned int i = 0; i < idx; i++){
                current = current->next;
            }
            // delete current
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            sz--;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx){
    if(idx <= sz){
        if(idx == 0){
            push_front(data);
        }
        else if(idx == sz){
            push_back(data);
        }
        else{
            Node<T>* current = head;
            for(unsigned int i = 0; i < idx; i++){
                current = current->next;
            }
            Node<T>* newNode = new Node<T>(data);
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
            sz++;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    Node<T> *current = head;
    Node<T> *next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }
    sz = 0;
    head = nullptr;
    tail = nullptr;
} // Clears linked list

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool operator==(DoublyLinkedList<T> const &lhs, DoublyLinkedList<T> const &rhs)
{
    if(lhs.size() == rhs.size()){
        Node<T>* lhsCurrent = lhs.head;
        Node<T>* rhsCurrent = rhs.head;
        for(unsigned int i = 0; i < rhs.size(); i++){
            if(*lhsCurrent != *rhsCurrent)
                return false;
            lhsCurrent = lhsCurrent->next;
            rhsCurrent = rhsCurrent->next;
        }
        return true;
    }
    return false;
}

template <typename T>
bool operator!=(DoublyLinkedList<T> const &lhs, DoublyLinkedList<T> const &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, DoublyLinkedList<T> const &rhs)
{
    os << rhs.to_str();
    return os;
}

#endif
