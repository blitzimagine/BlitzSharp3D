using System;

namespace BlitzEngine.Entities
{
	public class Light : Entity
	{
		public enum Type
		{
			Directional = 1,
			Point = 2,
			Spot = 3
		}

		public Light(Type type = Type.Directional, Entity parent = null) : base(Blitz3D.CreateLight((int)type, parent)) { }

		public void Color(float red, float green, float blue) => Blitz3D.LightColor(this, red, green, blue);

		protected Light(IntPtr instance) : base(instance) { }
	}
}
