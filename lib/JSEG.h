#include <opencv2/opencv.hpp>
#define COLOR_CLASSES (128 + 32)

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
  void SetInput( Mat mat );
  Mat  GetOutput( );
private:
  TClasses m_Classes;
  Mat      m_Image;
  int      m_Threshold;
private:
  void _Quantize( TClasses& classes );
}; // saalc
