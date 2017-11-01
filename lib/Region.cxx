#include "Region.h"

//--------------------------------------------------------------------------

Region::Region( )
{
}

//--------------------------------------------------------------------------

Region::~Region( )
{
}

//--------------------------------------------------------------------------

void Region::SetRegion( Mat mat )
{
  this->m_Region = mat;
}

//--------------------------------------------------------------------------

void Region::Update( )
{
  this->_RegionValues( );
}

//--------------------------------------------------------------------------

void Region::_RegionValues( )
{
  int rows = ( this->m_Region ).rows;
  int cols = ( this->m_Region ).cols;
  int pixel_count = rows * cols;

  uchar* data = ( this->m_Region ).data;
  for( int i = 0; i < rows; ++i )
    for( int j = 0; j < cols; ++j )
    {
      const int pi = i * cols * 3 + j * 3;
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
  std::cout << "Color classes: " << ( this->m_Classes ).size( ) << '\n';
  std::cout << "Calculating standard deviations and J values..." << std::endl;
  data = ( this->m_Region ).data;
  for( int i = 0; i < rows; ++i )
    for( int j = 0; j < cols; ++j )
    {
      float x_norm = j - ( this->m_Mean ).x;
      float y_norm = i - ( this->m_Mean ).y;
      float norm = sqrt( pow( x_norm, 2 ) + pow( y_norm, 2 ) );
      this->m_St += norm;
    } // rof
  this->m_St = pow( this->m_St, 2 );
  for(
    TClasses::iterator it = m_Classes.begin( );
    it != m_Classes.end( ); ++it
    )
  {
    m_Means[ it->first ].x = m_Means[ it->first ].x / ( it->second ).size( );
    m_Means[ it->first ].y = m_Means[ it->first ].y / ( it->second ).size( );
    for( Point2i class_pixel : m_Classes[ it->first ] )
    {
      float x_norm = class_pixel.x - ( this->m_Means[ it->first ] ).x;
      float y_norm = class_pixel.y - ( this->m_Means[ it->first ] ).y;
      float norm = sqrt( pow( x_norm, 2 ) + pow( y_norm, 2 ) );
      this->m_Swc[ it->first ] += norm;
    } // rof
    this->m_Swc[ it->first ] = pow( this->m_Swc[ it->first ], 2 );
    this->m_Sw += this->m_Swc[ it->first ];
  } // rof
  this->m_J += ( this->m_St - this->m_Sw ) / this->m_Sw;
  std::cout << "Class-map J value: " << this->m_J << '\n';
}
