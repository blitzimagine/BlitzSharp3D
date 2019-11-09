using System;

namespace BlitzEngine
{
	public class BBPointer
	{
		public IntPtr Pointer;

		public BBPointer(IntPtr pointer)
		{
			Pointer = pointer;
		}

		public override int GetHashCode()=>Pointer.GetHashCode();
		public override bool Equals(object obj)=>(obj is BBPointer that) && (this.Pointer==that.Pointer);

		public static bool operator ==(BBPointer a, BBPointer b)
		{
			if (a is null && b is null)
				return true;

			if (a is null && b.Pointer == IntPtr.Zero)
				return true;

			if (b is null && a.Pointer == IntPtr.Zero)
				return true;

			if (a is null || b is null)
				return false;

			return a.Pointer == b.Pointer;
		}

		public static bool operator !=(BBPointer a, BBPointer b)
		{
			return !(a == b);
		}

		public static implicit operator IntPtr(BBPointer that)=>that == null ? IntPtr.Zero : that.Pointer;
	}
}
