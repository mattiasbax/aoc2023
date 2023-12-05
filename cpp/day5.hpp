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

    std::pair<unsigned long, unsigned long> Solve( bool runOnTestInput = false )
    {
        enum class State {
            ExtractingSeeds,
            Mapping
        };

        State state = State::ExtractingSeeds;
        std::vector<std::pair<unsigned long, bool>> seeds;

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
                        std::vector<unsigned long> mapEntry;
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        std::string temp;
                        while ( stream >> temp )
                            mapEntry.push_back( std::stoul( temp ) );

                        auto hasNotTransformed = []( auto& seed ) { return !seed.second; };
                        auto isInRange = [ & ]( auto& seed ) {
                            return seed.first >= mapEntry[ 1 ] && seed.first <= mapEntry[ 1 ] + mapEntry[ 2 ];
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
        const unsigned long partOne =
            ( *std::ranges::min_element( seeds, []( auto& lhs, auto& rhs ) { return lhs.first < rhs.first; } ) ).first;
        return { partOne, 2 };
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
    ASSERT_EQ( partTwo, 2 );
}

TEST( Solve, day_5 )
{
    Day5 d5;
    const auto [ partOne, partTwo ] = d5.Solve( );
    std::cout << "Part one: " << partOne << std::endl;
    ASSERT_EQ( partOne, 1 );
    std::cout << "Part two: " << partOne << std::endl;
    ASSERT_EQ( partTwo, 2 );
}
