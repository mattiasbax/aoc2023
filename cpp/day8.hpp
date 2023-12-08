#pragma once

#include "utility.hpp"

#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

class Day8 {
public:
    Day8( ) = default;

    struct Paths {
        std::string left;
        std::string right;
    };
    std::unordered_map<std::string, Paths> routeGraph;
    std::string instructions;

    std::pair<int, int> Solve( int runOnTestInput = 0 )
    {
        processOnInput(
            date,
            [ & ]( auto s ) {
                if ( instructions.empty( ) )
                    instructions = s;
                else if ( !s.empty( ) )
                    addToRouteGraph( routeGraph, s );
                return;
            },
            runOnTestInput
        );

        int steps = 1;
        auto currentNode = routeGraph[ "AAA" ];
        for ( int i = 0; i <= instructions.size( ); ++i ) {
            if ( i == instructions.size( ) )
                i = 0;

            std::string nextNode = instructions[ i ] == 'L' ? currentNode.left : currentNode.right;
            if ( nextNode == "ZZZ" )
                break;
            currentNode = routeGraph[ nextNode ];

            ++steps;
        }

        return { steps, 2 };
    }

    static void addToRouteGraph( std::unordered_map<std::string, Paths>& routeGraph, const std::string& s )
    {
        std::regex pattern( R"((\w+)\s*=\s*\((\w+),\s*(\w+)\))" );
        std::smatch matches;
        std::regex_match( s, matches, pattern );
        routeGraph[ matches[ 1 ].str( ) ] = { matches[ 2 ].str( ), matches[ 3 ].str( ) };
    }

private:
    static constexpr int date = 8;
};

TEST( Day8, addToRouteGraph )
{
    std::unordered_map<std::string, Day8::Paths> routeGraph;
    Day8::addToRouteGraph( routeGraph, "AAA = (BBB, CCC)" );

    ASSERT_TRUE( routeGraph.contains( "AAA" ) );
    ASSERT_EQ( routeGraph[ "AAA" ].left, "BBB" );
    ASSERT_EQ( routeGraph[ "AAA" ].right, "CCC" );
}

TEST( Day8, Test )
{
    Day8 d8;
    const auto [ partOne, _ ] = d8.Solve( 1 );
    ASSERT_EQ( partOne, 6 );
}

TEST( Day8, Test_2 )
{
    Day8 d8;
    const auto [ _, partTwo ] = d8.Solve( 2 );
    ASSERT_EQ( partTwo, 6 );
}

TEST( Solve, day_8 )
{
    Day8 d8;
    const auto [ partOne, partTwo ] = d8.Solve( );
    ASSERT_EQ( partOne, 21409 );
    ASSERT_EQ( partTwo, 2 );
}
