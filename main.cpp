#include <iostream>
#include <fstream>

#include "brent.h"

using std::cout;
using std::endl;
using std::cerr;

void print_table(const Brent & tbl){

    for(int i = 0; i < tbl.data_vec.size(); i++){
        cout << i << ":  ";
        if(tbl.data_vec[i].valid){
            cout << tbl.data_vec[i].data <<  "     " << tbl.find_num_probes(tbl.data_vec[i].data);
        }
        cout << endl;
    }

    cout << endl << "Average # of probes: " << tbl.find_average_num_probes() << endl;
}

int main(){

    Brent tbl(11);
    tbl.insert(27);
    tbl.insert(18);
    tbl.insert(32);
    tbl.insert(44);
    tbl.insert(52);
    tbl.insert(66);
    tbl.insert(7);
    tbl.insert(9);
    tbl.insert(14);
    tbl.insert(19);
    tbl.insert(42);

    cout << endl << "---Tables---" <<endl;
    print_table(tbl);

    return 0;
}
