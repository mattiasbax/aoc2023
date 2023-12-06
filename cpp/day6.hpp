#pragma once

#include "utility.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>

class Day6 {
public:
    Day6( ) = default;

    std::vector<int> times;
    std::vector<int> distances;

    std::pair<int, int> Solve( bool runOnTestInput = false )
    {
        processOnInput(
            date,
            [ & ]( const std::string& s ) {
                const std::string& sub = s.substr( s.find( ':' ) + 1, s.size( ) );
                std::istringstream subStream( sub );

                int value;
                if ( times.empty( ) ) {
                    while ( subStream >> value )
                        times.push_back( value );
                }
                else {
                    while ( subStream >> value )
                        distances.push_back( value );
                }
            },
            runOnTestInput
        );

        std::vector<int> numberOfWaysToBeat;
        for ( int i = 0; i < times.size( ); ++i ) {
            numberOfWaysToBeat.push_back( calculateNumberOfRaceOptions( times[ i ], distances[ i ] ) );
        }
        int sumPartOne =
            std::accumulate( numberOfWaysToBeat.begin( ), numberOfWaysToBeat.end( ), 1, std::multiplies<int>( ) );

        std::stringstream tStream;
        for ( const auto& i : times ) {
            tStream << i;
        }
        long long timesValue = std::stoll( tStream.str( ) );

        std::stringstream dStream;
        for ( const auto& i : distances ) {
            dStream << i;
        }
        long long distanceValue = std::stoll( dStream.str( ) );

        int sumPartTwo = calculateNumberOfRaceOptions( timesValue, distanceValue );

        return { sumPartOne, sumPartTwo };
    }

    template <typename T>
    T calculateNumberOfRaceOptions( T totalRaceTime, T distanceToBeat )
    {
        auto numbers = std::views::iota( 1, totalRaceTime ) | std::views::transform( [ = ]( auto timePressingButton ) {
                           const auto velocity = timePressingButton;
                           const auto timeRacing = totalRaceTime - timePressingButton;
                           const auto distanceTravelled = timeRacing * velocity;
                           return distanceTravelled;
                       } );
        auto it = std::ranges::upper_bound( numbers, distanceToBeat );
        T upperBoundIdx = static_cast<T>( std::distance( numbers.begin( ), it ) + 1 );
        return totalRaceTime - ( 2 * upperBoundIdx ) + 1;
    }

private:
    static constexpr int date = 6;
};

TEST( Day6, calculateNumberOfRaceOptions )
{
    Day6 d6;
    ASSERT_EQ( 4, d6.calculateNumberOfRaceOptions( 7, 9 ) );
    ASSERT_EQ( 8, d6.calculateNumberOfRaceOptions( 15, 40 ) );
    ASSERT_EQ( 9, d6.calculateNumberOfRaceOptions( 30, 200 ) );
    ASSERT_EQ( 71503, d6.calculateNumberOfRaceOptions( 71530, 940200 ) );
}

TEST( Day6, Test )
{
    Day6 d6;
    const auto [ partOne, partTwo ] = d6.Solve( true );
    ASSERT_EQ( 288, partOne );
    ASSERT_EQ( 71503, partTwo );
}

TEST( Solve, day_6 )
{
    Day6 d6;
    const auto [ partOne, partTwo ] = d6.Solve( );
    ASSERT_EQ( 2065338, partOne );
    ASSERT_EQ( 34934171, partTwo );
}
