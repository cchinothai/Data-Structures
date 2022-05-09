// STUDENT CODE
// Author: Cody Chinothai
// San Diego State University
// CS210/CS496: Data Structures
//
// File: BinarySearchTree.h
//
// A concrete implementation of a basic binary search tree. This structure is
// useful only for education and illustration of the BAD things about growth.
//
// Additional Reading:
// https://en.wikipedia.org/wiki/Binary_search_tree


#ifndef PROG2_BINARYSEARCHTREE_H
#define PROG2_BINARYSEARCHTREE_H

#include <memory>

#include "Map.h"

namespace sdsu {
    template<typename KEY, typename VALUE>
    class BinarySearchTree : public sdsu::Map<KEY,VALUE> {

        // The BST links together BSTNode objects. The outside world never
        // needs to use these, but this data structure will use them to build
        // the search tree.
        struct BSTNode {

            // The BST structures itself around the KEY's ranking. The key is
            // so important, it must be unique in the BST.
            KEY key;


            // The value will almost certainly not be a void*, but this allows
            // us to store ANYTHING, for we can cast a void* into something else
            // void* is an address to anything . . . not nothingness. Values
            // in a map may be repeated, and values don't appear in a Set.
            VALUE value;
            //COLOR col;
            std::shared_ptr<BSTNode> childL;
            //std::shared_ptr<BSTNode> childM;
            std::shared_ptr<BSTNode> childR;

            BSTNode(){};
            BSTNode(KEY item) : key(item), childL(nullptr), childR(nullptr){};

            std::pair<std::shared_ptr<KEY*>&, int> keyset(std::shared_ptr<KEY*> &arr){
                std::pair<std::shared_ptr<KEY*>&,int> toRet(arr);
            };

            // This is something like Java's toString method.
            // This is an IN-ORDER traversal.
            friend std::ostream& operator<<(std::ostream& os,  BSTNode const &node) {
                if( node.childL != nullptr ) os << *node.childL;
                os << std::setw(8) << node.key << " ";
                if( node.childR != nullptr ) os << *node.childR;
                return os;
            }
        };

        std::shared_ptr<BSTNode> root;
        int isize;
        int wut;

        int contain(const KEY &key, std::shared_ptr<BSTNode> curNode) const {
            int result = 0;
            //std::cout << key << curNode.get()->key << std::endl;
            if (curNode.get()->key == key) {
                result = 2;
            }
            else if (key < curNode.get()->key && curNode.get()->childL != nullptr) {
                if(contain(key, curNode.get()->childL)==2){
                    result = 2;
                }
                else{
                    result = 0;
                }
            }
            else if (key > curNode.get()->key && curNode.get()->childR != nullptr) {
                if(contain(key, curNode.get()->childR)==2){
                    result = 2;
                }
                else{
                    result = 0;
                }
            }
            else{
                result = 0;
            }
            return result;
        }


        // this function may help when you write other functions. Sometimes you
        // want to literally work with the node holding the key, and not
        // just the keys and values themselves. Your design will decide if you
        // need something like this or not.
        std::shared_ptr<BSTNode> &getNode(const KEY &key, std::shared_ptr<BSTNode> curNode){
            if(curNode.get()->key == key)
                return curNode;
            else if(key < curNode.get()->key && curNode.get()->childL != nullptr)
                contain(key,curNode.get()->childL);
            else if(key > curNode.get()->key && curNode.get()->childR != nullptr){
                contain(key,curNode.get()->childR);
            }
            return nullptr;
        }

        VALUE &get(const KEY &key, std::shared_ptr<BSTNode> &curNode ) {
            if(curNode.get()->key == key)
                return curNode.get()->value;
            else if(key < curNode.get()->key && curNode.get()->childL != nullptr)
                contain(key,curNode.get()->childL);
            else if(key > curNode.get()->key && curNode.get()->childR != nullptr){
                contain(key,curNode.get()->childR);
            }
        }



        // This is a PRIVATE version of the insert function that no one on
        // the outside can call. I find it useful for something like
        // the public version to kick things off, and this does the real
        // work.

