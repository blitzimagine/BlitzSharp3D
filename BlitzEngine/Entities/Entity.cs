using System;
using System.Runtime.InteropServices;
using System.Text;
using Microsoft.Xna.Framework;

namespace BlitzEngine
{
	public /*abstract*/ class Entity:BBPointer
	{
		public Vector3 Position
		{
			get
			{
				return new Vector3(Blitz3D.EntityX(this), Blitz3D.EntityY(this), Blitz3D.EntityZ(this));
			}
			set
			{
				Blitz3D.PositionEntity(this,value.X,value.Y,value.Z);
			}
		}

		public Vector3 Rotation
		{
			get
			{
				return new Vector3(Blitz3D.EntityPitch(this), Blitz3D.EntityYaw(this), Blitz3D.EntityRoll(this));
			}
			set
			{
				Blitz3D.RotateEntity(this,value.X,value.Y,value.Z);
			}
		}

		public Brush Brush=>Blitz3D.GetEntityBrush(this);

		public Entity(IntPtr pointer):base(pointer){}

		public Entity Clone(Entity parent=null)=>Blitz3D.CopyEntity(this,parent);
		public float Distance(Entity that)=>Blitz3D.EntityDistance(this,that);

		public void Move(float x,float y,float z)=>Blitz3D.MoveEntity(this,x,y,z);
		public void Turn(float pitch, float yaw, float roll, bool global = false)=>Blitz3D.TurnEntity(this,pitch,yaw,roll,global);
		public void Translate(float x,float y,float z,bool global=false)=>Blitz3D.TranslateEntity(this,x,y,z,global);
		public void SetScale(float xScale, float yScale, float zScale, bool global = false)=>Blitz3D.ScaleEntity(this,xScale,yScale,zScale,global);
		public void SetColor(float red, float green, float blue)=>Blitz3D.EntityColor(this,red,green,blue);
		public void SetAlpha(float alpha)=>Blitz3D.EntityAlpha(this,alpha);
		public void SetTexture(Texture texture, int frame = 0, int index = 0)=>Blitz3D.EntityTexture(this,texture,frame,index);
		public void FX(int fx)=>Blitz3D.EntityFX(this,fx);
		public void Order(int order)=>Blitz3D.EntityOrder(this,order);
		public bool Hidden
		{
			get=>Blitz3D.EntityHidden(this);
			set
			{
				if(value)
				{
					Blitz3D.HideEntity(this);
				}
				else
				{
					Blitz3D.ShowEntity(this);
				}
			}
		}
		public void Free()=>Blitz3D.FreeEntity(this);
	}

	public static partial class Blitz3D
	{
		[DllImport(B3DDllLink)]
		private static extern IntPtr GetEntityBrush_internal(IntPtr entity);

		public static Brush GetEntityBrush(Entity entity)
		{
			Brush ret = new Brush(GetEntityBrush_internal(entity.Pointer));
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

		#region Animation
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
		private static extern int LoadAnimSeq_internal(IntPtr entity, string file);

		public static int LoadAnimSeq(Entity entity, string file)
		{
			return LoadAnimSeq_internal(entity.Pointer, file);
		}
		#endregion
	}
}
