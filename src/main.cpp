#include <iostream>
#include "avatar.h"

int main(int argc, char *argv[])
{
    std::cout << "\nThe Avatar Project!" << std::endl;

    CAvatar theAvatar;
    return theAvatar.OnExecute(0);
}
