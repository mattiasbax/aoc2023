#pragma once

#include "utility.hpp"

#include <algorithm>
#include <deque>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>

class Day9 {
public:
    Day9( ) = default;

    std::pair<int, int> Solve( bool runOnTestInput = false )
    {
        int sumPartOne = 0;
        int sumPartTwo = 0;
        processOnInput(
            date,
            [ & ]( auto s ) {
                std::istringstream stream( s );

                std::vector<int> sequence;
                int sequenceNumber;
                while ( stream >> sequenceNumber )
                    sequence.push_back( sequenceNumber );

                sumPartOne += extraPolateForward( sequence );
                sumPartTwo += extraPolateBackward( std::deque( sequence.begin( ), sequence.end( ) ) );
            },
            runOnTestInput
        );
        return { sumPartOne, sumPartTwo };
    }

    static int extraPolateForward( std::vector<int> sequence )
    {
        std::vector<int> lastElements;
        while ( !std::ranges::all_of( sequence, []( auto& val ) { return val == 0; } ) ) {
            lastElements.push_back( sequence.back( ) );
            std::adjacent_difference( sequence.begin( ) + 1, sequence.end( ), sequence.begin( ) );
            sequence.pop_back( );
        }
        return std::accumulate( lastElements.begin( ), lastElements.end( ), 0 );
    }

    static int extraPolateBackward( std::deque<int> sequence )
    {
        std::deque<int> firstElements;
        while ( !std::ranges::all_of( sequence, []( auto& val ) { return val == 0; } ) ) {
            firstElements.push_front( sequence.front( ) );
            std::adjacent_difference( sequence.begin( ), sequence.end( ), sequence.begin( ) );
            sequence.pop_front( );
        }
        return std::accumulate( firstElements.begin( ), firstElements.end( ), 0, []( int lhs, int rhs ) {
            return rhs - lhs;
        } );
    }

private:
    static constexpr int date = 9;
};

TEST( Day9, extraPolateBackward )
{
    int result = Day9::extraPolateBackward( { 10, 13, 16, 21, 30, 45 } );
    ASSERT_EQ( 5, result );
}

TEST( Day9, Test_1 )
{
    Day9 d9;
    const auto [ partOne, partTwo ] = d9.Solve( 1 );
    ASSERT_EQ( partOne, 114 );
    ASSERT_EQ( partOne, 2 );
}

TEST( Solve, day_9 )
{
    Day9 d9;
    const auto [ partOne, partTwo ] = d9.Solve( );
    ASSERT_EQ( partOne, 1898776583 );
    ASSERT_EQ( partTwo, 1100 );
}
