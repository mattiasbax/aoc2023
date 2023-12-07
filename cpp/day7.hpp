#pragma once

#include "utility.hpp"

#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<char, int> cardTable{
    { '2', 2 },
    { '3', 3 },
    { '4', 4 },
    { '5', 5 },
    { '6', 6 },
    { '7', 7 },
    { '8', 8 },
    { '9', 9 },
    { 'T', 10 },
    { 'J', 11 },
    { 'Q', 12 },
    { 'K', 13 },
    { 'A', 14 }
};

std::unordered_map<char, int> newRuleCardTable{
    { '2', 2 },
    { '3', 3 },
    { '4', 4 },
    { '5', 5 },
    { '6', 6 },
    { '7', 7 },
    { '8', 8 },
    { '9', 9 },
    { 'T', 10 },
    { 'J', 11 },
    { 'Q', 12 },
    { 'K', 13 },
    { 'A', 14 }
};

class Day7 {
public:
    Day7( ) = default;

    std::pair<int, int> Solve( bool runOnTestInput = false )
    {
        std::vector<Hand> hands;
        processOnInput(
            date, [ & ]( auto s ) { hands.push_back( createHand( s ) ); }, runOnTestInput
        );
        std::ranges::sort( hands, []( auto& lhs, auto& rhs ) { return lhs < rhs; } );

        unsigned int partOne = 0;
        for ( int rank = 1; const auto& hand : hands ) {
            partOne += ( hand.mBid * rank );
            ++rank;
        }

        return { partOne, 2 };
    }

    class Hand {
    public:
        enum class Type {
            HighCard,
            OnePair,
            TwoPair,
            ThreeOfAKind,
            FullHouse,
            FourOfAKind,
            FiveOfAKind
        };

        Hand( std::string cards, int bid ) : mCards( cards ), mBid( bid )
        {
            std::unordered_map<char, int> table;
            for ( auto card : cards ) {
                table[ card ]++;
            }
            std::vector<int> counts( 6, 0 );
            for ( const auto& [ _, count ] : table ) {
                counts[ count ]++;
            }
            if ( counts[ 5 ] )
                mType = Type::FiveOfAKind;
            else if ( counts[ 4 ] )
                mType = Type::FourOfAKind;
            else if ( counts[ 3 ] && counts[ 2 ] )
                mType = Type::FullHouse;
            else if ( counts[ 3 ] && !counts[ 2 ] )
                mType = Type::ThreeOfAKind;
            else if ( counts[ 2 ] == 2 )
                mType = Type::TwoPair;
            else if ( counts[ 2 ] )
                mType = Type::OnePair;
            else
                mType = Type::HighCard;
        }

        // bool isLesserThan( const Hand& rhs ) const
        // {
        //     if ( mType == rhs.mType ) {
        //         int idx = 0;
        //         while ( mCards[ idx ] == rhs.mCards[ idx ] ) {
        //             ++idx;
        //         }
        //         return cardTable[ mCards[ idx ] ] < cardTable[ rhs.mCards[ idx ] ];
        //     }
        //     else {
        //         return mType < rhs.mType;
        //     }
        // }

        // bool isGreaterThan(const Hand& rhs) const

        bool operator<( const Hand& rhs )
        {
            if ( mType == rhs.mType ) {
                int idx = 0;
                while ( mCards[ idx ] == rhs.mCards[ idx ] ) {
                    ++idx;
                }
                return cardTable[ mCards[ idx ] ] < cardTable[ rhs.mCards[ idx ] ];
            }
            else {
                return mType < rhs.mType;
            }
        }

        bool operator>( const Hand& rhs )
        {
            if ( mType == rhs.mType ) {
                int idx = 0;
                while ( mCards[ idx ] == rhs.mCards[ idx ] ) {
                    ++idx;
                }
                return cardTable[ mCards[ idx ] ] > cardTable[ rhs.mCards[ idx ] ];
            }
            else {
                return mType > rhs.mType;
            }
        }

        std::string mCards;
        int mBid;
        Type mType;
        Type mNewRuleType;
    };

    Hand createHand( std::string& s )
    {
        std::istringstream stream( s );
        std::string cards;
        int bid;
        stream >> cards;
        stream >> bid;
        Hand h( cards, bid );
        return h;
    }

private:
    static constexpr int date = 7;
    void doSomethingOnString( const std::string& s ) { return; }
};

TEST( Day7, createHand )
{
    Day7::Hand h1( "32T3K", 765 );
    ASSERT_EQ( h1.mType, Day7::Hand::Type::OnePair );

    Day7::Hand h2( "T55J5", 684 );
    ASSERT_EQ( h2.mType, Day7::Hand::Type::ThreeOfAKind );

    Day7::Hand h3( "KK677", 684 );
    ASSERT_EQ( h3.mType, Day7::Hand::Type::TwoPair );

    Day7::Hand h4( "KTJJT", 684 );
    ASSERT_EQ( h4.mType, Day7::Hand::Type::TwoPair );

    Day7::Hand h5( "QQQJA", 684 );
    ASSERT_EQ( h5.mType, Day7::Hand::Type::ThreeOfAKind );
}

TEST( Day7, compare )
{
    Day7::Hand h1( "32T3K", 765 ); // OnePair
    Day7::Hand h2( "T55J5", 684 ); // ThreeOfAKind
    Day7::Hand h3( "44444", 555 ); // FiveOfAKind
    Day7::Hand h4( "A55J5", 684 ); // ThreeOfAKind

    ASSERT_TRUE( h2 > h1 );
    ASSERT_TRUE( h1 < h2 );
    ASSERT_TRUE( h2 < h3 );
    ASSERT_TRUE( h3 > h1 );
    ASSERT_TRUE( h4 > h2 );
}

TEST( Day7, Test )
{
    Day7 d7;
    const auto [ partOne, partTwo ] = d7.Solve( true );
    ASSERT_EQ( partOne, 6440 );
    std::cout << "Part two: " << partOne << std::endl;
    ASSERT_EQ( partTwo, 2 );
}

TEST( Solve, day_7 )
{
    Day7 d7;
    const auto [ partOne, partTwo ] = d7.Solve( );
    ASSERT_EQ( partOne, 249638405 );
    ASSERT_EQ( partTwo, 2 );
}