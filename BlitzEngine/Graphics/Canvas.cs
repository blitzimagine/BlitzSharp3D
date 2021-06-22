using System;

namespace BlitzEngine
{
	public class Canvas : BBPointer
	{
		public Canvas(IntPtr pointer) : base(pointer) { }

		public bool Load(string bmpFile) => Blitz3D.LoadBuffer(this, bmpFile);
		public bool Save(string bmpFile) => Blitz3D.SaveBuffer(this, bmpFile);

		public void Dirty() => Blitz3D.BufferDirty(this);
		public void Lock() => Blitz3D.LockBuffer(this);
		public void Unlock() => Blitz3D.UnlockBuffer(this);

	}
}
