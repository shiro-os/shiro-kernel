#include "test.hpp"
#include "assert.hpp"
#include "../utils/string.hpp"
#include "../utils/math.h"
#include "../utils/util.hpp"

#define TEST(a, b, c) if(!Assert::assert(a, b, c)) return false
#define DO_TEST(a) if(!a) return false

bool testString(char* errorMsg) {
    String testStr = String("Bingus ist ");
    testStr.append("ein Kadser");
    TEST(strcmp(testStr.getData(), "Bingus ist ein Kadser"), "String: Construction, Appending", errorMsg);

    return true;
}

bool testStrcmp(char* errorMsg) {
    TEST(strcmp("abcd", "abcd"), "strcmp: Failed basic compare", errorMsg);

    return true;
}

bool testPow(char* errorMsg) {
    TEST(pow(88888, 1) == 88888, "pow: Failed calculation 1", errorMsg);
    TEST(pow(10, 2) == 100, "pow: Failed calculation 2", errorMsg);
    TEST(pow(10, 3) == 1000, "pow: Failed calculation 3", errorMsg);
    TEST(pow(10, 4) == 10000, "pow: Failed calculation 4", errorMsg);
    TEST(pow(10, 5) == 100000, "pow: Failed calculation 5", errorMsg);

    return true;
}

bool testItoa(char* errorMsg) {
    char itoaBuff[5];
    itoa(1000, itoaBuff, 5);
    TEST(strcmp(itoaBuff, "1000"), "itoa: Failed conversion 1", errorMsg);


    return true;
}

bool testAtoi(char* errorMsg) {
    TEST(atoi("1000") == 1000, "atoi: Failed conversion 1", errorMsg);
    TEST(atoi("-1000") == -1000, "atoi: Failed conversion 2", errorMsg);
    TEST(atoi("9123782") == 9123782, "atoi: Failed conversion 3", errorMsg);
    TEST(atoi("-883726223") == -883726223, "atoi: Failed conversion 4", errorMsg);
    return true;
}

bool Test::selfCheck(char* errorMsg) {
    DO_TEST(testStrcmp(errorMsg));
    DO_TEST(testPow(errorMsg));
    DO_TEST(testItoa(errorMsg));
    DO_TEST(testAtoi(errorMsg));
    DO_TEST(testString(errorMsg));

    return true;
}
