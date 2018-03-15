#include "hilexception.h"
#include <string.h>

using namespace Hardware;

HILException::HILException(std::string def) : info(def)
{

}

HILException::HILException(const int errnum)
{
    info = strerror(errnum);
}

HILException::~HILException() throw()
{

}

const char* HILException::what() const throw()
{
    return info.c_str();
}
