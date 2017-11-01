#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>

using namespace cv;

uchar _ReduceVal( const uchar val );

class Region
{
  public:
    typedef std::vector< Point2i >           TPixels;
    typedef std::map< std::string, TPixels > TClasses;
    typedef std::map< std::string, Point2f > TMeans;
    typedef std::map< std::string, float >   TSw;
    typedef std::map< std::string, float >   TJ;

  public:
    Region( );
    ~Region( );
    void SetRegion( Mat mat );
    void Update( );

  private:
    TClasses m_Classes;
    TMeans   m_Means;
    int      m_Threshold;
    float    m_St;
    float    m_J;
    Mat      m_Region;
    float    m_Sw;
    TSw      m_Swc;
    Point2f  m_Mean;

  private:
    void _RegionValues( );
}; // ssalc
