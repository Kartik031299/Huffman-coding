#include <bits/stdc++.h>
using namespace std;
#include "map.h"
//#include"priority_queue.h"
#include "decoding.h"
#include "jsonify.h"

int main()
{
    Map<string> codes = readJson();
    string decoded = get_encoded_string("binary.txt", get_flush_bits());
    getDecodedFile(decoded, codes);
    return 0;
}