#include "brent.h"
// Muhammet Hakan Taştan 20190701009-071 CSE341 Assignment 1

Brent::Brent(int table_size){
    data_vec.resize(table_size);
}


void Brent::insert(int new_data){
    for(int i = 0; i < data_vec.size(); i++){ // checks whether there is a space in the table
        if(data_vec[i].valid && (i == data_vec.size()-1)){
            return;
        } else if (!(data_vec[i].valid)){
            break;
        }
    }
    int home_address = new_data % data_vec.size();
    int increment = 1;
    if (new_data < data_vec.size()){
        increment = 1;
    }
    else{
        increment = ((int) new_data / data_vec.size()) % data_vec.size();
    }
    int s = 2;
    if(data_vec[home_address].valid){
        int new_add = (home_address + increment) % data_vec.size();
        if(!(data_vec[new_add].valid)){//directly inserts, if s is equals to 2
            data_vec[new_add].data = new_data;
            data_vec[new_add].valid = true;
        }
        else{// finds a potential place to insert and assign the s value accordingly
            while (data_vec[new_add].valid){
                new_add = (new_add + increment) % data_vec.size();
                s++;
            }
            int i;
            int j = 0;
            int possible_i = 100;
            int possible_j = 100;
            int inc_q = 1;
            while(s > j+1){
                i=0;
                new_add = (home_address + increment*j) % data_vec.size();
                if(data_vec[new_add].data < data_vec.size()){
                    inc_q = 1;
                } else {
                    inc_q = (data_vec[new_add].data / data_vec.size()) % data_vec.size();
                }
                while(data_vec[new_add].valid){
                    new_add = ((new_add + inc_q) % data_vec.size());
                    i++;
                }
                j++;
                if((s > i+j) && ((possible_i+possible_j) >= (i+j))){
                    if((possible_i+possible_j) == (i+j)){
                        if(j <= possible_j){
                            if(i <= possible_i){
                                possible_i = i;
                                possible_j = j;
                            }
                        }
                    } else{
                        possible_i = i;
                        possible_j = j;
                    }
                }
            }
            if ((possible_i+possible_j)<s){
                new_add = home_address;
                for (int i = 0; i < (possible_j-1); i++) {
                    new_add = (home_address + increment) % data_vec.size();
                }
                int temp = data_vec[new_add].data;
                data_vec[new_add].data = new_data;
                if(temp < data_vec.size()){
                    inc_q = 1;
                } else {
                    inc_q = (temp / data_vec.size()) % data_vec.size();
                }
                for(int i = 0; i < possible_i; i++){
                    new_add = (new_add+inc_q) % data_vec.size();
                }
                data_vec[new_add].data = temp;
                data_vec[new_add].valid = true;
            } else{
                new_add = (home_address + increment*(s-1)) % data_vec.size();
                data_vec[new_add].data = new_data;
                data_vec[new_add].valid = true;
            }
        }
    }
    else{ // if the home address is empty, insert it directly
        data_vec[home_address].data = new_data;
        data_vec[home_address].valid = true;
    }
}



int Brent::find_num_probes(int key) const{
    int num_probe = 1;
    int home_address = key % data_vec.size();
    int increment = 1;
    if(key < data_vec.size()){
        increment = 1;
    } else{
        increment = ((key / data_vec.size()) % data_vec.size());
    }
    int new_add = home_address;
    while (key != data_vec[new_add].data) {
        new_add = (new_add+increment) % data_vec.size();
        num_probe++;
    }
    return num_probe; //if the key is not a valid input returns -1
}



double Brent::find_average_num_probes() const{
    int itemNumber = 0;
    int sum_probe = 0;
    for(auto i : data_vec){
        if(i.valid){
            itemNumber++;
            sum_probe += find_num_probes(i.data);
        }
    }
    return ((double)sum_probe / itemNumber);
}