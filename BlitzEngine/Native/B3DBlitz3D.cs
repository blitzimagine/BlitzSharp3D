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
		private static extern int LoadAnimSeq_internal(IntPtr entity, string file);

		public static int LoadAnimSeq(Entity entity, string file)
		{
			return LoadAnimSeq_internal(entity.Pointer, file);
		}

		

		

		

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
		private static extern IntPtr CreateLight_internal(int type, IntPtr parent);

		public static Entity CreateLight(int type = 1, Entity parent = null)
		{
			Entity ret = new Entity(CreateLight_internal(type, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void LightColor_internal(IntPtr light, float red, float green, float blue);

		public static void LightColor(Entity light, float red, float green, float blue)
		{
			LightColor_internal(light.Pointer, red, green, blue);
		}

		[DllImport(B3DDllLink)]
		private static extern void LightRange_internal(IntPtr light, float range);

		public static void LightRange(Entity light, float range)
		{
			LightRange_internal(light.Pointer, range);
		}

		[DllImport(B3DDllLink)]
		private static extern void LightConeAngles_internal(IntPtr light, float innerAngle, float outerAngle);

		public static void LightConeAngles(Entity light, float innerAngle, float outerAngle)
		{
			LightConeAngles_internal(light.Pointer, innerAngle, outerAngle);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreatePivot_internal(IntPtr parent);

		public static Entity CreatePivot(Entity parent = null)
		{
			Entity ret = new Entity(CreatePivot_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

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

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadMD2_internal(string file, IntPtr parent);

		public static Entity LoadMD2(string file, Entity parent = null)
		{
			Entity ret = new Entity(LoadMD2_internal(file, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void AnimateMD2_internal(IntPtr md2, int mode = 1, float speed = 1.0f, int firstFrame = 0, int lastFrame = 9999, float transition = 0.0f);

		public static void AnimateMD2(Entity md2, int mode, float speed, int firstFrame, int lastFrame, float transition)
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

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateMirror_internal(IntPtr parent);

		public static Entity CreateMirror(Entity parent = null)
		{
			Entity ret = new Entity(CreateMirror_internal(parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreatePlane_internal(int segments, IntPtr parent);

		public static Entity CreatePlane(int segments = 1, Entity parent = null)
		{
			Entity ret = new Entity(CreatePlane_internal(segments, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

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
		private static extern IntPtr CopyEntity_internal(IntPtr entity, IntPtr parent);

		public static Entity CopyEntity(Entity entity, Entity parent = null)
		{
			Entity ret = new Entity(CopyEntity_internal(entity.Pointer, parent != null ? parent.Pointer : IntPtr.Zero));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityX_internal(IntPtr entity, bool global);

		public static float EntityX(Entity entity, bool global = false)
		{
			return EntityX_internal(entity.Pointer, global);
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityY_internal(IntPtr entity, bool global);

		public static float EntityY(Entity entity, bool global = false)
		{
			return EntityY_internal(entity.Pointer, global);
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityZ_internal(IntPtr entity, bool global);

		public static float EntityZ(Entity entity, bool global = false)
		{
			return EntityZ_internal(entity.Pointer, global);
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityPitch_internal(IntPtr entity, bool global);

		public static float EntityPitch(Entity entity, bool global = false)
		{
			return EntityPitch_internal(entity.Pointer, global);
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityYaw_internal(IntPtr entity, bool global);

		public static float EntityYaw(Entity entity, bool global = false)
		{
			return EntityYaw_internal(entity.Pointer, global);
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityRoll_internal(IntPtr entity, bool global);

		public static float EntityRoll(Entity entity, bool global = false)
		{
			return EntityRoll_internal(entity.Pointer, global);
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

		[DllImport(B3DDllLink)]
		private static extern void ResetEntity_internal(IntPtr entity);

		public static void ResetEntity(Entity entity)
		{
			ResetEntity_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityType_internal(IntPtr entity, int collisionType, bool recursive);

		public static void EntityType(Entity entity, int collisionType, bool recursive = false)
		{
			EntityType_internal(entity.Pointer, collisionType, recursive);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityPickMode_internal(IntPtr entity, int mode, bool obscurer);

		public static void EntityPickMode(Entity entity, int mode, bool obscurer = true)
		{
			EntityPickMode_internal(entity.Pointer, mode, obscurer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr GetParent_internal(IntPtr entity);

		public static Entity GetParent(Entity entity)
		{
			Entity ret = new Entity(GetParent_internal(entity.Pointer));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern int GetEntityType_internal(IntPtr entity);

		public static int GetEntityType(Entity entity)
		{
			return GetEntityType_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityRadius_internal(IntPtr entity, float xRadius, float yRadius);

		public static void EntityRadius(Entity entity, float xRadius, float yRadius = 0.0f)
		{
			EntityRadius_internal(entity.Pointer, xRadius, yRadius);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityBox_internal(IntPtr entity, float x, float y, float z, float width, float height, float depth);

		public static void EntityBox(Entity entity, float x, float y, float z, float width, float height, float depth)
		{
			EntityBox_internal(entity.Pointer, x, y, z, width, height, depth);
		}

		[DllImport(B3DDllLink)]
		private static extern float EntityDistance_internal(IntPtr src, IntPtr dest);

		public static float EntityDistance(Entity src, Entity dest)
		{
			return EntityDistance_internal(src.Pointer, dest.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr EntityCollided_internal(IntPtr entity, int type);

		public static Entity EntityCollided(Entity entity, int type)
		{
			Entity ret = new Entity(EntityCollided_internal(entity.Pointer, type));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern int CountCollisions_internal(IntPtr entity);

		public static int CountCollisions(Entity entity)
		{
			return CountCollisions_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionX_internal(IntPtr entity, int collisionIndex);

		public static float CollisionX(Entity entity, int collisionIndex)
		{
			return CollisionX_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionY_internal(IntPtr entity, int collisionIndex);

		public static float CollisionY(Entity entity, int collisionIndex)
		{
			return CollisionY_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionZ_internal(IntPtr entity, int collisionIndex);

		public static float CollisionZ(Entity entity, int collisionIndex)
		{
			return CollisionZ_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionNX_internal(IntPtr entity, int collisionIndex);

		public static float CollisionNX(Entity entity, int collisionIndex)
		{
			return CollisionNX_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionNY_internal(IntPtr entity, int collisionIndex);

		public static float CollisionNY(Entity entity, int collisionIndex)
		{
			return CollisionNY_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionNZ_internal(IntPtr entity, int collisionIndex);

		public static float CollisionNZ(Entity entity, int collisionIndex)
		{
			return CollisionNZ_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern float CollisionTime_internal(IntPtr entity, int collisionIndex);

		public static float CollisionTime(Entity entity, int collisionIndex)
		{
			return CollisionTime_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CollisionEntity_internal(IntPtr entity, int collisionIndex);

		public static Entity CollisionEntity(Entity entity, int collisionIndex)
		{
			Entity ret = new Entity(CollisionEntity_internal(entity.Pointer, collisionIndex));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CollisionSurface_internal(IntPtr entity, int collisionIndex);

		public static Surface CollisionSurface(Entity entity, int collisionIndex)
		{
			Surface ret = new Surface(CollisionSurface_internal(entity.Pointer, collisionIndex));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern int CollisionTriangle_internal(IntPtr entity, int collisionIndex);

		public static int CollisionTriangle(Entity entity, int collisionIndex)
		{
			return CollisionTriangle_internal(entity.Pointer, collisionIndex);
		}

		[DllImport(B3DDllLink)]
		private static extern void MoveEntity_internal(IntPtr entity, float x, float y, float z);

		public static void MoveEntity(Entity entity, float x, float y, float z)
		{
			MoveEntity_internal(entity.Pointer, x, y, z);
		}

		[DllImport(B3DDllLink)]
		private static extern void TurnEntity_internal(IntPtr entity, float pitch, float yaw, float roll, bool global);

		public static void TurnEntity(Entity entity, float pitch, float yaw, float roll, bool global = false)
		{
			TurnEntity_internal(entity.Pointer, pitch, yaw, roll, global);
		}

		[DllImport(B3DDllLink)]
		private static extern void TranslateEntity_internal(IntPtr entity, float x, float y, float z, bool global);

		public static void TranslateEntity(Entity entity, float x, float y, float z, bool global = false)
		{
			if (entity == null)
				throw new Blitz3DException("Entity is null!");
			TranslateEntity_internal(entity.Pointer, x, y, z, global);
		}

		[DllImport(B3DDllLink)]
		private static extern void PositionEntity_internal(IntPtr entity, float x, float y, float z, bool global);

		public static void PositionEntity(Entity entity, float x, float y, float z, bool global = false)
		{
			if (entity == null)
				throw new Blitz3DException("Entity is null!");
			PositionEntity_internal(entity.Pointer, x, y, z, global);
		}

		[DllImport(B3DDllLink)]
		private static extern void ScaleEntity_internal(IntPtr entity, float xScale, float yScale, float zScale, bool global);

		public static void ScaleEntity(Entity entity, float xScale, float yScale, float zScale, bool global = false)
		{
			ScaleEntity_internal(entity.Pointer, xScale, yScale, zScale, global);
		}

		[DllImport(B3DDllLink)]
		private static extern void RotateEntity_internal(IntPtr entity, float pitch, float yaw, float roll, bool global);

		public static void RotateEntity(Entity entity, float pitch, float yaw, float roll, bool global = false)
		{
			RotateEntity_internal(entity.Pointer, pitch, yaw, roll, global);
		}

		[DllImport(B3DDllLink)]
		private static extern void PointEntity_internal(IntPtr entity, IntPtr target, float roll);

		public static void PointEntity(Entity entity, Entity target, float roll = 0.0f)
		{
			PointEntity_internal(entity.Pointer, target.Pointer, roll);
		}

		[DllImport(B3DDllLink)]
		private static extern void AlignToVector_internal(IntPtr entity, float vectorX, float vectorY, float vectorZ, int axis, float rate);

		public static void AlignToVector(Entity entity, float vectorX, float vectorY, float vectorZ, int axis, float rate = 1.0f)
		{
			AlignToVector_internal(entity.Pointer, vectorX, vectorY, vectorZ, axis, rate);
		}

		[DllImport(B3DDllLink)]
		private static extern void SetAnimTime_internal(IntPtr entity, float time, int animSeq);

		public static void SetAnimTime(Entity entity, float time, int animSeq = 0)
		{
			SetAnimTime_internal(entity.Pointer, time, animSeq);
		}

		[DllImport(B3DDllLink)]
		private static extern void Animate_internal(IntPtr entity, int mode, float speed, int sequence, float transition);

		public static void Animate(Entity entity, int mode = 1, float speed = 1.0f, int sequence = 0, float transition = 0.0f)
		{
			Animate_internal(entity.Pointer, mode, speed, sequence, transition);
		}

		[DllImport(B3DDllLink)]
		private static extern void SetAnimKey_internal(IntPtr entity, int frame, bool posKey, bool rotKey, bool scaleKey);

		public static void SetAnimKey(Entity entity, int frame, bool posKey = true, bool rotKey = true, bool scaleKey = true)
		{
			SetAnimKey_internal(entity.Pointer, frame, posKey, rotKey, scaleKey);
		}

		[DllImport(B3DDllLink)]
		private static extern int AddAnimSeq_internal(IntPtr entity, int length);

		public static int AddAnimSeq(Entity entity, int length)
		{
			return AddAnimSeq_internal(entity.Pointer, length);
		}

		[DllImport(B3DDllLink)]
		private static extern int ExtractAnimSeq_internal(IntPtr entity, int firstFrame, int lastFrame, int animSeq);

		public static int ExtractAnimSeq(Entity entity, int firstFrame, int lastFrame, int animSeq = 0)
		{
			return ExtractAnimSeq_internal(entity.Pointer, firstFrame, lastFrame, animSeq);
		}

		[DllImport(B3DDllLink)]
		private static extern int AnimSeq_internal(IntPtr entity);

		public static int AnimSeq(Entity entity)
		{
			return AnimSeq_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float AnimTime_internal(IntPtr entity);

		public static float AnimTime(Entity entity)
		{
			return AnimTime_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int AnimLength_internal(IntPtr entity);

		public static int AnimLength(Entity entity)
		{
			return AnimLength_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern bool Animating_internal(IntPtr entity);

		public static bool Animating(Entity entity)
		{
			return Animating_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityParent_internal(IntPtr entity, IntPtr parent, bool global);

		public static void EntityParent(Entity entity, Entity parent, bool global = true)
		{
			EntityParent_internal(entity.Pointer, parent.Pointer, global);
		}

		[DllImport(B3DDllLink)]
		private static extern int CountChildren_internal(IntPtr entity);

		public static int CountChildren(Entity entity)
		{
			return CountChildren_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr GetChild_internal(IntPtr entity, int index);

		public static Entity GetChild(Entity entity, int index)
		{
			Entity ret = new Entity(GetChild_internal(entity.Pointer, index));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr FindChild_internal(IntPtr entity, string name);

		public static Entity FindChild(Entity entity, string name)
		{
			Entity ret = new Entity(FindChild_internal(entity.Pointer, name));
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void PaintEntity_internal(IntPtr entity, IntPtr brush);

		public static void PaintEntity(Entity entity, Brush brush)
		{
			PaintEntity_internal(entity.Pointer, brush.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityColor_internal(IntPtr entity, float red, float green, float blue);

		public static void EntityColor(Entity entity, float red, float green, float blue)
		{
			EntityColor_internal(entity.Pointer, red, green, blue);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityAlpha_internal(IntPtr entity, float alpha);

		public static void EntityAlpha(Entity entity, float alpha)
		{
			EntityAlpha_internal(entity.Pointer, alpha);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityShininess_internal(IntPtr entity, float shininess);

		public static void EntityShininess(Entity entity, float shininess)
		{
			EntityShininess_internal(entity.Pointer, shininess);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityTexture_internal(IntPtr entity, IntPtr texture, int frame, int index);

		public static void EntityTexture(Entity entity, Texture texture, int frame = 0, int index = 0)
		{
			if (entity == null)
				throw new Blitz3DException("Entity is null!");
			if (texture == null)
				throw new Blitz3DException("Texture is null!");

			EntityTexture_internal(entity.Pointer, texture.Pointer, frame, index);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityBlend_internal(IntPtr entity, int blend);

		public static void EntityBlend(Entity entity, int blend)
		{
			EntityBlend_internal(entity.Pointer, blend);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityFX_internal(IntPtr entity, int fx);

		public static void EntityFX(Entity entity, int fx)
		{
			EntityFX_internal(entity.Pointer, fx);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityAutoFade_internal(IntPtr entity, float nr, float fr);

		public static void EntityAutoFade(Entity entity, float nr, float fr)
		{
			EntityAutoFade_internal(entity.Pointer, nr, fr);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityOrder_internal(IntPtr entity, int order);

		public static void EntityOrder(Entity entity, int order)
		{
			EntityOrder_internal(entity.Pointer, order);
		}

		[DllImport(B3DDllLink)]
		private static extern void HideEntity_internal(IntPtr entity);

		public static void HideEntity(Entity entity)
		{
			HideEntity_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void ShowEntity_internal(IntPtr entity);

		public static void ShowEntity(Entity entity)
		{
			ShowEntity_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern bool EntityHidden_internal(IntPtr entity);

		public static bool EntityHidden(Entity entity)
		{
			return EntityHidden_internal(entity.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeEntity_internal(IntPtr entity);

		public static void FreeEntity(Entity entity)
		{
			if (entity != null && entity.Pointer != IntPtr.Zero)
			{
				FreeEntity_internal(entity.Pointer);
				entity.Pointer = IntPtr.Zero;
			}
		}

		[DllImport(B3DDllLink)]
		private static extern void NameEntity_internal(IntPtr entity, string name);

		public static void NameEntity(Entity entity, string name)
		{
			NameEntity_internal(entity.Pointer, name);
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityName_internal(StringBuilder ret, int retLen, IntPtr entity);

		public static string EntityName(Entity entity)
		{
			StringBuilder sb = new StringBuilder(4096);
			EntityName_internal(sb, sb.Capacity, entity.Pointer);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		private static extern void EntityClass_internal(StringBuilder ret, int retLen, IntPtr entity);

		public static string EntityClass(Entity entity)
		{
			StringBuilder sb = new StringBuilder(4096);
			EntityClass_internal(sb, sb.Capacity, entity.Pointer);
			return sb.ToString();
		}
	}
}
