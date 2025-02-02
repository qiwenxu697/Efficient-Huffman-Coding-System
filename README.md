# Efficient Huffman Coding System 

## 🔍 Overview
The **Efficient Huffman Coding System** is a C++ implementation of Huffman compression and decompression.  
It efficiently compresses text and binary files using **Huffman coding**, a lossless data compression algorithm.

This project demonstrates:
- **Bitwise file manipulation** with custom `FancyInputStream` and `FancyOutputStream`.
- **Tree-based compression** using **Huffman coding**.
- **Optimized file headers** to store Huffman trees efficiently.
- **Efficient memory management** with recursive tree deletion.

---

## 🚀 Features
✔️ **Fast Compression & Decompression**  
✔️ **Optimized Bitwise I/O Operations**  
✔️ **Tree-based Header Serialization** for Efficient Storage  
✔️ **Supports Large Input Files** (10MB+)  

**1️⃣ Clone the Repository**

**2️⃣ Compile the Program**
Use the provided Makefile to compile everything: 

``make``

**3️⃣ Run**

Compress a File

``./compress input.txt compressed.bin

input.txt can be change to name of the input file

Decompress a file
`./uncompress compressed.bin output.txt`

## 📊 Performance & Optimization
Tree-based header format reduces file size vs. naïve frequency tables.
Bitwise writing & reading optimizes disk usage.
Efficient memory management with proper tree deletion.
