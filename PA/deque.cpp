/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* Constructor for the Deque class */
template <class T>
Deque<T>::Deque(){
    vector<T> data;
    k1 = -1; // start
    k2 = -1; // end
/* your code here */
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{   
    data.push_back(newItem);
    k2++;
    if (k1 == -1 ){
        k1++;
    }
    /**
     * @todo Your code here!
     */
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The leftmost item of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    if (k2 >= 0 && k1 >= 0){
    T retVal = data[k1];
    // data.erase(begin(data)+k1); // "remove"
    k1++;
    if (k1 > k2) {
    k1 = -1;
    k2 = -1;
    data.clear();
    }
    else if (k2 - k1 + 1 <= k1){
        vector<T> newData;
        for (int i = k1; i <= k2; i++) {
        newData.push_back(data[i]);
        }        
        k2 = k2 - k1;
        k1 = 0;
        data.clear();
        this->data = newData;
    }
    return retVal;
}
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The rightmost item of the Deque.
 */
template <class T>
T Deque<T>::popR()
{   
    vector<T> newData;
    if (k2 >= 0 && k2 >= k1){
    T temp = data[k2];
    data.pop_back();
    k2--;
    // cout << data.front() << endl;
    // cout << "data back " << data.back() << endl;
    if (k2 >= 0 && k2 - k1 + 1 <= k1){     
        for (int i = 0; i < k2-k1 + 1; i++) {
        newData.push_back(data[i]);
        }
    k2 = k2 - k1 + 1;
    k1 = 0;
    data.clear();
    data = newData;
    // cout << data.front() << endl;
    // cout << data.back() << endl;
    }
    if (k2 == -1) {
        k1 = -1;
    }
    return temp;
    } 
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the left of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    if (k2 >= 0 && k1 >= 0){
        return data[k1];
    } 
}
/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    if (k2 >= 0  && k1 >= 0){
        return data[k2];
    } 
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return (k1 == -1 && k2 == -1);
}
