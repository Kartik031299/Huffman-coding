template <typename T>
class MapNode
{
public:
    string key;
    T value;
    MapNode<T> *next;
    MapNode(string key, T value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }

    ~MapNode()
    {
        delete next;
    }
};

template <typename T>
class Map
{
    MapNode<T> **buckets;
    int numBuckets;
    int count;

public:
    Map()
    {
        numBuckets = 5;
        count = 0;
        buckets = new MapNode<T> *[numBuckets];
        for (int i = 0; i < numBuckets; i++)
            buckets[i] = NULL;
    }

    ~Map()
    {
        for (int i = 0; i < numBuckets; i++)
            delete buckets[i];
        delete[] buckets;
    }

private:
    int getIndex(string key) // hash function
    {
        int l = key.length();
        int hashcode = 0, curr_coeff = 1;
        for (int i = l - 1; i >= 0; i--)
        {
            hashcode += key[i] * curr_coeff;
            curr_coeff *= 37;
            hashcode %= numBuckets;
            curr_coeff %= numBuckets;
        }
        return hashcode % numBuckets; // compression function
    }

    void rehash() // rehashing function:- rehashes our map when loadFactor exceeds 0.7
    {
        MapNode<T> **temp = buckets;
        int oldBuckets = numBuckets;
        numBuckets *= 2;
        count = 0;
        buckets = new MapNode<T> *[numBuckets];
        for (int i = 0; i < numBuckets; i++)
            buckets[i] = NULL;
        for (int i = 0; i < oldBuckets; i++)
        {
            MapNode<T> *head = temp[i];
            while (head != NULL)
            {
                string k = head->key;
                T val = head->value;
                insert(k, val);
                head = head->next;
            }
        }
        for (int i = 0; i < oldBuckets; i++)
            delete temp[i];
        delete[] temp;
    }

    double loadFactor() // function to return load factor
    {
        return (1.0 * count) / numBuckets;
    }

    int getSize() // function to return number of keys in our map
    {
        return count;
    }

public:
    void insert(string key, T value) // function to insert a key,value pair in our map
    {
        int index = getIndex(key);
        MapNode<T> *head = buckets[index];
        while (head != NULL)
        {
            if (head->key == key)
            {
                head->value = value;
                return;
            }
            head = head->next;
        }
        MapNode<T> *newnode = new MapNode<T>(key, value);
        newnode->next = buckets[index];
        buckets[index] = newnode;
        count++;
        double loadfactor = loadFactor();
        if (loadfactor > 0.7) // checking condition for rehashing
            rehash();
    }

    T getValue(string key) // function to get value corresponding to key
    {
        int index = getIndex(key);
        MapNode<T> *head = buckets[index];
        while (head != NULL)
        {
            if (head->key == key)
                return head->value;
            head = head->next;
        }
        return 0;
    }

    T removeKey(string key) // function to remove a key
    {
        int index = getIndex(key);
        MapNode<T> *head = buckets[index], *prev = NULL;
        while (head != NULL)
        {
            if (head->key == key)
            {
                if (prev == NULL)
                {
                    buckets[index] = head->next;
                }
                else
                {
                    prev->next = head->next;
                }
                T val = head->value;
                head->next = NULL;
                delete (head);
                count--;
                return val;
            }
            prev = head;
            head = head->next;
        }
        return 0; // denotes invalid key
    }
    T operator[](string key)
    {
        int index = getIndex(key);
        MapNode<T> *head = buckets[index];
        while (head != NULL)
        {
            if (head->key == key)
                return head->value;
            head = head->next;
        }
        return 0;
    }
    string keys()
    {
        string arr = "";
        for (int i = 0; i < numBuckets; i++)
        {
            MapNode<T> *head = buckets[i];
            while (head != NULL)
            {
                arr += head->key;
                head = head->next;
            }
        }
        return arr;
    }
    int size()
    {
        return count;
    }

    int getCount(string key)
    {
        int index = getIndex(key);
        MapNode<T> *head = buckets[index];
        while (head != NULL)
        {
            if (head->key == key)
                return 1;
            head = head->next;
        }
        return 0;
    }
};

Map<int> create_map(string filename)
{
    Map<int> m;
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
            if (m.getCount(key) == 0)
                m.insert(key, 1);
            else
            {
                int x = m.getValue(key);
                m.insert(key, x + 1);
            }
        }
        if (m.getCount("*") == 0)
            m.insert("*", 1);
        else
        {
            int x = m.getValue("*");
            m.insert("*", x + 1);
        }
    }
    return m;
}