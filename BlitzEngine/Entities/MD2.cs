using System;
using System.Runtime.InteropServices;

namespace BlitzEngine.Entities
{
	public class MD2:Entity
	{
		//public float AnimTime=>Blitz3D.MD2AnimTime(this);
		//public int AnimLength=>Blitz3D.MD2AnimLength(this);
		public bool Animating=>Blitz3D.MD2Animating(this);

		public MD2(string file,Entity parent=null):base(Blitz3D.LoadMD2(file,parent)){}

		public void AnimateMD2(int mode, float speed, int firstFrame, int lastFrame, float transition)=>Blitz3D.AnimateMD2(this,mode,speed,firstFrame,lastFrame,transition);
		
		protected MD2(IntPtr instance):base(instance){}
	}
}

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadMD2_internal(string file, IntPtr parent);

		public static Entity LoadMD2(string file, Entity parent = null)
		{
			Entity ret = new Entity(LoadMD2_internal(file, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void AnimateMD2_internal(IntPtr md2, int mode, float speed, int firstFrame, int lastFrame, float transition);

		public static void AnimateMD2(Entity md2, int mode = 1, float speed = 1.0f, int firstFrame = 0, int lastFrame = 9999, float transition = 0.0f)
		{
			AnimateMD2_internal(md2.Pointer, mode, speed, firstFrame, lastFrame, transition);
		}

		[DllImport(B3DDllLink)]
		private static extern float MD2AnimTime_internal(IntPtr md2);

		public static float MD2AnimTime(Entity md2)
		{
			return MD2AnimTime_internal(md2.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int MD2AnimLength_internal(IntPtr md2);

		public static int MD2AnimLength(Entity md2)
		{
			return MD2AnimLength_internal(md2.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern bool MD2Animating_internal(IntPtr md2);

		public static bool MD2Animating(Entity md2)
		{
			return MD2Animating_internal(md2.Pointer);
		}
	}
}