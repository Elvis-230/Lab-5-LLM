# Lab 5 - Cosine Distance (C++)

## Name
Elvis Chen

## Overview
This program reads vectors of doubles from an input file, computes cosine similarity and cosine distance for all pairs of vectors, and outputs the pairs ordered from closest (smallest cosine distance) to farthest.

---

## Files
All files are located in the same directory:

- main.cpp → main program execution
- CosDistance.cpp → implementation of cosine distance functions
- CosDistance.h → function declarations
- test.cpp → unit tests
- vectors.txt → sample input file

---

## How to Compile and Run

### Compile the main program

```bash
g++ -std=c++17 main.cpp CosDistance.cpp -o cos_distance