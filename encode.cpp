#include <bits/stdc++.h>
using namespace std;
#include"map.h"
#include"priority_queue.h"
#include "huffman_codes.h"
#include "encoding.h"
#include "jsonify.h"

int main(){
    Map<int> m = create_map("text.txt");
    Node* root=build_Huffman_Tree(m);
    Map<string> codes = getHuffmanCodes(root,"");
    printHuffmanCodes(codes, m);
    string ans = encoded(codes, "text.txt");
    int flush_bits = getfile(ans);
    createJson(codes, flush_bits);
    remove("text.txt");
    return 0;
}