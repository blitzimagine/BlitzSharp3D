using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace BlitzEngine
{
	[Serializable]
	public class Blitz3DException : Exception
	{
		public bool RuntimeError { get; set; }

		public Blitz3DException(string message) : base(message)
		{

		}

		public Blitz3DException(string message, Exception innerException) : base(message, innerException)
		{

		}

		protected Blitz3DException(SerializationInfo info, StreamingContext context) : base(info, context)
		{

		}
	}
}
