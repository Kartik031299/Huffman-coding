class Node
{
    int frequency;
    string key;
    string code;
    bool isTerminal;

public:
    Node *left, *right;
    Node(string key, int frequency, bool isTerminal = true)
    {
        this->key = key;
        this->frequency = frequency;
        this->isTerminal = isTerminal;
        this->code = "";
        this->left = NULL;
        this->right = NULL;
    }

    string getKey()
    {
        return this->key;
    }

    int getFrequency()
    {
        return this->frequency;
    }

    bool getIsTerminal()
    {
        return this->isTerminal;
    }

    string getCode()
    {
        return this->code;
    }

    void setCode(string s)
    {
        this->code = s;
    }
};
class PriorityQueue
{
    vector<Node *> v;

public:
    PriorityQueue() {}

    void insert(Node *n)
    {
        v.push_back(n);
        int childIndex = v.size() - 1;
        while (childIndex > 0) // up-heapify
        {
            int parentIndex = (childIndex - 1) / 2;
            if (v[parentIndex]->getFrequency() > v[childIndex]->getFrequency())
            {
                Node *temp = v[childIndex];
                v[childIndex] = v[parentIndex];
                v[parentIndex] = temp;
                childIndex = parentIndex;
            }
            else
                break;
        }
    }

    PriorityQueue(Map<int>& m)
    {
        string key_list = m.keys();
        for (int i = 0; i < m.size(); i++)
        {
            string k = "";
            k += key_list[i];
            Node *p = new Node(k, m[k]);
            insert(p);
        }
    }

    Node* removeMin()
    {
        if (v.size() == 0)
            return NULL;
        Node *ans = v[0];
        v[0] = v[v.size() - 1];
        v.pop_back();
        int parentIndex = 0;
        int leftIndex = 2 * parentIndex + 1;
        int rightIndex = 2 * parentIndex + 2;
        while (leftIndex < v.size()) // down-heapify
        {
            int minIndex = parentIndex;
            if (v[leftIndex]->getFrequency() < v[minIndex]->getFrequency())
                minIndex = leftIndex;
            if (rightIndex < v.size())
                if (v[rightIndex]->getFrequency() < v[minIndex]->getFrequency())
                    minIndex = rightIndex;
            if (minIndex == parentIndex)
                break;
            else
            {
                Node *temp = v[parentIndex];
                v[parentIndex] = v[minIndex];
                v[minIndex] = temp;
                parentIndex = minIndex;
                leftIndex = 2 * parentIndex + 1;
                rightIndex = 2 * parentIndex + 2;
            }
        }
        //cout<<"m";
        return ans;
    }
    string getMin()
    {
        if (v.size() == 0)
            return "";
        return v[0]->getKey();
    }

    int getSize()
    {
        return v.size();
    }
};


Node* build_Huffman_Tree(PriorityQueue* pq,const Map<int>& m)
{
    while (pq->getSize() > 1)
    {
        Node *n1 = pq->removeMin();
        Node *n2 = pq->removeMin();
        Node *n3 = new Node(n1->getKey() + n2->getKey(), n1->getFrequency() + n2->getFrequency(), false);
        n3->left = n1;
        n3->right = n2;
        pq->insert(n3);
    }
    return (pq->removeMin());
}