using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// ---------
		// Multiplay
		// ---------

		[DllImport(B3DDllLink)]
		public static extern int StartNetGame();

		[DllImport(B3DDllLink)]
		public static extern int HostNetGame(string name);

		[DllImport(B3DDllLink)]
		public static extern int JoinNetGame(string name, string ip);

		[DllImport(B3DDllLink)]
		public static extern void StopNetGame();

		[DllImport(B3DDllLink)]
		public static extern int CreateNetPlayer(string name);

		[DllImport(B3DDllLink)]
		public static extern void DeleteNetPlayer(int playerId);

		[DllImport(B3DDllLink)]
		private static extern void NetPlayerName_internal(StringBuilder ret, int retLen, int playerId);

		public static string NetPlayerName(int playerId)
		{
			StringBuilder sb = new StringBuilder(4096);
			NetPlayerName_internal(sb, sb.Capacity, playerId);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern bool NetPlayerLocal(int playerId);

		[DllImport(B3DDllLink)]
		public static extern int SendNetMsg(int type, string msg, int fromId, int toId = 0, bool reliable = true);

		[DllImport(B3DDllLink)]
		public static extern int RecvNetMsg();

		[DllImport(B3DDllLink)]
		public static extern int NetMsgType();

		[DllImport(B3DDllLink)]
		public static extern int NetMsgFrom();

		[DllImport(B3DDllLink)]
		public static extern int NetMsgTo();

		[DllImport(B3DDllLink)]
		private static extern void NetMsgData_internal(StringBuilder ret, int retLen);

		public static string NetMsgData()
		{
			StringBuilder sb = new StringBuilder(4096);
			NetMsgData_internal(sb, sb.Capacity);
			return sb.ToString();
		}
	}
}
