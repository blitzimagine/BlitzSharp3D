using System;
using System.Runtime.InteropServices;

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
	}
}
