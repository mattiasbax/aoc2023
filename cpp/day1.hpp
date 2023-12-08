#pragma once

#include "utility.hpp"

#include <algorithm>
#include <ranges>
#include <unordered_map>

class Day1 {
public:
    Day1( ) = default;

    std::pair<int, int> Solve( ) { return { partOne( ), partTwo( ) }; }

    int partOne( )
    {
        int sumPartOne = 0;
        processOnInput( date, [ & ]( const auto& s ) {
            for ( char c : s ) {
                if ( sizeOne.contains( c ) ) {
                    sumPartOne += 10 * sizeOne[ c ];
                    break;
                }
            }
            for ( char c : s | std::views::reverse ) {
                if ( sizeOne.contains( c ) ) {
                    sumPartOne += sizeOne[ c ];
                    break;
                }
            }
        } );
        return sumPartOne;
    }

    int partTwo( )
    {
        int sumPartTwo = 0;
        processOnInput( date, [ & ]( auto s ) {
            for ( size_t idx = 0; idx < s.size( ); ++idx ) {
                if ( sizeOne.contains( s[ idx ] ) ) {
                    sumPartTwo += 10 * sizeOne[ s[ idx ] ];
                    break;
                }
                if ( idx + 3 < s.size( ) ) {
                    const std::string& subStr = { s.begin( ) + idx, s.begin( ) + idx + 3 };
                    if ( sizeThree.contains( subStr ) ) {
                        sumPartTwo += 10 * sizeThree[ subStr ];
                        break;
                    }
                }
                if ( idx + 4 < s.size( ) ) {
                    const std::string& subStr = { s.begin( ) + idx, s.begin( ) + idx + 4 };
                    if ( sizeFour.contains( subStr ) ) {
                        sumPartTwo += 10 * sizeFour[ subStr ];
                        break;
                    }
                }
                if ( idx + 5 < s.size( ) ) {
                    const std::string& subStr = { s.begin( ) + idx, s.begin( ) + idx + 5 };
                    if ( sizeFive.contains( subStr ) ) {
                        sumPartTwo += 10 * sizeFive[ subStr ];
                        break;
                    }
                }
            }

            for ( int idx = static_cast<int>( s.size( ) ); idx >= 0; --idx ) {
                if ( sizeOne.contains( s[ idx ] ) ) {
                    sumPartTwo += sizeOne[ s[ idx ] ];
                    break;
                }
                if ( idx - 3 >= 0 ) {
                    const std::string& subStr = { s.begin( ) + idx - 3, s.begin( ) + idx };
                    if ( sizeThree.contains( subStr ) ) {
                        sumPartTwo += sizeThree[ subStr ];
                        break;
                    }
                }
                if ( idx - 4 >= 0 ) {
                    const std::string& subStr = { s.begin( ) + idx - 4, s.begin( ) + idx };
                    if ( sizeFour.contains( subStr ) ) {
                        sumPartTwo += sizeFour[ subStr ];
                        break;
                    }
                }
                if ( idx - 5 >= 0 ) {
                    const std::string& subStr = { s.begin( ) + idx - 5, s.begin( ) + idx };
                    if ( sizeFive.contains( subStr ) ) {
                        sumPartTwo += sizeFive[ subStr ];
                        break;
                    }
                }
            }
        } );
        return sumPartTwo;
    }

private:
    static constexpr int date = 1;

    std::unordered_map<char, int> sizeOne{
        { '1', 1 }, { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 }, { '8', 8 }, { '9', 9 }
    };
    std::unordered_map<std::string, int> sizeThree{ { "one", 1 }, { "two", 2 }, { "six", 6 } };
    std::unordered_map<std::string, int> sizeFour{ { "four", 4 }, { "five", 5 }, { "nine", 9 } };
    std::unordered_map<std::string, int> sizeFive{ { "three", 3 }, { "seven", 7 }, { "eight", 8 } };
};

TEST( Solve, day_1 )
{
    Day1 d1;
    const auto [ partOne, partTwo ] = d1.Solve( );
    ASSERT_EQ( partOne, 55386 );
    ASSERT_EQ( partTwo, 54824 );
}
