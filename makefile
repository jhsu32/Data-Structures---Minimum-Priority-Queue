all: cpujob-test heap-test sorted-test unsorted-test test

cpujob-test: cpu-job.h
	g++ -std=c++11 cpu-job-main.cpp -o cpujob-test

heap-test: MPQ.h BinaryHeapMPQ.h BinaryHeap.h
	g++ -std=c++11 binaryheap-mpq-main.cpp -o heap-test

sorted-test: MPQ.h SortedMPQ.h
	g++ -std=c++11 sortedmpq-main.cpp -o sorted-test

unsorted-test: MPQ.h UnsortedMPQ.h
	g++ -std=c++11 unsortedmpq-main.cpp -o unsorted-test

test: MPQ.h UnsortedMPQ.h SortedMPQ.h BinaryHeapMPQ.h BinaryHeap.h cpu-job.h
	g++ -std=c++11 main.cpp -o test

clean:
	rm *test OutputFiles/*

run: test
	./test
