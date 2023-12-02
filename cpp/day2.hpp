#include "utility.hpp"

#include <unordered_map>

class Day2 {
public:
    Day2( ) : maxRed( 12 ), maxGreen( 13 ), maxBlue( 14 ) { }

    std::pair<int, int> Solve( )
    {
        int gameCounter = 1;
        int sumPartOne = 0;
        int sumPartTwo = 0;
        processOnInput( date, [ & ]( auto s ) {
            // Part one
            if ( checkGameValidity( s ) ) {
                sumPartOne += gameCounter;
            }
            gameCounter++;

            // Part two
            sumPartTwo += countPowerOfFewestCubes( s );
        } );

        return { sumPartOne, sumPartTwo };
    }

    bool checkGameValidity( const std::string& s )
    {
        for ( int i = 10; i < s.size( ) - 2; ++i ) {
            if ( s[ i ] == 'r' && s[ i - 1 ] == ' ' ) {
                int redSum = hTable[ s[ i - 2 ] ];
                if ( hTable.contains( s[ i - 3 ] ) ) {
                    redSum += hTable[ s[ i - 3 ] ] * 10;
                }
                if ( redSum > maxRed )
                    return false;
            }
            else if ( s[ i ] == 'g' && s[ i - 1 ] == ' ' ) {
                int greenSum = hTable[ s[ i - 2 ] ];
                if ( hTable.contains( s[ i - 3 ] ) ) {
                    greenSum += hTable[ s[ i - 3 ] ] * 10;
                }
                if ( greenSum > maxGreen )
                    return false;
            }
            else if ( s[ i ] == 'b' && s[ i - 1 ] == ' ' ) {
                int blueSum = hTable[ s[ i - 2 ] ];
                if ( hTable.contains( s[ i - 3 ] ) ) {
                    blueSum += hTable[ s[ i - 3 ] ] * 10;
                }
                blueSum = std::max( blueSum, blueSum );
                if ( blueSum > maxBlue )
                    return false;
            }
        }
        return true;
    }

    int countPowerOfFewestCubes( const std::string& s )
    {
        int maxRedSum = 0;
        int maxGreenSum = 0;
        int maxBlueSum = 0;
        for ( int i = 10; i < s.size( ) - 2; ++i ) {
            if ( s[ i ] == 'r' && s[ i - 1 ] == ' ' ) {
                int redSum = hTable[ s[ i - 2 ] ];
                if ( hTable.contains( s[ i - 3 ] ) ) {
                    redSum += hTable[ s[ i - 3 ] ] * 10;
                }
                maxRedSum = std::max( maxRedSum, redSum );
            }
            else if ( s[ i ] == 'g' && s[ i - 1 ] == ' ' ) {
                int greenSum = hTable[ s[ i - 2 ] ];
                if ( hTable.contains( s[ i - 3 ] ) ) {
                    greenSum += hTable[ s[ i - 3 ] ] * 10;
                }
                maxGreenSum = std::max( maxGreenSum, greenSum );
            }
            else if ( s[ i ] == 'b' && s[ i - 1 ] == ' ' ) {
                int blueSum = hTable[ s[ i - 2 ] ];
                if ( hTable.contains( s[ i - 3 ] ) ) {
                    blueSum += hTable[ s[ i - 3 ] ] * 10;
                }
                maxBlueSum = std::max( maxBlueSum, blueSum );
            }
        }
        return maxRedSum * maxGreenSum * maxBlueSum;
    }

private:
    static constexpr int date = 2;
    const int maxRed;
    const int maxGreen;
    const int maxBlue;

    std::unordered_map<char, int> hTable{
        { '0', 0 },
        { '1', 1 },
        { '2', 2 },
        { '3', 3 },
        { '4', 4 },
        { '5', 5 },
        { '6', 6 },
        { '7', 7 },
        { '8', 8 },
        { '9', 9 }
    };
};

TEST( Day2, checkGameValidity )
{
    Day2 d2;
    ASSERT_TRUE( d2.checkGameValidity( "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green" ) );
    ASSERT_FALSE( d2.checkGameValidity( "8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red" ) );
}

TEST( Day2, countPowerOfFewestCubes )
{
    Day2 d2;
    ASSERT_EQ( 48, d2.countPowerOfFewestCubes( "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green" ) );
    ASSERT_EQ( 12, d2.countPowerOfFewestCubes( "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue" ) );
    ASSERT_EQ( 36, d2.countPowerOfFewestCubes( "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green" ) );
}

TEST( Day2, solve )
{
    Day2 d2;
    const auto [ partOne, partTwo ] = d2.Solve( );
    ASSERT_EQ( partOne, 2528 );
    ASSERT_EQ( partTwo, 67363 );
}
