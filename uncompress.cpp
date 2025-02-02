#include <iostream>
#include <string>
#include <vector>
#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

vector<int> readOptimizedHeader(FancyInputStream& in) {
    vector<int> freqs(256, 0);

    // Read total number of symbols
    int num_symbols = in.read_byte();
    cout << "num symbol:" << num_symbols ;
    //if empty
    if(num_symbols == -1){
    }

    // Read each the char and freq pair
    for (int i = 0; i < num_symbols; ++i) {
        unsigned char byte = in.read_byte(); 

        // Read the 3byte freq
        unsigned int freq = (in.read_byte() << 16) |
                            (in.read_byte() << 8) |
                            in.read_byte();
        cout << freq << " ";
        freqs[byte] = freq;
    }

    return freqs;
}

void printHuffmanTree(const HCNode* node, int depth = 0) {
    if (!node) return;

    // Indentation based on the depth of the node
    for (int i = 0; i < depth; ++i) {
        cout << "  ";
    }

    // Print the node's symbol and frequency
    if (!node->c0 && !node->c1) {
        // Leaf node: Display the symbol (ASCII or binary) and its count
        cout << "Leaf: '" << node->symbol << "' (ASCII: " 
             << static_cast<int>(node->symbol) << "), Frequency: " << node->count << "\n";
    } else {
        // Internal node: Display the combined frequency
        cout << "Internal: Frequency: " << node->count << "\n";
    }

    // Recursively print left and right subtrees
    printHuffmanTree(node->c0, depth + 1);
    printHuffmanTree(node->c1, depth + 1);
}


int main(int argc, char* argv[]) {
    cout << "argc = " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "] = " << argv[i] << " ";
    }
    if(argc!=3) {
        return 1;
    }

    FancyInputStream* in = new FancyInputStream(argv[1]);
    FancyOutputStream* out = new FancyOutputStream(argv[2]);
    //check good
    if (!(in->good())){ 
        error("One of the stream's error state flags (eofbit, failbit and badbit) is set.");
        return 1;
    }

    //Read the file header
    vector<int> freq = readOptimizedHeader(*in);
    //if empty


    HCTree* tree = new HCTree();
    tree->build(freq);
    printHuffmanTree(tree->getRoot(),0);
    //sum up freq
    int sumOfFreq = 0;
    int i=0;
    for(auto it=freq.begin(); it!=freq.end(); ++it){
        sumOfFreq+=freq[i];
        i++;
    }
    cout << "sum freq:" << sumOfFreq <<endl;

    //decode, output to file
    //for loop 
    for (int i = 0; i<sumOfFreq; i++) {
        char decodeChar = tree->decode(*in);
        cout << "Char write in:" << decodeChar << endl;
        out->write_byte(decodeChar);
    }
    
    delete tree;
    tree = nullptr;

    delete in;
    delete out;
    in = nullptr;
    out = nullptr;

    return 0;
}