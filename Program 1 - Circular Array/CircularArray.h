// STUDENT ORGANIC WAGYU CODE
// Author: Cody Chinothai
// San Diego State University
// CS210/CS496-01: Data Structures
//
// File: CircularArray.h
// Defines the CircularArray collection class.

#define VERSION_CIRARRAY 0.1

// STUDENT CODE
#ifndef PROG1_CIRCULARARRAY_H
#define PROG1_CIRCULARARRAY_H

#include "Queue.h"
#include "List.h"

namespace sdsu {
    template<typename T>
    class CircularArray : public sdsu::Queue<T>, public sdsu::List<T> {

    private:
        // Size represents how many T items the structure holds
        int curSize;

        // Capacity represents how many T items the structure CAN hold
        int curCapacity;

        // todo: head and tail counters for the circular nature
        int head;
        int tail;
        // the array on the heap
        T *storage;

        // dynamically resizes the array if the size reaches the capacity limit or if
        // the load factor reaches 0.5 or below (size <= capacity/2).
        T resizeArray(int a){
            T *newStorage;

            if(a == 0){
                newStorage = new T[curCapacity/2];
            }
            if(a == 1);{
                newStorage = new T[curCapacity*2];
            }

            //starting index relative to head that will copy into beginning of new array.
            int j = head;
            for(int i = 0; i < curCapacity; i++){
                newStorage[i] = storage[j];
                j = (j+1)%curCapacity;
            }

            if(a==0)
                curCapacity /= 2;
            if(a==1)
                curCapacity *= 2;
            delete[]storage;
            storage = newStorage;
            head = 0;
            tail = curSize-1;

        }
        //determines whether the passed in index is closer to the head or the tail.
        int findEnd(int idx){
            int mid = curSize/2;
            // index is closer to the head
            if(idx < mid){
                return 1;
            }
            //index is closer to the tail
            else{
                return 0;
            }
        }

        bool isFull(){
            return (curSize == curCapacity && curSize != 0) ;
        }


    public:

        // This is the default class constructor. It sets the current size to 0
        CircularArray() : curSize(0){
            // todo: initialize a default capacity storage array on the heap
            head = 0;
            tail = 0;
            storage = new T[16];
            curCapacity = 16;
        }

        // The copy constructor!
        CircularArray(const CircularArray<T> &other) : CircularArray() {
            std::cout << "Copying . . .";
            head = other.head;
            tail = other.tail;
            curCapacity = other.curCapacity;
            storage = new T[curCapacity];
            memcpy(storage,other.storage,curCapacity*sizeof(T));
        }

        ~CircularArray() override {
            delete[] storage;
        }

        void clear() override {
            // size == 0, and the capacity and dynamic array should
            // shrink back to its default size. There is a potential
            // for a memory leak here.
            delete[] storage;
            curSize = 0;
            curCapacity = TEST_START_SIZE; // define a default parameter later.
            storage = new T[curCapacity];
            head = 0;
            tail = 0;
        }

        T dequeue() override {
            T ret = storage[head];
            //storage[head] = null
            head++;
            return ret;
        }

        bool enqueue(T t) override {
            //circular array is full
            if(isFull()) {
                //return false;
                resizeArray(1);
            }
            //circular array is empty
            if(isEmpty()){
                head = 0;
                tail = 0;
                //storage[head] = t;
            }

            curSize++;
            if(curSize > 1)
                tail = (tail+1)%curCapacity;
            storage[tail] = t;




            return true;
        }

        bool isEmpty() const override {
            return size() == 0;
        }

        //returns the object at the head of the circular array.
        T& peek() override {
            if( curSize > 0)
                return storage[head];
        }

        T& get(int idx) override {
            if( idx > curSize-1 || idx < 0)
                throw std::out_of_range("CircularArray<T>::get(idx) : index out of range.");
            return storage[(head+idx)%curCapacity];
            //idx-1 >= curCapacity



        }

        bool insert(int idx, T t) override {
            if(isFull()){
                resizeArray(1);
            }
            // index relative to the head
            int focus = (head+idx)%curCapacity;


            //focus closer to head: move objects left of the head one space to the left
            //insert the desired object at the focus index.
            if(findEnd(focus) == 1){
                int leftOfHead = (head-1+curCapacity)%curCapacity;
                for(int i = leftOfHead; i< focus; i++){
                    storage[i] = storage[(i+1)%curCapacity];
                }

                storage[focus] = t;
                head = leftOfHead;
            }
            //focus closer to tail: move objects right of the tail one space to the right
            //insert the desired object at the focus index
            if(findEnd(focus) == 0){
                int rightOfTail = (tail+1)%curCapacity;
                for(int i = rightOfTail; i > focus; i--){
                    storage[i] = storage[(i-1+curCapacity)%curCapacity];
                }

                storage[focus] = t;
                tail = rightOfTail;
            }

            curSize++;
            return true;
        }

        bool addFirst(T t) override {
            // a well written insert method makes this a single line.
            return insert(0,t);

        }

        bool addLast(T t) override {
            // a well written insert method makes this a single line.
            return insert(size(),t);

        }

        T remove(int idx) override {
            if(curSize <= curCapacity / 2)
                resizeArray(0);
            // Figure out if the target index is closer to the front or back
            // and then shuffle from that index (tail or head).
            if( idx > curSize || idx < 0)
                throw std::out_of_range("CircularArray<T>::remove(i) : index out of range.");
            //index relative to the head
            int focus = (head+idx)%curCapacity;
            // index is closer to the head
            if(findEnd(focus) == 1){
                //moving objects over starting from the head (left side) to the right
                for(int i = focus - 1 ; i > head; i--){
                    storage[i+1] = storage[i];
                }
                head++;

            }
            // closer to the tail
            if(findEnd(focus) == 0){
                //move things over starting from the right side to the left
                for(int i = focus+1 ; i < curSize; i++){
                    storage[i-1] = storage[i];
                }
                tail--;
            }
            curSize--;



        }

        T removeFirst() override {
            // If you wrote remove correctly, this can be a single line.
            // you *might* want to clean up any exception handling though . . . .
            remove(head);
        }

        T removeLast() override {
            // If you wrote remove correctly, this can be a single line.
            // you *might* want to clean up any exception handling though . . . .
            remove(tail);
        }

        void set(int idx, T value) override {
            if(idx > curCapacity)
                throw std::out_of_range("CircularArray<T>::set(idx,value) : index out of range.");
            int headRelativeidx = (head+idx)%curCapacity;
            storage[headRelativeidx] = value;
        }

        int size() const override {
            return curSize;

        }
    };
}

#endif //PROG1_CIRCULARARRAY_H
