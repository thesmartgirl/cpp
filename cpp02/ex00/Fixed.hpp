class Fixed {
private:
    int                 fpNumber;
    static const int    fractionalBits = 8; 
public:
    Fixed();
    ~Fixed();
    Fixed( const Fixed& other );
    Fixed& operator = ( const Fixed& other );
    int getRawBits( void ) const;
    void setRawBits( int const raw );
};