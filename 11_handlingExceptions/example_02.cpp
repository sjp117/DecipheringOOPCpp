#include <iostream>
#include <exception>

void AppSpecificTerminate()
{
    std::cout << "Uncaught exception. Program terminating" << std::endl;
    exit(1);
}

int main()
{
    std::set_terminate(AppSpecificTerminate);
    return 0;
}