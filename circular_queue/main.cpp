#include "circularqueuetests.h"
#include <iostream>

int main()
{
    CircularQueueTests tests;
    bool result = false;
    try
    {
        result = tests.testAll();
    }
    catch(std::runtime_error& error)
    {
        std::cout << error.what() << "\n";
    }
    if(result)
        std::cout << "All tests passed successfully!";
}
