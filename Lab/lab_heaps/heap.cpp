/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <math.h>
#include "heap.h"

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    
    return (2*currentIdx);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    
    return (2*currentIdx + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child

    if (leftChild(currentIdx) <= _elems.size()){
        return false;
    }
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t lChildIndex = leftChild(currentIdx);
    size_t rChildIndex = rightChild(currentIdx);

    if (hasAChild(currentIdx)) {
        if (rChildIndex  < _elems.size()) {
            if (higherPriority(_elems[lChildIndex], _elems[rChildIndex])){
                return lChildIndex;
            } else return rChildIndex;
        } else return lChildIndex;
    } 
    else return currentIdx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx)){
        size_t minChildIdx = maxPriorityChild(currentIdx);
        std::cout << _elems[minChildIdx] << std::endl;
        if (_elems[currentIdx] > _elems[minChildIdx]){
            std::swap(_elems[currentIdx],_elems[minChildIdx]);
            heapifyDown(minChildIdx);
        }
    } else return;

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(0);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    if (elems.empty()){
        heap();
    }
    for (size_t i = 0; i < elems.size() ; i ++){
        T elem = elems[i];
        _elems.push_back(elem);
    }
    for (size_t i = parent(elems.size()); i > 0 ; i--){
        heapifyDown(i);
    }
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.
   
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    T toRemove = _elems[root()];
    
    _elems[root()] = _elems[_elems.size()-1];
    _elems.pop_back();
    for (size_t i = 0; i < parent(_elems.size()-1) ; i++){
        size_t highP = maxPriorityChild(i);
    }

    return highP;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    /// @todo Add elem to the heap

}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    if (_elems.size() == 0) {
        return true;
    } else return false;
} 
