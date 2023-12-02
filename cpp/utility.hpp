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

void processOnInput( int day, std::function<void( const std::string& )> fPreProcessData )
{
    std::string filePath = std::filesystem::path( __FILE__ )
                               .remove_filename( )
                               .append( std::format( "data/day{}.txt", std::to_string( day ) ) )
                               .string( );
    std::ifstream dataFile( filePath );

    if ( dataFile.is_open( ) ) {
        std::string line;
        while ( std::getline( dataFile, line ) ) {
            fPreProcessData( std::move( line ) );
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

    std::pair<int, int> Solve( )
    {
        processOnInput( 0, [ & ]( auto s ) { doSomethingOnString( s ); } );
        return { 1, 2 };
    }

private:
    void doSomethingOnString( const std::string& s ) { return; }
};

TEST( Day0, test_solution )
{
    Day0 d0;
    const auto [ partOne, partTwo ] = d0.Solve( );
    std::cout << "Part one: " << partOne << std::endl;
    ASSERT_EQ( partOne, 1 );
    std::cout << "Part two: " << partOne << std::endl;
    ASSERT_EQ( partTwo, 2 );
}
