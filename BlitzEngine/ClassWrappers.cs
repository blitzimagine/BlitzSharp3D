using System;

namespace BlitzEngine
{
	public class Timer : BBPointer
	{
		public Timer(IntPtr pointer) : base(pointer) { }
	}

	public class UDPStream : BBPointer
	{
		public UDPStream(IntPtr pointer) : base(pointer) { }
	}

	public class TCPStream : BBPointer
	{
		public TCPStream(IntPtr pointer) : base(pointer) { }
	}

	public class TCPServer : BBPointer
	{
		public TCPServer(IntPtr pointer) : base(pointer) { }
	}

	public class Bank : BBPointer
	{
		public Bank(IntPtr pointer) : base(pointer) { }
	}
}
