#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
#include <iostream>
using namespace std;
string get_encoded_string(string filename, int flush_bits)
{
    char *ch = new char[filename.length()];
    for (int i = 0; i < filename.length(); i++)
        ch[i] = filename[i];
    ch[filename.length()] = '\0';
    ifstream f(ch, ios::binary);
    char c;
    string ans = "";
    while (f.get(c))
    {
        int temp = c;
        bitset<8> b(temp);
        string t = b.to_string();
        reverse(t.begin(), t.end());
        ans += t;
    }
    ans.erase(ans.length() - flush_bits);
    return ans;
}
/*
string getDeocodedString(string s, Node *root)
{
    string ans = "";
    Node *temp = root;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
        {
            if (temp->left->getIsTerminal())
            {
                ans = ans + temp->left->getKey();
                temp = root;
            }
            else
                temp = temp->left;
        }
        else
        {
            if (temp->right->getIsTerminal())
            {
                ans = ans + temp->right->getKey();
                temp = root;
            }
            else
                temp = temp->right;
        }
    }
    return ans;
}
*/
void getDecodedFile(string s, Map<string> m)
{
    string keys = m.keys();
    Map<string> reverseMap;
    for (int i = 0; i < keys.length(); i++)
    {
        string key = "";
        key += keys[i];
        reverseMap.insert(m[key], key);
    }
    string ans = "";
    string key = "";
    ofstream o("text.txt");

    for (int i = 0; i < s.length(); i++)
    {
        key += s[i];
        if (reverseMap.getCount(key) > 0)
        {
            string value = reverseMap.getValue(key);
            if (value == "*")
            {
                cout<<ans<<"\n";
                o << ans;
                o <<"\n";
                ans = "";
                key = "";
            }
            else
            {
                ans = ans + value;
                key = "";
            }
        }
    }
    remove("binary.txt");
}