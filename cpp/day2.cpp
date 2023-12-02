#include "utility.hpp"

#include <iostream>
#include <sstream>
#include <string>

int getLargestNumberAfterSubstring( const std::string& str, const std::string& substring )
{
    size_t pos = 0;
    size_t maxNum = std::numeric_limits<size_t>::min( ); // Initialize to the smallest possible value

    while ( ( pos = str.find( substring, pos ) ) != std::string::npos ) {
        pos += substring.length( ); // Move to the end of the substring

        // Find the first digit after the substring
        size_t numStart = str.find_first_of( "0123456789", pos );
        if ( numStart != std::string::npos ) {
            // Extract the number using stringstream
            std::stringstream ss( str.substr( numStart ) );
            int number;
            ss >> number;

            // Update maxNum if the current number is larger
            maxNum = std::max( maxNum, static_cast<size_t>( number ) );
        }

        // Move to the next position to continue searching
        pos++;
    }

    if ( maxNum == std::numeric_limits<size_t>::min( ) ) {
        // No number found after any occurrence of the substring
        return -1; // or any other appropriate value indicating failure
    }

    return static_cast<int>( maxNum );
}

void day2( )
{
    int sumDayOne = 0;
    int dayCounter = 1;
    processOnInput<int>( 2, []( auto s ) {
        

        ++dayCounter;
    } );
}