using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// -------
		// Blitz3D
		// -------

		[DllImport(B3DDllLink)]
		public static extern void LoaderMatrix(string fileExt, float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz);

		[DllImport(B3DDllLink)]
		public static extern void HwMultiTex(bool enable);

		[DllImport(B3DDllLink)]
		public static extern int HwTexUnits();

		[DllImport(B3DDllLink)]
		public static extern int GfxDriverCaps3D();

		[DllImport(B3DDllLink)]
		public static extern void WBuffer(bool enable);

		[DllImport(B3DDllLink)]
		public static extern void Dither(bool enable);

		[DllImport(B3DDllLink)]
		public static extern void AntiAlias(bool enable);

		[DllImport(B3DDllLink)]
		public static extern void WireFrame(bool enable);

		[DllImport(B3DDllLink)]
		public static extern void AmbientLight(float red, float green, float blue);

		[DllImport(B3DDllLink)]
		public static extern void ClearCollisions();

		[DllImport(B3DDllLink)]
		public static extern void Collisions(int srcType, int destType, int method, int response);

		[DllImport(B3DDllLink)]
		public static extern void UpdateWorld(float elapsed = 1.0f);

		[DllImport(B3DDllLink)]
		public static extern void CaptureWorld();

		[DllImport(B3DDllLink)]
		public static extern void RenderWorld(float tween = 1.0f);

		[DllImport(B3DDllLink)]
		public static extern void ClearWorld(bool entities = true, bool brushes = true, bool textures = true);

		[DllImport(B3DDllLink)]
		public static extern int ActiveTextures();

		[DllImport(B3DDllLink)]
		public static extern int TrisRendered();

		[DllImport(B3DDllLink)]
		public static extern float Stats3D(int type);

		

		[DllImport(B3DDllLink)]
		public static extern void ClearTextureFilters();

		[DllImport(B3DDllLink)]
		public static extern void TextureFilter(string matchText, int textureFlags = 0);

		

		

		[DllImport(B3DDllLink)]
		private static extern bool EntityVisible_internal(IntPtr src, IntPtr dest);

		public static bool EntityVisible(Entity src, Entity dest)
		{
			return EntityVisible_internal(src.Pointer, dest.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr EntityPick_internal(IntPtr src, float range);

		public static Entity EntityPick(Entity src, float range)
		{
			Entity ret = new Entity(EntityPick_internal(src.Pointer, range));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LinePick_internal(float x, float y, float z, float dx, float dy, float dz, float radius);

		public static Entity LinePick(float x, float y, float z, float dx, float dy, float dz, float radius = 0.0f)
		{
			Entity ret = new Entity(LinePick_internal(x, y, z, dx, dy, dz, radius));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CameraPick_internal(IntPtr camera, float viewportX, float viewportY);

		public static Entity CameraPick(Entity camera, float viewportX, float viewportY)
		{
			Entity ret = new Entity(CameraPick_internal(camera.Pointer, viewportX, viewportY));
			return ret;
		}

		[DllImport(B3DDllLink)]
		public static extern float PickedX();

		[DllImport(B3DDllLink)]
		public static extern float PickedY();

		[DllImport(B3DDllLink)]
		public static extern float PickedZ();

		[DllImport(B3DDllLink)]
		public static extern float PickedNX();

		[DllImport(B3DDllLink)]
		public static extern float PickedNY();

		[DllImport(B3DDllLink)]
		public static extern float PickedNZ();

		[DllImport(B3DDllLink)]
		public static extern float PickedTime();

		[DllImport(B3DDllLink)]
		private static extern IntPtr PickedEntity_internal();

		public static Entity PickedEntity()
		{
			Entity ret = new Entity(PickedEntity_internal());
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr PickedSurface_internal();

		public static Surface PickedSurface()
		{
			Surface ret = new Surface(PickedSurface_internal());
			return ret;
		}

		[DllImport(B3DDllLink)]
		public static extern int PickedTriangle();

		

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadBSP_internal(string file, float gammaAdjust, IntPtr parent);

		public static Entity LoadBSP(string file, float gammaAdjust = 0.0f, Entity parent = null)
		{
			Entity ret = new Entity(LoadBSP_internal(file, gammaAdjust, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void BspLighting_internal(IntPtr bsp, bool useLightmaps);

		public static void BspLighting(Entity bsp, bool useLightmaps)
		{
			BspLighting_internal(bsp.Pointer, useLightmaps);
		}

		[DllImport(B3DDllLink)]
		private static extern void BspAmbientLight_internal(IntPtr bsp, float red, float green, float blue);

		public static void BspAmbientLight(Entity bsp, float red, float green, float blue)
		{
			BspAmbientLight_internal(bsp.Pointer, red, green, blue);
		}

		#region Mirror
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateMirror_internal(IntPtr parent);

		public static Entity CreateMirror(Entity parent = null)
		{
			Entity ret = new Entity(CreateMirror_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}
		#endregion

		#region Terrain
		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateTerrain_internal(int gridSize, IntPtr parent);

		public static Entity CreateTerrain(int gridSize, Entity parent = null)
		{
			Entity ret = new Entity(CreateTerrain_internal(gridSize, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadTerrain_internal(string heightmapFile, IntPtr parent);

		public static Entity LoadTerrain(string heightmapFile, Entity parent = null)
		{
			Entity ret = new Entity(LoadTerrain_internal(heightmapFile, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void TerrainDetail_internal(IntPtr terrain, int detailLevel, bool morph);

		public static void TerrainDetail(Entity terrain, int detailLevel, bool morph = false)
		{
			TerrainDetail_internal(terrain.Pointer, detailLevel, morph);
		}

		[DllImport(B3DDllLink)]
		private static extern void TerrainShading_internal(IntPtr terrain, bool enable);

		public static void TerrainShading(Entity terrain, bool enable)
		{
			TerrainShading_internal(terrain.Pointer, enable);
		}

		[DllImport(B3DDllLink)]
		private static extern float TerrainX_internal(IntPtr terrain, float worldX, float worldY, float worldZ);

		public static float TerrainX(Entity terrain, float worldX, float worldY, float worldZ)
		{
			return TerrainX_internal(terrain.Pointer, worldX, worldY, worldZ);
		}

		[DllImport(B3DDllLink)]
		private static extern float TerrainY_internal(IntPtr terrain, float worldX, float worldY, float worldZ);

		public static float TerrainY(Entity terrain, float worldX, float worldY, float worldZ)
		{
			return TerrainY_internal(terrain.Pointer, worldX, worldY, worldZ);
		}

		[DllImport(B3DDllLink)]
		private static extern float TerrainZ_internal(IntPtr terrain, float worldX, float worldY, float worldZ);

		public static float TerrainZ(Entity terrain, float worldX, float worldY, float worldZ)
		{
			return TerrainZ_internal(terrain.Pointer, worldX, worldY, worldZ);
		}

		[DllImport(B3DDllLink)]
		private static extern int TerrainSize_internal(IntPtr terrain);

		public static int TerrainSize(Entity terrain)
		{
			return TerrainSize_internal(terrain.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float TerrainHeight_internal(IntPtr terrain, int terrainX, int terrainZ);

		public static float TerrainHeight(Entity terrain, int terrainX, int terrainZ)
		{
			return TerrainHeight_internal(terrain.Pointer, terrainX, terrainZ);
		}

		[DllImport(B3DDllLink)]
		private static extern void ModifyTerrain_internal(IntPtr terrain, int terrainX, int terrainZ, float height, bool realtime);

		public static void ModifyTerrain(Entity terrain, int terrainX, int terrainZ, float height, bool realtime = false)
		{
			ModifyTerrain_internal(terrain.Pointer, terrainX, terrainZ, height, realtime);
		}
		#endregion

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateListener_internal(IntPtr parent, float rolloffFactor, float dopplerScale, float distanceScale);

		public static Entity CreateListener(Entity parent, float rolloffFactor = 1.0f, float dopplerScale = 1.0f, float distanceScale = 1.0f)
		{
			Entity ret = new Entity(CreateListener_internal(parent.Pointer, rolloffFactor, dopplerScale, distanceScale));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr EmitSound_internal(IntPtr sound, IntPtr entity);

		public static Channel EmitSound(Sound sound, Entity entity)
		{
			Channel ret = new Channel(EmitSound_internal(sound.Pointer, entity.Pointer));
			return ret;
		}

		

		[DllImport(B3DDllLink)]
		private static extern float GetMatElement_internal(IntPtr entity, int row, int column);

		public static float GetMatElement(Entity entity, int row, int column)
		{
			return GetMatElement_internal(entity.Pointer, row, column);
		}

		[DllImport(B3DDllLink)]
		private static extern void TFormPoint_internal(float x, float y, float z, IntPtr src, IntPtr dest);

		public static void TFormPoint(float x, float y, float z, Entity src, Entity dest)
		{
			TFormPoint_internal(x, y, z, src.Pointer, dest.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void TFormVector_internal(float x, float y, float z, IntPtr src, IntPtr dest);

		public static void TFormVector(float x, float y, float z, Entity src, Entity dest)
		{
			TFormVector_internal(x, y, z, src, dest);
		}

		[DllImport(B3DDllLink)]
		private static extern void TFormNormal_internal(float x, float y, float z, IntPtr src, IntPtr dest);

		public static void TFormNormal(float x, float y, float z, Entity src, Entity dest)
		{
			TFormNormal_internal(x, y, z, src.Pointer, dest.Pointer);
		}

		[DllImport(B3DDllLink)]
		public static extern float TFormedX();

		[DllImport(B3DDllLink)]
		public static extern float TFormedY();

		[DllImport(B3DDllLink)]
		public static extern float TFormedZ();

		[DllImport(B3DDllLink)]
		public static extern float VectorYaw(float x, float y, float z);

		[DllImport(B3DDllLink)]
		public static extern float VectorPitch(float x, float y, float z);

		[DllImport(B3DDllLink)]
		private static extern float DeltaPitch_internal(IntPtr src, IntPtr dest);

		public static float DeltaPitch(Entity src, Entity dest)
		{
			return DeltaPitch_internal(src.Pointer, dest.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float DeltaYaw_internal(IntPtr src, IntPtr dest);

		public static float DeltaYaw(Entity src, Entity dest)
		{
			return DeltaYaw_internal(src.Pointer, dest.Pointer);
		}
	}
}
