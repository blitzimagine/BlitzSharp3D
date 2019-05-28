using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// ----
		// Math
		// ----

		[DllImport(B3DDllLink)]
		public static extern float Sin(float deg);

		[DllImport(B3DDllLink)]
		public static extern float Cos(float deg);

		[DllImport(B3DDllLink)]
		public static extern float Tan(float deg);

		[DllImport(B3DDllLink)]
		public static extern float ASin(float f);

		[DllImport(B3DDllLink)]
		public static extern float ACos(float f);

		[DllImport(B3DDllLink)]
		public static extern float ATan(float f);

		[DllImport(B3DDllLink)]
		public static extern float ATan2(float n, float t);

		[DllImport(B3DDllLink)]
		public static extern float Sqr(float f);

		[DllImport(B3DDllLink)]
		public static extern float Floor(float f);

		[DllImport(B3DDllLink)]
		public static extern float Ceil(float f);

		[DllImport(B3DDllLink)]
		public static extern float Exp(float f);

		[DllImport(B3DDllLink)]
		public static extern float Log(float f);

		[DllImport(B3DDllLink)]
		public static extern float Log10(float f);

		[DllImport(B3DDllLink)]
		public static extern float Rnd(float from, float to = 0);

		[DllImport(B3DDllLink)]
		public static extern int Rand(int from, int to = 1);

		[DllImport(B3DDllLink)]
		public static extern void SeedRnd(int seed);

		[DllImport(B3DDllLink)]
		public static extern int RndSeed();
	}
}
