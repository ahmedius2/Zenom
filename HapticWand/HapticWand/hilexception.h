#ifndef HILEXCEPTION_H
#define HILEXCEPTION_H

#include <iostream>
#include <string>
#include "HapticWand_global.h"


namespace Hardware
{
    /**
     *
     * The base class for all exceptions thrown by the Quanser.Hardware.HIL class.
     *
     */
    class HAPTICWANDSHARED_EXPORT HILException: public std::exception
    {
    public:
        /**
          * Constructs an exception object.
          * @param def          A string identifying exception.
          */
        HILException(std::string def);

        /**
          * Constructs an exception object.
          * @param errnum        An integer identifying the error number
          */
        HILException(const int errnum);

        virtual ~HILException() throw();

        /**
         * Get string identifying exception.
         * @return            A pointer to a c-string with content related to the exception.
         */
        virtual const char* what() const throw();

    private:

        /**
         * Exception message
         */
        std::string info;
    };

}


#endif // HILEXCEPTION_H
