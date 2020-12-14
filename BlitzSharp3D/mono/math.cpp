#include "monoutil.h"
#include "../bbruntime/bbmath.h"

PUBLIC_METHOD float Sin(float deg)
{
	return bbSin(deg);
}

PUBLIC_METHOD float Cos(float deg)
{
	return bbCos(deg);
}

PUBLIC_METHOD float Tan(float deg)
{
	return bbTan(deg);
}

PUBLIC_METHOD float ASin(float f)
{
	return bbASin(f);
}

PUBLIC_METHOD float ACos(float f)
{
	return bbACos(f);
}

PUBLIC_METHOD float ATan(float f)
{
	return bbATan(f);
}

PUBLIC_METHOD float ATan2(float n, float t)
{
	return bbATan2(n, t);
}

PUBLIC_METHOD float Sqr(float f)
{
	return bbSqr(f);
}

PUBLIC_METHOD float Floor(float f)
{
	return bbFloor(f);
}

PUBLIC_METHOD float Ceil(float f)
{
	return bbCeil(f);
}

PUBLIC_METHOD float Exp(float f)
{
	return bbExp(f);
}

PUBLIC_METHOD float Log(float f)
{
	return bbLog(f);
}

PUBLIC_METHOD float Log10(float f)
{
	return bbLog10(f);
}

PUBLIC_METHOD float Rnd(float from, float to)
{
	return bbRnd(from, to);
}

PUBLIC_METHOD int Rand(int from, int to)
{
	return bbRand(from, to);
}

PUBLIC_METHOD void SeedRnd(int seed)
{
	return bbSeedRnd(seed);
}

PUBLIC_METHOD int RndSeed()
{
	return bbRndSeed();
}