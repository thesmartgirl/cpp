#include "Span.hpp"
#include <cstdlib>
#include <iostream>
#include <deque>
#include <string>
#include <vector>

static void printSection( const std::string &title ) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

static void printSpanResults( const std::string &label, Span &span ) {
    std::cout << label << std::endl;
    std::cout << "  shortest span: " << span.shortestSpan() << std::endl;
    std::cout << "  longest span : " << span.longestSpan() << std::endl;
}

static void printException( const std::string &label, const std::exception &e ) {
    std::cout << label << std::endl;
    std::cout << "  caught: " << e.what() << std::endl;
}

int main()
{
    printSection( "Basic span calculation" );
    Span basic( 4 );
    basic.addNumber( 6 );
    basic.addNumber( 9 );
    basic.addNumber( 0 );
    basic.addNumber( -5 );
    printSpanResults( "Values: { 6, 9, 0, -5 }", basic );

    printSection( "Duplicate values" );
    Span duplicates( 3 );
    duplicates.addNumber( 42 );
    duplicates.addNumber( 42 );
    duplicates.addNumber( 100 );
    printSpanResults( "Values: { 42, 42, 100 }", duplicates );

    printSection( "Range insertion from vector" );
    std::vector<int> vectorInput;
    vectorInput.push_back( 1 );
    vectorInput.push_back( 4 );
    vectorInput.push_back( 8 );
    vectorInput.push_back( 15 );
    vectorInput.push_back( 16 );
    vectorInput.push_back( 23 );

    Span vectorSpan( vectorInput.size() );
    vectorSpan.addRange( vectorInput.begin(), vectorInput.end() );
    printSpanResults( "Values: { 1, 4, 8, 15, 16, 23 }", vectorSpan );

    printSection( "Range insertion from deque" );
    std::deque<int> dequeInput;
    dequeInput.push_back( 42 );
    dequeInput.push_back( 7 );
    dequeInput.push_back( 19 );
    dequeInput.push_back( 11 );
    dequeInput.push_back( 60 );

    Span dequeSpan( dequeInput.size() );
    dequeSpan.addRange( dequeInput.begin(), dequeInput.end() );
    printSpanResults( "Values: { 42, 7, 19, 11, 60 }", dequeSpan );

    printSection( "Const iterator range insertion" );
    const std::vector<int> constVectorInput( vectorInput );
    Span constVectorSpan( constVectorInput.size() );
    constVectorSpan.addRange( constVectorInput.begin(), constVectorInput.end() );
    printSpanResults( "Values from const vector: { 1, 4, 8, 15, 16, 23 }", constVectorSpan );

    printSection( "Large span test" );
    std::vector<int> largeInput;
    for ( int i = 0; i < 100000; ++i )
        largeInput.push_back( i );

    Span largeSpan( largeInput.size() );
    largeSpan.addRange( largeInput.begin(), largeInput.end() );
    std::cout << "Inserted: " << largeInput.size() << " numbers" << std::endl;
    std::cout << "  expected shortest span: 1" << std::endl;
    std::cout << "  expected longest span : 99999" << std::endl;
    printSpanResults( "Consecutive values from 0 to 99999", largeSpan );

    printSection( "Copy and assignment" );
    Span original( 5 );
    original.addNumber( 3 );
    original.addNumber( 10 );
    original.addNumber( 25 );
    Span copied( original );
    Span assigned( 1 );
    assigned = original;
    printSpanResults( "Copied span", copied );
    printSpanResults( "Assigned span", assigned );

    std::cout << "Mutating the original after copy/assignment..." << std::endl;
    original.addNumber( 40 );
    printSpanResults( "Original span after mutation", original );
    printSpanResults( "Copied span after original mutation", copied );
    printSpanResults( "Assigned span after original mutation", assigned );

    printSection( "Exception handling" );
    try {
        Span empty( 2 );
        empty.shortestSpan();
    }
    catch ( const std::exception &e ) {
        printException( "Shortest span on an empty span", e );
    }

    try {
        Span single( 2 );
        single.addNumber( 99 );
        single.shortestSpan();
    }
    catch ( const std::exception &e ) {
        printException( "Shortest span with a single value", e );
    }

    try {
        Span single( 2 );
        single.addNumber( 99 );
        single.longestSpan();
    }
    catch ( const std::exception &e ) {
        printException( "Longest span with a single value", e );
    }

    try {
        Span full( 1 );
        full.addNumber( 5 );
        full.addNumber( 6 );
    }
    catch ( const std::exception &e ) {
        printException( "Adding past capacity with addNumber()", e );
    }

    try {
        std::vector<int> tooMany;
        tooMany.push_back( 1 );
        tooMany.push_back( 2 );
        tooMany.push_back( 3 );

        Span limited( 2 );
        limited.addRange( tooMany.begin(), tooMany.end() );
    }
    catch ( const std::exception &e ) {
        printException( "Adding past capacity with addRange()", e );
    }

    return 0;
}