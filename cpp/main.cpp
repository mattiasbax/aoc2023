#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"

#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main( int argc, char** argv )
{
    std::cout << "Merry christmas 2023!" << std::endl;
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}