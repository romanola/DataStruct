#ifndef PROJECT_DATASTRUCT_H
#define PROJECT_DATASTRUCT_H


#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string.h>
#include "../src/common.h"


#define LOG_FILE "../log.log"
#define INPUT_FILE "../tests/input.txt"
#define OUTPUT_FILE "../tests/output.txt"

using namespace std;


const UTYPE inf = INT_MAX;







//// ===========================================================
//// =================        DATA STRUCT       ================
//// ===========================================================

template <typename data> class DataStruct{
    /*
     * abstract class DataStruct
     * interface for data structures Heap and SegmentTree
     */

public:
    DataStruct() = default; // default constructor
    explicit DataStruct(UTYPE n){}; // constructor from number of items in data struct
    explicit DataStruct(vector<data> v){}; // constructor from vector of items
    DataStruct(data* v, UTYPE n){}; // constructor from array (pointer and size)

    ~DataStruct(); // destructor




    void print(); // output the items to console. separate by space
    bool is_present(data p); // true if p - present in data struct


    virtual bool append(data p) = 0; // append p to items
    virtual long find(data p) = 0; // find index of p in items, returns -1 if p is not present
    virtual bool remove(data p) = 0; // delete p from struct
    virtual data pop() = 0; // return min of items
    virtual bool is_empty() = 0; // return true if the struct is empty

protected:
    vector<data> items; // field - vector of items in data struct

};

template<typename data>
void DataStruct<data>::print() {
    log("DataStruct", "print");
    for (UTYPE i = 0; i < items.size(); i++){
        // output
        cout << items[i] << " ";
    }
    cout << endl;

}

template<typename data>
bool DataStruct<data>::is_present(data p) {
    log("DataStruct", "is_present");
    return find(p) != -1; // present if it's index not equals to -1
}

template<typename data>
DataStruct<data>::~DataStruct() {
    log("DataStruct", "destructor");
    this->items.clear(); // destructor. delete the single field (vector items)
}


//// ===========================================================
//// =================        DATA STRUCT       ================
//// ===========================================================



#endif //PROJECT_DATASTRUCT_H
