using System;
using System.Text;

namespace BlitzEngine
{
	public unsafe abstract class Stream
	{
		public const int EOF_ERROR = -1;
		public const int EOF_NOT = 0;
		public const int EOF_OK = 1;

		//returns chars read
		public int Read(byte[] buff, int size) => Read(buff, 0, size);
		public abstract int Read(byte[] buff, int offset, int size);

		//returns chars written
		public int Write(byte[] buff, int size) => Write(buff, 0, size);
		public abstract int Write(byte[] buff, int offset, int size);


		//returns chars avilable for reading
		public abstract int Avail();

		//returns EOF status
		public abstract bool Eof();

		public byte ReadByte()
		{
			byte[] bytes = new byte[1];
			Read(bytes, 1);
			return bytes[0];
		}

		public short ReadShort()
		{
			byte[] bytes = new byte[2];
			Read(bytes, 2);
			return BitConverter.ToInt16(bytes,0);
		}

		public int ReadInt()
		{
			byte[] bytes = new byte[4];
			Read(bytes, 4);
			return BitConverter.ToInt32(bytes,0);
		}

		public float ReadFloat()
		{
			byte[] bytes = new byte[4];
			Read(bytes, 4);
			return BitConverter.ToSingle(bytes,0);
		}

		public string ReadString()
		{
			int len = ReadInt();
			if(len>0)
			{
				byte[] buff = new byte[len];
				if(Read(buff, len)>0)
				{
					return Encoding.ASCII.GetString(buff);
				}
			}
			return string.Empty;
		}

		public string ReadLine()
		{
			StringBuilder str = new StringBuilder();
			byte[] buff = new byte[1];
			while(true)
			{
				int c = Read(buff, 1);
				if(c<=0)
				{
					break;
				}
				if(buff[0] == '\n')
				{
					break;
				}
				if(buff[0] != '\r')
				{
					str.Append(c);
				}
			}
			return str.ToString();
		}

		public void WriteByte(int n)
		{
			Write(new[]{(byte)n}, 1);
		}

		public void WriteShort(int n)
		{
			byte[] bytes = BitConverter.GetBytes((short)n);
			Write(bytes, 2);
		}

		public void WriteInt(int n)
		{
			byte[] bytes = BitConverter.GetBytes(n);
			Write(bytes, 4);
		}

		public void WriteFloat(float n)
		{
			byte[] bytes = BitConverter.GetBytes(n);
			Write(bytes, 4);
		}

		public void WriteString(string t)
		{
			byte[] bytes = Encoding.ASCII.GetBytes(t);
			byte[] lengthBytes = BitConverter.GetBytes(bytes.Length);
			Write(lengthBytes, 4);
			Write(bytes, bytes.Length);
		}

		public void WriteLine(string t)
		{
			byte[] bytes = Encoding.ASCII.GetBytes(t+"\r\n");
			Write(bytes, bytes.Length);
		}

		public static void CopyStream(Stream s, Stream d, int buff_size = 16384)
		{
			byte[] buff = new byte[buff_size];
			while(!s.Eof() && !d.Eof())
			{
				int n = s.Read(buff, buff_size);
				d.Write(buff, n);
				if(n < buff_size)
				{
					break;
				}
			}
		}
	}
}
