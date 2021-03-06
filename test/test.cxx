#include <JSEG.h>
#include <iostream>

int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cout << "Usage: " << argv[ 0 ] << " image_filename" << std::endl;
    return( -1 );
  } // fi

  Mat src = imread( argv[1], 1 );
  JSEG filter;

  filter.SetInput( src );
  filter.Update( );

  // Write results
  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  imwrite( basename + "_segmented.png", filter.GetOutput( ) );
}
