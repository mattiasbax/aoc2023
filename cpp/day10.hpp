#pragma once

#include "utility"

#include <iostream>
#include <unordered_map>
#include <vector>

class Day10 {
public:
    struct Pos {
        int x;
        int y;

        auto operator<=>( const Pos& ) const = default;
    };

    // std::unordered_map<char, Pos> pipes{
    //     { 'F', { 1, 1 } }, { '7', {-1,1} }, { 'J', {1,1} }, { '|', {0,1} }, { 'L', {1,-1} }, { '-', {1,0} }
    // };

    Day10( ) = default;

    std::pair<int, int> Solve( int runOnTestInput = 10 )
    {
        processOnInput(
            date, [ & ]( auto s ) { return; }, runOnTestInput
        );
        return { 1, 2 };
    }

    static Pos nextStep( Pos from, Pos current, char pipe )
    {
        Pos direction = { from.x - current.x, from.y - current.y };
        if ( direction == Pos{ 1, 0 } ) { // From left
            std::cout << "From left!" << std::endl;
        }
        else if ( direction == Pos{ -1, 0 } ) { // From right
            std::cout << "From right!" << std::endl;
        }
        else if ( direction == Pos{ 0, -1 } ) { // From above
            std::cout << "From above!" << std::endl;
        }
        else if ( direction == Pos{ 0, 1 } ) { // From above
            std::cout << "From below!" << std::endl;
        }
        else {
            std::cout << "This should not happen!" << std::endl;
        }
        return { 0, 0 };
    }

    static int findNumberOfStepsInGraphLoop( const Pos& start, std::vector<std::vector<char>>& map ) { return 0; }

private:
    static constexpr int date = 10;
    void doSomethingOnString( const std::string& s ) { return; }
};

TEST( Day10, findNumberOfStepsInGraphLoop )
{
    std::vector<std::vector<char>> map;
    map.push_back( { '.', '.', 'F', '7', '.' } );
    map.push_back( { '.', 'F', 'J', '|', '.' } );
    map.push_back( { 'S', 'J', '.', 'L', '7' } );
    map.push_back( { '|', 'F', '-', '-', 'J' } );
    map.push_back( { 'L', 'J', '.', '.', '.' } );

    Day10::Pos start{ 0, 2 };

    Day10::Pos p = Day10::nextStep( Day10::Pos{ 0, 2 }, Day10::Pos{ 0, 3 }, '|' );

    // ASSERT_EQ( 8, Day10::findStepsInGraphLoop( start, map ) );
    ASSERT_TRUE( true );
}

TEST( Solve, day_10 )
{
    Day10 d10;
    const auto [ partOne, partTwo ] = d10.Solve( );
    ASSERT_EQ( partOne, 1 );
    ASSERT_EQ( partTwo, 2 );
}
