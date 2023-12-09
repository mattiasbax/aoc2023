#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

void processOnInput( int day, std::function<void( const std::string& )> fPreProcessData, int testInput = 0 )
{
    const std::string filePath = std::filesystem::path( __FILE__ )
                                     .remove_filename( )
                                     .append( std::format(
                                         "data/day{}{}{}.txt",
                                         std::to_string( day ),
                                         testInput ? "_test" : "",
                                         testInput ? std::to_string( testInput ) : ""
                                     ) )
                                     .string( );
    std::ifstream dataFile( filePath );

    if ( dataFile.is_open( ) ) {
        std::string line;
        while ( std::getline( dataFile, line ) ) {
            fPreProcessData( line );
        }
        dataFile.close( );
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

class Day0 {
public:
    Day0( ) = default;

    std::pair<int, int> Solve( int runOnTestInput = 0 )
    {
        processOnInput(
            date, [ & ]( auto s ) { doSomethingOnString( s ); }, runOnTestInput
        );
        return { 1, 2 };
    }

private:
    static constexpr int date = 0;
    void doSomethingOnString( const std::string& s ) { return; }
};

TEST( Solve, day_0 )
{
    Day0 d0;
    const auto [ partOne, partTwo ] = d0.Solve( );
    ASSERT_EQ( partOne, 1 );
    ASSERT_EQ( partTwo, 2 );
}
