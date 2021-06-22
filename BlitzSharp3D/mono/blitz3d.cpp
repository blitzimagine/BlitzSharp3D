#include "monoutil.h"
#include "../bbruntime/bbruntime.h"
#include "../bbruntime/bbblitz3d.h"

PUBLIC_METHOD void LoaderMatrix(const char* fileExt, float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz)
{
	BBStr* ext = toBBStr(fileExt);
	bbLoaderMatrix(ext, xx, xy, xz, yx, yy, yz, zx, zy, zz);
	freeBBStr(ext);
}

PUBLIC_METHOD void HWMultiTex(int enable)
{
	bbHWMultiTex(enable ? 1 : 0);
}

PUBLIC_METHOD int HWTexUnits()
{
	return bbHWTexUnits();
}

PUBLIC_METHOD int GfxDriverCaps3D()
{
	return bbGfxDriverCaps3D();
}

PUBLIC_METHOD void WBuffer(int enable)
{
	bbWBuffer(enable ? 1 : 0);
}

PUBLIC_METHOD void Dither(int enable)
{
	bbDither(enable ? 1 : 0);
}

PUBLIC_METHOD void AntiAlias(int enable)
{
	bbAntiAlias(enable ? 1 : 0);
}

PUBLIC_METHOD void WireFrame(int enable)
{
	bbWireFrame(enable ? 1 : 0);
}

PUBLIC_METHOD void AmbientLight(float red, float green, float blue)
{
	bbAmbientLight(red, green, blue);
}

PUBLIC_METHOD void ClearCollisions()
{
	bbClearCollisions();
}

PUBLIC_METHOD void Collisions(int srcType, int destType, int method, int response)
{
	bbCollisions(srcType, destType, method, response);
}

PUBLIC_METHOD void UpdateWorld(float elapsed)
{
	bbUpdateWorld(elapsed);
}

PUBLIC_METHOD void CaptureWorld()
{
	bbCaptureWorld();
}

PUBLIC_METHOD void RenderWorld(float tween)
{
	bbRenderWorld(tween);
}

PUBLIC_METHOD void ClearWorld(int entities, int brushes, int textures)
{
	bbClearWorld(entities ? 1 : 0, brushes ? 1 : 0, textures ? 1 : 0);
}

PUBLIC_METHOD int ActiveTextures()
{
	return bbActiveTextures();
}

PUBLIC_METHOD int TrisRendered()
{
	return bbTrisRendered();
}

PUBLIC_METHOD float Stats3D(int type)
{
	return bbStats3D(type);
}

PUBLIC_METHOD Texture* CreateTexture_internal(int width, int height, int flags, int frames)
{
	return bbCreateTexture(width, height, flags, frames);
}

