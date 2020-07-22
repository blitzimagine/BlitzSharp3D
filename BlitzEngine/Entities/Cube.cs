using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Cube:Entity
	{
		public Cube(Entity parent=null):base(CreateCube_internal(parent?.Pointer ?? IntPtr.Zero)){}

		[DllImport(Blitz3D.B3DDllLink)]
		private static extern IntPtr CreateCube_internal(IntPtr parent);
	}
	public static partial class Blitz3D
	{
		public static Cube CreateCube(Entity parent = null) => new Cube(parent);
	}
}
