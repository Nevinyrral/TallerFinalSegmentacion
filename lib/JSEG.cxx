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
  this->m_Image = mat;
}

//--------------------------------------------------------------------------

void JSEG::Update( )
{
  this->_Quantize( this-> m_Classes );
}

//--------------------------------------------------------------------------

Mat JSEG::GetOutput( )
{
  return this->m_Image;
}

//--------------------------------------------------------------------------

void JSEG::_Quantize( TClasses& classes )
{
  int rows = ( this->m_Image ).rows;
  int cols = ( this->m_Image ).cols;

  uchar* data = ( this->m_Image ).data;
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
      classes[ color_signature ].push_back( Point2i( i, j ) );
    } // rof
  std::cout << "Color classes: " << classes.size( ) << '\n';
}

//--------------------------------------------------------------------------

uchar _ReduceVal( const uchar val )
{
  if (val < 64) return 0;
  if (val < 128) return 64;
  return 255;
}