PUBLIC_METHOD Texture* LoadTexture_internal(const char* file, int flags)
{
	BBStr* f = toBBStr(file);
	Texture* ret = bbLoadTexture(f, flags);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD Texture* LoadAnimTexture_internal(const char* file, int flags, int width, int height, int first, int count)
{
	BBStr* f = toBBStr(file);
	Texture* ret = bbLoadAnimTexture(f, flags, width, height, first, count);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void FreeTexture_internal(Texture* texture)
{
	bbFreeTexture(texture);
}

PUBLIC_METHOD void TextureBlend_internal(Texture* texture, int blend)
{
	bbTextureBlend(texture, blend);
}

PUBLIC_METHOD void TextureCoords_internal(Texture* texture, int coords)
{
	bbTextureCoords(texture, coords);
}

PUBLIC_METHOD void ScaleTexture_internal(Texture* texture, float uScale, float vScale)
{
	bbScaleTexture(texture, uScale, vScale);
}

PUBLIC_METHOD void RotateTexture_internal(Texture* texture, float angle)
{
	bbRotateTexture(texture, angle);
}

PUBLIC_METHOD void PositionTexture_internal(Texture* texture, float uOffset, float vOffset)
{
	bbPositionTexture(texture, uOffset, vOffset);
}

PUBLIC_METHOD int TextureWidth_internal(Texture* texture)
{
	return bbTextureWidth(texture);
}

PUBLIC_METHOD int TextureHeight_internal(Texture* texture)
{
	return bbTextureHeight(texture);
}

PUBLIC_METHOD void TextureName_internal(char* ret, int retLen, Texture* texture)
{
	strcpy_s(ret, retLen, toMonoStr(bbTextureName(texture)));
}

PUBLIC_METHOD void SetCubeFace_internal(Texture* texture, int face)
{
	bbSetCubeFace(texture, face);
}

PUBLIC_METHOD void SetCubeMode_internal(Texture* texture, int mode)
{
	bbSetCubeMode(texture, mode);
}

PUBLIC_METHOD gxCanvas* TextureBuffer_internal(Texture* texture, int frame)
{
	return bbTextureBuffer(texture, frame);
}

PUBLIC_METHOD void ClearTextureFilters()
{
	bbClearTextureFilters();
}

PUBLIC_METHOD void TextureFilter(const char* matchText, int textureFlags)
{
	BBStr* m = toBBStr(matchText);
	bbTextureFilter(m, textureFlags);
	freeBBStr(m);
}

PUBLIC_METHOD Brush* CreateBrush_internal(float red, float green, float blue)
{
	return bbCreateBrush(red, green, blue);
}

PUBLIC_METHOD Brush* LoadBrush_internal(const char* file, int textureFlags, float uScale, float vScale)
{
	BBStr* f = toBBStr(file);
	Brush* ret = bbLoadBrush(f, textureFlags, uScale, vScale);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void FreeBrush_internal(Brush* brush)
{
	bbFreeBrush(brush);
}

PUBLIC_METHOD void BrushColor_internal(Brush* brush, float red, float green, float blue)
{
	bbBrushColor(brush, red, green, blue);
}

PUBLIC_METHOD void BrushAlpha_internal(Brush* brush, float alpha)
{
	bbBrushAlpha(brush, alpha);
}

PUBLIC_METHOD void BrushShininess_internal(Brush* brush, float shininess)
{
	bbBrushShininess(brush, shininess);
}

PUBLIC_METHOD void BrushTexture_internal(Brush* brush, Texture* texture, int frame, int index)
{
	bbBrushTexture(brush, texture, frame, index);
}

PUBLIC_METHOD Texture* GetBrushTexture_internal(Brush* brush, int index)
{
	return bbGetBrushTexture(brush, index);
}

PUBLIC_METHOD void BrushBlend_internal(Brush* brush, int blend)
{
	bbBrushBlend(brush, blend);
}

PUBLIC_METHOD void BrushFX_internal(Brush* brush, int fx)
{
	bbBrushFX(brush, fx);
}

PUBLIC_METHOD Entity* LoadMesh_internal(const char* file, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadMesh(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD Entity* LoadAnimMesh_internal(const char* file, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadAnimMesh(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD int LoadAnimSeq_internal(Entity* entity, const char* file)
{
	BBStr* f = toBBStr(file);
	int ret = bbLoadAnimSeq((Object*)entity, f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD Entity* CreateMesh_internal(Entity* parent)
{
	return bbCreateMesh(parent);
}

PUBLIC_METHOD Entity* CreateCube_internal(Entity* parent)
{
	return bbCreateCube(parent);
}

PUBLIC_METHOD Entity* CreateSphere_internal(int segments, Entity* parent)
{
	return bbCreateSphere(segments, parent);
}

PUBLIC_METHOD Entity* CreateCylinder_internal(int segments, int solid, Entity* parent)
{
	return bbCreateCylinder(segments, solid ? 1 : 0, parent);
}

PUBLIC_METHOD Entity* CreateCone_internal(int segments, int solid, Entity* parent)
{
	return bbCreateCone(segments, solid ? 1 : 0, parent);
}

PUBLIC_METHOD Entity* CopyMesh_internal(Entity* mesh, Entity* parent)
{
	return bbCopyMesh((MeshModel*)mesh, parent);
}

PUBLIC_METHOD void ScaleMesh_internal(Entity* mesh, float xScale, float yScale, float zScale)
{
	bbScaleMesh((MeshModel*)mesh, xScale, yScale, zScale);
}

PUBLIC_METHOD void RotateMesh_internal(Entity* mesh, float pitch, float yaw, float roll)
{
	bbRotateMesh((MeshModel*)mesh, pitch, yaw, roll);
}

PUBLIC_METHOD void PositionMesh_internal(Entity* mesh, float x, float y, float z)
{
	bbPositionMesh((MeshModel*)mesh, x, y, z);
}

PUBLIC_METHOD void FitMesh_internal(Entity* mesh, float x, float y, float z, float width, float height, float depth, int uniform)
{
	bbFitMesh((MeshModel*)mesh, x, y, z, width, height, depth, uniform ? 1 : 0);
}

PUBLIC_METHOD void FlipMesh_internal(Entity* mesh)
{
	bbFlipMesh((MeshModel*)mesh);
}

PUBLIC_METHOD void PaintMesh_internal(Entity* mesh, Brush* brush)
{
	bbPaintMesh((MeshModel*)mesh, brush);
}

PUBLIC_METHOD void AddMesh_internal(Entity* srcMesh, Entity* destMesh)
{
	bbAddMesh((MeshModel*)srcMesh, (MeshModel*)destMesh);
}

PUBLIC_METHOD void UpdateNormals_internal(Entity* mesh)
{
	bbUpdateNormals((MeshModel*)mesh);
}

PUBLIC_METHOD void LightMesh_internal(Entity* mesh, float red, float green, float blue, float range, float x, float y, float z)
{
	bbLightMesh((MeshModel*)mesh, red, green, blue, range, x, y, z);
}

PUBLIC_METHOD float MeshWidth_internal(Entity* mesh)
{
	return bbMeshWidth((MeshModel*)mesh);
}

PUBLIC_METHOD float MeshHeight_internal(Entity* mesh)
{
	return bbMeshHeight((MeshModel*)mesh);
}

PUBLIC_METHOD float MeshDepth_internal(Entity* mesh)
{
	return bbMeshDepth((MeshModel*)mesh);
}

PUBLIC_METHOD int MeshesIntersect_internal(Entity* meshA, Entity* meshB)
{
	return bbMeshesIntersect((MeshModel*)meshA, (MeshModel*)meshB) != 0;
}

PUBLIC_METHOD int CountSurfaces_internal(Entity* mesh)
{
	return bbCountSurfaces((MeshModel*)mesh);
}

PUBLIC_METHOD Surface* GetSurface_internal(Entity* mesh, int surfaceIndex)
{
	return bbGetSurface((MeshModel*)mesh, surfaceIndex);
}

PUBLIC_METHOD void MeshCullBox_internal(Entity* mesh, float x, float y, float z, float width, float height, float depth)
{
	bbMeshCullBox((MeshModel*)mesh, x, y, z, width, height, depth);
}

PUBLIC_METHOD Surface* CreateSurface_internal(Entity* mesh, Brush* brush)
{
	return bbCreateSurface((MeshModel*)mesh, brush);
}

PUBLIC_METHOD Brush* GetSurfaceBrush_internal(Surface* surface)
{
	return bbGetSurfaceBrush(surface);
}

PUBLIC_METHOD Brush* GetEntityBrush_internal(Entity* entity)
{
	return bbGetEntityBrush((Model*)entity);
}

PUBLIC_METHOD Surface* FindSurface_internal(Entity* mesh, Brush* brush)
{
	return bbFindSurface((MeshModel*)mesh, brush);
}

PUBLIC_METHOD void ClearSurface_internal(Surface* surface, int clearVertices, int clearTriangles)
{
	bbClearSurface(surface, clearVertices ? 1 : 0, clearTriangles ? 1 : 0);
}

PUBLIC_METHOD void PaintSurface_internal(Surface* surface, Brush* brush)
{
	bbPaintSurface(surface, brush);
}

PUBLIC_METHOD int AddVertex_internal(Surface* surface, float x, float y, float z, float u, float v, float w)
{
	return bbAddVertex(surface, x, y, z, u, v, w);
}

PUBLIC_METHOD int AddTriangle_internal(Surface* surface, int v0, int v1, int v2)
{
	return bbAddTriangle(surface, v0, v1, v2);
}

PUBLIC_METHOD void VertexCoords_internal(Surface* surface, int index, float x, float y, float z)
{
	bbVertexCoords(surface, index, x, y, z);
}

PUBLIC_METHOD void VertexNormal_internal(Surface* surface, int index, float nx, float ny, float nz)
{
	bbVertexNormal(surface, index, nx, ny, nz);
}

PUBLIC_METHOD void VertexColor_internal(Surface* surface, int index, float red, float green, float blue, float alpha)
{
	bbVertexColor(surface, index, red, green, blue, alpha);
}

PUBLIC_METHOD void VertexTexCoords_internal(Surface* surface, int index, float u, float v, float w, int coordSet)
{
	bbVertexTexCoords(surface, index, u, v, w, coordSet);
}

PUBLIC_METHOD int CountVertices_internal(Surface* surface)
{
	return bbCountVertices(surface);
}

PUBLIC_METHOD int CountTriangles_internal(Surface* surface)
{
	return bbCountTriangles(surface);
}

PUBLIC_METHOD float VertexX_internal(Surface* surface, int index)
{
	return bbVertexX(surface, index);
}

PUBLIC_METHOD float VertexY_internal(Surface* surface, int index)
{
	return bbVertexY(surface, index);
}

PUBLIC_METHOD float VertexZ_internal(Surface* surface, int index)
{
	return bbVertexZ(surface, index);
}

PUBLIC_METHOD float VertexNX_internal(Surface* surface, int index)
{
	return bbVertexNX(surface, index);
}

PUBLIC_METHOD float VertexNY_internal(Surface* surface, int index)
{
	return bbVertexNY(surface, index);
}

PUBLIC_METHOD float VertexNZ_internal(Surface* surface, int index)
{
	return bbVertexNZ(surface, index);
}

PUBLIC_METHOD float VertexRed_internal(Surface* surface, int index)
{
	return bbVertexRed(surface, index);
}

PUBLIC_METHOD float VertexGreen_internal(Surface* surface, int index)
{
	return bbVertexGreen(surface, index);
}

PUBLIC_METHOD float VertexBlue_internal(Surface* surface, int index)
{
	return bbVertexBlue(surface, index);
}

PUBLIC_METHOD float VertexAlpha_internal(Surface* surface, int index)
{
	return bbVertexAlpha(surface, index);
}

PUBLIC_METHOD float VertexU_internal(Surface* surface, int index, int coordSet)
{
	return bbVertexU(surface, index, coordSet);
}

PUBLIC_METHOD float VertexV_internal(Surface* surface, int index, int coordSet)
{
	return bbVertexV(surface, index, coordSet);
}

PUBLIC_METHOD float VertexW_internal(Surface* surface, int index, int coordSet)
{
	return bbVertexW(surface, index, coordSet);
}

PUBLIC_METHOD int TriangleVertex_internal(Surface* surface, int index, int vertex)
{
	return bbTriangleVertex(surface, index, vertex);
}

PUBLIC_METHOD Entity* CreateCamera_internal(Entity* parent)
{
	return bbCreateCamera(parent);
}

PUBLIC_METHOD void CameraZoom_internal(Entity* camera, float zoom)
{
	bbCameraZoom((Camera*)camera, zoom);
}

PUBLIC_METHOD void CameraRange_internal(Entity* camera, float nr, float fr)
{
	bbCameraRange((Camera*)camera, nr, fr);
}

PUBLIC_METHOD void CameraClsColor_internal(Entity* camera, float red, float green, float blue)
{
	bbCameraClsColor((Camera*)camera, red, green, blue);
}

PUBLIC_METHOD void CameraClsMode_internal(Entity* camera, int color, int zBuffer)
{
	bbCameraClsMode((Camera*)camera, color ? 1 : 0, zBuffer ? 1 : 0);
}

PUBLIC_METHOD void CameraProjMode_internal(Entity* camera, int mode)
{
	bbCameraProjMode((Camera*)camera, mode);
}

PUBLIC_METHOD void CameraViewport_internal(Entity* camera, int x, int y, int width, int height)
{
	bbCameraViewport((Camera*)camera, x, y, width, height);
}

PUBLIC_METHOD void CameraFogColor_internal(Entity* camera, float red, float green, float blue)
{
	bbCameraFogColor((Camera*)camera, red, green, blue);
}

PUBLIC_METHOD void CameraFogRange_internal(Entity* camera, float nr, float fr)
{
	bbCameraFogRange((Camera*)camera, nr, fr);
}

PUBLIC_METHOD void CameraFogMode_internal(Entity* camera, int mode)
{
	bbCameraFogMode((Camera*)camera, mode);
}

PUBLIC_METHOD int CameraProject_internal(Entity* camera, float x, float y, float z)
{
	return bbCameraProject((Camera*)camera, x, y, z);
}

PUBLIC_METHOD float ProjectedX()
{
	return bbProjectedX();
}

PUBLIC_METHOD float ProjectedY()
{
	return bbProjectedY();
}

PUBLIC_METHOD float ProjectedZ()
{
	return bbProjectedZ();
}

PUBLIC_METHOD int EntityInView_internal(Entity* entity, Entity* camera)
{
	return bbEntityInView(entity, (Camera*)camera) != 0;
}

PUBLIC_METHOD int EntityVisible_internal(Entity* src, Entity* dest)
{
	return bbEntityVisible((Object*)src, (Object*)dest) != 0;
}

PUBLIC_METHOD Entity* EntityPick_internal(Entity* src, float range)
{
	return bbEntityPick((Object*)src, range);
}

PUBLIC_METHOD Entity* LinePick_internal(float x, float y, float z, float dx, float dy, float dz, float radius)
{
	return bbLinePick(x, y, z, dx, dy, dz, radius);
}

PUBLIC_METHOD Entity* CameraPick_internal(Entity* camera, float viewportX, float viewportY)
{
	return bbCameraPick((Camera*)camera, viewportX, viewportY);
}

PUBLIC_METHOD float PickedX()
{
	return bbPickedX();
}

PUBLIC_METHOD float PickedY()
{
	return bbPickedY();
}

PUBLIC_METHOD float PickedZ()
{
	return bbPickedZ();
}

PUBLIC_METHOD float PickedNX()
{
	return bbPickedNX();
}

PUBLIC_METHOD float PickedNY()
{
	return bbPickedNY();
}

PUBLIC_METHOD float PickedNZ()
{
	return bbPickedNZ();
}

PUBLIC_METHOD float PickedTime()
{
	return bbPickedTime();
}

PUBLIC_METHOD Entity* PickedEntity_internal()
{
	return bbPickedEntity();
}

PUBLIC_METHOD Surface* PickedSurface_internal()
{
	return (Surface*)bbPickedSurface();
}

PUBLIC_METHOD int PickedTriangle()
{
	return bbPickedTriangle();
}

PUBLIC_METHOD Entity* CreateLight_internal(int type, Entity* parent)
{
	return bbCreateLight(type, parent);
}

PUBLIC_METHOD void LightColor_internal(Entity* light, float red, float green, float blue)
{
	bbLightColor((Light*)light, red, green, blue);
}

PUBLIC_METHOD void LightRange_internal(Entity* light, float range)
{
	bbLightRange((Light*)light, range);
}

PUBLIC_METHOD void LightConeAngles_internal(Entity* light, float innerAngle, float outerAngle)
{
	bbLightConeAngles((Light*)light, innerAngle, outerAngle);
}

PUBLIC_METHOD Entity* CreatePivot_internal(Entity* parent)
{
	return bbCreatePivot(parent);
}

PUBLIC_METHOD Entity* CreateSprite_internal(Entity* parent)
{
	return bbCreateSprite(parent);
}

PUBLIC_METHOD Entity* LoadSprite_internal(const char* file, int textureFlags, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadSprite(f, textureFlags, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void RotateSprite_internal(Entity* sprite, float angle)
{
	bbRotateSprite((Sprite*)sprite, angle);
}

PUBLIC_METHOD void ScaleSprite_internal(Entity* sprite, float xScale, float yScale)
{
	bbScaleSprite((Sprite*)sprite, xScale, yScale);
}

PUBLIC_METHOD void HandleSprite_internal(Entity* sprite, float xHandle, float yHandle)
{
	bbHandleSprite((Sprite*)sprite, xHandle, yHandle);
}

PUBLIC_METHOD void SpriteViewMode_internal(Entity* sprite, int viewMode)
{
	bbSpriteViewMode((Sprite*)sprite, viewMode);
}

PUBLIC_METHOD Entity* LoadMD2_internal(const char* file, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadMD2(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void AnimateMD2_internal(Entity* md2, int mode, float speed, int firstFrame, int lastFrame, float transition)
{
	bbAnimateMD2((MD2Model*)md2, mode, speed, firstFrame, lastFrame, transition);
}

PUBLIC_METHOD float MD2AnimTime_internal(Entity* md2)
{
	return bbMD2AnimTime((MD2Model*)md2);
}

PUBLIC_METHOD int MD2AnimLength_internal(Entity* md2)
{
	return bbMD2AnimLength((MD2Model*)md2);
}

PUBLIC_METHOD int MD2Animating_internal(Entity* md2)
{
	return bbMD2Animating((MD2Model*)md2) != 0;
}

PUBLIC_METHOD Entity* LoadBSP_internal(const char* file, float gammaAdjust, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadBSP(f, gammaAdjust, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void BSPLighting_internal(Entity* bsp, int useLightmaps)
{
	bbBSPLighting((Q3BSPModel*)bsp, useLightmaps ? 1 : 0);
}

PUBLIC_METHOD void BSPAmbientLight_internal(Entity* bsp, float red, float green, float blue)
{
	bbBSPAmbientLight((Q3BSPModel*)bsp, red, green, blue);
}

PUBLIC_METHOD Entity* CreateMirror_internal(Entity* parent)
{
	return bbCreateMirror(parent);
}

PUBLIC_METHOD Entity* CreatePlane_internal(int segments, Entity* parent)
{
	return bbCreatePlane(segments, parent);
}

PUBLIC_METHOD Entity* CreateTerrain_internal(int gridSize, Entity* parent)
{
	return bbCreateTerrain(gridSize, parent);
}

PUBLIC_METHOD Entity* LoadTerrain_internal(const char* heightmapFile, Entity* parent)
{
	BBStr* f = toBBStr(heightmapFile);
	Entity* ret = bbLoadTerrain(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void TerrainDetail_internal(Entity* terrain, int detailLevel, int morph)
{
	bbTerrainDetail((Terrain*)terrain, detailLevel, morph ? 1 : 0);
}

PUBLIC_METHOD void TerrainShading_internal(Entity* terrain, int enable)
{
	bbTerrainShading((Terrain*)terrain, enable ? 1 : 0);
}

PUBLIC_METHOD float TerrainX_internal(Entity* terrain, float worldX, float worldY, float worldZ)
{
	return bbTerrainX((Terrain*)terrain, worldX, worldY, worldZ);
}

PUBLIC_METHOD float TerrainY_internal(Entity* terrain, float worldX, float worldY, float worldZ)
{
	return bbTerrainY((Terrain*)terrain, worldX, worldY, worldZ);
}

PUBLIC_METHOD float TerrainZ_internal(Entity* terrain, float worldX, float worldY, float worldZ)
{
	return bbTerrainZ((Terrain*)terrain, worldX, worldY, worldZ);
}

PUBLIC_METHOD int TerrainSize_internal(Entity* terrain)
{
	return bbTerrainSize((Terrain*)terrain);
}

PUBLIC_METHOD float TerrainHeight_internal(Entity* terrain, int terrainX, int terrainZ)
{
	return bbTerrainHeight((Terrain*)terrain, terrainX, terrainZ);
}

PUBLIC_METHOD void ModifyTerrain_internal(Entity* terrain, int terrainX, int terrainZ, float height, int realtime)
{
	bbModifyTerrain((Terrain*)terrain, terrainX, terrainZ, height, realtime ? 1 : 0);
}

PUBLIC_METHOD Entity* CreateListener_internal(Entity* parent, float rolloffFactor, float dopplerScale, float distanceScale)
{
	return bbCreateListener(parent, rolloffFactor, dopplerScale, distanceScale);
}

PUBLIC_METHOD gxChannel* EmitSound_internal(gxSound* sound, Entity* entity)
{
	return bbEmitSound(sound, (Object*)entity);
}

PUBLIC_METHOD Entity* CopyEntity_internal(Entity* entity, Entity* parent)
{
	return bbCopyEntity(entity, parent);
}

PUBLIC_METHOD float EntityX_internal(Entity* entity, int global)
{
	return bbEntityX(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityY_internal(Entity* entity, int global)
{
	return bbEntityY(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityZ_internal(Entity* entity, int global)
{
	return bbEntityZ(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityPitch_internal(Entity* entity, int global)
{
	return bbEntityPitch(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityYaw_internal(Entity* entity, int global)
{
	return bbEntityYaw(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityRoll_internal(Entity* entity, int global)
{
	return bbEntityRoll(entity, global ? 1 : 0);
}

PUBLIC_METHOD float GetMatElement_internal(Entity* entity, int row, int column)
{
	return bbGetMatElement(entity, row, column);
}

PUBLIC_METHOD void TFormPoint_internal(float x, float y, float z, Entity* src, Entity* dest)
{
	bbTFormPoint(x, y, z, src, dest);
}

PUBLIC_METHOD void TFormVector_internal(float x, float y, float z, Entity* src, Entity* dest)
{
	bbTFormVector(x, y, z, src, dest);
}

PUBLIC_METHOD void TFormNormal_internal(float x, float y, float z, Entity* src, Entity* dest)
{
	bbTFormNormal(x, y, z, src, dest);
}

PUBLIC_METHOD float TFormedX()
{
	return bbTFormedX();
}

PUBLIC_METHOD float TFormedY()
{
	return bbTFormedY();
}

PUBLIC_METHOD float TFormedZ()
{
	return bbTFormedZ();
}

PUBLIC_METHOD float VectorYaw(float x, float y, float z)
{
	return bbVectorYaw(x, y, z);
}

PUBLIC_METHOD float VectorPitch(float x, float y, float z)
{
	return bbVectorPitch(x, y, z);
}

PUBLIC_METHOD float DeltaPitch_internal(Entity* src, Entity* dest)
{
	return bbDeltaPitch(src, dest);
}

PUBLIC_METHOD float DeltaYaw_internal(Entity* src, Entity* dest)
{
	return bbDeltaYaw(src, dest);
}

PUBLIC_METHOD void ResetEntity_internal(Entity* entity)
{
	bbResetEntity((Object*)entity);
}

PUBLIC_METHOD void EntityType_internal(Entity* entity, int collisionType, int recursive)
{
	bbEntityType((Object*)entity, collisionType, recursive ? 1 : 0);
}

PUBLIC_METHOD void EntityPickMode_internal(Entity* entity, int mode, int obscurer)
{
	bbEntityPickMode((Object*)entity, mode, obscurer ? 1 : 0);
}

PUBLIC_METHOD Entity* GetParent_internal(Entity* entity)
{
	return bbGetParent(entity);
}

PUBLIC_METHOD int GetEntityType_internal(Entity* entity)
{
	return bbGetEntityType((Object*)entity);
}

PUBLIC_METHOD void EntityRadius_internal(Entity* entity, float xRadius, float yRadius)
{
	bbEntityRadius((Object*)entity, xRadius, yRadius);
}

PUBLIC_METHOD void EntityBox_internal(Entity* entity, float x, float y, float z, float width, float height, float depth)
{
	bbEntityBox((Object*)entity, x, y, z, width, height, depth);
}

PUBLIC_METHOD float EntityDistance_internal(Entity* src, Entity* dest)
{
	return bbEntityDistance(src, dest);
}

PUBLIC_METHOD Entity* EntityCollided_internal(Entity* entity, int type)
{
	return (Entity*)bbEntityCollided((Object*)entity, type);
}

PUBLIC_METHOD int CountCollisions_internal(Entity* entity)
{
	return bbCountCollisions((Object*)entity);
}

PUBLIC_METHOD float CollisionX_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionX((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionY_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionY((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionZ_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionZ((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionNX_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionNX((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionNY_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionNY((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionNZ_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionNZ((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionTime_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionTime((Object*)entity, collisionIndex);
}

PUBLIC_METHOD Entity* CollisionEntity_internal(Entity* entity, int collisionIndex)
{
	return (Entity*)bbCollisionEntity((Object*)entity, collisionIndex);
}

PUBLIC_METHOD Surface* CollisionSurface_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionSurface((Object*)entity, collisionIndex);
}

PUBLIC_METHOD int CollisionTriangle_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionTriangle((Object*)entity, collisionIndex);
}

PUBLIC_METHOD void MoveEntity_internal(Entity* entity, float x, float y, float z)
{
	bbMoveEntity(entity, x, y, z);
}

PUBLIC_METHOD void TurnEntity_internal(Entity* entity, float pitch, float yaw, float roll, int global)
{
	bbTurnEntity(entity, pitch, yaw, roll, global ? 1 : 0);
}

PUBLIC_METHOD void TranslateEntity_internal(Entity* entity, float x, float y, float z, int global)
{
	bbTranslateEntity(entity, x, y, z, global ? 1 : 0);
}

PUBLIC_METHOD void PositionEntity_internal(Entity* entity, float x, float y, float z, int global)
{
	bbPositionEntity(entity, x, y, z, global ? 1 : 0);
}

PUBLIC_METHOD void ScaleEntity_internal(Entity* entity, float xScale, float yScale, float zScale, int global)
{
	bbScaleEntity(entity, xScale, yScale, zScale, global ? 1 : 0);
}

PUBLIC_METHOD void RotateEntity_internal(Entity* entity, float pitch, float yaw, float roll, int global)
{
	bbRotateEntity(entity, pitch, yaw, roll, global ? 1 : 0);
}

PUBLIC_METHOD void PointEntity_internal(Entity* entity, Entity* target, float roll)
{
	bbPointEntity(entity, target, roll);
}

PUBLIC_METHOD void AlignToVector_internal(Entity* entity, float vectorX, float vectorY, float vectorZ, int axis, float rate)
{
	bbAlignToVector(entity, vectorX, vectorY, vectorZ, axis, rate);
}

PUBLIC_METHOD void SetAnimTime_internal(Entity* entity, float time, int animSeq)
{
	bbSetAnimTime((Object*)entity, time, animSeq);
}

PUBLIC_METHOD void Animate_internal(Entity* entity, int mode, float speed, int sequence, float transition)
{
	bbAnimate((Object*)entity, mode, speed, sequence, transition);
}

PUBLIC_METHOD void SetAnimKey_internal(Entity* entity, int frame, int posKey, int rotKey, int scaleKey)
{
	bbSetAnimKey((Object*)entity, frame, posKey ? 1 : 0, rotKey ? 1 : 0, scaleKey ? 1 : 0);
}

PUBLIC_METHOD int AddAnimSeq_internal(Entity* entity, int length)
{
	return bbAddAnimSeq((Object*)entity, length);
}

PUBLIC_METHOD int ExtractAnimSeq_internal(Entity* entity, int firstFrame, int lastFrame, int animSeq)
{
	return bbExtractAnimSeq((Object*)entity, firstFrame, lastFrame, animSeq);
}

PUBLIC_METHOD int AnimSeq_internal(Entity* entity)
{
	return bbAnimSeq((Object*)entity);
}

PUBLIC_METHOD float AnimTime_internal(Entity* entity)
{
	return bbAnimTime((Object*)entity);
}

PUBLIC_METHOD int AnimLength_internal(Entity* entity)
{
	return bbAnimLength((Object*)entity);
}

PUBLIC_METHOD int Animating_internal(Entity* entity)
{
	return bbAnimating((Object*)entity) != 0;
}

PUBLIC_METHOD void EntityParent_internal(Entity* entity, Entity* parent, int global)
{
	bbEntityParent(entity, parent, global ? 1 : 0);
}

PUBLIC_METHOD int CountChildren_internal(Entity* entity)
{
	return bbCountChildren(entity);
}

PUBLIC_METHOD Entity* GetChild_internal(Entity* entity, int index)
{
	return bbGetChild(entity, index);
}

PUBLIC_METHOD Entity* FindChild_internal(Entity* entity, const char* name)
{
	BBStr* n = toBBStr(name);
	Entity* ret = bbFindChild(entity, n);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void PaintEntity_internal(Entity* entity, Brush* brush)
{
	bbPaintEntity((Model*)entity, brush);
}

PUBLIC_METHOD void EntityColor_internal(Entity* entity, float red, float green, float blue)
{
	bbEntityColor((Model*)entity, red, green, blue);
}

PUBLIC_METHOD void EntityAlpha_internal(Entity* entity, float alpha)
{
	bbEntityAlpha((Model*)entity, alpha);
}

PUBLIC_METHOD void EntityShininess_internal(Entity* entity, float shininess)
{
	bbEntityShininess((Model*)entity, shininess);
}

PUBLIC_METHOD void EntityTexture_internal(Entity* entity, Texture* texture, int frame, int index)
{
	bbEntityTexture((Model*)entity, texture, frame, index);
}

PUBLIC_METHOD void EntityBlend_internal(Entity* entity, int blend)
{
	bbEntityBlend((Model*)entity, blend);
}

PUBLIC_METHOD void EntityFX_internal(Entity* entity, int fx)
{
	bbEntityFX((Model*)entity, fx);
}

PUBLIC_METHOD void EntityAutoFade_internal(Entity* entity, float nr, float fr)
{
	bbEntityAutoFade((Model*)entity, nr, fr);
}

PUBLIC_METHOD void EntityOrder_internal(Entity* entity, int order)
{
	bbEntityOrder((Object*)entity, order);
}

PUBLIC_METHOD void HideEntity_internal(Entity* entity)
{
	bbHideEntity(entity);
}

PUBLIC_METHOD void ShowEntity_internal(Entity* entity)
{
	bbShowEntity(entity);
}

PUBLIC_METHOD int EntityHidden_internal(Entity* entity)
{
	return bbEntityHidden(entity) != 0;
}

PUBLIC_METHOD void FreeEntity_internal(Entity* entity)
{
	bbFreeEntity(entity);
}

PUBLIC_METHOD void NameEntity_internal(Entity* entity, const char* name)
{
	BBStr* n = toBBStr(name);
	bbNameEntity(entity, n);
	freeBBStr(n);
}

PUBLIC_METHOD void EntityName_internal(char* ret, int retLen, Entity* entity)
{
	strcpy_s(ret, retLen, toMonoStr(bbEntityName(entity)));
}

PUBLIC_METHOD void EntityClass_internal(char* ret, int retLen, Entity* entity)
{
	strcpy_s(ret, retLen, toMonoStr(bbEntityClass(entity)));
}

PUBLIC_METHOD void GetBuildType_internal(char* ret, int retLen)
{
	strcpy_s(ret, retLen, toMonoStr(bbGetBuildType()));
}