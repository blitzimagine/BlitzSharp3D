using System;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// ----
		// Math
		// ----

		private static int rnd_state = 0x1234;

		private const int RND_A = 48271;
		private const int RND_M = 2147483647;
		private const int RND_Q = 44488;
		private const int RND_R = 3399;

		private const float dtor = 0.0174532925199432957692369076848861f;
		private const float rtod = 57.2957795130823208767981548141052f;

		public static float Sin(float deg) => (float)Math.Sin(deg * dtor);

		public static float Cos(float deg) => (float)Math.Cos(deg * dtor);

		public static float Tan(float deg) => (float)Math.Tan(deg * dtor);

		public static float ASin(float f) => (float)Math.Asin(f) * rtod;

		public static float ACos(float f) => (float)Math.Acos(f) * rtod;

		public static float ATan(float f) => (float)Math.Atan(f) * rtod;

		public static float ATan2(float n, float t) => (float)Math.Atan2(n, t) * rtod;

		public static float Sqr(float f) => (float)Math.Sqrt(f);

		public static float Floor(float f) => (float)Math.Floor(f);

		public static float Ceil(float f) => (float)Math.Ceiling(f);

		public static float Exp(float f) => (float)Math.Exp(f);

		public static float Log(float f) => (float)Math.Log(f);

		public static float Log10(float f) => (float)Math.Log10(f);

		//return rand float from 0...1
		private static float rnd()
		{
			rnd_state = RND_A * (rnd_state % RND_Q) - RND_R * (rnd_state / RND_Q);
			if (rnd_state < 0) rnd_state += RND_M;
			return (rnd_state & 65535) / 65536.0f + (.5f / 65536.0f);
		}

		public static float Rnd(float from, float to = 0) => rnd() * (to - from) + from;

		public static int Rand(int from, int to = 1)
		{
			if (to < from)
			{
				int temp = from;
				from = to;
				to = temp;
			}
			return (int)(rnd() * (to - from + 1)) + from;
		}

		public static void SeedRnd(int seed)
		{
			seed &= 0x7fffffff;
			rnd_state = seed!=0 ? seed : 1;
		}

		public static int RndSeed() => rnd_state;


		internal static bool math_create()
		{
			SeedRnd(0x1234);
			return true;
		}

		internal static bool math_destroy()
		{
			return true;
		}
	}
}
