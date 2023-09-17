#include "build-settings.h"
#if RUN_TESTS == true
#include "test/test.hpp"
#include "test/assert.hpp"
#include "utils/string.hpp"
#include "utils/math.h"
#include "utils/util.hpp"
#include "io/MemoryMgmt.hpp"
#include "logic/collections/LinkedList.hpp"

#define TEST(a, b, c) if(!Assert::assert(a, b, 0, c)) return false
#define DO_TEST(a) if(!a) return false;

bool testString(char* errorMsg) {
    String testStr = String("Bingus ist ");
    testStr.append("ein Kadser\0");
    TEST(strcmp(testStr.getData(), "Bingus ist ein Kadser"), "String (1): Construction, Appending\0", errorMsg);
    TEST(testStr.equals("Bingus ist ein Kadser"), "String (2): equals w/ char*: expected true\0", errorMsg);
    TEST(testStr.equals(String("Bingus ist ein Kadser")), "String (3): equals w/ string: expected true\0", errorMsg);
    TEST(!testStr.equals("This is wrong"), "String (4): equals w/ string failed: expected false\0", errorMsg);
    TEST(!testStr.equals(String("This is wrong")), "String (5): equals w/ string failed: expected false\0", errorMsg);


    return true;
}

bool testStrcmp(char* errorMsg) {
    TEST(strcmp("abcd", "abcd"), "strcmp (1): Failed basic compare: expected true\0", errorMsg);
    TEST(!strcmp("abcd", "dcba"), "strcmp (2): Failed basic compare: expected false\0", errorMsg);

    return true;
}

bool testPow(char* errorMsg) {
    TEST(pow(88888, 1) == 88888, "pow (1): Failed calculation 1\0", errorMsg);
    TEST(pow(10, 2) == 100, "pow (2): Failed calculation 2\0", errorMsg);
    TEST(pow(10, 3) == 1000, "pow (3): Failed calculation 3\0", errorMsg);
    TEST(pow(10, 4) == 10000, "pow (4): Failed calculation 4\0", errorMsg);
    TEST(pow(10, 5) == 100000, "pow (5): Failed calculation 5\0", errorMsg);

    return true;
}

bool testItoa(char* errorMsg) {
    char itoaBuff[5];
    itoa(1000, itoaBuff, 5);
    TEST(strcmp(itoaBuff, "1000"), "itoa (1): Failed conversion 1\0", errorMsg);

    return true;
}

bool testAtoi(char* errorMsg) {
    TEST(atoi("1000") == 1000, "atoi (1): Failed conversion 1\0", errorMsg);
    TEST(atoi("-1000") == -1000, "atoi (2): Failed conversion 2\0", errorMsg);
    TEST(atoi("9123782") == 9123782, "atoi (3): Failed conversion 3\0", errorMsg);
    TEST(atoi("-883726223") == -883726223, "atoi (4): Failed conversion 4\0", errorMsg);
    return true;
}

bool testMemoryAllocation(char* errorMsg) {
    unsigned long requestedMemory = 1024;
    MemoryPageDetails allocation = MemoryMgmt::allocateMemory(requestedMemory);
    TEST(allocation.allocated, "MemoryMgmt (1): Failed correct allocation\0", errorMsg);

    char* numChar = new char[10];
    itoa(allocation.length, numChar, 9);
    String error = String("MemoryMgmt (2): Failed allocation of 1024 bytes, got ");
    error.append(numChar);
    TEST(allocation.length >= requestedMemory, error.getData(), errorMsg);

    requestedMemory = 1024000;
    const char* testChars = new char[requestedMemory];

    for(int i = 0; i < requestedMemory; i++) {
        TEST(testChars[i] == '\0', "MemoryMgmt (3): Failed cleanup of 1024000 bytes\0", errorMsg);
    }

    return true;
}

bool testLinkedList(char* errorMsg) {
    LinkedList<String*>* linkedList = new LinkedList<String*>();
    linkedList->append(new String("Hello"));
    linkedList->append(new String("World"));
    linkedList->append(new String("!"));

    LinkedListEnumerator<String*> enumerator = linkedList->getEnumerator();
    String** currentEntry;
    int counter = 0;

    String error = String("");

    while(currentEntry = enumerator.next()) {
        if(currentEntry == 0) {
            continue;
        }

        counter++;
        if(counter == 1) {
            error = String("Invalid entry, expected Hello, got ");
            error.append((*currentEntry)->getData());
            TEST((*currentEntry)->equals("Hello"), error.getData(), errorMsg);
        }
        else if(counter == 2) {
            error = String("Invalid entry, expected World, got ");
            error.append((*currentEntry)->getData());
            TEST((*currentEntry)->equals("World"), error.getData(), errorMsg);
        }
        else if(counter == 3) {
            error = String("Invalid entry, expected !, got ");
            error.append((*currentEntry)->getData());
            TEST((*currentEntry)->equals("!"), error.getData(), errorMsg);
        }
        else if(counter > 3) {
            TEST(false, "LinkedList: Too many entries\0", errorMsg);
        }
    }

    TEST(counter == 3, "LinkedList: Too few entries\0", errorMsg);

    return true;
}

bool Test::selfCheck(char* errorMsg) {
    DO_TEST(testStrcmp(errorMsg));
    DO_TEST(testPow(errorMsg));
    DO_TEST(testItoa(errorMsg));
    DO_TEST(testAtoi(errorMsg));
    DO_TEST(testMemoryAllocation(errorMsg));
    DO_TEST(testString(errorMsg));
    DO_TEST(testLinkedList(errorMsg));

    return true;
}
#endif
