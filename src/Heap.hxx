#ifndef DATASTRUCT_HEAP_H
#define DATASTRUCT_HEAP_H

#include "DataStruct.hxx"




//// ===========================================================
//// =====================        HEAP       ===================
//// ===========================================================


template <typename data> class Heap : public DataStruct<data>{
    /*
     * class Heap
     * class heir DataStruct
     */

    /*
     * A binary binary is such a binary tree, for which three conditions are fulfilled:
     *
     *  The value at any vertex is not less than the value of its descendants [K 1].
     *  The depth of all leaves (distance to the root) differs by no more than 1 layer.
     *  The last layer is filled from left to right without “holes”.
     *
     *  A convenient data structure for a sorting tree is an array A, which has the first element,
     *  A [1] - the element at the root, and the descendants
     *  of the element A [i] are A [2i] and A [2i + 1] (with the numbering of elements from the first) .
     *  When numbering elements from zero, the root element is A [0],
     *  and the descendants of A [i] are A [2i + 1] and A [2i + 2].
     *  With this storage method, conditions 2 and 3 are met automatically.
     */

public:

    // identical comments are presented in class DataStruct

    Heap() = default;
    explicit Heap(UTYPE n){};
    explicit Heap(vector<data> v);
    Heap(data* v, UTYPE n);


    bool append(data p);
    long find(data p);
    bool remove(data p);
    data pop();
    bool is_empty();

    void outHeap(); // output in console as a tree

    bool read_console();
    bool read_file();
    bool pop_file();

protected:
    void heapify(UTYPE i); // sift
};


template<typename data>
Heap<data>::Heap(vector<data> v){
    log("Heap", "constructor(vector<data> v)");
    for (UTYPE i = 0; i < v.size(); i++){
        // just append every item in vector
        this->append(v[i]);
    }
}

template<typename data>
Heap<data>::Heap(data *v, UTYPE n):DataStruct<data>(v, n) {
    log("Heap", "constructor(data*v, UTYPE n)");
    for (UTYPE i = 0; i < n; i++){
        // just append every item in array
        this->append(v[i]);
    }
}


template<typename data>
void Heap<data>::heapify(UTYPE i) {
    // recursively sift
    log("Heap", "heapify");
    UTYPE left, right;
    data temp;
    left = 2 * i + 1;
    right = 2 * i + 2;
    UTYPE size = this->items.size();
    if (left < size){
        if (this->items[i] < this->items[left]){
            temp = this->items[i];
            this->items[i] = this->items[left];
            this->items[left] = temp;
            heapify(left);
        }
    }
    if (right < size){
        if (this->items[i] < this->items[right]){
            temp = this->items[i];
            this->items[i] = this->items[right];
            this->items[right] = temp;
            heapify(right);
        }
    }
}

template<typename data>
bool Heap<data>::append(data p) {
    // append item p
    log("Heap", "append");
    if (this->is_present(p)) {
        return true; // if already present
    }

    UTYPE i, parent;
    i = this->items.size();
    this->items.push_back(p); // push to the end
    parent = (i - 1) / 2;
    // and sift
    while (parent >= 0 && i > 0){
        // recursively change the values
        if (this->items[i] < this->items[parent]){
            data temp = this->items[i];
            this->items[i] = this->items[parent];
            this->items[parent] = temp;
        }
        i = parent;
        parent = (i - 1) / 2;
    }
    return true;
}


template<typename data>
data Heap<data>::pop() {
    // extract minimum
    log("Heap", "pop");
    if (this->is_empty()) { // empty check
        throw length_error("EMPTY STRUCT!");
    }
    return this->items[0]; // return the root
}

template<typename data>
void Heap<data>::outHeap() {
    log("Heap", "outHeap");
    UTYPE i = 0, k = 1;
    while (i < this->items.size()){
        while ((i < k) && (i < this->items.size())){
            cout << this->items[i] << " ";
            i++;
        }
        cout << endl;
        k = k * 2 + 1;
    }


}

template<typename data>
long Heap<data>::find(data p) {
    // return the index of item, -1 in other way
    log("Heap", "find");
    long ind = -1;
    for (UTYPE i = 0; i < this->items.size(); i++){
        if (this->items[i] == p){
            // compare
            ind = i;
            break;
        }
    }
    return ind;
}

template<typename data>
bool Heap<data>::is_empty() {
    log("Heap", "is_empty");
    // empty check
    return this->items.size() == 0;
}

template<typename data>
bool Heap<data>::remove(data p) {
    // remove item p from heap
    log("Heap", "remove");

    if (this->is_present(p)){
        vector<data> v;
        for (UTYPE i = 0; i < this->items.size(); i++){
            if (this->items[i] != p){
                // delete from items
                v.push_back(this->items[i]);
            }



        }

        // and build again
        this->items.resize(0);
        for(UTYPE i = 0; i < v.size(); i++){
            this->append(v[i]);
        }
    }

    return true;
}

/* INPUT AND OUTPUT ARE EQUAL TO SEGMENT TREE*/

template<typename data>
bool Heap<data>::read_console() {

    log("Heap", "read_console");
    string inp;

    cout << "enter the elements of the binary heap, stop - to stop: " << endl;

    this->items.resize(0);


    while (true){
        cin >> inp;
        if (inp == "stop"){
            break;
        }
        this->append(atoi(inp.c_str()));

    }

    return true;
}

template<typename data>
bool Heap<data>::read_file() {
    log("Heap", "read_file");

    this->items.resize(0);

    ifstream fin(INPUT_FILE);

    string buff;

    vector<data> v;
    while (!fin.eof()) {
        getline(fin, buff);


        char* str = (char*) malloc(sizeof(char) * buff.length());

        char sep[10] = " ";

        for (UTYPE i = 0; i < buff.length(); i++){
            str[i] = buff[i];
        }

        char* istr;

        istr = strtok (str,sep);

        // selection of subsequent parts
        UTYPE i = 0;

        while (istr != NULL)
        {

            this->append(atoi(istr));
            // conclusion of the next selected part
            istr = strtok (NULL, sep);
            i++;
        }

    }
    fin.close();


    return true;
}

template<typename data>
bool Heap<data>::pop_file() {
    log("Heap", "pop_file");
    ofstream fout(OUTPUT_FILE);

    fout << this->pop();

    fout.close();

    return true;
}


//// ===========================================================
//// =====================        HEAP       ===================
//// ===========================================================




#endif //DATASTRUCT_HEAP_H
