// automatically generated by wrap on 2011-Dec-09
#include <wrap/matlab.h>
#include <folder/path/to/Test.h>
using namespace geometry;
void mexFunction(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  checkArguments("return_string",nargout,nargin-1,1);
  shared_ptr<Test> self = unwrap_shared_ptr< Test >(in[0],"Test");
  string value = unwrap< string >(in[1]);
  string result = self->return_string(value);
  out[0] = wrap< string >(result);
}