        //each time public insert called, curRoot is the true root node
        bool insert(const KEY &key, std::shared_ptr<BSTNode> &curRoot){

            //add the first node to the BST
            if(curRoot == nullptr){
                //insert node
                std::shared_ptr<BSTNode> newNode = std::make_shared<BSTNode>(key);
                curRoot = newNode;
                curRoot.get()->childL = nullptr;
                curRoot.get()->childR = nullptr;
                isize++;
                return true;
            }

            if(key < curRoot.get()->key){
                //insert node as curRoot->childL
                if(curRoot.get()->childL == nullptr) {
                    std::shared_ptr<BSTNode> newNode = std::make_shared<BSTNode>(key);
                    curRoot.get()->childL = newNode;
                    newNode.get()->childL = nullptr;
                    newNode.get()->childR = nullptr;
                    isize++;
                    return true;
                }
                return insert(key, curRoot.get()->childL);
            }
            if(key > curRoot.get()->key){
                //insert node as curRoot->childR
                if(curRoot.get()->childR == nullptr) {
                    std::shared_ptr<BSTNode> newNode = std::make_shared<BSTNode>(key);
                    curRoot.get()->childR = newNode;
                    newNode.get()->childL = nullptr;
                    newNode.get()->childR = nullptr;
                    isize++;
                    return true;
                }
                return insert(key, curRoot.get()->childR);
            }


            return false;

        }

        VALUE insert(const KEY &key, VALUE val,  std::shared_ptr<BSTNode> &curRoot){
            //add the first node to the BST
            if(curRoot == nullptr){
                //insert node
                std::shared_ptr<BSTNode> newNode = std::make_shared<BSTNode>(key);
                newNode.get()->value = val;
                curRoot = newNode;
                newNode.get()->childL = nullptr;
                newNode.get()->childR = nullptr;
                isize++;
                return val;
            }

            if(key < curRoot.get()->key){
                //insert node as curRoot->childL
                if(curRoot.get()->childL == nullptr) {
                    std::shared_ptr<BSTNode> newNode = std::make_shared<BSTNode>(key);
                    newNode.get()->value = val;
                    curRoot.get()->childL = newNode;
                    newNode.get()->childL = nullptr;
                    newNode.get()->childR = nullptr;
                    isize++;
                    return val;
                }
                return insert(key, val, curRoot.get()->childL);
            }
            if(key > curRoot.get()->key){
                //insert node as curRoot->childR
                if(curRoot.get()->childR == nullptr) {
                    std::shared_ptr<BSTNode> newNode = std::make_shared<BSTNode>(key);
                    newNode.get()->value = val;
                    curRoot.get()->childR = newNode;
                    newNode.get()->childL = nullptr;
                    newNode.get()->childR = nullptr;
                    isize++;
                    return val;
                }
                return insert(key,val,  curRoot.get()->childR);
            }


        }

        //traverses BST in pre-order pattern by recursion to store values into an array.
        int * collectValues(std::shared_ptr<BSTNode> &root, int values[], int counter){
            if(root != nullptr){
                values[counter] = root.get()->value;

                collectValues(root.get()->childL, values, counter++);

                collectValues(root.get()->childR, values, counter++);
            }
            return values;

        }
        //checks for duplicates within value array and returns true if no duplicates are found.
        bool uniqueValues(std::shared_ptr<BSTNode> &root){
            int vals[isize];
            int counter = 0;
            vals = collectValues(root,vals,counter);
            for(int i = 0; i < isize; i++){
                for(int j = 1; j < isize-1; j++){
                    if(i == j)
                        return false;
                }
            }
            return true;
        }

        //public remove method:
        //bool remove(const KEY &key) override {
        //            //if size == 0
        //            if (this->isEmpty()) return false; // or you can keep track of curSize
        //            return remove(key,nullptr,root,);
        //        }
        bool remove(const KEY &key, std::shared_ptr<BSTNode> parent, std::shared_ptr<BSTNode> current){
            //case 1: remove the only node in the tree
            if(current.get()->key == key && isize == 1){
                isize = 0;
                root = nullptr;
                return true;
            }

            //Iterative traversal of BST
            while(current.get()->key != key){
                if(current.get()-> key > key && current.get()->childL != nullptr) {
                    parent = current;
                    current = current.get()->childL;
                }
                else if(current.get()-> key > key && current.get()->childL == nullptr){
                    return false;
                }

                if(current.get()-> key < key && current.get()->childR != nullptr) {
                    parent = current;
                    current = current.get()->childR;
                }
                else if(current.get()-> key < key &&current.get()->childR == nullptr){
                    return false;
                }

            }
            //key found, case 2: node has no children
            if(current.get()->childL == nullptr && current.get()->childR == nullptr){
                if (parent.get()->key > key)
                    parent.get()->childL = nullptr;
                else {
                    parent.get()->childR = nullptr;
                }
                isize--;
                return true;
            }

            //case 3: *current has one child*
            // remove a root node OR a node in the middle of the tree
            std::shared_ptr<BSTNode> child = std::make_shared<BSTNode>();
            //set temp var to know child is on the left
            if(current.get()->childL != nullptr && current.get()->childR == nullptr){
                //KEY child = current->childL->key;
                child = current.get()->childL;
            }
            //set temp var to know child is on the right
            if(current.get()->childL == nullptr && current.get()->childR != nullptr) {
                child = current.get()->childR;
            }
            //if current is a root node
            if(root.get()->key == current.get()->key){
                root = child;
                current = NULL;
                isize--;
                return true;
            }
            //if current IS a left child
            if(current.get()->key < parent.get()-> key){
                parent.get()->childL = nullptr;
                parent.get()->childL = child;
                isize--;
                return true;
            }
            //if current IS a right child
            if(current.get()->key > parent.get()-> key){
                parent.get()->childR = nullptr;
                parent.get()->childR = child;
                isize--;
                return true;
            }

            //case 4: node with key has two children
            if(current->key == key){
                if(current.get()->childL != nullptr && current.get()->childR != nullptr){
                    KEY replacement = getInOrderPredecessor(current);
                    current.get()->key = replacement;
                    //if parent and child have the same duplicate key
                    std::shared_ptr<BSTNode> copiedChild = std::make_shared<BSTNode>(replacement);

                    //Treat current's left child as the root of its own BST
                    parent = current;
                    current = current.get()->childL;

                    if(current.get()->key == copiedChild.get()->key){
                        current.get()->childR = nullptr;
                        isize--;
                        return true;
                    }
                    else {
                        remove(replacement, parent, current);
                    }
                }



            }

            return true;

        }

