#pragma once

#include "utility.hpp"

#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<char, int> CARD_TABLE{
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

std::unordered_map<char, int> NEW_RULES_CARD_TABLE{
    { 'J', 1 },
    { '2', 2 },
    { '3', 3 },
    { '4', 4 },
    { '5', 5 },
    { '6', 6 },
    { '7', 7 },
    { '8', 8 },
    { '9', 9 },
    { 'T', 10 },
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
        std::vector<Hand> handsWithJokers;
        processOnInput(
            date,
            [ & ]( auto s ) {
                hands.push_back( createHand( s, false ) );
                handsWithJokers.push_back( createHand( s, true ) );
            },
            runOnTestInput
        );
        std::ranges::sort( hands, []( auto& lhs, auto& rhs ) { return lhs.isLesserThan( rhs, CARD_TABLE ); } );
        std::ranges::sort( handsWithJokers, []( auto& lhs, auto& rhs ) {
            unsigned int partTwo = 0;
            return lhs.isLesserThan( rhs, NEW_RULES_CARD_TABLE );
        } );

        unsigned int partOne = 0;
        unsigned int partTwo = 0;
        for ( int i = 0; i < hands.size( ); ++i ) {
            const int rank = i + 1;
            partOne += ( hands[ i ].mBid * rank );
            partTwo += ( handsWithJokers[ i ].mBid * rank );
        }

        return { partOne, partTwo };
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

        Type getType( std::string cards, bool withWildCards )
        {
            std::unordered_map<char, int> cardCount;
            for ( auto card : cards ) {
                cardCount[ card ]++;
            }
            const int nrOfWildCards = withWildCards ? cardCount[ 'J' ] : 0;
            if ( withWildCards )
                cardCount[ 'J' ] = 0;

            std::vector<int> counts( 6, 0 );
            for ( const auto& [ _, count ] : cardCount ) {
                counts[ count ]++;
            }

            if ( counts[ 5 ] || nrOfWildCards == 5 || counts[ 4 ] && nrOfWildCards == 1
                 || counts[ 3 ] && nrOfWildCards == 2 || counts[ 2 ] && nrOfWildCards == 3
                 || counts[ 1 ] && nrOfWildCards == 4 )
                return Type::FiveOfAKind;
            else if ( counts[ 4 ] || counts[ 3 ] && nrOfWildCards == 1 || counts[ 2 ] && nrOfWildCards == 2 || counts[ 1 ] && nrOfWildCards == 3 )
                return Type::FourOfAKind;
            else if ( counts[ 3 ] && counts[ 2 ] || counts[ 2 ] == 2 && nrOfWildCards == 1 )
                return Type::FullHouse;
            else if ( counts[ 3 ] || counts[ 2 ] && nrOfWildCards == 1 || counts[ 1 ] && nrOfWildCards == 2 )
                return Type::ThreeOfAKind;
            else if ( counts[ 2 ] == 2 || nrOfWildCards == 2 )
                return Type::TwoPair;
            else if ( counts[ 2 ] || nrOfWildCards == 1 )
                return Type::OnePair;
            else
                return Type::HighCard;
        }

        Hand( std::string cards, int bid, bool withWildCards = false ) :
            mCards( cards ),
            mBid( bid ),
            mType( getType( cards, withWildCards ) )
        {
        }

        bool isLesserThan( const Hand& rhs, std::unordered_map<char, int>& cardValues ) const
        {
            if ( mType == rhs.mType ) {
                int idx = 0;
                while ( mCards[ idx ] == rhs.mCards[ idx ] ) {
                    ++idx;
                }
                return cardValues[ mCards[ idx ] ] < cardValues[ rhs.mCards[ idx ] ];
            }
            else {
                return mType < rhs.mType;
            }
        }

        bool isGreaterThan( const Hand& rhs, std::unordered_map<char, int>& cardValues ) const
        {
            if ( mType == rhs.mType ) {
                int idx = 0;
                while ( mCards[ idx ] == rhs.mCards[ idx ] ) {
                    ++idx;
                }
                return cardValues[ mCards[ idx ] ] > cardValues[ rhs.mCards[ idx ] ];
            }
            else {
                return mType > rhs.mType;
            }
        }

        std::string mCards;
        int mBid;
        Type mType;
    };

    Hand createHand( std::string& s, bool withWildCards )
    {
        std::istringstream stream( s );
        std::string cards;
        int bid;
        stream >> cards;
        stream >> bid;
        Hand h( cards, bid, withWildCards );
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

    Day7::Hand h6( "2345J", 333, true );
    ASSERT_EQ( h6.mType, Day7::Hand::Type::OnePair );
}

TEST( Day7, compare )
{
    Day7::Hand h1( "32T3K", 765 ); // OnePair
    Day7::Hand h2( "T55J5", 684 ); // ThreeOfAKind
    Day7::Hand h3( "44444", 555 ); // FiveOfAKind
    Day7::Hand h4( "A55J5", 684 ); // ThreeOfAKind

    ASSERT_TRUE( h2.isGreaterThan( h1, CARD_TABLE ) );
    ASSERT_TRUE( h1.isLesserThan( h2, CARD_TABLE ) );
    ASSERT_TRUE( h2.isLesserThan( h3, CARD_TABLE ) );
    ASSERT_TRUE( h3.isGreaterThan( h1, CARD_TABLE ) );
    ASSERT_TRUE( h4.isGreaterThan( h2, CARD_TABLE ) );
}

TEST( Day7, Test )
{
    Day7 d7;
    const auto [ partOne, partTwo ] = d7.Solve( true );
    ASSERT_EQ( partOne, 6440 );
    ASSERT_EQ( partTwo, 5905 );
}

TEST( Solve, day_7 )
{
    Day7 d7;
    const auto [ partOne, partTwo ] = d7.Solve( );
    ASSERT_EQ( partOne, 249638405 );
    ASSERT_EQ( partTwo, 249776650 );
}