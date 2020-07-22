using System;
using System.Runtime.InteropServices;
using BlitzEngine.Entities;

namespace BlitzEngine.Entities
{
	public class Pivot:Entity
	{
		public Pivot(Entity parent = null):base(CreatePivot_internal(parent != null ? parent.Pointer : IntPtr.Zero)){}

		protected Pivot(IntPtr instance):base(instance){}

		[DllImport(Blitz3D.B3DDllLink)]
		private static extern IntPtr CreatePivot_internal(IntPtr parent);
	}
}

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		public static Entity CreatePivot(Entity parent = null) => new Pivot(parent);
	}
}