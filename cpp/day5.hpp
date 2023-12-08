#pragma once

#include "utility.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

class Day5 {
public:
    Day5( ) = default;

    std::pair<long long, long long> Solve( bool runOnTestInput = false )
    {
        return { partOne( runOnTestInput ), partTwo( runOnTestInput ) };
    }

    long long partOne( bool runOnTestInput = false )
    {
        enum class State {
            ExtractingSeeds,
            Mapping
        };

        State state = State::ExtractingSeeds;
        std::vector<std::pair<long long, bool>> seeds;

        processOnInput(
            date,
            [ & ]( auto s ) {
                switch ( state ) {
                case State::ExtractingSeeds:
                    if ( !s.empty( ) ) {
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        std::string temp;
                        while ( stream >> temp )
                            seeds.push_back( { std::stoul( temp ), false } );
                    }
                    else {
                        state = State::Mapping;
                    }
                    break;
                case State::Mapping:
                    if ( s.empty( ) ) {
                        std::ranges::for_each( seeds, []( auto& seed ) { seed.second = false; } );
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                        std::vector<long long> mapEntry;
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        std::string temp;
                        while ( stream >> temp )
                            mapEntry.push_back( std::stoul( temp ) );

                        auto hasNotTransformed = []( auto& seed ) { return !seed.second; };
                        auto isInRange = [ & ]( auto& seed ) {
                            return seed.first >= mapEntry[ 1 ] && seed.first < mapEntry[ 1 ] + mapEntry[ 2 ];
                        };
                        auto transform = [ & ]( auto& seed ) {
                            seed.first = seed.first + mapEntry[ 0 ] - mapEntry[ 1 ];
                            seed.second = true;
                        };

                        std::ranges::for_each(
                            seeds | std::views::filter( hasNotTransformed ) | std::views::filter( isInRange ), transform
                        );
                    }
                    break;
                }
            },
            runOnTestInput
        );
        return ( *std::ranges::min_element( seeds, []( auto& lhs, auto& rhs ) { return lhs.first < rhs.first; } )
        ).first;
    }

    long long partTwo( bool runOnTestInput = false )
    {
        enum class State {
            ExtractingSeeds,
            Mapping
        };

        struct Seed {
            long long start;
            long long end;
            bool hasTransformed;
        };

        State state = State::ExtractingSeeds;
        std::vector<Seed> seeds;

        processOnInput(
            date,
            [ & ]( auto s ) {
                switch ( state ) {
                case State::ExtractingSeeds:
                    if ( !s.empty( ) ) {
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        std::string seedStart;
                        std::string seedRange;
                        while ( stream >> seedStart ) {
                            stream >> seedRange;
                            long long start = std::stoll( seedStart );
                            long long end = start + std::stoll( seedRange ) - 1;
                            seeds.push_back( { start, end, false } );
                        }
                    }
                    else {
                        state = State::Mapping;
                    }
                    break;
                case State::Mapping:
                    if ( s.empty( ) ) {
                        std::ranges::for_each( seeds, []( auto& seed ) { seed.hasTransformed = false; } );
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                        std::vector<long long> mapEntry;
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        std::string temp;
                        while ( stream >> temp )
                            mapEntry.push_back( std::stoul( temp ) );

                        auto hasNotTransformed = []( auto& seed ) { return !seed.hasTransformed; };
                        auto isInRange = [ & ]( auto& seed ) {
                            const bool startIsInRange =
                                seed.start >= mapEntry[ 1 ] && seed.start < mapEntry[ 1 ] + mapEntry[ 2 ];
                            const bool endIsInRange =
                                seed.end >= mapEntry[ 1 ] && seed.end < mapEntry[ 1 ] + mapEntry[ 2 ];
                            return startIsInRange || endIsInRange;
                        };
                        auto transform = [ & ]( auto& seed ) {
                            const auto sourceRangeStart = mapEntry[ 1 ];
                            const auto sourceRangeEnd = mapEntry[ 1 ] + mapEntry[ 2 ];
                            const auto diff = mapEntry[ 0 ] - mapEntry[ 1 ];
                            seed.start = std::clamp( seed.start, sourceRangeStart, sourceRangeEnd );
                            seed.end = std::clamp( seed.end, seed.start, sourceRangeEnd );
                            // seed.end = std::min( seed.start, mapEntry[ 1 ] + mapEntry[ 2 ] );

                            // * if isClamped, push new seed to new vector of seeds, add this new vector after transform
                            // is done

                            seed.start = seed.start + diff;
                            seed.end = seed.end + diff;
                            seed.hasTransformed = true;
                        };

                        std::ranges::for_each(
                            seeds | std::views::filter( hasNotTransformed ) | std::views::filter( isInRange ), transform
                        );
                    }
                    break;
                }
            },
            runOnTestInput
        );
        return ( *std::ranges::min_element( seeds, []( auto& lhs, auto& rhs ) { return lhs.start < rhs.start; } )
        ).start;
    }

private:
    static constexpr int date = 5;
    void doSomethingOnString( const std::string& s ) { return; }
};

TEST( Day5, Test )
{
    Day5 d5;
    const auto [ partOne, partTwo ] = d5.Solve( true );
    ASSERT_EQ( partOne, 35 );
    // ASSERT_EQ( partTwo, 82 );
}

TEST( Solve, day_5_part1 )
{
    Day5 d5;
    const auto partOne = d5.partOne( );
    ASSERT_EQ( partOne, 218513636 );
}

// TEST( Solve, day_5_part2 )
// {
//     Day5 d5;
//     const auto partTwo = d5.partTwo( );
//     std::cout << "Part two: " << partTwo << std::endl;
//     ASSERT_EQ( partTwo, 2 );
// }
