using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BlitzEngine;

namespace BlitzGame
{
	public static class Program
	{
		public static void Main(string[] args)
		{
			try
			{
				new MainScript().Start();
			}
			catch (Exception e)
			{
				string title = "Error";
				if (e is Blitz3DException bex)
					title = (bex.RuntimeError ? "Runtime" : "Debug") + " Error";
				MessageBox.Show(e.Message + "\n\n" + e.StackTrace, title, MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
	}
}
