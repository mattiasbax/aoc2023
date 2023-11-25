#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

template <typename T>
std::vector<T> readInput( int day, std::function<T( std::string&& )> fPreProcessData )
{
    std::vector<T> input;
    std::string filePath = std::filesystem::path( __FILE__ )
                               .remove_filename( )
                               .append( std::format( "data/day{}.txt", std::to_string( day ) ) )
                               .string( );
    std::ifstream dataFile( filePath );

    if ( dataFile.is_open( ) ) {
        std::string line;
        while ( std::getline( dataFile, line ) ) {
            input.push_back( fPreProcessData( std::move( line ) ) );
        }
        dataFile.close( );
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
    return input;
}

void day0( )
{
    std::vector<int> input = readInput<int>( 0, []( auto s ) { return std::stoi( s ); } );

    for ( auto i : input )
        std::cout << i << std::endl;
}

TEST( Day0, test_solution )
{
    day0( );
    ASSERT_TRUE( true );
}
