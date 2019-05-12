#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Interface.h"
#include <iostream>


int main() {
    testing::InitGoogleTest();
    testing::InitGoogleMock();
    RUN_ALL_TESTS();

    /*std::cout << "Hello! It's a text - strategy. Your aim is to destroy army of your opposite fraction " << std::endl;
    std::cout << "Select your fraction: 1 - Alliance, 2 - Horde " << std::endl;
    size_t fraction;
    std::cin >> fraction;
    Game game(fraction);
    game.Handle();
    game.logger_->Analyze();*/

    return 0;

}
