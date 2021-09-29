#ifndef UNSORTEDMPQ_H
#define UNSORTEDMPQ_H

#include <stdexcept>
#include <vector>
#include "MPQ.h"
using namespace std;
/**
 * Minimum Priority Queue based on a vector
 */
template <typename T>
class UnsortedMPQ: MPQ<T> {
	private:
		vector<T> vec;
	public:
		T remove_min(){
			if(is_empty()){ throw invalid_argument("The vector is empty");}
			T min = vec.at(0);
			int mark = 0;
			for(int i =0; i < vec.size(); i++){
				if(vec.at(i) < min){
					min = vec.at(i);
					mark = i;
				}
			}
			vec.erase(vec.begin() + mark);			
			return min;
		}

		T min(){
			if(is_empty()){ throw invalid_argument("The vector is empty");}
			T min = vec.at(0);
			for(int i =0; i < vec.size(); i++){
				if(vec.at(i) < min){
					min = vec.at(i);
				}
			}
			return min;
		}

		bool is_empty(){
			if(vec.empty()){
				return true;
			}
			return false;
		}

		void insert(const T& data){
			vec.push_back(data);
		}
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::vector
   // For remove_min() and min() just throw exception if the UnsortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
};

#endif