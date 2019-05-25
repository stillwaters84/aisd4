//
// Created by Kendrick on 11.03.2019.
//

//#ifndef NUMBERC1_MYLIST_H
//#define NUMBERC1_MYLIST_H

//#endif //NUMBERC1_MYLIST_H
#pragma once
#include <cassert>
#include <list>
#include <iostream>
//#include "HuffTree.h"

using namespace std;

template <class T> class MyList;

template <class T>
class NodeList{
public:
    NodeList<T>(T number, NodeList<T>*next = nullptr){ 
        this->number = number; 
        this->next = next;
    }
    ~NodeList<T>(){};
    T number;
    NodeList<T> *next;
    friend class MyList<T>;
};

template <class T>
class MyList {
public:
    NodeList<T> *first;
    NodeList<T> *last;
    size_t size;
    MyList();
    void addfirst(T newElem);
    void clear();
    void push_back(T LastElem);
    void push_front(T FirstElem);
    void pop_back();
    void pop_front();
    bool isEmpty();
    void insert (int index, T newElem);
    T at(int index);
    void set(int index, int newElem);
    void remove(int index);
    size_t get_size() const;
	int findMin();
	//friend class HuffLeaf;

    friend std::ostream& operator<< (std::ostream &out, const MyList<T> &list){
        NodeList<T> *tmp = list.first;
        std::cout << "Size: " << list.get_size() << std::endl;
        std::cout << "List: ";
        while (tmp){
            std::cout << tmp->number << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
        return out;
    }
};

template <class T>
MyList<T>::MyList() {
    this->first = nullptr;
    this->last = nullptr;
    size=0;
}

template <class T>
void MyList<T>::addfirst(T newElem){
    NodeList<T> *newNode = new NodeList<T> (newElem);
    this->first = newNode;
    this->last = newNode;
    this->last->next = nullptr;
    this->size = 1;
}

template <class T>
int MyList<T>::findMin() {
    if (get_size() == 0)
        return -1;
    auto minElem = first;
    int minIndex = 0;
	auto tmp = first->next;
    int currIndex = 1;
    while (tmp){
        if (*(tmp->number) < *(minElem->number)){
            minElem = tmp;
            minIndex = currIndex;
        }
        tmp = tmp->next;
        currIndex++;
    }
    return minIndex;
}

template <class T>
void MyList<T>::clear(){
    NodeList<T> *newNode;
    if(size!=0) {
        for (int i = 0; i < size; i++) {
            if (this->first != this->last) {
                newNode = this->first;
                this->first = this->first->next;
                delete newNode;
            } else
                delete this->last;
        }
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
        cout << "List is empty!" << endl;
    } else cout << "List already empty!" << endl;
}

template <class T>
size_t MyList<T>::get_size() const {
    // cout << "Size is: " << this->size << endl;
    return size;
}

template <class T>
void MyList<T>::push_back(T LastElem){
    NodeList<T> *newNode;
    newNode = new NodeList<T>(LastElem);
    if (this->size == 0){
        addfirst(LastElem);
    }
    else {
        last->next= newNode;
        last = last->next;
        this->size++;
    }
}

template <class T>
void MyList<T>::push_front(T FirstElem){
    NodeList<T> *newNode;
    newNode = new NodeList<T>(FirstElem);
    newNode->next = this->first;
    this->first = newNode;
    this->size++;
}

template <class T>
void MyList<T>::pop_back(){
    if (this->size == 0){     //if the list is empty
        return;
    }
    if (this->size == 1){     //if there is only one element in list
        delete this->last;
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
    }
    if (this->size > 1){
        NodeList<T> *newNode;
        newNode = this->first;
        for (int i=0; i<size-1; i++){
            newNode = newNode->next;
        }
        delete newNode->next;
        this->last = newNode;
        newNode->next = nullptr;
        this->size--;
    }
}

template <class T>
void MyList<T>::pop_front(){
    if (this->size == 0){     //if the list is empty
        return;
    }
    if (this->size == 1){     //if there is only one element in list
        delete this->first;
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
    }
    if (this->size > 1){
        NodeList<T> *newNode;
        newNode = this->first->next;
        delete this->first;
        this->first = newNode;
        this->size--;
    }
}

template <class T>
bool MyList<T>::isEmpty(){
    if (size == 0){
        cout << "List is empty!" << endl;
        return true;
    } else {
        cout << "List is not empty!" << endl;
        return false;
    }
}

template <class T>
void MyList<T>::insert(int index, T newElem){  ///algorithm be like "index 4, we found 3, new will be 4, new->next is 5"
    if (index <=size && index >=0) {
        NodeList<T> *oldNode = this->first;
        NodeList<T> *newNode;
        newNode = new NodeList<T>(newElem);
        for (int i = 0; i < index - 1; i++) {    ///finding index-1 element
            oldNode = oldNode->next;
        }
        newNode->next = oldNode->next;
        oldNode->next = newNode;
        this->size++;
    }
    else cout << "Can't insert element" << endl;
}

template <class T>
T MyList<T>::at(int index){  ///need to check, are this index exists?(!!!!)
    auto newNode = first;
    if(index <= this->size && index >=0) {
        for (int i = 0; i < index; i++) {
            newNode = newNode->next;
        }
        // cout << "Data at this index is: " << newNode->number << endl;
    }
    else {
        throw "At errroe!\n";
    }
    // else cout << "There is no element with this index!" << endl;
    return newNode->number;
}

template <class T>
void MyList<T>::set(int index, int newElem){
    if (index <= this->size && index>=0) {
        NodeList<T> *oldNode = this->first;
        for (int i = 0; i < index; i++) {
            oldNode = oldNode->next;
        }
        oldNode->number = newElem;
    }
    else {
        cout << "Index is too big!" << endl;
        return;
    }
}

template <class T>
ostream& operator<< (ostream &out, const MyList<T> &myList){
    NodeList<T> *newNode;
    newNode = myList.first;
    for (int i = 0; i<myList.size; i++){
        out << "Index: " << i << "; Element: " << newNode->number << endl;
        newNode = newNode->next;
    }
    return out;
}


template <class T>
void MyList<T>::remove(int index){
    if(index <= this->size && index>=0) {
        NodeList<T> *deletingNode = first;
        NodeList<T> *prev = nullptr;
        for (int i = 0; i < index; i++) {
            prev = deletingNode;
            deletingNode = deletingNode->next;
        }
        if (deletingNode == first){ // prev == nullptr
            assert(!prev);
            first = first->next;
        } else
        if (deletingNode == last){
            prev->next = nullptr;
            last = prev;
        }
        else {
            prev->next = deletingNode->next;
        }
        delete deletingNode;
        size--;
    } else cout << "There is no element with this index!" << endl;
}