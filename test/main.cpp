
// system includes
#include <iostream>

// Include generated version file
#include "TestApp_version.h"


int main(int argc, char* argv[])
{
#if defined (TESTAPP_NAME) && defined (TESTAPP_VERSION) && defined (TESTAPP_VERSION_STRING)
    std::cout << "This is " << TESTAPP_NAME << std::endl;
    std::cout << "version: " << TESTAPP_VERSION_STRING << " (" << std::hex << TESTAPP_VERSION << ")" << std::endl;
    return 0;
#else
    std::cout << "Version not found" << std::endl;
    return 1;
#endif
}
