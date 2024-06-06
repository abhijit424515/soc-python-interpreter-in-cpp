#include "pic.hh"

CSV* init_csv(VecWrapper* header) {
    if (header==nullptr){
        cerr<<"Header is null"<<endl;
        exit(1);
    }
    CSV *csv = new CSV();
    for(CSVElem* elem: header->vec){
        // assert(elem->vtype == CSV_STRING);
        Column* col = new Column();
        // I will use CSV_NULL for the column that is not yet type known
        col->vtype = CSV_NULL;
        col->name = *(string*)elem->value;
        csv->columns.push_back(col);
    }
    return csv;
}

void CSV::process_entries(VecVecWrapper* entries){
    if (entries == nullptr){
        cerr<<"Entries is null"<<endl;
        exit(1);
    }
    for(VecWrapper* entry: entries->vec){
        if (entry->vec.size() != columns.size()){
            cerr<<"Entry size does not match header size"<<endl;
            exit(1);
        }
        for(int i=0; i<entry->vec.size(); i++){
            CSVElem* elem = entry->vec[i];
            Column* col = columns[i];
            if (col->vtype == CSV_NULL){
                col->vtype = elem->vtype;
            } else if (elem->vtype!=CSV_NULL && col->vtype != elem->vtype){
                cerr<<"Type mismatch in column "<<col->name<<endl;
                exit(1);
            }
            col->values.push_back(elem->value);
        }
    }
}