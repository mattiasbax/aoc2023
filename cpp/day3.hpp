#pragma once

#include "utility.hpp"

#include <unordered_map>
#include <unordered_set>

class Day3 {
public:
    Day3( ) = default;

    struct number {
        int startPosition;
        int endPosition;
        int value;
    };

    std::pair<int, int> Solve( )
    {
        int engineSchematicsSum = 0;
        int gearRatioSum = 0;
        int rowNumber = 0;
        processOnInput( date, [ & ]( const auto& s ) {
            scanForSymbolsAndNumbers( s, rowNumber );
            if ( rowNumber > 0 ) {
                engineSchematicsSum += calculateEngineSchematicsForRow( rowNumber - 1 );
                gearRatioSum += calculateGearRatioForRow( rowNumber - 1 );
            }
            ++rowNumber;
        } );
        engineSchematicsSum += calculateEngineSchematicsForRow( rowNumber - 1 );
        gearRatioSum += calculateGearRatioForRow( rowNumber - 1 );
        return { engineSchematicsSum, gearRatioSum };
    }

    int calculateEngineSchematicsForRow( int rowNumber )
    {
        int engineSchematics = 0;
        for ( const auto& n : numbers[ rowNumber ] ) {
            if ( checkIfNumberHasNeighboringSymbol( n, rowNumber ) ) {
                engineSchematics += n.value;
            }
        }
        return engineSchematics;
    }

    int calculateGearRatioForRow( int rowNumber )
    {
        int gearRatio = 0;
        if ( gears.contains( rowNumber ) ) {
            for ( const auto gear : gears[ rowNumber ] ) {
                gearRatio += calculateGearRatio( gear, rowNumber );
            }
        }
        return gearRatio;
    }

    void scanForSymbolsAndNumbers( const std::string& s, int rowNumber )
    {
        for ( int i = 0; i < s.size( ); ++i ) {
            if ( numberSet.contains( s[ i ] ) ) {
                const number n = getNumber( s, i );
                numbers[ rowNumber ].push_back( n );
                i = n.endPosition;
            }
            else if ( s[ i ] != '.' ) {
                symbols[ rowNumber ].insert( i );
                if ( s[ i ] == '*' ) {
                    gears[ rowNumber ].push_back( i );
                }
            }
        }
        return;
    }

    number getNumber( const std::string& s, int numberStartPosition )
    {
        int numberEndPosition = numberStartPosition;
        while ( numberEndPosition < s.size( ) && numberSet.contains( s[ numberEndPosition + 1 ] ) ) {
            ++numberEndPosition;
        }
        return {
            numberStartPosition,
            numberEndPosition,
            std::stoi( s.substr( numberStartPosition, numberEndPosition - numberStartPosition + 1 ) )
        };
    }

    bool checkIfNumberHasNeighboringSymbol( const number& n, int rowNumber )
    {
        if ( symbols.contains( rowNumber - 1 ) ) {
            for ( int i = n.startPosition - 1; i <= n.endPosition + 1; ++i ) {
                if ( symbols[ rowNumber - 1 ].contains( i ) )
                    return true;
            }
        }
        if ( symbols.contains( rowNumber ) ) {
            if ( symbols[ rowNumber ].contains( n.startPosition - 1 ) )
                return true;
            if ( symbols[ rowNumber ].contains( n.endPosition + 1 ) )
                return true;
        }
        if ( symbols.contains( rowNumber + 1 ) ) {
            for ( int i = n.startPosition - 1; i <= n.endPosition + 1; ++i ) {
                if ( symbols[ rowNumber + 1 ].contains( i ) )
                    return true;
            }
        }
        return false;
    }

    int calculateGearRatio( int gearPosition, int rowNumber )
    {
        std::vector<number> neighbors;
        if ( numbers.contains( rowNumber - 1 ) ) {
            for ( const auto& n : numbers[ rowNumber - 1 ] ) {
                if ( gearPosition >= ( n.startPosition - 1 ) && gearPosition <= ( n.endPosition + 1 ) )
                    neighbors.push_back( n );
            }
        }
        if ( numbers.contains( rowNumber ) ) {
            for ( const auto& n : numbers[ rowNumber ] ) {
                if ( gearPosition == n.endPosition + 1 || gearPosition == n.startPosition - 1 )
                    neighbors.push_back( n );
            }
        }
        if ( numbers.contains( rowNumber + 1 ) ) {
            for ( const auto& n : numbers[ rowNumber + 1 ] ) {
                if ( gearPosition >= ( n.startPosition - 1 ) && gearPosition <= ( n.endPosition + 1 ) )
                    neighbors.push_back( n );
            }
        }

        if ( neighbors.size( ) == 2 )
            return neighbors.front( ).value * neighbors.back( ).value;
        else
            return 0;
    }

    static constexpr int date = 3;

    std::unordered_set<char> numberSet{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    std::unordered_map<int, std::unordered_set<int>> symbols;

    std::unordered_map<int, std::vector<int>> gears;
    std::unordered_map<int, std::vector<number>> numbers;
};

TEST( Day3, getNumber )
{
    Day3 d3;
    const auto [ numberStartPosition, numberEndPosition, numberValue ] = d3.getNumber( "...437...", 3 );
    ASSERT_EQ( 3, numberStartPosition );
    ASSERT_EQ( 5, numberEndPosition );
    ASSERT_EQ( 437, numberValue );
}

TEST( Day3, scanForSymbols )
{
    Day3 d3;
    constexpr int rowNumber = 0;
    d3.scanForSymbolsAndNumbers( "...#...*...$...", rowNumber );
    ASSERT_EQ( 3, d3.symbols[ rowNumber ].size( ) );
    ASSERT_TRUE( d3.symbols[ rowNumber ].contains( 3 ) );
    ASSERT_TRUE( d3.symbols[ rowNumber ].contains( 7 ) );
    ASSERT_TRUE( d3.symbols[ rowNumber ].contains( 11 ) );
}

TEST( Day3, checkIfNumberHasNeighboringSymbol )
{
    Day3 d3;
    constexpr int rowNumber = 0;
    d3.scanForSymbolsAndNumbers( "...#.......$...", rowNumber );
    const Day3::number n1{ 4, 6, 1 };
    const Day3::number n2{ 5, 7, 1 };
    ASSERT_TRUE( d3.checkIfNumberHasNeighboringSymbol( n1, rowNumber ) );
    ASSERT_FALSE( d3.checkIfNumberHasNeighboringSymbol( n2, rowNumber ) );
}

TEST( Day3, solve )
{
    Day3 d3;
    const auto [ partOne, partTwo ] = d3.Solve( );
    ASSERT_EQ( 531561, partOne );
    ASSERT_EQ( 83279367, partTwo );
}
