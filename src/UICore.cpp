#include "UICore.h"

#include <iostream>

namespace UICore
{
    void ShowImageWindow(const std::filesystem::path imagePath)
    {
        std::cout << "Displaying image: " << imagePath.string() << std::endl;
    }
}
