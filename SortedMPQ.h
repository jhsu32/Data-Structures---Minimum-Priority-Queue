#ifndef SORTEDMPQ_H
#define SORTEDMPQ_H

#include <stdexcept>
#include <list>
#include <iostream>
#include "MPQ.h"
using namespace std;
/*
 * Minimum Priority Queue based on a linked list
 */
template <typename T>
class SortedMPQ: MPQ<T> {
	private:
		std::list<T> potato;
	public:
		T remove_min(){
			if(is_empty()){ throw invalid_argument("The vector is empty");}
			T min = potato.front();
			potato.pop_front();
			return min;
		}

		T min(){
			if(is_empty()){ throw invalid_argument("The vector is empty");}
			T min = potato.front();
			return min;
		}

		bool is_empty(){
			if(potato.empty()){
				return true;
			}
			return false;
		}

		void insert(const T& data){
			if(is_empty()){ 
				potato.push_front(data);
				//cout << data << endl;
				return;
			}
			for (auto i=potato.begin(); i!=potato.end(); i++){
				if(data < *i){
					//cout << data << endl;
					 potato.insert(i,data);
					 return;
				}
			}
			if(potato.back() < data){
				potato.push_back(data);
			}
		}
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::list
   // For remove_min() and min() throw exception if the SortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
};

#endif