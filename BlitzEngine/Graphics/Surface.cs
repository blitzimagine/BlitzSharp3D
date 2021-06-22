using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class Surface : BBPointer
	{
		//public Brush Brush=>Blitz3D.GetSurfaceBrush(this);
		//public int VerticeCount=>Blitz3D.CountVertices(this);
		//public int TriangleCount=>Blitz3D.CountTriangles(this);

		public Surface(IntPtr pointer) : base(pointer) { }

		public Surface(StaticMesh mesh, Brush brush = null) : this(Blitz3D.CreateSurface(mesh, brush)) { }

		//public void Clear(bool clearVertices = true, bool clearTriangles = true)=>Blitz3D.ClearSurface(this,clearVertices,clearTriangles);
		//public void Paint(Brush brush)=>Blitz3D.PaintSurface(this,brush);
		public int AddVertex(float x, float y, float z, float u = 0, float v = 0, float w = 1) => Blitz3D.AddVertex(this, x, y, z, u, v, w);
		public int AddTriangle(int v0, int v1, int v2) => Blitz3D.AddTriangle(this, v0, v1, v2);
		//public void VertexCoords(int index,float x,float y,float z)=>Blitz3D.VertexCoords(this,index,x,y,z);
		//public void VertexNormal(int index,float nx,float ny,float nz)=>Blitz3D.VertexNormal(this,index,nx,ny,nz);
		//public void VertexColor(int index,float red,float green,float blue,float alpha = 1)=>Blitz3D.VertexColor(this,index,red,green,blue,alpha);
		//public void VertexTexCoords(int index, float u, float v, float w = 1.0f, int coordSet = 0)=>Blitz3D.VertexTexCoords(this,index,u,v,w,coordSet);
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr GetSurfaceBrush_internal(IntPtr surface);

		public static Brush GetSurfaceBrush(Surface surface)
		{
			Brush ret = new Brush(GetSurfaceBrush_internal(surface.Pointer));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void ClearSurface_internal(IntPtr surface, bool clearVertices, bool clearTriangles);

		public static void ClearSurface(Surface surface, bool clearVertices = true, bool clearTriangles = true)
		{
			ClearSurface_internal(surface.Pointer, clearVertices, clearTriangles);
		}

		[DllImport(B3DDllLink)]
		private static extern void PaintSurface_internal(IntPtr surface, IntPtr brush);

		public static void PaintSurface(Surface surface, Brush brush)
		{
			PaintSurface_internal(surface.Pointer, brush.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int AddVertex_internal(IntPtr surface, float x, float y, float z, float u, float v, float w);

		public static int AddVertex(Surface surface, float x, float y, float z, float u = 0.0f, float v = 0.0f, float w = 1.0f)
		{
			return AddVertex_internal(surface.Pointer, x, y, z, u, v, w);
		}

		[DllImport(B3DDllLink)]
		private static extern int AddTriangle_internal(IntPtr surface, int v0, int v1, int v2);

		public static int AddTriangle(Surface surface, int v0, int v1, int v2)
		{
			return AddTriangle_internal(surface.Pointer, v0, v1, v2);
		}

		[DllImport(B3DDllLink)]
		private static extern void VertexCoords_internal(IntPtr surface, int index, float x, float y, float z);

		public static void VertexCoords(Surface surface, int index, float x, float y, float z)
		{
			VertexCoords_internal(surface.Pointer, index, x, y, z);
		}

		[DllImport(B3DDllLink)]
		private static extern void VertexNormal_internal(IntPtr surface, int index, float nx, float ny, float nz);

		public static void VertexNormal(Surface surface, int index, float nx, float ny, float nz)
		{
			VertexNormal_internal(surface.Pointer, index, nx, ny, nz);
		}

		[DllImport(B3DDllLink)]
		private static extern void VertexColor_internal(IntPtr surface, int index, float red, float green, float blue, float alpha);

		public static void VertexColor(Surface surface, int index, float red, float green, float blue, float alpha = 1.0f)
		{
			VertexColor_internal(surface.Pointer, index, red, green, blue, alpha);
		}

		[DllImport(B3DDllLink)]
		private static extern void VertexTexCoords_internal(IntPtr surface, int index, float u, float v, float w, int coordSet);

		public static void VertexTexCoords(Surface surface, int index, float u, float v, float w = 1.0f, int coordSet = 0)
		{
			VertexTexCoords_internal(surface.Pointer, index, u, v, w, coordSet);
		}

		[DllImport(B3DDllLink)]
		private static extern int CountVertices_internal(IntPtr surface);

		public static int CountVertices(Surface surface)
		{
			return CountVertices_internal(surface.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int CountTriangles_internal(IntPtr surface);

		public static int CountTriangles(Surface surface)
		{
			return CountTriangles_internal(surface.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexX_internal(IntPtr surface, int index);

		public static float VertexX(Surface surface, int index)
		{
			return VertexX_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexY_internal(IntPtr surface, int index);

		public static float VertexY(Surface surface, int index)
		{
			return VertexY_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexZ_internal(IntPtr surface, int index);

		public static float VertexZ(Surface surface, int index)
		{
			return VertexZ_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexNX_internal(IntPtr surface, int index);

		public static float VertexNX(Surface surface, int index)
		{
			return VertexNX_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexNY_internal(IntPtr surface, int index);

		public static float VertexNY(Surface surface, int index)
		{
			return VertexNY_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexNZ_internal(IntPtr surface, int index);

		public static float VertexNZ(Surface surface, int index)
		{
			return VertexNZ_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexRed_internal(IntPtr surface, int index);

		public static float VertexRed(Surface surface, int index)
		{
			return VertexRed_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexGreen_internal(IntPtr surface, int index);

		public static float VertexGreen(Surface surface, int index)
		{
			return VertexGreen_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexBlue_internal(IntPtr surface, int index);

		public static float VertexBlue(Surface surface, int index)
		{
			return VertexBlue_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexAlpha_internal(IntPtr surface, int index);

		public static float VertexAlpha(Surface surface, int index)
		{
			return VertexAlpha_internal(surface.Pointer, index);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexU_internal(IntPtr surface, int index, int coordSet);

		public static float VertexU(Surface surface, int index, int coordSet = 0)
		{
			return VertexU_internal(surface.Pointer, index, coordSet);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexV_internal(IntPtr surface, int index, int coordSet);

		public static float VertexV(Surface surface, int index, int coordSet = 0)
		{
			return VertexV_internal(surface.Pointer, index, coordSet);
		}

		[DllImport(B3DDllLink)]
		private static extern float VertexW_internal(IntPtr surface, int index, int coordSet);

		public static float VertexW(Surface surface, int index, int coordSet = 0)
		{
			return VertexW_internal(surface.Pointer, index, coordSet);
		}

		[DllImport(B3DDllLink)]
		private static extern int TriangleVertex_internal(IntPtr surface, int index, int vertex);

		public static int TriangleVertex(Surface surface, int index, int vertex)
		{
			return TriangleVertex_internal(surface.Pointer, index, vertex);
		}
	}
}
