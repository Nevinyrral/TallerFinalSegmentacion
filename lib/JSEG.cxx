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

void JSEG::SetInput( Mat mat )
{
  this->m_Input = mat;
  this->m_Output = ( this->m_Input ).clone( );
}

//--------------------------------------------------------------------------

void JSEG::Update( )
{
  this->_Quantize( );
  this->_GetDivisors( );
  this->_Subdivide( );
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
    } // rof
}

//--------------------------------------------------------------------------

bool _IsPrime( int n )
{
    bool prime[ n + 1 ];
    std::set< int > primes;
    memset( prime, true, sizeof( prime ) );

    for( int p = 2; p * p <= n; p++ )
        if( prime[ p ] == true )
        {
            for ( int i = p * 2; i <= n; i += p )
                prime[ i ] = false;
        } // fi
    return prime[ n ];
}

//--------------------------------------------------------------------------

void JSEG::_GetDivisors( )
{
  int region_sizes[] = { 512, 256, 128, 64 };
  bool even_cols = ( this->m_Output.cols % 2 ) == 0;
  bool even_rows = ( this->m_Output.rows % 2 ) == 0;
  int current_size_cols = 0;
  int current_size_rows = 0;
  if( even_cols )
  {
    while( true )
    {
      if( this->m_Output.cols == region_sizes[ current_size_cols ] )
      {
        this->m_CDivisor++;
        break;
      }
      else if( this->m_Output.cols < region_sizes[ current_size_cols ] )
      {
        current_size_cols++;
        continue;
      }
      else if( this->m_Output.cols % region_sizes[ current_size_cols ] == 0 )
      {
        this->m_CDivisor =
          this->m_Output.cols / region_sizes[ current_size_cols ];
        break;
      }
      else
      {
        int divs = 2;
        while( true )
        {
          if( this->m_Output.cols % divs == 0 )
          {
            if( region_sizes[ 0 ] > this->m_Output.cols / divs )
            {
              this->m_CDivisor = divs;
              break;
            }
            else divs ++;// fi
          }
          else divs ++; // fi
        } // elihw
        break;
      } // fi
    }
  }
  else if( _IsPrime( this->m_Output.cols ) )
  {
    this->m_CDivisor++;
  } // fi

  if( even_rows )
  {
    while( true )
    {
      if( this->m_Output.rows == region_sizes[ current_size_rows ] )
      {
        this->m_RDivisor++;
        break;
      }
      else if( this->m_Output.rows < region_sizes[ current_size_rows ] )
      {
        current_size_rows++;
        continue;
      }
      else if( this->m_Output.rows % region_sizes[ current_size_rows ] == 0 )
      {
        this->m_RDivisor =
          this->m_Output.rows / region_sizes[ current_size_rows ];
        break;
      }
      else
      {
        int divs = 2;
        while( true )
        {
          if( this->m_Output.rows % divs == 0 )
          {
            if( region_sizes[ 0 ] > this->m_Output.rows / divs )
            {
              this->m_RDivisor = divs;
              break;
            }
            else divs ++; // fi
          }
          else divs ++; // fi
        } // elihw
        break;
      } // fi
    }
  }
  else if( _IsPrime( this->m_Output.rows ) )
  {
    this->m_RDivisor++;
  } // fi
}

//--------------------------------------------------------------------------

bool JSEG::_Subdivide( )
{
  if( !this->m_Output.data || this->m_Output.empty( ) )
  {
    std::cerr << "Problem Loading Image" << std::endl;
    return false;
  } // fi

  cv::Mat maskImg = this->m_Output.clone( );
  if( !maskImg.data || maskImg.empty( ) )
  {
    std::cerr << "Problem Loading Image" << std::endl;
    return false;
  } // fi

  if(
    this->m_Output.cols % this->m_CDivisor == 0 &&
    this->m_Output.rows % this->m_RDivisor == 0
    )
  {
    for(
      int y = 0; y < this->m_Output.cols;
      y += this->m_Output.cols / this->m_CDivisor
      )
    {
      for(
        int x = 0; x < this->m_Output.rows;
        x += this->m_Output.rows / this->m_RDivisor
        )
      {
        Region new_region;
        new_region.SetRegion(
          this->m_Output(
            cv::Rect(
              y, x, ( this->m_Output.cols / this->m_CDivisor ),
              ( this->m_Output.rows / this->m_RDivisor )
              )
            ).clone( )
          );
        new_region.Update( );
        this->m_Regions.push_back(
          new_region
          );
        rectangle(
          maskImg, Point( y, x ),
          Point( y + ( maskImg.cols / this->m_CDivisor ) - 1,
          x + ( maskImg.rows / this->m_RDivisor ) - 1 ),
          CV_RGB(255, 0, 0), 1
          ); // visualization
      } // rof
    } // rof
  } // fi
  else if( this->m_Output.cols % this->m_CDivisor != 0 )
  {
    std::cerr << "Error: Please use another divisor for the column split." <<
      std::endl;
    return false;
  } // fi
  else if( this->m_Output.rows % this->m_RDivisor != 0 )
  {
    std::cerr << "Error: Please use another divisor for the row split." <<
      std::endl;
    return false;
  } // fi
  std::cout << "Regions: " << this->m_Regions.size( ) <<
    std::endl;
  imshow( "Image", maskImg ); // visualization
  waitKey( 0 ); // visualization
  return true;
}

//--------------------------------------------------------------------------

uchar _ReduceVal( const uchar val )
{
  if (val < 64) return 0;
  if (val < 128) return 64;
  return 255;
}
