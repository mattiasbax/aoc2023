#include "utility.hpp"

#include <algorithm>
#include <ranges>

void day1( )
{
    int sum = 0;
    processOnInput( 1, [ & ]( auto s ) {
        auto first = std::ranges::find_if( s, []( char c ) { return c >= '1' && c <= '9'; } );
        auto last = std::ranges::find_if( s | std::views::reverse, []( char c ) { return c >= '1' && c <= '9'; } );
        std::string rowNumber( 1, *first );
        rowNumber += *last;
        const int rowSum = std::stoi( rowNumber );
        sum += rowSum;
    } );

    std::cout << "Part one: " << sum << std::endl;
}

TEST( Day1, test_solution )
{
    day1( );
    ASSERT_TRUE( true );
}
