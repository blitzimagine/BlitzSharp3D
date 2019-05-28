using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Camera:Entity
	{
		public Camera(Entity parent=null):base(Blitz3D.CreateCamera(parent)){}

		protected Camera(IntPtr instance):base(instance){}

		public void Zoom(float zoom)=>Blitz3D.CameraZoom(this,zoom);
		public void Range(float nr, float fr)=>Blitz3D.CameraRange(this,nr,fr);
		//public void CameraClsColor(float red, float green, float blue)=>Blitz3D.CameraClsColor(this,red,green,blue);
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateCamera_internal(IntPtr parent);

		public static Entity CreateCamera(Entity parent = null)
		{
			Entity ret = new Entity(CreateCamera_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraZoom_internal(IntPtr camera, float zoom);

		public static void CameraZoom(Entity camera, float zoom)
		{
			CameraZoom_internal(camera.Pointer, zoom);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraRange_internal(IntPtr camera, float nr, float fr);

		public static void CameraRange(Entity camera, float nr, float fr)
		{
			CameraRange_internal(camera.Pointer, nr, fr);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraClsColor_internal(IntPtr camera, float red, float green, float blue);

		public static void CameraClsColor(Entity camera, float red, float green, float blue)
		{
			CameraClsColor_internal(camera.Pointer, red, green, blue);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraClsMode_internal(IntPtr camera, bool color, bool zBuffer);

		public static void CameraClsMode(Entity camera, bool color, bool zBuffer)
		{
			CameraClsMode_internal(camera.Pointer, color, zBuffer);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraProjMode_internal(IntPtr camera, int mode);

		public static void CameraProjMode(Entity camera, int mode)
		{
			CameraProjMode_internal(camera.Pointer, mode);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraViewport_internal(IntPtr camera, int x, int y, int width, int height);

		public static void CameraViewport(Entity camera, int x, int y, int width, int height)
		{
			CameraViewport_internal(camera.Pointer, x, y, width, height);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraFogColor_internal(IntPtr camera, float red, float green, float blue);

		public static void CameraFogColor(Entity camera, float red, float green, float blue)
		{
			CameraFogColor_internal(camera.Pointer, red, green, blue);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraFogRange_internal(IntPtr camera, float nr, float fr);

		public static void CameraFogRange(Entity camera, float nr, float fr)
		{
			CameraFogRange_internal(camera.Pointer, nr, fr);
		}

		[DllImport(B3DDllLink)]
		private static extern void CameraFogMode_internal(IntPtr camera, int mode);

		public static void CameraFogMode(Entity camera, int mode)
		{
			CameraFogMode_internal(camera.Pointer, mode);
		}

		[DllImport(B3DDllLink)]
		private static extern int CameraProject_internal(IntPtr camera, float x, float y, float z);

		public static int CameraProject(Entity camera, float x, float y, float z)
		{
			return CameraProject_internal(camera.Pointer, x, y, z);
		}

		[DllImport(B3DDllLink)]
		public static extern float ProjectedX();

		[DllImport(B3DDllLink)]
		public static extern float ProjectedY();

		[DllImport(B3DDllLink)]
		public static extern float ProjectedZ();

		[DllImport(B3DDllLink)]
		private static extern bool EntityInView_internal(IntPtr entity, IntPtr camera);

		public static bool EntityInView(Entity entity, Entity camera)
		{
			return EntityInView_internal(entity.Pointer, camera.Pointer);
		}
	}
}
