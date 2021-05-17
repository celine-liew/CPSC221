#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
  clear();
  delete head_;
  head_ = NULL; //head_ is global variable. so need to NULL it.
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  Node* nodeInsert = new Node (ndata);
  head_->prev->next = nodeInsert;
  nodeInsert->prev = head_->prev;
  head_->prev = nodeInsert;
  nodeInsert->next = head_;
  length_++;
}

/**
 * Modifies the Chain by moving the subchain of len Nodes,
 * starting at position startPos, dist positions toward the
 * end of the chain.  If startPos + len - 1 + dist > length
 * then dist = length - startPos - len + 1 (to prevent gaps
 * in the new chain).
 * The subchain occupies positions (startPos + dist) through
 * (startPos + dist + len - 1) of the resulting chain.
 * The order of subchain nodes is not changed in the move.
 * You may assume that: 1 <= startPos <= length - len + 1,
 * 0 <= dist <= length, and 0 <= len <= length. 
 */
void Chain::moveBack(int startPos, int len, int dist){
  if (dist == 0){
    return;
  }
  if (startPos + len - 1 + dist > length_) {
    dist = length_ - startPos - len + 1;
  }
  Node* startSub = head_;
  Node* beforeStartSub = head_;
  Node* endSub;
  Node* afterSub = head_; //to join with beforeStart
  Node* insertAfter;
  Node* insertBefore = head_; // to insert in between after and before.

  startSub = walk(startSub, startPos);
  beforeStartSub = startSub->prev;
  endSub = startSub;
  endSub = walk(endSub, len-1);
  afterSub = endSub->next;
  insertAfter = beforeStartSub;
  insertAfter = walk(insertAfter, len + dist);
  insertBefore = insertAfter->next;

  beforeStartSub->next = afterSub;
  afterSub->prev = beforeStartSub;
  startSub->prev = insertAfter;
  insertAfter->next = startSub;
  endSub->next = insertBefore;
  insertBefore->prev = endSub;
  /* your code here */
}

/**
 * Rolls the current Chain by k nodes: reorders the current list
 * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
 * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
 * nodes of the original list where n is the length.
 */
void Chain::roll(int k){
  if (length_ == k) {
    return;
  } else if (head_->next != head_) {
  Node* originalOne = head_->next;
  Node* rollStart = head_;
  Node* rollEnd = head_->prev; //last nth node
  Node* tail = head_->prev;
  rollStart = walk(head_ , length_ - k + 1);
  tail = rollStart->prev;
  tail->next = head_;
  head_->prev = tail;
  head_->next = rollStart;
  rollStart->prev = head_;
  rollEnd->next = originalOne;
  originalOne->prev = rollEnd;
  }
}

/**
 * Modifies the current chain by reversing the sequence
 * of nodes from pos1 up to and including pos2. You may
 * assume that pos1 and pos2 exist in the given chain,
 * and pos1 <= pos2.
 * The positions are 1-based.
 */
void Chain::reverseSub(int pos1, int pos2){
  int dist = pos2 - pos1; 
  for (int i = 0; i < pos2 - pos1; i++) {
    moveBack(pos1, 1, dist);
    dist--;
  }
  
  /* your code here */
}

/*
* Modifies both the current chain and the "other" chain by removing
* nodes from the other chain and adding them between the nodes
* of the current chain -- one "other" node between two current nodes --
* until one of the two chains is exhausted.  Then the rest of the
* nodes in the non-empty chain follow.
* The length of the resulting chain should be the sum of the lengths
* of current and other. The other chain should have only
* the head_ sentinel at the end of the operation.
* The weave fails and the original
* chains should be unchanged if block sizes are different.
* In that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
  if (width_ != other.width_ || height_ != other.height_){
    cout << "Block sizes differ." << endl;
  } else {
    if (other.length_ != 0)  {
      int shorterLen = length_;
      if (length_ > other.length_ ) {
        shorterLen = other.length_;
      }
      Node* toWeave = other.head_->next;
      Node* startWeave = head_->next;
      Node* endWeave = startWeave->next;
      if (length_ == 0) {
        toWeave->prev = head_;
        head_->next = toWeave;
        endWeave = other.head_->prev;
        head_->prev = endWeave;
        endWeave->next = head_;
        length_ = other.length_;
      }
      else {
        for (int i = 0; i < shorterLen; i++) {
          other.head_->next = other.head_->next->next;
          other.head_->next->prev = other.head_;
          toWeave->prev = startWeave;
          startWeave->next = toWeave;
          toWeave->next = endWeave;
          endWeave->prev = toWeave;
          startWeave = toWeave->next;
          endWeave = toWeave->next->next;
          toWeave = other.head_->next;
          other.length_--;
          length_ ++;
        }
        if (other.length_ !=0) {
          toWeave = other.head_->next;
          toWeave->prev = head_->prev;
          head_->prev->next = toWeave;
          endWeave = other.head_->prev;
          endWeave->next = head_;
          head_->prev = endWeave;
          length_ += other.length_;
      }
      }
  other.head_->next = other.head_;
  other.head_->prev = other.head_;
  other.length_ = 0;
  }
}
}
/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
void Chain::clear() {
  Node* toDelete = head_->next;
  Node* next = toDelete->next;;
  for (int i = 0; i < length_; i++){
    delete toDelete;
    toDelete = next;
    next = next->next;
  }
  head_->next = head_;
  head_->prev = head_;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  Node* copyStart = other.head_->next; //start node of other to copy
  for (int i = 0; i < other.length_; i++){
    insertBack(copyStart->data);
    copyStart = copyStart->next;
  }
  height_ = other.height_;
  width_ = other.width_;
}
