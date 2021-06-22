using System;

namespace BlitzEngine.Entities
{
	public class MD2 : Entity
	{
		//public float AnimTime=>Blitz3D.MD2AnimTime(this);
		//public int AnimLength=>Blitz3D.MD2AnimLength(this);
		public bool Animating => Blitz3D.MD2Animating(this);

		public MD2(string file, Entity parent = null) : base(Blitz3D.LoadMD2(file, parent)) { }

		public void AnimateMD2(int mode, float speed, int firstFrame, int lastFrame, float transition) => Blitz3D.AnimateMD2(this, mode, speed, firstFrame, lastFrame, transition);

		protected MD2(IntPtr instance) : base(instance) { }
	}
}
