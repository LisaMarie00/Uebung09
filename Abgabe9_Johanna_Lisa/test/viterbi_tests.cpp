#include <gtest/gtest.h>

#include "../Viterbi.h" 


TEST(Viterbi, prove) {
    Viterbi viterbi ("01001010010", 0.9, 0.1, 0.75);
    ASSERT_TRUE(viterbi.prove());
}

TEST(Viterbi, proveFalse) {
    Viterbi viterbi ("0120101010", 0.9, 0.1, 0.75);
    ASSERT_FALSE(viterbi.prove());
}

TEST(Viterbi, executeSimple) {
    Viterbi viterbi ("010", 0.9, 0.1, 0.75);
    std::string q = viterbi.execute();
    std::string s = "nnn";
    ASSERT_EQ(s, q);
}

TEST(Viterbi, ac1) {
    Viterbi viterbi ("010001010", 0.9, 1.0, 0.5);
    std::string q = viterbi.execute();
    std::string s = "ngngngngn";
    ASSERT_EQ(s, q);
}

TEST(Viterbi, execute) {
    Viterbi viterbi ("010001010", 0.9, 0.1, 0.75);
    std::string q = viterbi.execute();
    std::string s = "nnnnnnnnn";
    ASSERT_EQ(s, q);
}
