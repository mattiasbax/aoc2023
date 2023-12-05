#pragma once

#include "utility.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Day4 {
public:
    Day4( ) = default;

    std::pair<int, int> Solve( bool testInput = false )
    {
        int sumPartOne = 0;
        int sumPartTwo = 0;
        int ticketNumber = 0;
        std::unordered_map<int, int> copies;
        processOnInput(
            date,
            [ & ]( auto s ) {
                const auto st = convertString( s );
                int numberOfWinningNumbers = numberOfwinningNumbers( st );

                if ( numberOfWinningNumbers ) {
                    sumPartOne += static_cast<int>( std::pow( 2, numberOfWinningNumbers - 1 ) );
                }

                copies[ ticketNumber ]++;
                sumPartTwo += copies[ ticketNumber ];
                for ( int i = 0; i < numberOfWinningNumbers; ++i ) {
                    copies[ ticketNumber + 1 + i ] += copies[ ticketNumber ];
                }
                ++ticketNumber;
            },
            testInput
        );

        return { sumPartOne, sumPartTwo };
    }

    struct ScratchTicket {
        std::unordered_set<int> winningNumbers;
        std::vector<int> numbers;
    };

    ScratchTicket convertString( const std::string& s )
    {
        ScratchTicket st;
        auto begin = s.find( ':' );
        auto end = s.find( '|', begin + 1 );
        const std::string& winningNumbers = s.substr( begin + 2, end - begin - 3 );
        const std::string& numbers = s.substr( end + 2, s.size( ) );

        int temp;
        std::istringstream winningNumberStream( winningNumbers );
        while ( winningNumberStream >> temp ) {
            st.winningNumbers.insert( temp );
        }

        std::istringstream numberStream( numbers );
        while ( numberStream >> temp ) {
            st.numbers.push_back( temp );
        }

        return st;
    }

    int numberOfwinningNumbers( const ScratchTicket& st )
    {
        int numberOfWinningNumbers = 0;
        for ( int number : st.numbers ) {
            if ( st.winningNumbers.contains( number ) ) {
                ++numberOfWinningNumbers;
            }
        }
        return numberOfWinningNumbers;
    }

private:
    static constexpr int date = 4;
};

TEST( Day4, convertString )
{
    Day4 d4;
    ASSERT_EQ( 4, d4.numberOfwinningNumbers( d4.convertString( "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53" ) ) );
}

TEST( Day4, Test )
{
    Day4 d4;
    const auto& [ partOne, partTwo ] = d4.Solve( true );
    ASSERT_EQ( partTwo, 30 );
}

TEST( Solve, day_4 )
{
    Day4 d4;
    const auto& [ partOne, partTwo ] = d4.Solve( );
    ASSERT_EQ( partOne, 21105 );
    ASSERT_EQ( partTwo, 5329815 );
}
