#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

bool isEmpty(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate); // Open in binary mode, position at the end
    return file.is_open() && file.tellg() == 0;      // Check if position (size) is 0
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
    //TODO: throw an error message
    if(argc!=3) {
        return 1;
    }
    int totalFreq=0;
    int totalChar=0;

    //count the freq
    FancyInputStream* in = new FancyInputStream(argv[1]);
    FancyOutputStream* out = new FancyOutputStream(argv[2]);

    vector<int> freq = vector(256,0);
    int byte = in->read_byte();
    //if empty
    string filename = argv[1];
    if(isEmpty(filename)){
        //out.write_bit();
        delete in;
        delete out;
        return 0;
    }
    while (byte != -1){
        ++freq[byte];
        byte = in->read_byte();
    }
    HCTree* tree = new HCTree();
    tree->build(freq);
    printHuffmanTree(tree->getRoot(),0);

    //file header
    //for each symbol in vector

    for (int f : freq) {
        cout << f << " ";
        ++totalChar;
        if (f>0){
            ++totalFreq;
        }
    }
    out->write_byte(totalFreq);
    for(int i=0;i<256;i++) {
        if (freq[i] > 0) {
            out->write_byte(i); //Write in the char
            out->write_byte((freq[i] >> 16) & 0xFF); // Most significant byte of frequency
            out->write_byte((freq[i] >> 8) & 0xFF);  // Middle byte
            out->write_byte(freq[i] & 0xFF);         // Least significant byte
        }
    }

    //Move back to the beginning of the input file
    in->reset();
    byte = in->read_byte();
    while (byte != -1){
        tree->encode(char(byte),*out);
        cout << "end";
        byte = in->read_byte();
    }

    //Close the input and output files
    delete tree;
    delete in;
    delete out;
    return 0;
}