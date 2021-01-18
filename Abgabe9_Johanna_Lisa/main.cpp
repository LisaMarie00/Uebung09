#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<cassert>
#include<sstream>

#include "Viterbi.h"

int main(int argc, char* argv[])
{
    std::string h = "-h";
    std::string help = "--help";
	//if one of our arguments is --help or -h we print a text on the command line
    for (int i = 0; i < argc; i++) {
        if (h.compare(argv[i]) == 0 || help.compare(argv[i]) == 0){
            std::cout << "Help window:\n";
            std::cout << "-h / --help: opens this help window\n";
            std::cout << "-x [x1..xn]: the sequence of coin toss\n";
            std::cout << "-abn / --abegin->n [probability out of [0,1]]: the probability to start with the fair coin\n";
            std::cout << "-ac /--ak->q [probability out of [0,1]]: the probability to change the coins\n";
            std::cout << "-pg0 [probability out of [0,1]]: the probability to get number under the condition you play with the unfair coin\n";
            return 0;
        }
    }
    std::string x = "-x";
    std::string a = "-abn";
    std::string abn = "--abegin->n";
    std::string ac = "-ac";
    std::string akq = "--ak->q";
    std::string pg = "-pg0";
    std::string xstr;
    std::string abegstr;
    std::string achstr;
    std::string pgstr;
    double abeginn;
    double achange;
    double pg0;
    if (argc != 9) {
        std::cerr << "wrong number of arguments\n";
        return 1;
    }
    for (int i = 0; i < argc; i++) {
        if (x.compare(argv[i]) == 0) {
            if (i+1 >= argc) {
                std::cerr << "flag but no sequence \n use -h or --help to open the help window\n";
                return 1;
            }
            size_t comp0 = 0;
            if (xstr.size() == comp0) {
                xstr = argv[i+1];
            } else {
                std::cerr << "more than one sequence given\n use -h or --help to open the help window\n";
                return 1;
            }
        }
        if (a.compare(argv[i]) == 0 || abn.compare(argv[i]) == 0) {
            if (i+1 >= argc) {
                std::cerr << "flag but no probability\n use -h or --help to open the help window\n";
                return 1;
            }
            size_t comp0 = 0;
            if (abegstr.size() == comp0) {
                abegstr = argv[i+1];
                abeginn = stod(abegstr);
            } else {
                std::cerr << "more than one probability given\n use -h or --help to open the help window\n";
                return 1;
            }
        }
        if (ac.compare(argv[i]) == 0 || akq.compare(argv[i]) == 0) {
            if (i+1 >= argc) {
                std::cerr << "flag but no probability given\n use -h or --help to open the help window\n";
                return 1;
            }
            size_t comp0 = 0;
            if (achstr.size() == comp0) {
                achstr = argv[i+1];
                achange = stod(achstr);
            } else {
                std::cerr << "more than one probability given\n use -h or --help to open the help window\n";
                return 1;
            }
        }
        if (pg.compare(argv[i]) == 0) {
            if (i+1 >= argc) {
                std::cerr << "flag but no probability given\n use -h or --help to open the help window\n";
                return 1;
            }
            size_t comp0 = 0;
            if (pgstr.size() == comp0) {
                pgstr = argv[i+1];
                pg0 = stod(pgstr);
            } else {
                std::cerr << "more than one probability given\n use -h or --help to open the help window\n";
                return 1;
            }
        }
    }

    if (!pgstr.size() || !abegstr.size() || !xstr.size() || !achstr.size()) {
        std::cerr << "something important is not given.\n use -h or --help to open the help window\n";
        return 1;
    }
    
    Viterbi viterbi(xstr, abeginn, achange, pg0);
    if (viterbi.prove()) {
        std::string q = viterbi.execute();
        std::cout << "computed path: \n" << q << std::endl;
        return 0;
    } else {
        std::cerr << "sequence can' include any other char than 0 or 1\n";
        return 1;
    }
} 
