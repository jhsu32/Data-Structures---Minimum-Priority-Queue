#ifndef MPQ_H
#define MPQ_H

//Abstract Minimum Priority Queue Class
/**
 * Parent class MPQ
 * The 4 functions in class MPQ has to be implemented in SortedMPQ.h, UnsortedMPQ.h, BinaryHeapMPQ.h
 */
template<typename T>
class MPQ{
public:
    // Remove minimum from MPQ and return it
    virtual T remove_min() = 0;
    // Get the minimum from MPQ
    virtual T min() = 0;
    // Check if MPQ is empty
    virtual bool is_empty() = 0;
    // Insert into MPQ
    virtual void insert(const T& data) = 0;
};
#endif