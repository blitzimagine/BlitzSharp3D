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
		// -------
		// Sockets
		// -------

		[DllImport(B3DDllLink)]
		private static extern void DottedIP_internal(StringBuilder ret, int retLen, int ip);

		public static string DottedIP(int ip)
		{
			StringBuilder sb = new StringBuilder(4096);
			DottedIP_internal(sb, sb.Capacity, ip);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern int CountHostIPs(string hostName);

		[DllImport(B3DDllLink)]
		public static extern int HostIP(int hostIndex);

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateUDPStream_internal(int port);

		public static UDPStream CreateUDPStream(int port = 0)
		{
			IntPtr pointer = CreateUDPStream_internal(port);
			UDPStream ret = new UDPStream(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void CloseUDPStream_internal(IntPtr stream);

		public static void CloseUDPStream(UDPStream stream)
		{
			CloseUDPStream_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void SendUDPMsg_internal(IntPtr stream, int ip, int port);

		public static void SendUDPMsg(UDPStream stream, int ip, int port = 0)
		{
			SendUDPMsg_internal(stream.Pointer, ip, port);
		}

		[DllImport(B3DDllLink)]
		private static extern int RecvUDPMsg_internal(IntPtr stream);

		public static int RecvUDPMsg(UDPStream stream)
		{
			return RecvUDPMsg_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int UDPStreamIP_internal(IntPtr stream);

		public static int UDPStreamIP(UDPStream stream)
		{
			return UDPStreamIP_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int UDPStreamPort_internal(IntPtr stream);

		public static int UDPStreamPort(UDPStream stream)
		{
			return UDPStreamPort_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int UDPMsgIP_internal(IntPtr stream);

		public static int UDPMsgIP(UDPStream stream)
		{
			return UDPMsgIP_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int UDPMsgPort_internal(IntPtr stream);

		public static int UDPMsgPort(UDPStream stream)
		{
			return UDPMsgPort_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		public static extern void UDPTimeouts(int recvTimeout);

		[DllImport(B3DDllLink)]
		private static extern IntPtr OpenTCPStream_internal(string server, int serverPort, int localPort);

		public static TCPStream OpenTCPStream(string server, int serverPort, int localPort = 0)
		{
			IntPtr pointer = OpenTCPStream_internal(server, serverPort, localPort);
			TCPStream ret = new TCPStream(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void CloseTCPStream_internal(IntPtr stream);

		public static void CloseTCPStream(TCPStream stream)
		{
			CloseTCPStream_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr CreateTCPServer_internal(int port);

		public static TCPServer CreateTCPServer(int port)
		{
			IntPtr pointer = CreateTCPServer_internal(port);
			TCPServer ret = new TCPServer(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void CloseTCPServer_internal(IntPtr server);

		public static void CloseTCPServer(TCPServer stream)
		{
			CloseTCPServer_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr AcceptTCPStream_internal(IntPtr server);

		public static TCPStream AcceptTCPStream(TCPServer server)
		{
			IntPtr pointer = AcceptTCPStream_internal(server.Pointer);
			TCPStream ret = new TCPStream(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern int TCPStreamIP_internal(IntPtr stream);

		public static int TCPStreamIP(TCPStream stream)
		{
			return TCPStreamIP_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int TCPStreamPort_internal(IntPtr stream);

		public static int TCPStreamPort(TCPStream stream)
		{
			return TCPStreamPort_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		public static extern void TCPTimeouts(int readMS, int acceptMS);
	}
}
