#ifndef BBSYS_H
#define BBSYS_H

#include "basic.h"
#include "../gxruntime/gxruntime.h"

extern gxRuntime* gx_runtime;

struct bbEx : std::exception
{
    const char* message;
    bool runtime;

    bbEx(const char* message, bool runtime = false);

    void showError() const;
};

extern void ThrowBlitzException(bbEx ex);

#define RTEX( _X_ ) ThrowBlitzException(bbEx( _X_ ));
#define RTEXR( _X_ ) ThrowBlitzException(bbEx( _X_, true ));

#endif
