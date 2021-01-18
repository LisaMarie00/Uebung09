#ifndef BIOINFO_VITERBI_H
#define BIOINFO_VITERBI_H

#include <string>

class Viterbi {
    
public:
    /**
     * constructor takes all the necessary arguments
     */
    Viterbi (std::string x, double abn, double ac, double pg0);
    
    /**
     * proves whether x is legit
     */
    bool prove();
    
    /**
     * computes q
     */
    std::string execute();
    
    
private:
    std::string x_;
    double abn_;
    double ac_;
    double pg0_;
};

#endif
