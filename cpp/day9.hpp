#pragma once

#include "utility.hpp"

#include <algorithm>
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
                sumPartTwo += extraPolateBackward( sequence );
            },
            runOnTestInput
        );
        return { sumPartOne, 2 };
    }

    int extraPolateForward( std::vector<int> sequence )
    {
        std::vector<int> lastElements;
        while ( !std::ranges::all_of( sequence, []( auto& val ) { return val == 0; } ) ) {
            lastElements.push_back( sequence.back( ) );
            for ( int i = 0; i < sequence.size( ) - 1; ++i ) {
                sequence[ i ] = sequence[ i + 1 ] - sequence[ i ];
            }
            sequence.pop_back( );
        }
        return std::accumulate( lastElements.begin( ), lastElements.end( ), 0 );
    }

    int extraPolateBackward( std::vector<int> sequence ) { return 0; }

private:
    static constexpr int date = 9;
};

TEST( Day9, Test_1 )
{
    Day9 d9;
    const auto [ partOne, partTwo ] = d9.Solve( 1 );
    ASSERT_EQ( partOne, 114 );
}

TEST( Solve, day_9 )
{
    Day9 d9;
    const auto [ partOne, partTwo ] = d9.Solve( );
    ASSERT_EQ( partOne, 1898776583 );
    ASSERT_EQ( partTwo, 2 );
}
