#include <opencv2/opencv.hpp>
#include <Region.h>
#include <string>
#include <cmath>

using namespace cv;

bool  _IsPrime( int n );
uchar _ReduceVal( const uchar val );

class JSEG
{
  public:
    typedef std::vector< Point2i >           TPixels;
    typedef std::map< std::string, TPixels > TClasses;
    typedef std::vector< Region >            TRegions;

  public:
    JSEG( );
    ~JSEG( );
    void Update( );
    void SetInput( Mat mat );
    Mat  GetOutput( );

  private:
    Mat      m_Input;
    Mat      m_Output;
    TRegions m_Regions;
    TClasses m_Classes;
    int      m_RDivisor;
    int      m_CDivisor;

  private:
    void _Quantize( );
    void _GetDivisors( );
    bool _Subdivide( );
}; // ssalc
