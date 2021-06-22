
#ifndef GXTIMER_H
#define GXTIMER_H

class gxRuntime;

class gxTimer {
public:
	gxTimer(gxRuntime* rt, int hertz);
	~gxTimer();

	static void CALLBACK timerCallback(UINT id, UINT msg, DWORD_PTR user, DWORD_PTR dw1, DWORD_PTR dw2);

private:
	gxRuntime* runtime;
	HANDLE event;
	MMRESULT timerID;
	int ticks_put, ticks_get;

	/***** GX INTERFACE *****/
public:
	int wait();
};

#endif