using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Cube:Entity
	{
		public Cube(Entity parent=null):base(Blitz3D.CreateCube(parent)){}
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateCube_internal(IntPtr parent);

		public static Entity CreateCube(Entity parent = null)
		{
			Entity ret = new Entity(CreateCube_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
	}
}
