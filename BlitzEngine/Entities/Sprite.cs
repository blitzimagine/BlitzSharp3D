using System;
using System.Runtime.InteropServices;

namespace BlitzEngine.Entities
{
	public class Sprite:Entity
	{
		public Sprite(Entity parent=null):base(Blitz3D.CreateSprite(parent)){}

		public void RotateSprite(float angle)=>Blitz3D.RotateSprite(this,angle);
		public void ScaleSprite(float xScale, float yScale)=>Blitz3D.ScaleSprite(this,xScale,yScale);

		protected Sprite(IntPtr instance):base(instance){}
	}
}

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateSprite_internal(IntPtr parent);

		public static Entity CreateSprite(Entity parent = null)
		{
			Entity ret = new Entity(CreateSprite_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadSprite_internal(string file, int textureFlags, IntPtr parent);

		public static Entity LoadSprite(string file, int textureFlags = 1, Entity parent = null)
		{
			Entity ret = new Entity(LoadSprite_internal(file, textureFlags, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void RotateSprite_internal(IntPtr sprite, float angle);

		public static void RotateSprite(Entity sprite, float angle)
		{
			RotateSprite_internal(sprite.Pointer, angle);
		}

		[DllImport(B3DDllLink)]
		private static extern void ScaleSprite_internal(IntPtr sprite, float xScale, float yScale);

		public static void ScaleSprite(Entity sprite, float xScale, float yScale)
		{
			ScaleSprite_internal(sprite.Pointer, xScale, yScale);
		}

		[DllImport(B3DDllLink)]
		private static extern void HandleSprite_internal(IntPtr sprite, float xHandle, float yHandle);

		public static void HandleSprite(Entity sprite, float xHandle, float yHandle)
		{
			HandleSprite_internal(sprite.Pointer, xHandle, yHandle);
		}

		[DllImport(B3DDllLink)]
		private static extern void SpriteViewMode_internal(IntPtr sprite, int viewMode);

		public static void SpriteViewMode(Entity sprite, int viewMode)
		{
			SpriteViewMode_internal(sprite.Pointer, viewMode);
		}
	}
}