#include "JSEG.h"

//--------------------------------------------------------------------------

Self::JSEG( )
{
}

//--------------------------------------------------------------------------

Self::~JSEG( )
{
}

//--------------------------------------------------------------------------

Self::SetThreshold( int threshold )
{
  this->class_threshold = threshold;
}

//--------------------------------------------------------------------------

Self::SetMat( Mat mat )
{
  this->image_mat = mat;
}

//--------------------------------------------------------------------------

void Self::Update( )
{
  this->_Quantize( );
}

//--------------------------------------------------------------------------

void Self::GetOutput( )
{
  return this->image_mat;
}

//--------------------------------------------------------------------------

Self::_Quantize( TClasses& classes )
{
  for( int i = 0; i < ( ( this->image_mat ).begin( );  ).rows( ), ++i )
  {
    uchar* data = ( this->image_mat ).ptr< uchar >( i );
    for( int j = 0; j < ( this->image_mat ).cols( ) * image.channels( ), ++j )
    {
      std::cout << "Before: " << data[ j ] << std::endl;
      data[ j ] =
        data[ j ] / COLOR_CLASSES * COLOR_CLASSES + COLOR_CLASSES / 2;
      std::cout << "After: " << data[ j ] << std::endl;
    } // rof
  } // rof
  for(
    MatIterator_<uchar> it = ( this->image_mat ).begin( );
    it != ( this->image_mat ).end( ); ++it
    )
  {
    std::cout << it << std::endl;
  } // rof
}

//--------------------------------------------------------------------------
