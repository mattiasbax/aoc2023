#pragma once

#include "utility.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Day8 {
public:
    Day8( ) = default;

    struct Paths {
        std::string left;
        std::string right;
    };
    std::unordered_map<std::string, Paths> routeGraph;
    std::string instructions;

    std::pair<int, long long> Solve( int runOnTestInput = 0 )
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

        return { partOne( routeGraph, instructions ), partTwo( routeGraph, instructions ) };
    }

    static int partOne( std::unordered_map<std::string, Paths>& routeGraph, const std::string& instructions )
    {
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
        return steps;
    }

    static long long gcd( long long lhs, long long rhs )
    {
        while ( rhs != 0 ) {
            long temp = rhs;
            rhs = lhs % rhs;
            lhs = temp;
        }
        return lhs;
    }

    static long long lcm( long long lhs, long long rhs ) { return ( lhs * rhs ) / gcd( lhs, rhs ); }

    static long long partTwo( std::unordered_map<std::string, Paths>& routeGraph, const std::string& instructions )
    {
        std::vector<long long> stepVector;
        for ( const auto& [ node, paths ] : routeGraph ) {
            if ( node.back( ) == 'A' ) {
                int steps = 1;
                auto currentNode = routeGraph[ node ];
                for ( int i = 0; i <= instructions.size( ); ++i ) {
                    if ( i == instructions.size( ) )
                        i = 0;

                    std::string nextNode = instructions[ i ] == 'L' ? currentNode.left : currentNode.right;
                    if ( nextNode.back( ) == 'Z' )
                        break;
                    currentNode = routeGraph[ nextNode ];

                    ++steps;
                }
                stepVector.push_back( steps );
            }
        }

        long long result = std::accumulate( stepVector.begin( ) + 1, stepVector.end( ), stepVector[ 0 ], lcm );

        return result;
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

TEST( Solve, day_8 )
{
    Day8 d8;
    const auto [ partOne, partTwo ] = d8.Solve( );
    ASSERT_EQ( partOne, 21409 );
    ASSERT_EQ( partTwo, 21165830176709LL );
}
