#ifndef DATASTRUCT_SEGMENTTREE_H
#define DATASTRUCT_SEGMENTTREE_H

#include "DataStruct.hxx"



//// ===========================================================
//// =================        SEGMENT TREE       ===============
//// ===========================================================


template <typename data> class SegmentTree: public DataStruct<data>{
    /*
     * class SegmentTree
     * class heir DataStruct
     */

    /*
     * Let's get an array of T [2n - 1]. The root will lie in the first element of the array,
     * and the sons of the i-th vertex will lie in the elements
     * with numbers 2i and 2i + 1 - left and right, respectively.
     * Immediately you can notice the obvious property:
     * T [i] = min (T [2i], T [2i + 1]) for the i-th vertex,
     * which is not a leaf. Sheets, by the way, will lie with this
     * numbering in the elements with numbers from n to 2n - 1.
     */

public:

    // identical comments are presented in class DataStruct

    SegmentTree() = default;
    explicit SegmentTree(UTYPE n);
    explicit SegmentTree(vector<data> v);
    SegmentTree(data*v, UTYPE n);



    bool append(data p);
    long find(data p);
    bool remove(data p);
    data pop();
    bool is_empty();
    void update(data old, data n);

    bool read_console();
    bool read_file();
    bool pop_file();
};

template<typename data>
SegmentTree<data>::SegmentTree(data *v, UTYPE n){
    log("SegmentTree", "constructor(data*v, UTYPE n)");
    UTYPE k = find_num_items(n); // returns the number of elements in a full binary tree
    this->items.resize(k, inf); // resize the field and fill the max value

    UTYPE j = 0;

    for (UTYPE i = k - n; i < k; i++){
        // fill leafs with elements from an array
        this->items[i] = v[j];
        j++;
    }

    for (UTYPE i = k - k/2 - 1; i > 0; i--){
        // then recursively fill the tree
        // T [i] = min (T [2i], T [2i + 1])
        this->items[i] = min(this->items[2*i], this->items[2*i+1]);
    }
}

template<typename data>
SegmentTree<data>::SegmentTree(UTYPE n){
    log("SegmentTree", "constructor(UTYPE n)");
    this->items.resize(find_num_items(n), inf); // just resize
}

template<typename data>
SegmentTree<data>::SegmentTree(vector<data> v){
    log("SegmentTree", "constructor(vector<data> v)");
    UTYPE n = v.size(); // returns the number of elements in a full binary tree
    UTYPE k = find_num_items(n); // resize the field and fill the max value
    this->items.resize(k, inf);

    UTYPE j = 0;
    for (UTYPE i = k - n; i < k; i++){
        // fill leafs with elements from a vector
        this->items[i] = v[j];
        j++;
    }

    for (UTYPE i = k - k/2 - 1; i > 0; i--){
        // then recursively fill the tree
        // T [i] = min (T [2i], T [2i + 1])
        this->items[i] = min(this->items[2*i], this->items[2*i+1]);
    }
}

template<typename data>
bool SegmentTree<data>::append(data p) {
    // append item p to a tree
    log("SegmentTree", "append");
    vector<data> n; // create vector - new vector of items
    UTYPE k = this->items.size();
    for (UTYPE i = k - k / 2; i < k; i++){
        // push every old items
        if (this->items[i] != inf){
            n.push_back(this->items[i]);
        }
    }


    // then build tree again

    n.push_back(p);


    UTYPE n1 = n.size();
    UTYPE k1 = find_num_items(n1);
    this->items.resize(k1, inf);

    UTYPE j = 0;
    for (UTYPE i = k1 - n1; i < k1; i++){
        this->items[i] = n[j];
        j++;
    }

    for (UTYPE i = k1 - k1/2 - 1; i > 0; i--){
        this->items[i] = min(this->items[2*i], this->items[2*i+1]);
    }

    return true;
}

template<typename data>
long SegmentTree<data>::find(data p) {
    // returns the index of item p, -1 - in other way
    log("SegmentTree", "find");
    long ind = -1; // declare as -1
    UTYPE n = this->items.size();
    for (UTYPE i = n - n / 2; i< n; i++){
        // search by leaves
        if (this->items[i] == p){
            // change index
            ind = i;
            break;
        }
    }
    return ind;
}

template<typename data>
void SegmentTree<data>::update(data old, data n) {
    // update old item to a new item
    log("SegmentTree", "update");

    long i = this->find(old); // find the index of old item

    if (i != -1) {
        this->items[i] = n; // change
        // and sift
        while (i /= 2) {
            // update values behind the vertices
            this->items[i] = min(this->items[2 * i], this->items[2 * i + 1]);
        }
    }
}

template<typename data>
bool SegmentTree<data>::remove(data p) {
    // remove the item p
    log("SegmentTree", "remove");
    this->update(p, inf); // update it's value to inf
    return true;
}

template<typename data>
data SegmentTree<data>::pop() {
    // extract minimum
    log("SegmentTree", "pop");
    if (this->is_empty()) { // empty check
        throw length_error("EMPTY STRUCT!");
    }
    return this->items[1]; // return the root
}

template<typename data>
bool SegmentTree<data>::is_empty() {
    log("SegmentTree", "is_empty");
    return 2 > this->items.size();
}

template<typename data>
bool SegmentTree<data>::read_console() {
    // read from console
    log("SegmentTree", "read_console");

    string inp;

    cout << "enter the elements of the segment tree, stop - to stop: " << endl;

    vector<data> v;


    while (true){
        // while not stop read data
        cin >> inp;
        if (inp == "stop"){
            break;
        }
        v.push_back(atoi(inp.c_str())); // and push to vector

    }


    // then identically to constructor

    UTYPE n = v.size();
    UTYPE k = find_num_items(n);
    this->items.resize(k, inf);

    UTYPE j = 0;
    for (UTYPE i = k - n; i < k; i++){
        this->items[i] = v[j];
        j++;
    }

    for (UTYPE i = k - k/2 - 1; i > 0; i--){
        this->items[i] = min(this->items[2*i], this->items[2*i+1]);
    }



    return true;
}

template<typename data>
bool SegmentTree<data>::read_file() {
    // read from file
    log("SegmentTree", "read_file");

    ifstream fin(INPUT_FILE);

    string buff;

    vector<data> v;
    while (!fin.eof()) {
        // read all words from file
        getline(fin, buff);


        // separate them by space
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

            v.push_back(atoi(istr));

            // conclusion of the next selected part
            istr = strtok (NULL, sep);
            i++;
        }

    }
    fin.close(); // close the file


    // identically to constructor

    UTYPE n = v.size();
    UTYPE k = find_num_items(n);
    this->items.resize(k, inf);

    UTYPE j = 0;
    for (UTYPE i = k - n; i < k; i++){
        this->items[i] = v[j];
        j++;
    }

    for (UTYPE i = k - k/2 - 1; i > 0; i--){
        this->items[i] = min(this->items[2*i], this->items[2*i+1]);
    }


    return true;
}

template<typename data>
bool SegmentTree<data>::pop_file() {
    // pop to file
    log("SegmentTree", "pop_file");

    ofstream fout(OUTPUT_FILE);

    fout << this->pop();

    fout.close();

    return true;
}




//// ===========================================================
//// =================        SEGMENT TREE       ===============
//// ===========================================================


#endif //DATASTRUCT_SEGMENTTREE_H
