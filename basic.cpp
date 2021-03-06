#include <iostream>
#include <vector>
#include <complex.h>
#include <cmath>
#include "dsp.hpp"
using std::vector;
using namespace std;
using namespace utils;
using namespace filter;

// Decimation, Interpolation and Resampling

namespace basic {

    // Performs 1-d Convolution on two complex vectors

    vector<complex<float>> conv1d(vector<complex<float>> x1, vector<complex<float>> x2) {
        int LEN_CONV_SEQ = x1.size() + x2.size() - 1;

        // Adding zeros in order to have both the sequences 
        // of the same length

        x1 = zeroPadding(x1, len(x2));
        x2 = zeroPadding(x2, len(x1));

        vector<complex<float>> y;

        // Convolution sum

        for (int i = 0; i < LEN_CONV_SEQ; i++) {
            complex<float> tmp = 0;
            for (int j = 0; j <= i; j++) {
                tmp += x1[j] * x2[i - j];
            }
            y.push_back(tmp);
        }

        return y;
    }

    // Performs 1-d Circular Convolution on two complex vectors

    vector<complex<float>> circConv(vector<complex<float>> x1, vector<complex<float>> x2) {
        int LEN_CONV_SEQ = utils::max(len(x1), len(x2));

        // Adding zeros in order to have both the sequences 
        // of the same length
        
        x1 = zeroPadding(x1, (LEN_CONV_SEQ - len(x1)));
        x2 = zeroPadding(x2, (LEN_CONV_SEQ - len(x2)));

        vector<complex<float>> y;
        int ind = 0;

        for (int i = 0; i < LEN_CONV_SEQ; i++) {
            complex<float> tmp = 0;
            for (int j = 0; j < LEN_CONV_SEQ; j++) {
                ind = ((i - j) < 0) * (LEN_CONV_SEQ + i - j) + (((i - j) >= 0) * (i - j));
                tmp += x1[j] * x2[ind];
            }
            y.push_back(tmp);
        }

        return y;
    }

    vector<complex<float>> correlation(vector<complex<float>> x1, vector<complex<float>> x2) {
        vector<complex<float>> y;

        y = conv1d(x1, conj(flip(x2)));

        return y;
    }

    
    vector<complex<float>> dft(vector<complex<float>> x, int N) {
        complex<float> tmp;
        vector<complex<float>> y;

        if (x.size() < N) {
            int tmp = x.size();
            for (int i = 0; i < (N - tmp); i++) {
                x.push_back(complex<float>{0, 0});
            }
        }

        for (int i = 0; i < N; i++) {
            tmp = complex<float>{0, 0};
            for (int j = 0; j < N; j++) {
                tmp += x[j] * complex<float>{cos(2 * M_PI * j * i / N), -sin(2 * M_PI * j * i / N)};
            }
            y.push_back(tmp);
        }
        return y;
    }

    vector<complex<float>> idft(vector<complex<float>> x, int N) {
        complex<float> tmp;

        vector<complex<float>> y;

        if (x.size() < N) {
            int tmp = x.size();
            for (int i = 0; i < (N - tmp); i++) {
                x.push_back(complex<float>{0, 0});
            }
        }

        for (int i = 0; i < N; i++) {
            tmp = complex<float>{0, 0};
            for (int j = 0; j < N; j++) {
                tmp += x[j] * complex<float>{cos(2 * M_PI * j * i / N), sin(2 * M_PI * j * i / N)};
            }
            y.push_back(tmp/(complex<float>){N, 0});
        }
        return y;
    }

    vector<complex<float>> fft(vector<complex<float>> x, int N, int inv) {
        complex<float> tmp;
        const int D = log2(N);

        if (x.size() < N) {
            int tmp = x.size();
            for (int i = 0; i < (N - tmp); i++) {
                x.push_back(complex<float>{0, 0});
            }
        }
        return fftCompute(x, N, inv);   
    }

    vector<complex<float>> twiddle(int N, int inv) {
        vector<complex<float>> y;
        for (int i = 0; i < N; i++) {
            y.push_back(complex<float>(cos(2 * M_PI * i / N), sin(2 * M_PI * (2 * inv - 1) * i / N)));
        }
        return y;
    }

    vector<complex<float>> fftCompute(vector<complex<float>> x, int N, int inv) {
        if (N == 2) {
            vector<complex<float>> y;
            y.push_back(x[0] + x[1]);
            y.push_back(x[0] - x[1]);
            return y;
        }
        vector<complex<float>> tmp1, tmp2, fft1, fft2;
        tmp1 = utils::getEvenOddTerms(x, 0);
        tmp2 = utils::getEvenOddTerms(x, 1);
        fft1 = fftCompute(tmp1 , N/2, inv);
        fft2 = fftCompute(tmp2 , N/2, inv);
        return fftCombine(fft1, fft2, N, inv);
    }

    vector<complex<float>> fftCombine(vector<complex<float>> x1, vector<complex<float>> x2, int N, int inv) {
        vector<complex<float>> y, w = twiddle(N, inv);
                
        for (int i = 0; i < N/2; i++) {
            y.push_back(x1[i] + w[i] * x2[i]);
        }
        for (int i = 0; i < N/2; i++) {
            y.push_back(x1[i] - w[i] * x2[i]);
        }
        return y;
    }

    vector<complex<float>> ifft(vector<complex<float>> x, int N) {
        vector<complex<float>> y;
        
        if (x.size() < N) {
            int tmp = x.size();
            for (int i = 0; i < (N - tmp); i++) {
                x.push_back(complex<float>{0, 0});
            }
        }

        y = fft(x, N, 1);

        for (int i = 0; i < N; i++) {
            y[i] /= complex<float>{N, 0};
        }

        return y;        
    }

    vector<complex<float>> downSample(vector<complex<float>> x, int downSampleRate) {
        vector<complex<float>> y;

        for (int i = 0; i < x.size(); i += downSampleRate) {
            y.push_back(x[i]);
        }

        return y;
    }

    vector<complex<float>> decimate(vector<complex<float>> x, int downSampleRate, float sampleRate) {
        float newSampleRate = sampleRate / downSampleRate;
        
        vector<complex<float>> filterResp = FIRLowPass(newSampleRate / 2, newSampleRate / 2, sampleRate, 7, 0);
        vector<complex<float>> LPFOut = applyFIRFilter(filterResp, x);
        return downSample(LPFOut, downSampleRate);
    }

    vector<complex<float>> upSample(vector<complex<float>> x, int upSampleRate) {
        vector<complex<float>> y;

        for (int i = 0; i < x.size(); i ++) {
            y.push_back(x[i]);
            for (int j = 0; j < upSampleRate; j++) {
                y.push_back(complex<float>{0, 0});
            }
        }

        return y;
    }

    vector<complex<float>> interpolate(vector<complex<float>> x, int upSampleRate, float sampleRate) {
        float newSampleRate = upSampleRate * sampleRate;
        
        vector<complex<float>> filterResp = FIRLowPass(newSampleRate / 2, newSampleRate / 2, newSampleRate, 7, 0);
        vector<complex<float>> LPFOut = applyFIRFilter(filterResp, upSample(x, upSampleRate));
        return LPFOut;    
    }

};