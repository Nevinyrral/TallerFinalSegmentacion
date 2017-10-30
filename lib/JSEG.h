#include <opencv2/opencv.hpp>
#include <string>
#define COLOR_CLASSES (128 + 64 + 32)

using namespace cv;

uchar _ReduceVal( const uchar val );

class JSEG
{
public:
  typedef std::vector< Point2i >           TPixels;
  typedef std::map< std::string, TPixels > TClasses;
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
