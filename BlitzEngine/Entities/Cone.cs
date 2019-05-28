using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Cone:Entity
	{
		public Cone(int segments=8,bool solid=true,Entity parent=null):base(Blitz3D.CreateCone(segments,solid,parent)){}
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateCone_internal(int segments, bool solid, IntPtr parent);

		public static Entity CreateCone(int segments = 8, bool solid = true, Entity parent = null)
		{
			Entity ret = new Entity(CreateCone_internal(segments, solid, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
	}
}
