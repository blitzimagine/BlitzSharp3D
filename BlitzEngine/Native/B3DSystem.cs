using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using BlitzEngine.Enums;

namespace BlitzEngine
{
    public static partial class Blitz3D
	{
#if DEBUG_ENGINE
		internal const string B3DDllLink = "BlitzSharp3D_DEBUG.dll";
#else
		internal const string B3DDllLink = "BlitzSharp3D.dll";
#endif

		// -------
		// System
		// -------

		[DllImport(B3DDllLink, EntryPoint = "InitBlitz")]private static extern bool InitBlitz_internal();
		public static bool InitBlitz()
        {
            return InitBlitz_internal();
        }

		[DllImport(B3DDllLink)]
		public static extern bool CloseBlitz();
        
        [DllImport(B3DDllLink)]
        public static extern void Restart();

        [DllImport(B3DDllLink)]
        public static extern void End();

        [DllImport(B3DDllLink)]
        public static extern void AppTitle(string title, string closePrompt = "");
        
        [DllImport(B3DDllLink)]
        public static extern void Stop();

        [DllImport(B3DDllLink)]
        public static extern void RuntimeError(string message);

        [DllImport(B3DDllLink)]
        public static extern int ExecFile(string command);

        [DllImport(B3DDllLink)]
        public static extern void Delay(int millisecs);

        [DllImport(B3DDllLink)]
        public static extern int MilliSecs();

        [DllImport(B3DDllLink)]
        private static extern void CommandLine_internal(StringBuilder ret, int retLen);

        public static string CommandLine()
        {
			StringBuilder sb = new StringBuilder(4096);
			CommandLine_internal(sb, sb.Capacity);
			return sb.ToString();
        }

        [DllImport(B3DDllLink)]
        public static extern void SystemProperty_internal(StringBuilder ret, int retLen, string property);

        public static string SystemProperty(string property)
        {
	        StringBuilder sb = new StringBuilder(4096);
	        SystemProperty_internal(sb, sb.Capacity, property);
	        return sb.ToString();
        }

		[DllImport(B3DDllLink)]
        public static extern void GetEnv_internal(StringBuilder ret, int retLen, string var);

        public static string GetEnv(string var)
        {
	        StringBuilder sb = new StringBuilder(4096);
	        GetEnv_internal(sb, sb.Capacity, var);
	        return sb.ToString();
        }

		[DllImport(B3DDllLink)]
        public static extern void SetEnv(string var, string value);

        [DllImport(B3DDllLink)]
        private static extern IntPtr CreateTimer_internal(int hertz);

        public static Timer CreateTimer(int hertz)
        {
            IntPtr pointer = CreateTimer_internal(hertz);
            Timer timer = new Timer(pointer);
            return timer;
        }

        [DllImport(B3DDllLink)]
        private static extern int WaitTimer_internal(IntPtr timer);

        public static int WaitTimer(Timer timer)
        {
            return WaitTimer_internal(timer.Pointer);
        }

        [DllImport(B3DDllLink)]
        private static extern void FreeTimer_internal(IntPtr timer);

        public static void FreeTimer(Timer timer)
        {
            FreeTimer_internal(timer.Pointer);
        }

        [DllImport(B3DDllLink)]
        public static extern void DebugLog(string text);

        [DllImport(B3DDllLink)]
        private static extern void GetBuildType_internal(StringBuilder ret, int retLen);

        public static BuildType GetBuildType()
        {
	        StringBuilder sb = new StringBuilder(4096);
	        GetBuildType_internal(sb, sb.Capacity);

	        switch (sb.ToString().ToLower())
	        {
				case "debug":
					return BuildType.Debug;
				case "release":
					return BuildType.Release;
				default:
					return BuildType.Unknown;
	        }
        }

        public static BuildType GetWrapperBuildType()
        {
#if DEBUG_ENGINE
	        return BuildType.DebugEngine;
#elif DEBUG
	        return BuildType.Debug;
#else
	        return BuildType.Release;
#endif
        }
	}
}
