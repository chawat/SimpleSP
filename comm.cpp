#include <iostream>
#include <vector>
#include <complex.h>
#include <cmath>
#include "dsp.hpp"
using std::vector;
using namespace std;
using namespace utils;

namespace comm {

    vector<complex<float>> QAM = {{-0.7071, -0.7071}, {-0.7071, 0.7071}, {0.7071, -0.7071}, {0.7071, 0.7071}, {-0.7071, -0.7071}, {-0.7071, -0.2357}, {-0.7071, 0.2357}, {-0.7071, 0.7071}, {-0.2357, -0.7071}, {-0.2357, -0.2357}, {-0.2357, 0.2357}, {-0.2357, 0.7071}, {0.2357, -0.7071}, {0.2357, -0.2357}, {0.2357, 0.2357}, {0.2357, 0.7071}, {0.7071, -0.7071}, {0.7071, -0.2357}, {0.7071, 0.2357}, {0.7071, 0.7071}, {-0.7071, -0.7071}, {-0.7071, -0.5051}, {-0.7071, -0.303}, {-0.7071, -0.101}, {-0.7071, 0.101}, {-0.7071, 0.303}, {-0.7071, 0.5051}, {-0.7071, 0.7071}, {-0.5051, -0.7071}, {-0.5051, -0.5051}, {-0.5051, -0.303}, {-0.5051, -0.101}, {-0.5051, 0.101}, {-0.5051, 0.303}, {-0.5051, 0.5051}, {-0.5051, 0.7071}, {-0.303, -0.7071}, {-0.303, -0.5051}, {-0.303, -0.303}, {-0.303, -0.101}, {-0.303, 0.101}, {-0.303, 0.303}, {-0.303, 0.5051}, {-0.303, 0.7071}, {-0.101, -0.7071}, {-0.101, -0.5051}, {-0.101, -0.303}, {-0.101, -0.101}, {-0.101, 0.101}, {-0.101, 0.303}, {-0.101, 0.5051}, {-0.101, 0.7071}, {0.101, -0.7071}, {0.101, -0.5051}, {0.101, -0.303}, {0.101, -0.101}, {0.101, 0.101}, {0.101, 0.303}, {0.101, 0.5051}, {0.101, 0.7071}, {0.303, -0.7071}, {0.303, -0.5051}, {0.303, -0.303}, {0.303, -0.101}, {0.303, 0.101}, {0.303, 0.303}, {0.303, 0.5051}, {0.303, 0.7071}, {0.5051, -0.7071}, {0.5051, -0.5051}, {0.5051, -0.303}, {0.5051, -0.101}, {0.5051, 0.101}, {0.5051, 0.303}, {0.5051, 0.5051}, {0.5051, 0.7071}, {0.7071, -0.7071}, {0.7071, -0.5051}, {0.7071, -0.303}, {0.7071, -0.101}, {0.7071, 0.101}, {0.7071, 0.303}, {0.7071, 0.5051}, {0.7071, 0.7071}, {-0.7071, -0.7071}, {-0.7071, -0.6128}, {-0.7071, -0.5185}, {-0.7071, -0.4243}, {-0.7071, -0.33}, {-0.7071, -0.2357}, {-0.7071, -0.1414}, {-0.7071, -0.0471}, {-0.7071, 0.0471}, {-0.7071, 0.1414}, {-0.7071, 0.2357}, {-0.7071, 0.33}, {-0.7071, 0.4243}, {-0.7071, 0.5185}, {-0.7071, 0.6128}, {-0.7071, 0.7071}, {-0.6128, -0.7071}, {-0.6128, -0.6128}, {-0.6128, -0.5185}, {-0.6128, -0.4243}, {-0.6128, -0.33}, {-0.6128, -0.2357}, {-0.6128, -0.1414}, {-0.6128, -0.0471}, {-0.6128, 0.0471}, {-0.6128, 0.1414}, {-0.6128, 0.2357}, {-0.6128, 0.33}, {-0.6128, 0.4243}, {-0.6128, 0.5185}, {-0.6128, 0.6128}, {-0.6128, 0.7071}, {-0.5185, -0.7071}, {-0.5185, -0.6128}, {-0.5185, -0.5185}, {-0.5185, -0.4243}, {-0.5185, -0.33}, {-0.5185, -0.2357}, {-0.5185, -0.1414}, {-0.5185, -0.0471}, {-0.5185, 0.0471}, {-0.5185, 0.1414}, {-0.5185, 0.2357}, {-0.5185, 0.33}, {-0.5185, 0.4243}, {-0.5185, 0.5185}, {-0.5185, 0.6128}, {-0.5185, 0.7071}, {-0.4243, -0.7071}, {-0.4243, -0.6128}, {-0.4243, -0.5185}, {-0.4243, -0.4243}, {-0.4243, -0.33}, {-0.4243, -0.2357}, {-0.4243, -0.1414}, {-0.4243, -0.0471}, {-0.4243, 0.0471}, {-0.4243, 0.1414}, {-0.4243, 0.2357}, {-0.4243, 0.33}, {-0.4243, 0.4243}, {-0.4243, 0.5185}, {-0.4243, 0.6128}, {-0.4243, 0.7071}, {-0.33, -0.7071}, {-0.33, -0.6128}, {-0.33, -0.5185}, {-0.33, -0.4243}, {-0.33, -0.33}, {-0.33, -0.2357}, {-0.33, -0.1414}, {-0.33, -0.0471}, {-0.33, 0.0471}, {-0.33, 0.1414}, {-0.33, 0.2357}, {-0.33, 0.33}, {-0.33, 0.4243}, {-0.33, 0.5185}, {-0.33, 0.6128}, {-0.33, 0.7071}, {-0.2357, -0.7071}, {-0.2357, -0.6128}, {-0.2357, -0.5185}, {-0.2357, -0.4243}, {-0.2357, -0.33}, {-0.2357, -0.2357}, {-0.2357, -0.1414}, {-0.2357, -0.0471}, {-0.2357, 0.0471}, {-0.2357, 0.1414}, {-0.2357, 0.2357}, {-0.2357, 0.33}, {-0.2357, 0.4243}, {-0.2357, 0.5185}, {-0.2357, 0.6128}, {-0.2357, 0.7071}, {-0.1414, -0.7071}, {-0.1414, -0.6128}, {-0.1414, -0.5185}, {-0.1414, -0.4243}, {-0.1414, -0.33}, {-0.1414, -0.2357}, {-0.1414, -0.1414}, {-0.1414, -0.0471}, {-0.1414, 0.0471}, {-0.1414, 0.1414}, {-0.1414, 0.2357}, {-0.1414, 0.33}, {-0.1414, 0.4243}, {-0.1414, 0.5185}, {-0.1414, 0.6128}, {-0.1414, 0.7071}, {-0.0471, -0.7071}, {-0.0471, -0.6128}, {-0.0471, -0.5185}, {-0.0471, -0.4243}, {-0.0471, -0.33}, {-0.0471, -0.2357}, {-0.0471, -0.1414}, {-0.0471, -0.0471}, {-0.0471, 0.0471}, {-0.0471, 0.1414}, {-0.0471, 0.2357}, {-0.0471, 0.33}, {-0.0471, 0.4243}, {-0.0471, 0.5185}, {-0.0471, 0.6128}, {-0.0471, 0.7071}, {0.0471, -0.7071}, {0.0471, -0.6128}, {0.0471, -0.5185}, {0.0471, -0.4243}, {0.0471, -0.33}, {0.0471, -0.2357}, {0.0471, -0.1414}, {0.0471, -0.0471}, {0.0471, 0.0471}, {0.0471, 0.1414}, {0.0471, 0.2357}, {0.0471, 0.33}, {0.0471, 0.4243}, {0.0471, 0.5185}, {0.0471, 0.6128}, {0.0471, 0.7071}, {0.1414, -0.7071}, {0.1414, -0.6128}, {0.1414, -0.5185}, {0.1414, -0.4243}, {0.1414, -0.33}, {0.1414, -0.2357}, {0.1414, -0.1414}, {0.1414, -0.0471}, {0.1414, 0.0471}, {0.1414, 0.1414}, {0.1414, 0.2357}, {0.1414, 0.33}, {0.1414, 0.4243}, {0.1414, 0.5185}, {0.1414, 0.6128}, {0.1414, 0.7071}, {0.2357, -0.7071}, {0.2357, -0.6128}, {0.2357, -0.5185}, {0.2357, -0.4243}, {0.2357, -0.33}, {0.2357, -0.2357}, {0.2357, -0.1414}, {0.2357, -0.0471}, {0.2357, 0.0471}, {0.2357, 0.1414}, {0.2357, 0.2357}, {0.2357, 0.33}, {0.2357, 0.4243}, {0.2357, 0.5185}, {0.2357, 0.6128}, {0.2357, 0.7071}, {0.33, -0.7071}, {0.33, -0.6128}, {0.33, -0.5185}, {0.33, -0.4243}, {0.33, -0.33}, {0.33, -0.2357}, {0.33, -0.1414}, {0.33, -0.0471}, {0.33, 0.0471}, {0.33, 0.1414}, {0.33, 0.2357}, {0.33, 0.33}, {0.33, 0.4243}, {0.33, 0.5185}, {0.33, 0.6128}, {0.33, 0.7071}, {0.4243, -0.7071}, {0.4243, -0.6128}, {0.4243, -0.5185}, {0.4243, -0.4243}, {0.4243, -0.33}, {0.4243, -0.2357}, {0.4243, -0.1414}, {0.4243, -0.0471}, {0.4243, 0.0471}, {0.4243, 0.1414}, {0.4243, 0.2357}, {0.4243, 0.33}, {0.4243, 0.4243}, {0.4243, 0.5185}, {0.4243, 0.6128}, {0.4243, 0.7071}, {0.5185, -0.7071}, {0.5185, -0.6128}, {0.5185, -0.5185}, {0.5185, -0.4243}, {0.5185, -0.33}, {0.5185, -0.2357}, {0.5185, -0.1414}, {0.5185, -0.0471}, {0.5185, 0.0471}, {0.5185, 0.1414}, {0.5185, 0.2357}, {0.5185, 0.33}, {0.5185, 0.4243}, {0.5185, 0.5185}, {0.5185, 0.6128}, {0.5185, 0.7071}, {0.6128, -0.7071}, {0.6128, -0.6128}, {0.6128, -0.5185}, {0.6128, -0.4243}, {0.6128, -0.33}, {0.6128, -0.2357}, {0.6128, -0.1414}, {0.6128, -0.0471}, {0.6128, 0.0471}, {0.6128, 0.1414}, {0.6128, 0.2357}, {0.6128, 0.33}, {0.6128, 0.4243}, {0.6128, 0.5185}, {0.6128, 0.6128}, {0.6128, 0.7071}, {0.7071, -0.7071}, {0.7071, -0.6128}, {0.7071, -0.5185}, {0.7071, -0.4243}, {0.7071, -0.33}, {0.7071, -0.2357}, {0.7071, -0.1414}, {0.7071, -0.0471}, {0.7071, 0.0471}, {0.7071, 0.1414}, {0.7071, 0.2357}, {0.7071, 0.33}, {0.7071, 0.4243}, {0.7071, 0.5185}, {0.7071, 0.6128}, {0.7071, 0.7071}};

