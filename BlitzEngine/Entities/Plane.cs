using System;
using System.Runtime.InteropServices;

namespace BlitzEngine.Entities
{
	public class Plane:Entity
	{
		public Plane(int segments=1,Entity parent=null):this(Blitz3D.CreatePlane(segments,parent)){}

		protected Plane(IntPtr instance):base(instance){}
	}
}

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreatePlane_internal(int segments, IntPtr parent);

		public static Entity CreatePlane(int segments = 1, Entity parent = null)
		{
			Entity ret = new Entity(CreatePlane_internal(segments, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
	}
}