string encoded(Map<string>& codes, string filename)
{
    string ans = "";
    ifstream fin;
    char *ch = new char[filename.length()+1];
    for (int i = 0; i < filename.length(); i++)
        ch[i] = filename[i];
    ch[filename.length()] = '\0';
    fin.open(ch, ios::in);
    string data;
    while (getline(fin, data))
    {
        for (int i = 0; i < data.length(); i++)
        {
            string key = "";
            key += data[i];
            ans += codes[key];
        }
        ans+=codes["*"];
    }
    fin.close();
    return ans;
}

int current_bit = 0;
unsigned char bit_buffer;
FILE *f;
void WriteBit(int bit)
{
    if (bit)
        bit_buffer |= 1 << current_bit;
    current_bit++;
    if (current_bit == 8)
    {
        ofstream fout("binary.txt", ios::app);
        fout << bit_buffer;
        bit_buffer = 0;
        current_bit = 0;
        fout.close();
    }
}
int Flush_Bits(void)
{
    int count = 0;
    while (current_bit)
    {
        count++;
        WriteBit(0);
    }
    return count;
}
int getfile(string a)
{
    remove("binary.txt");
    string s = a;
    for (int i = 0; i < s.size(); i++)
    {
        WriteBit((int)s[i] - 48);
    }
    return Flush_Bits();
}