using System;
using System.Runtime.InteropServices;
using System.Text;

namespace BlitzEngine
{
	public class Texture:BBPointer
	{
		public Texture(IntPtr pointer):base(pointer){}
		public Texture(int width, int height, int flags = 0, int frames = 1):base(Blitz3D.CreateTexture(width,height,flags,frames)){}
		public Texture(string file, int flags = 1):base(Blitz3D.LoadTexture(file,flags)){}
		public Texture(string file, int flags, int width, int height, int first, int count):base(Blitz3D.LoadAnimTexture(file,flags,width,height,first,count)){}
		public void Free()=>Blitz3D.FreeTexture(this);
		public void Blend(int blend)=>Blitz3D.TextureBlend(this,blend);
		public void Scale(float uScale, float vScale)=>Blitz3D.ScaleTexture(this,uScale,vScale);
		public void Rotate(float angle)=>Blitz3D.RotateTexture(this,angle);
		public void Position(float uOffset, float vOffset)=>Blitz3D.PositionTexture(this,uOffset,vOffset);
	}

	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateTexture_internal(int width, int height, int flags, int frames);

		public static Texture CreateTexture(int width, int height, int flags = 0, int frames = 1)
		{
			Texture ret = new Texture(CreateTexture_internal(width, height, flags, frames));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadTexture_internal(string file, int flags);

		public static Texture LoadTexture(string file, int flags = 1)
		{
			Texture ret = new Texture(LoadTexture_internal(file, flags));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadAnimTexture_internal(string file, int flags, int width, int height, int first, int count);

		public static Texture LoadAnimTexture(string file, int flags, int width, int height, int first, int count)
		{
			Texture ret = new Texture(LoadAnimTexture_internal(file, flags, width, height, first, count));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeTexture_internal(IntPtr texture);

		public static void FreeTexture(Texture texture)
		{
			if (texture != null && texture.Pointer != IntPtr.Zero)
			{
				FreeTexture_internal(texture.Pointer);
				texture.Pointer = IntPtr.Zero;
			}
		}

		[DllImport(B3DDllLink)]
		private static extern void TextureBlend_internal(IntPtr texture, int blend);

		public static void TextureBlend(Texture texture, int blend)
		{
			TextureBlend_internal(texture.Pointer, blend);
		}

		[DllImport(B3DDllLink)]
		private static extern void TextureCoords_internal(IntPtr texture, int coords);

		public static void TextureCoords(Texture texture, int coords)
		{
			TextureCoords_internal(texture.Pointer, coords);
		}

		[DllImport(B3DDllLink)]
		private static extern void ScaleTexture_internal(IntPtr texture, float uScale, float vScale);

		public static void ScaleTexture(Texture texture, float uScale, float vScale)
		{
			ScaleTexture_internal(texture.Pointer, uScale, vScale);
		}

		[DllImport(B3DDllLink)]
		private static extern void RotateTexture_internal(IntPtr texture, float angle);

		public static void RotateTexture(Texture texture, float angle)
		{
			RotateTexture_internal(texture.Pointer, angle);
		}

		[DllImport(B3DDllLink)]
		private static extern void PositionTexture_internal(IntPtr texture, float uOffset, float vOffset);

		public static void PositionTexture(Texture texture, float uOffset, float vOffset)
		{
			PositionTexture_internal(texture.Pointer, uOffset, vOffset);
		}

		[DllImport(B3DDllLink)]
		private static extern int TextureWidth_internal(IntPtr texture);

		public static int TextureWidth(Texture texture)
		{
			return TextureWidth_internal(texture.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int TextureHeight_internal(IntPtr texture);

		public static int TextureHeight(Texture texture)
		{
			return TextureHeight_internal(texture.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void TextureName_internal(StringBuilder ret, int retLen, IntPtr texture);

		public static string TextureName(Texture texture)
		{
			StringBuilder sb = new StringBuilder(4096);
			TextureName_internal(sb, sb.Capacity, texture.Pointer);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		private static extern void SetCubeFace_internal(IntPtr texture, int face);

		public static void SetCubeFace(Texture texture, int face)
		{
			SetCubeFace_internal(texture.Pointer, face);
		}

		[DllImport(B3DDllLink)]
		private static extern void SetCubeMode_internal(IntPtr texture, int mode);

		public static void SetCubeMode(Texture texture, int mode)
		{
			SetCubeMode_internal(texture.Pointer, mode);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr TextureBuffer_internal(IntPtr texture, int frame);

		public static Canvas TextureBuffer(Texture texture, int frame = 0)
		{
			Canvas ret = new Canvas(TextureBuffer_internal(texture.Pointer, frame));
			return ret;
		}
	}
}
