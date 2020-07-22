using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using BlitzEngine.Enums;
using Microsoft.Xna.Framework;

namespace BlitzEngine
{
	public class B3DGame:Game
	{
		public static B3DGame Instance{get;private set;}

		private GraphicsDeviceManager graphics;

		public Camera CurrentCamera;

		private B3DGame(int width, int height, BitDepth depth = BitDepth.Bits32, WindowMode mode = WindowMode.Windowed, int monitor = 0)
		{
			graphics = new GraphicsDeviceManager(this)
			{
				PreferredBackBufferWidth = width,
				PreferredBackBufferHeight = height,
				IsFullScreen = (mode == WindowMode.Fullscreen)
			};
		}

		protected override void Draw(GameTime gameTime)
		{
			base.Draw(gameTime);
			CurrentCamera.Draw(this);
		}

		protected override void Update(GameTime gameTime)
		{
			base.Update(gameTime);
			B3DInput.Update();
		}

		public bool HasFocus => IsActive || IsFocused();

		public static void Start(int width, int height, BitDepth depth = BitDepth.Bits32, WindowMode mode = WindowMode.Windowed, int monitor = 0)
		{
			if(Instance != null){throw new Exception();}

			Instance = new B3DGame(width, height, depth, mode, monitor);
			Task.Run(Instance.Run);
		}

		public void ShowPointer() => IsMouseVisible = true;
		public void HidePointer() => IsMouseVisible = false;

		[DllImport(Blitz3D.B3DDllLink)]public static extern bool IsFocused();
	}
}
