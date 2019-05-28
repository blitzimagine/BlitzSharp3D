
#include "std.h"
#include "bbsys.h"

gxRuntime *gx_runtime;

bbEx::bbEx(const char* message, bool runtime) : message(message), runtime(runtime)
{

}

void bbEx::showError() const
{
    if (message)
    {
        if (runtime)
            gx_runtime->runtimeError(message);
        else
            gx_runtime->debugError(message);
    }
}

void ThrowBlitzException(bbEx ex)
{
    ex.showError();

    ExitProcess(0);
}
