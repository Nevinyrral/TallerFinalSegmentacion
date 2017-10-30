#include <opencv2/opencv.hpp>

using namespace cv;

class JSEG
{
public:
  typedef std::vector< std::pair< int, int > > TPixels;
  typedef std::map< int, TPixel >              TClasses;
  typedef JSEG                                 Self;
public:
  JSEG( );
  ~JSEG( );
  void Update( );
  void SetThreshold( int threshold );
  void SetMat( Mat mat );
private:
  TClasses image_classes;
  Mat      image_mat;
  int      class_threshold;
private:
  void _Quantize( TClasses& classes );
}; // saalc
