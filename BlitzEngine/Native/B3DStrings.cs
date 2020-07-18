namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// ----
		// Strings
		// ----

		private static void CHKPOS(int x)
		{
			if(x<0)
			{
				throw new Blitz3DException("parameter must be positive");
			}
		}

		private static void CHKOFF(int x)
		{
			if(x<=0)
			{
				throw new Blitz3DException("parameter must be greater than 0");
			}
		}

		public static string Left(string str, int length)
		{
			CHKPOS(length);
			if(length>=str.Length)
				return str;
			return str.Substring(0, length);
		}

		public static string Right(string str, int length)
		{
			CHKPOS(length);
			int pos = str.Length - length;
			if (pos < 0)
				pos = 0;
			return str.Substring(pos);
		}

		public static string Mid(string str, int offset, int length)
		{
			CHKOFF(offset);
			offset--;
			if (offset > str.Length)
			{
				return string.Empty;
			}
			else if(length<0 || offset+length>=str.Length)
			{
				return str.Substring(offset);
			}
			else
			{
				return str.Substring(offset, length);
			}
		}

		public static int Instr(string str1, string str2, int offset)
		{
			CHKOFF(offset);
			offset--;
			int n = str1.IndexOf(str2, offset);
			return n<0 ? 0 : n + 1;
		}
	}
}
