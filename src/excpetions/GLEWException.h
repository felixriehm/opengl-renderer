//
// Created by Felix on 25/09/2021.
//

#ifndef OPENGL_RENDERER_GLEWEXCEPTION_H
#define OPENGL_RENDERER_GLEWEXCEPTION_H

#include <exception>
#include <string>

namespace Exception {
    class GLEWException: public std::exception
    {
    private:
        const char * ErrorMsg = "";
    public:
        GLEWException(const char * errorMsg)
        {
            ErrorMsg = errorMsg;
        }

        virtual const char* what() const throw()
        {
            return ErrorMsg;
        }
    };
}

#endif //OPENGL_RENDERER_GLEWEXCEPTION_H
