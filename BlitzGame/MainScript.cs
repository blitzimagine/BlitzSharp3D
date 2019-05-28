using System;
using BlitzEngine;

namespace BlitzGame
{
	public class MainScript
	{
		public static ConsoleLogger Logger = new ConsoleLogger("console.log", true);

		private bool _enableObjects;
		private bool _running;

		public MainScript()
		{
			_enableObjects = false;
			_running = false;
		}

		public void Start()
		{
			if (!Blitz3D.InitBlitz())
			{
				Logger.Error("Failed to initialize Blitz!");
				return;
			}

			Init();

			Run();
			
			Blitz3D.End();
		}

		public void Init()
		{
			Blitz3D.Graphics3D(640, 480);
			Blitz3D.AppTitle("Sample App");

			Entity camera = Blitz3D.CreateCamera();
			Blitz3D.PositionEntity(camera, 0, 0, -5);

			Entity light = Blitz3D.CreateLight();
			Blitz3D.PositionEntity(light, 255, 255, 255);

			Entity cube = Blitz3D.CreateCube();
		}

		public void Run()
		{
			_running = true;

			while (_running)
			{
				Update();
				Render();
			}
		}

		public void Stop()
		{
			_running = false;
		}

		public void Update()
		{
			if (Blitz3D.KeyHit(Keys.ESCAPE))
				Stop();

			if (Blitz3D.KeyHit(Keys.ENTER))
				_enableObjects = !_enableObjects;
		}

		public void Render()
		{
			Blitz3D.Cls();

			Blitz3D.UpdateWorld();
			Blitz3D.RenderWorld();

			Blitz3D.Color(255, 255, 255);
			Blitz3D.Text(0, 0, "Options:");
			Blitz3D.Text(40, 20, "Enable Objects:");

			if (_enableObjects)
			{
				Blitz3D.Color(0, 255, 0);
				Blitz3D.Text(170, 20, "ON");
			}
			else
			{
				Blitz3D.Color(255, 0, 0);
				Blitz3D.Text(170, 20, "OFF");
			}

			Blitz3D.Flip();
		}
	}
}