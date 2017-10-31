#include "JSEG.h"

//--------------------------------------------------------------------------

JSEG::JSEG( )
{
}

//--------------------------------------------------------------------------

JSEG::~JSEG( )
{
}

//--------------------------------------------------------------------------

void JSEG::SetThreshold( int threshold )
{
  this->m_Threshold = threshold;
}

//--------------------------------------------------------------------------

void JSEG::SetInput( Mat mat )
{
  this->m_Input = mat;
  this->m_Output = ( this->m_Input ).clone( );
}

//--------------------------------------------------------------------------

void JSEG::Update( )
{
  this->_Quantize( );
}

//--------------------------------------------------------------------------

Mat JSEG::GetOutput( )
{
  return this->m_Output;
}

//--------------------------------------------------------------------------

void JSEG::_Quantize( )
{
  int rows = ( this->m_Output ).rows;
  int cols = ( this->m_Output ).cols;
  int pixel_count = rows * cols;

  uchar* data = ( this->m_Output ).data;
  for( int i = 0; i < rows; ++i )
    for( int j = 0; j < cols; ++j )
    {
      const int pi = i * cols * 3 + j * 3;
      data[ pi + 0 ] = _ReduceVal( data[ pi + 0 ] );
      data[ pi + 1 ] = _ReduceVal( data[ pi + 1 ] );
      data[ pi + 2 ] = _ReduceVal( data[ pi + 2 ] );
      std::string color_signature =
        std::to_string( (int) data[ pi + 0 ] ) +
        std::to_string( (int) data[ pi + 1 ] ) +
        std::to_string( (int) data[ pi + 2 ] );
      ( this->m_Classes )[ color_signature ].push_back( Point2i( j, i ) );
      ( this->m_Mean ).x += j / ( float ) pixel_count;
      ( this->m_Mean ).y += i / ( float ) pixel_count;
      m_Means[ color_signature ].x += j;
      m_Means[ color_signature ].y += i;
    } // rof
  // ( this->m_Mean ).x = ( this->m_Mean ).x / pixel_count;
  // ( this->m_Mean ).y = ( this->m_Mean ).y / pixel_count;
  for(
    TClasses::iterator it = m_Classes.begin( );
    it != m_Classes.end( ); ++it
    )
  {
    m_Means[ it->first ].x = m_Means[ it->first ].x / ( it->second ).size( );
    m_Means[ it->first ].y = m_Means[ it->first ].y / ( it->second ).size( );
    std::cout << "Mean for " << it->first  << ": " <<
      m_Means[ it->first ] << '\n';
  } // rof
  std::cout << "Color classes: " << ( this->m_Classes ).size( ) << '\n';
  std::cout << "Mean class-map: " << this->m_Mean << '\n';
}

//--------------------------------------------------------------------------

uchar _ReduceVal( const uchar val )
{
  if (val < 64) return 0;
  if (val < 128) return 64;
  return 255;
}