        KEY getInOrderPredecessor(std::shared_ptr<BSTNode> currentPredecessor) const {
            currentPredecessor = currentPredecessor.get()->childL;
            while(currentPredecessor.get()->childR != nullptr)
            {
                currentPredecessor = currentPredecessor.get()->childR;
            }
            return currentPredecessor.get()->key;

        }

        KEY getInOrderSuccessor(std::shared_ptr<BSTNode> current) const{
            current = current->childR;
            while(current->childL == nullptr)
            {
                current = current->childL;
                return current->key;
            }
        }

        KEY getHighestKey(std::shared_ptr<BSTNode> curRoot) const {
            while(curRoot.get()->childR != nullptr)
            {
                curRoot = curRoot.get()->childR;
            }
            return curRoot.get()->key;

        }



    public:
        BinarySearchTree() {
            root = nullptr;
            isize = 0;

        }
        //copy constructor
        BinarySearchTree(const BinarySearchTree<KEY,VALUE> &other) {
            root = other.root;
            isize = other.size();
        }

        ~BinarySearchTree() override {
            //no need to delete if we use smart pointers?
        }

        bool contains(const KEY &key) const override {
            if(root == nullptr){return false;}
            int result = contain(key,root);
            if (result == 2){
                return true;
            }
            else
            {
                return false;
            }

        }

        bool exists( const KEY &key) const override{
            return contains(key);
        }

        void clear() override {
            root = nullptr;
            isize = 0;
        }

        virtual VALUE &get(const KEY &key) override {
            return get(key, root);

        }

        bool insert(const KEY &key) override {
            return insert(key, root);
        }

        VALUE insert(const KEY &key, const VALUE &val) override {
            return insert(key,val,root);
        }

        bool uniqueVals(){

            return uniqueValues(root);
        }

        std::pair<std::shared_ptr<KEY*>,int> keys() override{
            KEY* raw = new KEY[size()];
            std::shared_ptr<KEY*> arr = std::make_shared<KEY*>(raw);

            // Todo: Extra Credit Students fill up the arr[] with the keys in-order

            std::pair<std::shared_ptr<KEY*>,int> toRet(arr,size());
            return toRet;
        };

        virtual std::pair<std::shared_ptr<VALUE*>,int> values() override {
            VALUE* raw = new VALUE[size()];
            std::shared_ptr<VALUE*> arr = std::make_shared<VALUE*>(raw);

            // Todo: Students fill up the arr[] with the values in-order
            // Todo: with respect to their keys (not each other). Extra Credit

            std::pair<std::shared_ptr<VALUE*>,int> vals(arr,size());
            return vals;
        };

        bool remove(const KEY &key) override {
            //if size == 0
            if(root == nullptr) return false;
            return remove(key,nullptr,root);
        }



        int size() const override {
            return isize;
        }

        VALUE& operator[](std::size_t idx){
            return get(idx);
        }

        friend std::ostream& operator<<(std::ostream& os, sdsu::BinarySearchTree<KEY,VALUE> const &bst) {
            if( bst.root != nullptr ) return os << "[" << (*bst.root) << "]";
            return os;
        }
    };
}
#endif //PROG2_BINARYSEARCHTREE_H
