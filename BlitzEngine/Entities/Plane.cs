using System;

namespace BlitzEngine.Entities
{
	public class Plane : Entity
	{
		public Plane(int segments = 1, Entity parent = null) : this(Blitz3D.CreatePlane(segments, parent)) { }

		protected Plane(IntPtr instance) : base(instance) { }
	}
}
