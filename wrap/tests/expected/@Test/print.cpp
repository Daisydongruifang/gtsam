// automatically generated by wrap on 2011-Dec-09
#include <wrap/matlab.h>
#include <folder/path/to/Test.h>
using namespace geometry;
void mexFunction(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  checkArguments("print",nargout,nargin-1,0);
  shared_ptr<Test> self = unwrap_shared_ptr< Test >(in[0],"Test");
  self->print();
}
