struct node {
    int eos = 0, chi = 0;
    node * c[26];
};

node * root;

int getIndex(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    return 0;
}

node * createNode() {
    node * r = new node();
    for (int i = 0; i < 26; i++)
        r->c[i] = 0;
    return r;
}

void insertString(string & s, int i = 0, node * n = root) {
    if (i == s.size()) {
        n->eos++;
        return;
    }
    if (n->c[getIndex(s[i])] == 0)
        n->c[getIndex(s[i])] = createNode(), n->chi++;
    insertString(s, i + 1, n->c[getIndex(s[i])]);
}

bool deleteString(string & s, int i = 0, node * n = root) {
    if (i == s.size()) {
        if (n->eos > 0)
            n->eos--;
        if (n->eos == 0 && n->chi == 0)
            return true;
        else
            return false;
    }
    if (n->c[getIndex(s[i])] == 0)
        return false;
    bool del = deleteString(s, i + 1, n->c[getIndex(s[i])]);
    if (del)
        delete n->c[getIndex(s[i])], n->c[getIndex(s[i])] = 0, n->chi--;
    if (n->eos == 0 && n->chi == 0)
        return true;
    else
        return false;
}

bool inTrie(string & s, int i = 0, node * n = root) {
    if (i == s.size())
        return n->eos > 0;
    if (n->c[getIndex(s[i])] == 0)
        return false;
    else
        return inTrie(s, i + 1, n->c[getIndex(s[i])]);
}

int main() {
    root = createNode();
    string s;
    //insert a string
    insertString(s);
    //delete a string
    deleteString(s);
    //string in trie
    inTrie(s);
}
