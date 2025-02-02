#include "HCTree.hpp"

void HCTree::deleteTree(HCNode* node) {
    if (!node) { return; }

    // Recursively delete left and right 
    deleteTree(node->c0); 
    deleteTree(node->c1); 

    delete node;
}

HCTree::~HCTree() {
    deleteTree(root);

    root = nullptr;
}

void HCTree::build(const vector<int>& freqs) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    for(long unsigned int i = 0; i < freqs.size(); ++i) {
        if(freqs[i] > 0){
            HCNode* leafNode = new HCNode(freqs[i], static_cast<unsigned char>(i)); //pointer
            pq.push(leafNode);
            this->leaves[i] = leafNode;
        }
    }
    if (pq.size() == 1) {
        root = pq.top();
    }

    while(pq.size() > 1) {
        HCNode* t1 = pq.top();
        pq.pop();
        HCNode* t2 = pq.top();
        
        HCNode* parent = new HCNode(t1->count + t2->count,t2->symbol);
        pq.pop();
        parent->c0=t2;
        parent->c1=t1;
        t1->p=parent;
        t2->p=parent;
        pq.push(parent);

        if (!pq.empty()){
            root = pq.top();
        } else {
            root = nullptr;
        }
    }
}

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const {
    //find the symbol in the tree
    stack<bool> code;
    int numSym = symbol;
    HCNode* current = leaves[numSym];
    if(current == nullptr) {
        return; //can't find the symbol in tree, not in ascii
    }
    HCNode* currParent = current->p;
    while(currParent != nullptr){
        cout << "\n symbol:" << symbol; 
        if(currParent->c0 == current){
            //current is the child with label 0
            code.push(0); 
        } else {
            code.push(1);
        }
        current = currParent;
        currParent = currParent->p;
    }
    while (!code.empty()){
        out.write_bit(code.top());
        cout << "wirte in: " << code.top() << " "; 
        code.pop();
    }

}

unsigned char HCTree::decode(FancyInputStream &in) const {
    HCNode* curr = root;
    if(curr->c0 == nullptr || curr->c1 == nullptr) {
        return curr->symbol;
    }
    while (curr->c0 != nullptr || curr->c1 != nullptr) {
        int bit = in.read_bit();
        cout <<"read in: " << bit << "; ";
        if (bit == 0) {
            curr=curr->c0;
        } else if(bit == 1) {
            curr=curr->c1;
        } 
    }
    cout << "\nwrite in: " << curr->symbol << endl; 
    return curr->symbol;
}

HCNode* HCTree::getRoot() const {
    return root;
}

