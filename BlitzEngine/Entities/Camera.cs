using System;
using System.Runtime.InteropServices;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace BlitzEngine
{
	public class Camera:Entity
	{
		public Color BackgroundColor;
		public ClearOptions ClearMode;
		public BasicEffect Effect;

		private Viewport viewport;
		public Viewport Viewport
		{
			get => viewport;
			set
			{
				CameraViewport_internal(Pointer, value.X, value.Y, value.Width, value.Height);
				viewport = value;
			}
		}

		public Camera(Entity parent=null):base(CreateCamera_internal(parent != null ? parent.Pointer : IntPtr.Zero))
		{
			if(B3DGame.Instance.CurrentCamera != null){throw new Exception();}
			B3DGame.Instance.CurrentCamera = this;
		}

		internal void Draw(B3DGame game)
		{
			if(Effect is null)
			{
				Effect = new BasicEffect(game.GraphicsDevice);
			}
			game.GraphicsDevice.Viewport = Viewport;
			game.GraphicsDevice.Clear(ClearMode, BackgroundColor, 1, 0);

			foreach(EffectPass pass in Effect.CurrentTechnique.Passes)
			{
				pass.Apply();
				//GraphicsDevice.DrawUserPrimitives(PrimitiveType.TriangleList,vertices,0,vertices.Length/3);
			}

		}

		public void Zoom(float zoom)
		{
			CameraZoom_internal(Pointer,zoom);

		}
		public void Range(float nr, float fr)
		{
			CameraRange_internal(Pointer,nr,fr);
		}

		public void ClsColor(float red, float green, float blue)
		{
			CameraClsColor_internal(Pointer,red,green,blue);
			BackgroundColor = new Color(red, green, blue);
		}
		public void ClsMode(bool color, bool zBuffer)
		{
			CameraClsMode_internal(Pointer, color, zBuffer);
			ClearMode = 0;
			if(color)	{ClearMode |= ClearOptions.Target;}
			if(zBuffer)	{ClearMode |= ClearOptions.DepthBuffer;}
		}

		public void ProjMode(int mode)
		{
			CameraProjMode_internal(Pointer, mode);
		}

		public void FogColor(float red, float green, float blue)
		{
			CameraFogColor_internal(Pointer, red, green, blue);
			Effect.FogColor = new Vector3(red, green, blue);
		}
		public void FogRange(float nr, float fr)
		{
			CameraFogRange_internal(Pointer, nr, fr);
			Effect.FogStart = nr;//Near
			Effect.FogEnd = fr;//Far
		}
		public void FogMode(int mode)
		{
			CameraFogMode_internal(Pointer, mode);
			Effect.FogEnabled = mode!=0;
		}
		public int Project(float x, float y, float z)
		{
			return CameraProject_internal(Pointer, x, y, z);
		}

		public static float ProjectedX => ProjectedX_internal();
		public static float ProjectedY => ProjectedY_internal();
		public static float ProjectedZ => ProjectedZ_internal();

		public bool EntityInView(Entity entity)
		{
			return EntityInView_internal(entity.Pointer, Pointer);
		}

		[DllImport(Blitz3D.B3DDllLink)]private static extern IntPtr CreateCamera_internal(IntPtr parent);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraZoom_internal(IntPtr camera, float zoom);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraRange_internal(IntPtr camera, float nr, float fr);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraClsColor_internal(IntPtr camera, float red, float green, float blue);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraClsMode_internal(IntPtr camera, bool color, bool zBuffer);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraProjMode_internal(IntPtr camera, int mode);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraViewport_internal(IntPtr camera, int x, int y, int width, int height);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraFogColor_internal(IntPtr camera, float red, float green, float blue);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraFogRange_internal(IntPtr camera, float nr, float fr);
		[DllImport(Blitz3D.B3DDllLink)]private static extern void CameraFogMode_internal(IntPtr camera, int mode);
		[DllImport(Blitz3D.B3DDllLink)]private static extern int CameraProject_internal(IntPtr camera, float x, float y, float z);

		[DllImport(Blitz3D.B3DDllLink,EntryPoint = "ProjectedX")]public static extern float ProjectedX_internal();
		[DllImport(Blitz3D.B3DDllLink,EntryPoint = "ProjectedY")]public static extern float ProjectedY_internal();
		[DllImport(Blitz3D.B3DDllLink,EntryPoint = "ProjectedZ")]public static extern float ProjectedZ_internal();

		[DllImport(Blitz3D.B3DDllLink)]private static extern bool EntityInView_internal(IntPtr entity, IntPtr camera);
	}
	public static partial class Blitz3D
	{
		public static Camera CreateCamera(Entity parent = null) => new Camera(parent);
		public static void CameraZoom(Entity camera, float zoom) => ((Camera)camera).Zoom(zoom);
		public static void CameraRange(Entity camera, float nr, float fr) => ((Camera)camera).Range(nr, fr);
		public static void CameraClsColor(Entity camera, float red, float green, float blue) => ((Camera)camera).ClsColor(red,green,blue);
		public static void CameraClsMode(Entity camera, bool color, bool zBuffer) => ((Camera)camera).ClsMode(color, zBuffer);
		public static void CameraProjMode(Entity camera, int mode) => ((Camera)camera).ProjMode(mode);
		public static void CameraViewport(Entity camera, int x, int y, int width, int height) => ((Camera)camera).Viewport = new Viewport(x, y, width, height);
		public static void CameraFogColor(Entity camera, float red, float green, float blue) => ((Camera)camera).FogColor(red, green, blue);
		public static void CameraFogRange(Entity camera, float nr, float fr) => ((Camera)camera).FogRange(nr, fr);
		public static void CameraFogMode(Entity camera, int mode) => ((Camera)camera).FogMode(mode);
		public static int CameraProject(Entity camera, float x, float y, float z) => ((Camera)camera).Project(x, y, z);
		public static float ProjectedX() => Camera.ProjectedX;
		public static float ProjectedY() => Camera.ProjectedY;
		public static float ProjectedZ() => Camera.ProjectedZ;
		public static bool EntityInView(Entity entity, Entity camera) => ((Camera)camera).EntityInView(entity);
	}
}
