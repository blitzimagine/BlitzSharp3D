using System;
using System.Runtime.InteropServices;
using BlitzEngine.Entities;

namespace BlitzEngine.Entities
{
	public class Light:Entity
	{
		public enum Type:int
		{
			Directional=1,
			Point=2,
			Spot=3
		}
		
		public Light(Type type=Type.Directional,Entity parent=null):base(CreateLight_internal(type, parent != null ? parent.Pointer : IntPtr.Zero)){}

		public void Color(float red, float green, float blue) => LightColor_internal(Pointer, red, green, blue);
		public void Range(float range) => LightRange_internal(Pointer, range);
		public void ConeAngles(float innerAngle, float outerAngle) => LightConeAngles_internal(Pointer, innerAngle, outerAngle);

		[DllImport(Blitz3D.B3DDllLink)]private static extern IntPtr CreateLight_internal(Type type, IntPtr parent);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void LightColor_internal(IntPtr light, float red, float green, float blue);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void LightRange_internal(IntPtr light, float range);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void LightConeAngles_internal(IntPtr light, float innerAngle, float outerAngle);
	}
}

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		public static Entity CreateLight(int type = 1, Entity parent = null) => new Light((Light.Type)type, parent);
		public static void LightColor(Entity light, float red, float green, float blue) => ((Light)light).Color(red, green, blue);
		public static void LightRange(Entity light, float range) => ((Light)light).Range(range);
		public static void LightConeAngles(Entity light, float innerAngle, float outerAngle) => ((Light)light).ConeAngles(innerAngle, outerAngle);
	}
}