    vector<complex<float>> QAMMod(vector<int> data, int M, int size) {
        // Number of bits per symbol
        int bitsPerSym = log2(M);

        // Total number of QAM Symbols

        int numSyms = size / bitsPerSym;

        // Buffer for output modulated vector
        vector<complex<float>> modData(numSyms);

        // Iterating over the groups of bits (symbols)
        for (int iter_sym = 0; iter_sym < numSyms; iter_sym++) {
            // Variable representing the symbol in decimal form
            int modIdx = 0;
            // Iterating over each bit in symbol
            for (int iter_bits = 0; iter_bits < bitsPerSym; iter_bits++) {
                // Bit shifting and forming decimal symbol
                modIdx = modIdx << 1;
                modIdx ^= data[iter_sym * bitsPerSym + iter_bits];
            }
            // QAM Modulation from lookup array using symbol as index
            modIdx = (M > 4) * 4 + (M > 16) * 16 + (M > 64) * 64 + modIdx;
            
            modData[iter_sym] = QAM[modIdx];
        }

        return modData;    
    }
    
    vector<int> QAMDemod(vector<complex<float>> modData, int M, int size, int softOut) {
        float dist = 1000;
        int distIdx = 0;
        float dist_tmp = 0;
        int bitsPerSym = log2(M);
        int modIdx = (M > 4) * 4 + (M > 16) * 16 + (M > 64) * 64;
            
        vector<int> demodOut(size * bitsPerSym);

        if (softOut == 0) { // Hard Output
            for (int iter_data = 0; iter_data < size; iter_data++) {
                
                // Iterating over all constellation points and finding the nearest
                // point (smallest euclidean distance)

                for (int iter_const = 0; iter_const < M; iter_const++) {
                    dist_tmp = cAbsDiffSqr(modData[iter_data], QAM[modIdx + iter_const]);   
                    if (dist_tmp <= dist) {
                        distIdx = modIdx + iter_const;
                        dist = dist_tmp;
                    } 
                }

                // Converting decimal symbol into bits

                for (int iter_bits = 0; iter_bits < bitsPerSym; iter_bits++) {
                    demodOut[iter_data * bitsPerSym + bitsPerSym - iter_bits - 1] = distIdx % 2;
                    distIdx /= 2;
                }
            }
        } else { // Soft Output

        }

        return demodOut;
    }

}