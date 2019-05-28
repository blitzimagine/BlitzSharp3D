using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class AnimMesh:Entity
	{
		private AnimMesh(string file,Entity parent=null):base(Blitz3D.LoadAnimMesh(file,parent)){}

		public static AnimMesh LoadAnimMesh(string file,Entity parent=null)=>new AnimMesh(file,parent);
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadAnimMesh_internal(string file, IntPtr parent);

		public static Entity LoadAnimMesh(string file, Entity parent = null)
		{
			Entity ret = new Entity(LoadAnimMesh_internal(file, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
	}
}
