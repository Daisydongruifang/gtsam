// automatically generated by wrap on 2011-Dec-09
#include <wrap/matlab.h>
#include <Point2.h>
using namespace geometry;
void mexFunction(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  checkArguments("y",nargout,nargin-1,0);
  shared_ptr<Point2> self = unwrap_shared_ptr< Point2 >(in[0],"Point2");
  double result = self->y();
  out[0] = wrap< double >(result);
}
