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
		// Bank
		// ----

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateBank_internal(int size);

		public static Bank CreateBank(int size = 0)
		{
			IntPtr pointer = CreateBank_internal(size);
			Bank ret = new Bank(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeBank_internal(IntPtr bank);

		public static void FreeBank(Bank bank)
		{
			FreeBank_internal(bank.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int BankSize_internal(IntPtr bank);

		public static int BankSize(Bank bank)
		{
			return BankSize_internal(bank.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void ResizeBank_internal(IntPtr bank, int size);

		public static void ResizeBank(Bank bank, int size)
		{
			ResizeBank_internal(bank.Pointer, size);
		}

		[DllImport(B3DDllLink)]
		private static extern void CopyBank_internal(IntPtr src, int srcOffset, IntPtr dest, int destOffset, int count);

		public static void CopyBank(Bank src, int srcOffset, Bank dest, int destOffset, int count)
		{
			CopyBank_internal(src.Pointer, srcOffset, dest.Pointer, destOffset, count);
		}

		[DllImport(B3DDllLink)]
		private static extern byte PeekByte_internal(IntPtr bank, int offset);

		public static byte PeekByte(Bank bank, int offset)
		{
			return PeekByte_internal(bank.Pointer, offset);
		}

		[DllImport(B3DDllLink)]
		private static extern short PeekShort_internal(IntPtr bank, int offset);

		public static short PeekShort(Bank bank, int offset)
		{
			return PeekShort_internal(bank.Pointer, offset);
		}

		[DllImport(B3DDllLink)]
		private static extern int PeekInt_internal(IntPtr bank, int offset);

		public static int PeekInt(Bank bank, int offset)
		{
			return PeekInt_internal(bank.Pointer, offset);
		}

		[DllImport(B3DDllLink)]
		private static extern float PeekFloat_internal(IntPtr bank, int offset);

		public static float PeekFloat(Bank bank, int offset)
		{
			return PeekFloat_internal(bank.Pointer, offset);
		}

		[DllImport(B3DDllLink)]
		private static extern void PokeByte_internal(IntPtr bank, int offset, byte value);

		public static void PokeByte(Bank bank, int offset, byte value)
		{
			PokeByte_internal(bank.Pointer, offset, value);
		}

		[DllImport(B3DDllLink)]
		private static extern void PokeShort_internal(IntPtr bank, int offset, short value);

		public static void PokeShort(Bank bank, int offset, short value)
		{
			PokeShort_internal(bank.Pointer, offset, value);
		}

		[DllImport(B3DDllLink)]
		private static extern void PokeInt_internal(IntPtr bank, int offset, int value);

		public static void PokeInt(Bank bank, int offset, int value)
		{
			PokeInt_internal(bank.Pointer, offset, value);
		}

		[DllImport(B3DDllLink)]
		private static extern void PokeFloat_internal(IntPtr bank, int offset, float value);

		public static void PokeFloat(Bank bank, int offset, float value)
		{
			PokeFloat_internal(bank.Pointer, offset, value);
		}

		[DllImport(B3DDllLink)]
		private static extern int ReadBytes_internal(IntPtr bank, IntPtr stream, int offset, int count);

		public static int ReadBytes(Bank bank, Stream stream, int offset, int count)
		{
			return ReadBytes_internal(bank.Pointer, stream.Pointer, offset, count);
		}

		[DllImport(B3DDllLink)]
		private static extern int WriteBytes_internal(IntPtr bank, IntPtr stream, int offset, int count);

		public static int WriteBytes(Bank bank, Stream stream, int offset, int count)
		{
			return WriteBytes_internal(bank.Pointer, stream.Pointer, offset, count);
		}

		[DllImport(B3DDllLink)]
		private static extern int CallDLL_internal(string dll, string func, IntPtr input, IntPtr output);

		public static int CallDLL(string dll, string func, Bank input, Bank output)
		{
			return CallDLL_internal(dll, func, input.Pointer, output.Pointer);
		}
	}
}
