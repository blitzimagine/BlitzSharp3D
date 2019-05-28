using System;
using System.Runtime.InteropServices;

namespace BlitzEngine
{
	public class StaticMesh:Entity
	{
		public float Width=>Blitz3D.MeshWidth(this);
		public float Height=>Blitz3D.MeshHeight(this);
		public float Depth=>Blitz3D.MeshDepth(this);
		public int SurfaceCount=>Blitz3D.CountSurfaces(this);

		public StaticMesh(System.IntPtr pointer):base(pointer){}
		public StaticMesh(string file,Entity parent=null):base(Blitz3D.LoadMesh(file,parent)){}

		public StaticMesh(Entity parent=null):base(Blitz3D.CreateMesh(parent)){}
		
		public StaticMesh CopyMesh(StaticMesh parent=null)=>new StaticMesh(Blitz3D.CopyMesh(this,parent));
		
		public void ScaleMesh(float xScale, float yScale, float zScale)=>Blitz3D.ScaleMesh(this,xScale,yScale,zScale);
		public void RotateMesh(float pitch, float yaw, float roll)=>Blitz3D.RotateMesh(this,pitch,yaw,roll);
		public void PositionMesh(float x, float y, float z)=>Blitz3D.PositionMesh(this,x,y,z);
		public void FitMesh(float x, float y, float z, float width, float height, float depth, bool uniform = false)=>Blitz3D.FitMesh(this,x,y,z,width,height,depth,uniform);
		public void FlipMesh()=>Blitz3D.FlipMesh(this);
		public void PaintMesh(Brush brush)=>Blitz3D.PaintMesh(this,brush);
		public void Add(StaticMesh src)=>Blitz3D.AddMesh(src,this);
		public void UpdateNormals()=>Blitz3D.UpdateNormals(this);
		public void Light(float red, float green, float blue, float range = 0, float x = 0, float y = 0, float z = 0)=>Blitz3D.LightMesh(this,red,green,blue,range,x,y,z);
		
		public bool MeshIntersects(StaticMesh that)=>Blitz3D.MeshesIntersect(this,that);
		public Surface GetSurface(int surfaceIndex)=>Blitz3D.GetSurface(this,surfaceIndex);
		public void CullBox(float x, float y, float z, float width, float height, float depth)=>Blitz3D.MeshCullBox(this,x,y,z,width,height,depth);
		public Surface FindSurface(Brush brush)=>Blitz3D.FindSurface(this,brush);
	}
	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadMesh_internal(string file, IntPtr parent);

		public static Entity LoadMesh(string file, Entity parent = null)
		{
			Entity ret = new Entity(LoadMesh_internal(file, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateMesh_internal(IntPtr parent);

		public static Entity CreateMesh(Entity parent = null)
		{
			Entity ret = new Entity(CreateMesh_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CopyMesh_internal(IntPtr mesh, IntPtr parent);

		public static Entity CopyMesh(Entity mesh, Entity parent = null)
		{
			Entity ret = new Entity(CopyMesh_internal(mesh.Pointer, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void ScaleMesh_internal(IntPtr mesh, float xScale, float yScale, float zScale);

		public static void ScaleMesh(Entity mesh, float xScale, float yScale, float zScale)
		{
			ScaleMesh_internal(mesh.Pointer, xScale, yScale, zScale);
		}

		[DllImport(B3DDllLink)]
		private static extern void RotateMesh_internal(IntPtr mesh, float pitch, float yaw, float roll);

		public static void RotateMesh(Entity mesh, float pitch, float yaw, float roll)
		{
			RotateMesh_internal(mesh.Pointer, pitch, yaw, roll);
		}

		[DllImport(B3DDllLink)]
		private static extern void PositionMesh_internal(IntPtr mesh, float x, float y, float z);

		public static void PositionMesh(Entity mesh, float x, float y, float z)
		{
			PositionMesh_internal(mesh.Pointer, x, y, z);
		}

		[DllImport(B3DDllLink)]
		private static extern void FitMesh_internal(IntPtr mesh, float x, float y, float z, float width, float height, float depth, bool uniform);

		public static void FitMesh(Entity mesh, float x, float y, float z, float width, float height, float depth, bool uniform = false)
		{
			FitMesh_internal(mesh.Pointer, x, y, z, width, height, depth, uniform);
		}

		[DllImport(B3DDllLink)]
		private static extern void FlipMesh_internal(IntPtr mesh);

		public static void FlipMesh(Entity mesh)
		{
			FlipMesh_internal(mesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void PaintMesh_internal(IntPtr mesh, IntPtr brush);

		public static void PaintMesh(Entity mesh, Brush brush)
		{
			PaintMesh_internal(mesh.Pointer, brush.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void AddMesh_internal(IntPtr srcMesh, IntPtr destMesh);

		public static void AddMesh(Entity srcMesh, Entity destMesh)
		{
			AddMesh_internal(srcMesh.Pointer, destMesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void UpdateNormals_internal(IntPtr mesh);

		public static void UpdateNormals(Entity mesh)
		{
			UpdateNormals_internal(mesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void LightMesh_internal(IntPtr mesh, float red, float green, float blue, float range, float x, float y, float z);

		public static void LightMesh(Entity mesh, float red, float green, float blue, float range = 0.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f)
		{
			LightMesh_internal(mesh.Pointer, red, green, blue, range, x, y, z);
		}

		[DllImport(B3DDllLink)]
		private static extern float MeshWidth_internal(IntPtr mesh);

		public static float MeshWidth(Entity mesh)
		{
			return MeshWidth_internal(mesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float MeshHeight_internal(IntPtr mesh);

		public static float MeshHeight(Entity mesh)
		{
			return MeshHeight_internal(mesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float MeshDepth_internal(IntPtr mesh);

		public static float MeshDepth(Entity mesh)
		{
			return MeshDepth_internal(mesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern bool MeshesIntersect_internal(IntPtr meshA, IntPtr meshB);

		public static bool MeshesIntersect(Entity meshA, Entity meshB)
		{
			return MeshesIntersect_internal(meshA.Pointer, meshB.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int CountSurfaces_internal(IntPtr mesh);

		public static int CountSurfaces(Entity mesh)
		{
			return CountSurfaces_internal(mesh.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr GetSurface_internal(IntPtr mesh, int surfaceIndex);

		public static Surface GetSurface(Entity mesh, int surfaceIndex)
		{
			Surface ret = new Surface(GetSurface_internal(mesh.Pointer, surfaceIndex));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void MeshCullBox_internal(IntPtr mesh, float x, float y, float z, float width, float height, float depth);

		public static void MeshCullBox(Entity mesh, float x, float y, float z, float width, float height, float depth)
		{
			MeshCullBox_internal(mesh.Pointer, x, y, z, width, height, depth);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateSurface_internal(IntPtr mesh, IntPtr brush);

		public static Surface CreateSurface(Entity mesh, Brush brush = null)
		{
			Surface ret = new Surface(CreateSurface_internal(mesh.Pointer, brush != null ? brush.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr FindSurface_internal(IntPtr mesh, IntPtr brush);

		public static Surface FindSurface(Entity mesh, Brush brush)
		{
			Surface ret = new Surface(FindSurface_internal(mesh.Pointer, brush.Pointer));
			return ret;
		}
	}
}
