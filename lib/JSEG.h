#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>

#define COLOR_CLASSES (128 + 64 + 32)

using namespace cv;

uchar _ReduceVal( const uchar val );

class JSEG
{
  public:
    typedef std::vector< Point2i >           TPixels;
    typedef std::map< std::string, TPixels > TClasses;
    typedef std::map< std::string, Point2f > TMeans;
    typedef std::map< std::string, float >   TSw;

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
    float    m_St;
    TSw      m_Sw;
    Point2f  m_Mean;

  private:
    void _Quantize( );

}; // saalc
