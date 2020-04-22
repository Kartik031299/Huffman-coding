#include<iostream>
#include<iomanip>
using namespace std;
#include"json.hpp"
using json = nlohmann::json;


void createJson(Map<string> m, int flush_bits){
    string keys = m.keys();
    json j;
    for(int i=0; i<m.size(); i++){
        string key = "";
        key += keys[i];
        j[key] = m[key];
    }
    j["flush_bits"] = flush_bits;
    ofstream o("codes.json");
    o<<setw(4)<<j<<endl;
}

Map<string> readJson(){
    ifstream i("codes.json");
    json j;
    i>>j;
    Map<string> code;
    for(json::iterator it = j.begin(); it!=j.end();it++){
        if(it.key().length()>1){
            continue;
        }
        code.insert(it.key(),string(*it));
    }
    return code;
}

int get_flush_bits(){
    ifstream i("codes.json");
    json j;
    i>>j;
    return j["flush_bits"];
}