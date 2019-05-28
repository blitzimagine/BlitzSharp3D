using System;

namespace BlitzEngine.Entities
{
	public class Sprite:Entity
	{
		public Sprite(Entity parent=null):base(Blitz3D.CreateSprite(parent)){}

		public void RotateSprite(float angle)=>Blitz3D.RotateSprite(this,angle);
		public void ScaleSprite(float xScale, float yScale)=>Blitz3D.ScaleSprite(this,xScale,yScale);

		protected Sprite(IntPtr instance):base(instance){}
	}
}
