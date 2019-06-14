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
		// Strings
		// ----

		[DllImport(B3DDllLink)]
		private static extern void Left_internal(StringBuilder ret, int retLen, string str, int length);

		public static string Left(string str, int length)
		{
			StringBuilder sb = new StringBuilder(4096);
			Left_internal(sb, sb.Capacity, str, length);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		private static extern void Right_internal(StringBuilder ret, int retLen, string str, int length);

		public static string Right(string str, int length)
		{
			StringBuilder sb = new StringBuilder(4096);
			Right_internal(sb, sb.Capacity, str, length);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		private static extern void Mid_internal(StringBuilder ret, int retLen, string str, int offset, int length);

		public static string Mid(string str, int offset, int length)
		{
			StringBuilder sb = new StringBuilder(4096);
			Mid_internal(sb, sb.Capacity, str, offset, length);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern int Instr(string str1, string str2, int offset);
	}
}
