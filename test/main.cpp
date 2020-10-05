
// system includes
#include <iostream>

// Include generated version file
#include "test_app_version.h"


int main(int argc, char* argv[])
{
    std::cout << "This is " << TEST_APP_NAME << std::endl;
    std::cout << "version: " << TEST_APP_VERSION_STRING << " (" << std::hex << TEST_APP_VERSION << ")" << std::endl;

    return 0;
}
