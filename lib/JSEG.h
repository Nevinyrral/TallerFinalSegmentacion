#include <opencv2/opencv.hpp>
#define COLOR_CLASSES (20)

using namespace cv;

class JSEG
{
public:
  typedef std::vector< std::pair< int, int > >  TPixels;
  typedef std::map< int, TPixels >              TClasses;
  typedef JSEG                                  Self;
public:
  JSEG( );
  ~JSEG( );
  void Update( );
  void SetThreshold( int threshold );
  void SetMat( Mat mat );
  Mat  GetOutput( );
private:
  TClasses image_classes;
  Mat      image_mat;
  int      threshold;
private:
  void _Quantize( TClasses& classes );
}; // saalc
