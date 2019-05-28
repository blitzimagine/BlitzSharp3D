using System;

namespace BlitzEngine.Entities
{
	public class Pivot:Entity
	{
		public Pivot(Entity parent):base(Blitz3D.CreatePivot(parent)){}

		protected Pivot(IntPtr instance):base(instance){}
	}
}
