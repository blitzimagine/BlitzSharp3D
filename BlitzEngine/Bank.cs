using System;

namespace BlitzEngine
{
	public unsafe class Bank
	{
		private byte[] data;
		private int capacity;

		public int Size{get;private set;}

		public Bank(int sz)
		{
			Size = sz;
			capacity = (Size + 15) & ~15;
			data = new byte[capacity];
		}
		
		public void Resize(int newSize)
		{
			if (newSize > Size)
			{
				if (newSize > capacity)
				{
					capacity = capacity * 3 / 2;
					if (newSize > capacity)
					{
						capacity = newSize;
					}
					capacity = (capacity + 15) & ~15;
					Array.Resize(ref data, capacity);
				}
				else
				{
					Array.Clear(data,Size,newSize-Size);
				}
			}
			Size = newSize;
		}

		public T Peek<T>(int offset) where T:unmanaged
		{
			fixed(byte* data0 = data)
			{
				return *(T*)(data0+offset);
			}
		}

		public void Poke<T>(int offset, T value) where T:unmanaged
		{
			fixed(byte* data0 = data)
			{
				*(T*)(data0+offset) = value;
			}
		}

		public static void Copy(Bank src, int src_p, Bank dest, int dest_p, int count)
		{
			Array.Copy(src.data, src_p, dest.data, dest_p, count);
		}

		public int ReadBytes(Stream s, int offset, int count) => s.Read(data, offset, count);

		public int WriteBytes(Stream s, int offset, int count) => s.Write(data, offset, count);
	}
}
