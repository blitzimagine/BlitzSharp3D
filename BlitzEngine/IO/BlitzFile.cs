using System;
namespace BlitzEngine
{
	public class BlitzFile : Stream
	{
		public BlitzFile(IntPtr pointer) : base(pointer) { }
	}
}
