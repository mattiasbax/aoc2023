#pragma once

#include "utility.hpp"

#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

class Day5 {
public:
    Day5( ) = default;

    std::pair<int, int> Solve( bool runOnTestInput = false )
    {
        enum class State {
            ExtractingSeeds = 0,
            SeedToSoil,
            SoilToFert,
            FertToWater,
            WaterToLight,
            LightToTemp,
            TempToHumid,
            HumidToLoc,
        };

        State state = State::ExtractingSeeds;
        std::vector<int> seeds;
        std::vector<int> soils;
        std::vector<int> ferts;
        std::vector<int> waters;
        std::vector<int> lights;
        std::vector<int> temps;
        std::vector<int> humids;
        std::vector<int> locations;

        processOnInput(
            date,
            [ & ]( auto s ) {
                switch ( state ) {
                case State::ExtractingSeeds:
                    if ( !s.empty( ) ) {
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        int temp;
                        while ( stream >> temp )
                            seeds.push_back( temp );
                    }
                    else {
                        state = State::SeedToSoil;
                    }
                    break;
                case State::SeedToSoil:
                    if ( s.empty( ) ) {
                        state = State::SoilToFert;
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                        std::vector<int> mapEntry;
                        std::istringstream stream( s.substr( s.find( ':' ) + 1, s.size( ) ) );
                        int temp;
                        while ( stream >> temp )
                            mapEntry.push_back( temp );
                        transformViaMapEntry( seeds, soils, mapEntry );
                    }
                    break;
                case State::SoilToFert:
                    if ( s.empty( ) ) {
                        state = State::FertToWater;
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                    }
                    break;
                case State::FertToWater:
                    if ( s.empty( ) ) {
                        state = State::WaterToLight;
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                    }
                    break;
                case State::WaterToLight:
                    if ( s.empty( ) ) {
                        state = State::LightToTemp;
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                    }
                    break;
                case State::LightToTemp:
                    if ( s.empty( ) ) {
                        state = State::TempToHumid;
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                    }
                    break;
                case State::TempToHumid:
                    if ( s.empty( ) ) {
                        state = State::HumidToLoc;
                    }
                    else if ( std::isdigit( s.front( ) ) ) {
                    }
                    break;
                case State::HumidToLoc:
                    if ( std::isdigit( s.front( ) ) ) {
                    }
                    break;
                }
            },
            runOnTestInput
        );
        return { 1, 2 };
    }

    void transformViaMapEntry( std::vector<int> source, std::vector<int>& dest, std::vector<int> mapEntry )
    {
        if ( source.size( ) != dest.size( ) )
            dest.resize( source.size( ) );

        auto isInRange = [ & ]( int i ) { return i >= mapEntry[ 1 ] && i <= mapEntry[ 1 ] + mapEntry[ 2 ] };

        std::ranges::transform( dest, source | std::views::filter( isInRange ) )
    }

private:
    static constexpr int date = 5;
    void doSomethingOnString( const std::string& s ) { return; }
};

TEST( Day5, Test )
{
    Day5 d5;
    const auto [ partOne, partTwo ] = d5.Solve( true );
    std::cout << "Part one: " << partOne << std::endl;
    ASSERT_EQ( partOne, 1 );
    std::cout << "Part two: " << partOne << std::endl;
    ASSERT_EQ( partTwo, 2 );
}

TEST( Day5, Solve )
{
    Day5 d5;
    const auto [ partOne, partTwo ] = d5.Solve( );
    std::cout << "Part one: " << partOne << std::endl;
    ASSERT_EQ( partOne, 1 );
    std::cout << "Part two: " << partOne << std::endl;
    ASSERT_EQ( partTwo, 2 );
}
