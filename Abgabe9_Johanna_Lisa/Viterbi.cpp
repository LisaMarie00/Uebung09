#include "Viterbi.h"
#include "Matrix.h"
#include <cmath>
#include <algorithm>

Viterbi::Viterbi(std::string x, double abn, double ac, double pg0) : x_(x), abn_(abn), ac_(ac), pg0_(pg0) {}

bool Viterbi::prove() {
    bool erg = true;
    auto iter = x_.begin();
    for (; iter != x_.end(); iter++) {
        char c = *iter;
        if (c != '0' && c != '1') {
           erg = false;
           break;
        }
    }
    return erg;
}

std::string Viterbi::execute() {
    Matrix matrix = Matrix::Matrix(x_.size() + 1, 3);
    //initialization
    matrix.setValue(0, 0, 0); //n
    matrix.setValue(1, 0, 0); //g
    matrix.setValue(2, 0, 1); //begin
    matrix.setValue(0, 1, log10(0.5) + 1 + log10(abn_));
    if (x_.at(0) == '0') {
        matrix.setValue(1, 1, log10(pg0_) + 1 + log10(1 - abn_));
    } else {
        matrix.setValue(1, 1, log10(1 - pg0_) + 1 + log10(1 - abn_));
    }
    for (int j = 2; j <= x_.size(); j++) {
        char c = x_.at(j-1);
        double valn = log10(0.5) + std::max (
            matrix.getValue(1, j-1) + log10(ac_), matrix.getValue(0, j-1) + log10(1 - ac_)
        );
        double valg;
        if  (c == '0') {
            valg = log10(pg0_) + std::max (
            matrix.getValue(1, j-1) + log10(1 - ac_), matrix.getValue(0, j-1) + log10(ac_)
        );
        } else {
            valg = log10(1 - pg0_) + std::max (
            matrix.getValue(1, j-1) + log10(1 - ac_), matrix.getValue(0, j-1) + log10(ac_)
            );
        }
        matrix.setValue(0, j, valn);
        matrix.setValue(1, j, valg);
    }
    std::string q;
    /*
     * find max of last column
     * we save our actual q: 0 = n, 1 = g
     */
    int qi;
    if (matrix.getValue(0, x_.size()) > matrix.getValue(1, x_.size())) {
        qi = 0;
        q.push_back('n');
    } else {
        qi = 1;
        q.push_back('g');
    }
    for (int j = x_.size() - 1; j > 0; j--) {
        if (qi == 0) {
            double n = log10(0.5) + matrix.getValue(0, j-1) + log10(1 - ac_);
            double g = log10(0.5) + matrix.getValue(0, j-1) + log10(ac_);
            double val = matrix.getValue(0, j);
            if (fabs(val - n) < fabs(val - g)) {
                q.push_back('n');
            } else {
                q.push_back('g');
                qi = 1;
            }
        } else {
            if (x_.at(j-1) == '0') {
                double n = log10(pg0_) + matrix.getValue(0, j-1) + log10(ac_);
                double g = log10(pg0_) + matrix.getValue(0, j-1) + log10(1 - ac_);
                double val = matrix.getValue(1, j);
            if (fabs(val - n) < fabs(val - g)) {
                q.push_back('n');
                qi = 0;
            } else {
                q.push_back('g');
            }
            } else {
                double n = log10(1 - pg0_) + matrix.getValue(0, j-1) + log10(ac_);
                double g = log10(1 - pg0_) + matrix.getValue(0, j-1) + log10(1 - ac_);
                double val = matrix.getValue(1, j);
                if (fabs(val - n) < fabs(val - g)) {
                    q.push_back('n');
                    qi = 0;
                } else {
                    q.push_back('g');
                }
            }
        }
    }
    std::reverse(q.begin(), q.end());
    return q;
}
