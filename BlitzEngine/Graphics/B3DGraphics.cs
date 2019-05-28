using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using BlitzEngine.Enums;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// --------
		// Graphics
		// --------

		[DllImport(B3DDllLink)]
		public static extern int CountGfxDrivers();

		[DllImport(B3DDllLink)]
		private static extern void GfxDriverName_internal(StringBuilder ret, int retLen, int driver);

		public static string GfxDriverName(int driver)
		{
			StringBuilder sb = new StringBuilder(4096);
			GfxDriverName_internal(sb, sb.Capacity, driver);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern void SetGfxDriver(int driver);

		[DllImport(B3DDllLink)]
		public static extern int CountGfxModes();

		[DllImport(B3DDllLink)]
		public static extern bool GfxModeExists(int width, int height, int depth);

		[DllImport(B3DDllLink)]
		public static extern int GfxModeWidth(int mode);

		[DllImport(B3DDllLink)]
		public static extern int GfxModeHeight(int mode);

		[DllImport(B3DDllLink)]
		public static extern int GfxModeDepth(int mode);

		[DllImport(B3DDllLink)]
		public static extern int AvailVidMem();

		[DllImport(B3DDllLink)]
		public static extern int TotalVidMem();

		[DllImport(B3DDllLink)]
		public static extern bool GfxDriver3D(int driver);

		[DllImport(B3DDllLink)]
		public static extern int CountGfxModes3D();

		[DllImport(B3DDllLink)]
		public static extern bool GfxMode3DExists(int width, int height, BitDepth depth);

		[DllImport(B3DDllLink)]
		public static extern bool GfxMode3D(int mode);

		[DllImport(B3DDllLink)]
		public static extern bool Windowed3D();

		[DllImport(B3DDllLink)]
		public static extern void Graphics(int width, int height, BitDepth depth = BitDepth.Bits32, WindowMode mode = WindowMode.Windowed, int monitor = 0);

		[DllImport(B3DDllLink)]
		public static extern void Graphics3D(int width, int height, BitDepth depth = BitDepth.Bits32, WindowMode mode = WindowMode.Windowed, int monitor = 0);

		[DllImport(B3DDllLink)]
		public static extern void EndGraphics();

		[DllImport(B3DDllLink)]
		public static extern bool SetGraphicsMode_internal(int width, int height, BitDepth depth = BitDepth.Bits32, WindowMode mode = WindowMode.Windowed, int monitor = 0);

		[DllImport(B3DDllLink)]
		public static extern bool GraphicsLost();

		[DllImport(B3DDllLink)]
		public static extern bool IsFocused();

		[DllImport(B3DDllLink)]
		public static extern void SetGamma(int srcRed, int srcGreen, int srcBlue, float destRed, float destGreen, float destBlue);

		[DllImport(B3DDllLink)]
		public static extern void UpdateGamma(bool calibrate = false);

		[DllImport(B3DDllLink)]
		public static extern float GammaRed(int red);

		[DllImport(B3DDllLink)]
		public static extern float GammaGreen(int green);

		[DllImport(B3DDllLink)]
		public static extern float GammaBlue(int blue);

		[DllImport(B3DDllLink)]
		private static extern IntPtr FrontBuffer_internal();

		public static Canvas FrontBuffer()
		{
			IntPtr pointer = FrontBuffer_internal();
			Canvas ret = new Canvas(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr BackBuffer_internal();

		public static Canvas BackBuffer()
		{
			IntPtr pointer = BackBuffer_internal();
			Canvas ret = new Canvas(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		public static extern int ScanLine();

		[DllImport(B3DDllLink)]
		public static extern void VWait(int frames = 1);

		[DllImport(B3DDllLink)]
		public static extern void Flip(bool vwait = true);

		[DllImport(B3DDllLink)]
		public static extern int GraphicsWidth();

		[DllImport(B3DDllLink)]
		public static extern int GraphicsHeight();

		[DllImport(B3DDllLink)]
		public static extern int GraphicsDepth();

		[DllImport(B3DDllLink)]
		private static extern void SetBuffer_internal(IntPtr buffer);

		public static void SetBuffer(Canvas buffer)
		{
			SetBuffer_internal(buffer.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr GraphicsBuffer_internal();

		public static Canvas GraphicsBuffer()
		{
			Canvas ret = new Canvas(GraphicsBuffer_internal());
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern bool LoadBuffer_internal(IntPtr buffer, string bmpFile);

		public static bool LoadBuffer(Canvas buffer, string bmpFile)
		{
			return LoadBuffer_internal(buffer.Pointer, bmpFile);
		}

		[DllImport(B3DDllLink)]
		private static extern bool SaveBuffer_internal(IntPtr buffer, string bmpFile);

		public static bool SaveBuffer(Canvas buffer, string bmpFile)
		{
			return SaveBuffer_internal(buffer.Pointer, bmpFile);
		}

		[DllImport(B3DDllLink)]
		private static extern void BufferDirty_internal(IntPtr buffer);

		public static void BufferDirty(Canvas buffer)
		{
			BufferDirty_internal(buffer.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void LockBuffer_internal(IntPtr buffer);

		public static void LockBuffer(Canvas buffer = null)
		{
			LockBuffer_internal(buffer != null ? buffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern void UnlockBuffer_internal(IntPtr buffer);

		public static void UnlockBuffer(Canvas buffer = null)
		{
			UnlockBuffer_internal(buffer != null ? buffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern int ReadPixel_internal(int x, int y, IntPtr buffer);

		public static int ReadPixel(int x, int y, Canvas buffer = null)
		{
			return ReadPixel_internal(x, y, buffer != null ? buffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern void WritePixel_internal(int x, int y, int argb, IntPtr buffer);

		public static void WritePixel(int x, int y, int argb, Canvas buffer = null)
		{
			WritePixel_internal(x, y, argb, buffer != null ? buffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern int ReadPixelFast_internal(int x, int y, IntPtr buffer);

		public static int ReadPixelFast(int x, int y, Canvas buffer = null)
		{
			return ReadPixelFast_internal(x, y, buffer != null ? buffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern void WritePixelFast_internal(int x, int y, int argb, IntPtr buffer);

		public static void WritePixelFast(int x, int y, int argb, Canvas buffer = null)
		{
			WritePixelFast_internal(x, y, argb, buffer != null ? buffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern void CopyPixel_internal(int srcX, int srcY, IntPtr srcBuffer, int destX, int destY, IntPtr destBuffer);

		public static void CopyPixel(int srcX, int srcY, Canvas srcBuffer, int destX, int destY, Canvas destBuffer = null)
		{
			CopyPixel_internal(srcX, srcY, srcBuffer.Pointer, destX, destY, destBuffer != null ? destBuffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern void CopyPixelFast_internal(int srcX, int srcY, IntPtr srcBuffer, int destX, int destY, IntPtr destBuffer);

		public static void CopyPixelFast(int srcX, int srcY, Canvas srcBuffer, int destX, int destY, Canvas destBuffer = null)
		{
			CopyPixelFast_internal(srcX, srcY, srcBuffer.Pointer, destX, destY, destBuffer != null ? destBuffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		public static extern void Origin(int x, int y);

		[DllImport(B3DDllLink)]
		public static extern void Viewport(int x, int y, int width, int height);

		[DllImport(B3DDllLink)]
		public static extern void Color(int r, int g, int b);

		[DllImport(B3DDllLink)]
		public static extern void GetColor(int x, int y);

		[DllImport(B3DDllLink)]
		public static extern int ColorRed();

		[DllImport(B3DDllLink)]
		public static extern int ColorGreen();

		[DllImport(B3DDllLink)]
		public static extern int ColorBlue();

		[DllImport(B3DDllLink)]
		public static extern void ClsColor(int r, int g, int b);

		[DllImport(B3DDllLink)]
		private static extern void SetFont_internal(IntPtr font);

		public static void SetFont(Font font)
		{
			SetFont_internal(font.Pointer);
		}

		[DllImport(B3DDllLink)]
		public static extern void Cls();

		[DllImport(B3DDllLink)]
		public static extern void Plot(int x, int y);

		[DllImport(B3DDllLink)]
		public static extern void Rect(int x, int y, int width, int height, bool solid = true);

		[DllImport(B3DDllLink)]
		public static extern void Oval(int x, int y, int width, int height, bool solid = true);

		[DllImport(B3DDllLink)]
		public static extern void Line(int x1, int y1, int x2, int y2);

		[DllImport(B3DDllLink)]
		public static extern void Text(int x, int y, string str, bool centerX = false, bool centerY = false);

		[DllImport(B3DDllLink)]
		private static extern void CopyRect_internal(int srcX, int srcY, int width, int height, int destX, int destY, IntPtr srcBuffer, IntPtr destBuffer);

		public static void CopyRect(int srcX, int srcY, int width, int height, int destX, int destY, Canvas srcBuffer = null, Canvas destBuffer = null)
		{
			CopyRect_internal(srcX, srcY, width, height, destX, destY, srcBuffer != null ? srcBuffer.Pointer : IntPtr.Zero, destBuffer != null ? destBuffer.Pointer : IntPtr.Zero);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadFont_internal(string name, int height, bool bold, bool italic, bool underline);

		public static Font LoadFont(string name, int height = 12, bool bold = false, bool italic = false, bool underline = false)
		{
			Font ret = new Font(LoadFont_internal(name, height, bold, italic, underline));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeFont_internal(IntPtr font);

		public static void FreeFont(Font font)
		{
			FreeFont_internal(font.Pointer);
		}

		[DllImport(B3DDllLink)]
		public static extern int FontWidth();

		[DllImport(B3DDllLink)]
		public static extern int FontHeight();

		[DllImport(B3DDllLink)]
		public static extern int StringWidth(string str);

		[DllImport(B3DDllLink)]
		public static extern int StringHeight(string str);

		[DllImport(B3DDllLink)]
		private static extern IntPtr OpenMovie_internal(string file);

		public static Movie OpenMovie(string file)
		{
			Movie ret = new Movie(OpenMovie_internal(file));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern bool DrawMovie_internal(IntPtr movie, int x, int y, int width, int height);

		public static bool DrawMovie(Movie movie, int x = 0, int y = 0, int width = -1, int height = -1)
		{
			return DrawMovie_internal(movie.Pointer, x, y, width, height);
		}

		[DllImport(B3DDllLink)]
		private static extern int MovieWidth_internal(IntPtr movie);

		public static int MovieWidth(Movie movie)
		{
			return MovieWidth_internal(movie.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int MovieHeight_internal(IntPtr movie);

		public static int MovieHeight(Movie movie)
		{
			return MovieHeight_internal(movie.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern bool MoviePlaying_internal(IntPtr movie);

		public static bool MoviePlaying(Movie movie)
		{
			return MoviePlaying_internal(movie.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void CloseMovie_internal(IntPtr movie);

		public static void CloseMovie(Movie movie)
		{
			CloseMovie_internal(movie.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadImage_internal(string bmpFile);

		public static Image LoadImage(string bmpFile)
		{
			Image ret = new Image(LoadImage_internal(bmpFile));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadAnimImage_internal(string bmpFile, int cellwidth, int cellheight, int first, int count);

		public static Image LoadAnimImage(string bmpFile, int cellwidth, int cellheight, int first, int count)
		{
			Image ret = new Image(LoadAnimImage_internal(bmpFile, cellwidth, cellheight, first, count));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CopyImage_internal(IntPtr image);

		public static Image CopyImage(Image image)
		{
			Image ret = new Image(CopyImage_internal(image.Pointer));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateImage_internal(int width, int height, int frames);

		public static Image CreateImage(int width, int height, int frames = 1)
		{
			Image ret = new Image(CreateImage_internal(width, height, frames));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeImage_internal(IntPtr image);

		public static void FreeImage(Image image)
		{
			FreeImage_internal(image.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern bool SaveImage_internal(IntPtr image, string bmpFile, int frame);

		public static bool SaveImage(Image image, string bmpFile, int frame = 0)
		{
			return SaveImage_internal(image.Pointer, bmpFile, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void GrabImage_internal(IntPtr image, int x, int y, int frame);

		public static void GrabImage(Image image, int x, int y, int frame = 0)
		{
			GrabImage_internal(image.Pointer, x, y, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr ImageBuffer_internal(IntPtr image, int frame);

		public static Canvas ImageBuffer(Image image, int frame = 0)
		{
			Canvas ret = new Canvas(ImageBuffer_internal(image.Pointer, frame));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void DrawImage_internal(IntPtr image, int x, int y, int frame);

		public static void DrawImage(Image image, int x, int y, int frame = 0)
		{
			DrawImage_internal(image.Pointer, x, y, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void DrawBlock_internal(IntPtr image, int x, int y, int frame);

		public static void DrawBlock(Image image, int x, int y, int frame = 0)
		{
			DrawBlock_internal(image.Pointer, x, y, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void TileImage_internal(IntPtr image, int x, int y, int frame);

		public static void TileImage(Image image, int x = 0, int y = 0, int frame = 0)
		{
			TileImage_internal(image.Pointer, x, y, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void TileBlock_internal(IntPtr image, int x, int y, int frame);

		public static void TileBlock(Image image, int x = 0, int y = 0, int frame = 0)
		{
			TileBlock_internal(image.Pointer, x, y, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void DrawImageRect_internal(IntPtr image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame);

		public static void DrawImageRect(Image image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame = 0)
		{
			DrawImageRect_internal(image.Pointer, x, y, rectX, rectY, rectWidth, rectHeight, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void DrawBlockRect_internal(IntPtr image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame);

		public static void DrawBlockRect(Image image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame = 0)
		{
			DrawBlockRect_internal(image.Pointer, x, y, rectX, rectY, rectWidth, rectHeight, frame);
		}

		[DllImport(B3DDllLink)]
		private static extern void MaskImage_internal(IntPtr image, int red, int green, int blue);

		public static void MaskImage(Image image, int red, int green, int blue)
		{
			MaskImage_internal(image.Pointer, red, green, blue);
		}

		[DllImport(B3DDllLink)]
		private static extern void HandleImage_internal(IntPtr image, int x, int y);

		public static void HandleImage(Image image, int x, int y)
		{
			HandleImage_internal(image.Pointer, x, y);
		}

		[DllImport(B3DDllLink)]
		private static extern void MidHandle_internal(IntPtr image);

		public static void MidHandle(Image image)
		{
			MidHandle_internal(image.Pointer);
		}

		[DllImport(B3DDllLink)]
		public static extern void AutoMidHandle(bool enable);

		[DllImport(B3DDllLink)]
		private static extern int ImageWidth_internal(IntPtr image);

		public static int ImageWidth(Image image)
		{
			return ImageWidth_internal(image.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int ImageHeight_internal(IntPtr image);

		public static int ImageHeight(Image image)
		{
			return ImageHeight_internal(image.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int ImageXHandle_internal(IntPtr image);

		public static int ImageXHandle(Image image)
		{
			return ImageXHandle_internal(image.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int ImageYHandle_internal(IntPtr image);

		public static int ImageYHandle(Image image)
		{
			return ImageYHandle_internal(image.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void ScaleImage_internal(IntPtr image, float xscale, float yscale);

		public static void ScaleImage(Image image, float xscale, float yscale)
		{
			ScaleImage_internal(image.Pointer, xscale, yscale);
		}

		[DllImport(B3DDllLink)]
		private static extern void ResizeImage_internal(IntPtr image, float width, float height);

		public static void ResizeImage(Image image, float width, float height)
		{
			ResizeImage_internal(image.Pointer, width, height);
		}

		[DllImport(B3DDllLink)]
		private static extern void RotateImage_internal(IntPtr image, float angle);

		public static void RotateImage(Image image, float angle)
		{
			RotateImage_internal(image.Pointer, angle);
		}

		[DllImport(B3DDllLink)]
		private static extern void TFormImage_internal(IntPtr image, float a, float b, float c, float d);

		public static void TFormImage(Image image, float a, float b, float c, float d)
		{
			TFormImage_internal(image.Pointer, a, b, c, d);
		}

		[DllImport(B3DDllLink)]
		public static extern void TFormFilter(bool enable);

		[DllImport(B3DDllLink)]
		private static extern bool ImagesOverlap_internal(IntPtr image1, int x1, int y1, IntPtr image2, int x2, int y2);

		public static bool ImagesOverlap(Image image1, int x1, int y1, Image image2, int x2, int y2)
		{
			return ImagesOverlap_internal(image1.Pointer, x1, y1, image2.Pointer, x2, y2);
		}

		[DllImport(B3DDllLink)]
		private static extern bool ImagesCollide_internal(IntPtr image1, int x1, int y1, int frame1, IntPtr image2, int x2, int y2, int frame2);

		public static bool ImagesCollide(Image image1, int x1, int y1, int frame1, Image image2, int x2, int y2, int frame2)
		{
			return ImagesCollide_internal(image1.Pointer, x1, y1, frame1, image2.Pointer, x2, y2, frame2);
		}

		[DllImport(B3DDllLink)]
		public static extern bool RectsOverlap(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

		[DllImport(B3DDllLink)]
		private static extern bool ImageRectOverlap_internal(IntPtr image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight);

		public static bool ImageRectOverlap(Image image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight)
		{
			return ImageRectOverlap_internal(image.Pointer, x, y, rectX, rectY, rectWidth, rectHeight);
		}

		[DllImport(B3DDllLink)]
		private static extern bool ImageRectCollide_internal(IntPtr image, int x, int y, int frame, int rectX, int rectY, int rectWidth, int rectHeight);

		public static bool ImageRectCollide(Image image, int x, int y, int frame, int rectX, int rectY, int rectWidth, int rectHeight)
		{
			return ImageRectCollide_internal(image.Pointer, x, y, frame, rectX, rectY, rectWidth, rectHeight);
		}

		[DllImport(B3DDllLink)]
		public static extern void Write(string str);

		[DllImport(B3DDllLink)]
		public static extern void Print(string str = "");

		[DllImport(B3DDllLink)]
		private static extern void Input_internal(StringBuilder ret, int retLen, string prompt = "");

		public static string Input(string prompt = "")
		{
			StringBuilder sb = new StringBuilder(4096);
			Input_internal(sb, sb.Capacity, prompt);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern void Locate(int x, int y);

		[DllImport(B3DDllLink)]
		public static extern void ShowPointer();

		[DllImport(B3DDllLink)]
		public static extern void HidePointer();
	}
}
