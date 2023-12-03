#pragma once

#include "utility.hpp"

#include <unordered_map>
#include <unordered_set>

class Day3 {
public:
    Day3( ) = default;

    std::pair<int, int> Solve( )
    {
        int engineSchematicsSum = 0;
        std::string previousRow;
        int rowNumber = 0;
        processOnInput( date, [ & ]( const auto& s ) {
            scanForSymbols( s, rowNumber );
            if ( !previousRow.empty( ) ) {
                engineSchematicsSum += calculateEngineSchematicsForRow( previousRow, rowNumber - 1 );
            }
            previousRow = s;
            ++rowNumber;
        } );
        engineSchematicsSum += calculateEngineSchematicsForRow( previousRow, rowNumber - 1 );
        return { engineSchematicsSum, 2 };
    }

    int calculateEngineSchematicsForRow( const std::string& s, int rowNumber )
    {
        int sum = 0;
        for ( int i = 0; i < s.size( ); ++i ) {
            if ( numberSet.contains( s[ i ] ) ) {
                int numberEndPosition;
                int engineNumber = getNumber( s, i, numberEndPosition );
                if ( checkIfNumberHasNeighbors( i, numberEndPosition, rowNumber ) ) {
                    sum += engineNumber;
                }
                i = numberEndPosition;
            }
        }
        return sum;
    }

    void scanForSymbols( const std::string& s, int rowNumber )
    {
        for ( int i = 0; i < s.size( ); ++i ) {
            if ( s[ i ] != '.' ) {
                symbols[ rowNumber ].insert( i );
            }
        }
        return;
    }

    int getNumber( const std::string& s, int numberStartPosition, int& numberEndPosition )
    {
        if ( !numberSet.contains( s[ numberStartPosition ] ) ) {
            return 0;
        }

        numberEndPosition = numberStartPosition;
        while ( numberEndPosition < s.size( ) && numberSet.contains( s[ numberEndPosition + 1 ] ) ) {
            ++numberEndPosition;
        }
        return std::stoi( s.substr( numberStartPosition, numberEndPosition - numberStartPosition + 1 ) );
    }

    bool checkIfNumberHasNeighbors( int numberStartPosition, int numberEndPosition, int rowNumber )
    {
        if ( symbols.contains( rowNumber - 1 ) ) {
            for ( int i = numberStartPosition - 1; i <= numberEndPosition + 1; ++i ) {
                if ( symbols[ rowNumber - 1 ].contains( i ) )
                    return true;
            }
        }
        if ( symbols.contains( rowNumber ) ) {
            if ( symbols[ rowNumber ].contains( numberStartPosition - 1 ) )
                return true;
            if ( symbols[ rowNumber ].contains( numberEndPosition + 1 ) )
                return true;
        }
        if ( symbols.contains( rowNumber + 1 ) ) {
            for ( int i = numberStartPosition - 1; i <= numberEndPosition + 1; ++i ) {
                if ( symbols[ rowNumber + 1 ].contains( i ) )
                    return true;
            }
        }
        return false;
    }

    static constexpr int date = 3;

    std::unordered_set<char> numberSet{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    std::unordered_map<int, std::unordered_set<int>> symbols;
};

TEST( Day3, getNumber )
{
    Day3 d3;
    int numberEndPosition;
    ASSERT_EQ( 437, d3.getNumber( "...437...", 3, numberEndPosition ) );
    ASSERT_EQ( 5, numberEndPosition );
}

TEST( Day3, scanForSymbols )
{
    Day3 d3;
    constexpr int rowNumber = 0;
    d3.scanForSymbols( "...#...*...$...", rowNumber );
    ASSERT_EQ( 3, d3.symbols[ rowNumber ].size( ) );
    ASSERT_TRUE( d3.symbols[ rowNumber ].contains( 3 ) );
    ASSERT_TRUE( d3.symbols[ rowNumber ].contains( 7 ) );
    ASSERT_TRUE( d3.symbols[ rowNumber ].contains( 11 ) );
}

TEST( Day3, checkIfNumberHasNeighbors )
{
    Day3 d3;
    constexpr int rowNumber = 0;
    d3.scanForSymbols( "...#.......$...", rowNumber );
    ASSERT_TRUE( d3.checkIfNumberHasNeighbors( 4, 6, 1 ) );
    ASSERT_FALSE( d3.checkIfNumberHasNeighbors( 5, 7, 1 ) );
}

TEST( Day3, solve )
{
    Day3 d3;
    const auto [ partOne, partTwo ] = d3.Solve( );
    std::cout << "Part one: " << partOne << std::endl;
    ASSERT_TRUE( true );
}
