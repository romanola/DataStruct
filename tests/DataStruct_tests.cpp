#include "../src/SegmentTree.hxx"
#include "../src/Heap.hxx"




//// ========================== ##TESTS##  ==========================


bool test_SegmentTree(bool console_inp, bool console_out) {
    SegmentTree<int> s; // constructor
    if (console_inp) {
        s.read_console(); // input from console


    }

    else
    {
        s.read_file(); // input from file

    }

    s.append(-65); // test append
    s.append(10);
    s.remove(-65); // test remove

    if (s.is_empty()) {
        // test is_empty()
        throw logic_error("TEST ERROR");
    }

    if (!s.is_present(10)) {
        // test is_present()
        throw logic_error("TEST ERROR");
    }

    s.update(10, 20); // test update

    if (console_out){
        cout << "test SegmentTree: " << s.pop() << endl;
    }
    else{
        s.pop_file();
    }

    return true;
}


bool test_Heap(bool console_inp, bool console_out){
    Heap<int> s; // constructor
    if (console_inp) {
        s.read_console(); // input from console


    }

    else
    {
        s.read_file(); // input from file

    }

    s.append(-65); // test append
    s.append(10);
    s.remove(-65); // test remove

    if (s.is_empty()) {
        // test is_empty()
        throw logic_error("TEST ERROR");
    }

    if (!s.is_present(10)) {
        // test is_present()
        throw logic_error("TEST ERROR");
    }


    if (console_out){
        cout << "test Heap: " << s.pop() << endl;
    }
    else{
        s.pop_file();
    }

    return true;
}


int main(){

    // test

    _clear(); // clear log and output files

    bool in, out;
    cout << "hello! enter the way you want test:" << endl;
    cout << "1 - to input from console, 0 - to input from file:" << endl;
    cin >> in;
    cout << "1 - to output from console, 0 - to output from file:" << endl;
    cin >> out;

    if (test_SegmentTree(in, out) && test_Heap(in, out)){
        cout << endl << "that's done! congratulations!" << endl;
    }

    return 0;
}

