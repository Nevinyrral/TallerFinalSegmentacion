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
    typedef std::map< std::string, Point2f > TMeans;

  public:
    JSEG( );
    ~JSEG( );
    void Update( );
    void SetThreshold( int threshold );
    void SetInput( Mat mat );
    Mat  GetOutput( );

  private:
    TClasses m_Classes;
    TMeans   m_Means;
    Mat      m_Input;
    Mat      m_Output;
    int      m_Threshold;
    Point2f  m_Mean;

  private:
    void _Quantize( );
    void _CalculateCriteria( );

}; // saalc
