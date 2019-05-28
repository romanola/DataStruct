#include "DataStruct.hxx"


UTYPE find_num_items(UTYPE n) {
    log("NULL", "find_num_items");
    // returns the number of elements in a complete binary tree in which n sheets
    UTYPE val = 1;
    while (val < n){
        val *=2; // the nearest degree 2 is greater than or equal to n
    }
    return 2 * val; // returns 2 * n
}


bool log(string class_name, string method_name){
    // logging

    ofstream fout(LOG_FILE, ios::app); // open file log.log in append mode

    // time
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    // note in log file : CLASS METHOD TIME
    fout << "CLASS: " << class_name << " METHOD: " << method_name << " TIME: " << asctime(timeinfo) << endl;

    fout.close(); // close file
    return true;
}


bool _clear() {
    // clear the log and the output files

    ofstream fout1(LOG_FILE);
    fout1.clear();
    fout1.close();

    ofstream fout2(OUTPUT_FILE);
    fout2.clear();
    fout2.close();

    return true;
}
