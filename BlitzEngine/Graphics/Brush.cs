using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Brush : BBPointer
	{
		public Brush(System.IntPtr pointer) : base(pointer) { }
		public Brush(float red = 255, float green = 255, float blue = 255) : base(Blitz3D.CreateBrush(red, green, blue)) { }
		public Brush(string file, int textureFlags = 1, float uScale = 1, float vScale = 1) : base(Blitz3D.LoadBrush(file, textureFlags, uScale, vScale)) { }
		public void Free() => Blitz3D.FreeBrush(this);
		public void Alpha(float alpha) => Blitz3D.BrushAlpha(this, alpha);
		public void Texture(Texture texture, int frame = 0, int index = 0) => Blitz3D.BrushTexture(this, texture, frame, index);
		public void GetTexture(int index = 0) => Blitz3D.GetBrushTexture(this, index);
	}

	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateBrush_internal(float red, float green, float blue);

		public static Brush CreateBrush(float red = 255.0f, float green = 255.0f, float blue = 255.0f)
		{
			Brush ret = new Brush(CreateBrush_internal(red, green, blue));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadBrush_internal(string file, int textureFlags, float uScale, float vScale);

		public static Brush LoadBrush(string file, int textureFlags = 1, float uScale = 1.0f, float vScale = 1.0f)
		{
			Brush ret = new Brush(LoadBrush_internal(file, textureFlags, uScale, vScale));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeBrush_internal(IntPtr brush);

		public static void FreeBrush(Brush brush)
		{
			FreeBrush_internal(brush.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void BrushColor_internal(IntPtr brush, float red, float green, float blue);

		public static void BrushColor(Brush brush, float red, float green, float blue)
		{
			BrushColor_internal(brush.Pointer, red, green, blue);
		}

		[DllImport(B3DDllLink)]
		private static extern void BrushAlpha_internal(IntPtr brush, float alpha);

		public static void BrushAlpha(Brush brush, float alpha)
		{
			BrushAlpha_internal(brush.Pointer, alpha);
		}

		[DllImport(B3DDllLink)]
		private static extern void BrushShininess_internal(IntPtr brush, float shininess);

		public static void BrushShininess(Brush brush, float shininess)
		{
			BrushShininess_internal(brush.Pointer, shininess);
		}

		[DllImport(B3DDllLink)]
		private static extern void BrushTexture_internal(IntPtr brush, IntPtr texture, int frame, int index);

		public static void BrushTexture(Brush brush, Texture texture, int frame = 0, int index = 0)
		{
			BrushTexture_internal(brush.Pointer, texture.Pointer, frame, index);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr GetBrushTexture_internal(IntPtr brush, int index);

		public static Texture GetBrushTexture(Brush brush, int index = 0)
		{
			Texture ret = new Texture(GetBrushTexture_internal(brush.Pointer, index));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void BrushBlend_internal(IntPtr brush, int blend);

		public static void BrushBlend(Brush brush, int blend)
		{
			BrushBlend_internal(brush.Pointer, blend);
		}

		[DllImport(B3DDllLink)]
		private static extern void BrushFX_internal(IntPtr brush, int fx);

		public static void BrushFX(Brush brush, int fx)
		{
			BrushFX_internal(brush.Pointer, fx);
		}
	}
}
