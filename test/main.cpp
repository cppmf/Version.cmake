
// system includes
#include <iostream>

// Include generated version file
#include "TestApp_version.h"


int main(int argc, char* argv[])
{
#if defined (APP_NAME) && defined (APP_VERSION) && defined (APP_VERSION_STRING)
    std::cout << "This is " << APP_NAME << std::endl;
    std::cout << "version: " << APP_VERSION_STRING << " (" << std::hex << APP_VERSION << ")" << std::endl;
    return 0;
#else
    std::cout << "Version not found" << std::endl;
    return 1;
#endif
}
