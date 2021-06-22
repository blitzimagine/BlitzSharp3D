using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Cylinder : Entity
	{
		public Cylinder(int segments = 8, bool solid = true, Entity parent = null) : base(Blitz3D.CreateCylinder(segments, solid, parent)) { }
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateCylinder_internal(int segments, bool solid, IntPtr parent);

		public static Entity CreateCylinder(int segments = 8, bool solid = true, Entity parent = null)
		{
			Entity ret = new Entity(CreateCylinder_internal(segments, solid, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
	}
}
