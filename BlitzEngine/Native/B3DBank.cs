namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// ----
		// Bank
		// ----

		public static Bank CreateBank(int size = 0) => new Bank(size);

		public static void FreeBank(Bank bank){}

		public static int BankSize(Bank bank) => bank.Size;

		public static void ResizeBank(Bank bank, int size) => bank.Resize(size);

		public static void CopyBank(Bank src, int srcOffset, Bank dest, int destOffset, int count)
		{
			Bank.Copy(src, srcOffset, dest, destOffset, count);
		}

		public static byte PeekByte(Bank bank, int offset) => bank.Peek<byte>(offset);

		public static short PeekShort(Bank bank, int offset) => bank.Peek<short>(offset);

		public static int PeekInt(Bank bank, int offset) => bank.Peek<int>(offset);

		public static float PeekFloat(Bank bank, int offset) => bank.Peek<float>(offset);

		public static void PokeByte(Bank bank, int offset, byte value) => bank.Poke(offset, value);

		public static void PokeShort(Bank bank, int offset, short value) => bank.Poke(offset, value);

		public static void PokeInt(Bank bank, int offset, int value) => bank.Poke(offset, value);

		public static void PokeFloat(Bank bank, int offset, float value) => bank.Poke(offset, value);

		public static int ReadBytes(Bank bank, Stream stream, int offset, int count) => bank.ReadBytes(stream, offset, count);
		
		public static int WriteBytes(Bank bank, Stream stream, int offset, int count) => bank.WriteBytes(stream, offset, count);
	}
}
