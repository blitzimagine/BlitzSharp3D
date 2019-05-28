using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Sphere:Entity
	{
		public Sphere(int segments=8,Entity parent=null):base(Blitz3D.CreateSphere(segments,parent)){}
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateSphere_internal(int segments, IntPtr parent);

		public static Entity CreateSphere(int segments = 8, Entity parent = null)
		{
			Entity ret = new Entity(CreateSphere_internal(segments, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
	}
}
