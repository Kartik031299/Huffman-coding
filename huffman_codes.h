Map<string> m;
Map<string> getHuffmanCodes(Node *root, string c)
{
    if (root == NULL)
        return m;
    root->setCode(root->getCode() + c);
    if (root->getIsTerminal())
    {
        m.insert(root->getKey(), root->getCode());
    }
    if (root->left != NULL)
        getHuffmanCodes(root->left, c + "0");
    if (root->right != NULL)
        getHuffmanCodes(root->right, c + "1");
    return m;
}
void printHuffmanCodes(Map<string> codes, Map<int> m)
{
    for (int i = 0; i < 42; i++)
        cout << "-";
    cout<<endl;
    cout << setw(7) << left << "| Key" << setw(15) << left << "| frequency" << setw(20) << left << "| code" << "|";
    string keys = codes.keys();
    for (int i = 0; i < codes.size(); i++)
    {
        string key = "";
        key += keys[i];
        cout << setw(2) << left <<"| "<<setw(5)<<left<< key << setw(2) << left <<"| "<<setw(13)<<left<< m[key] <<setw(2)<<left<<"| "<<setw(18)<<left<< codes[key] << "|"<<endl;
    }
    for (int i = 0; i < 42; i++)
        cout << "-";
}