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
  int channels = ( this->m_Image ).channels( );

  for( int i = 0; i < rows; ++i )
  {
    uchar* data = ( this->m_Image ).ptr< uchar >( i );
    for( int j = 0; j < cols * channels; ++j )
    {
      data[ j ] =
        data[ j ] / COLOR_CLASSES * COLOR_CLASSES + COLOR_CLASSES / 2;
    } // rof
  } // rof
  std::set< int > colors;
  for(
    MatIterator_< Vec3i > it = ( this->m_Image ).begin< Vec3i >( );
    it != ( this->m_Image ).end< uchar >( ); ++it
    )
  {
    colors.insert( (*it)[0] + (*it)[1] + (*it)[2] );
  } // rof
  std::cout << "Color classes: " << colors.size( ) << '\n';
}

//--------------------------------------------------------------------------
