using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlitzEngine
{
	public class ConsoleLogger
	{
		private readonly StreamWriter _writer;

		public bool ShowDebug { get; set; }

		public ConsoleLogger(string logFile, bool showDebug = false)
		{
			try
			{
				System.IO.Stream s = System.IO.File.Open(logFile, FileMode.Create);
				_writer = new StreamWriter(s);
                _writer.AutoFlush = true;
            }
			catch (IOException ex)
			{
				Console.WriteLine("Failed to create log file: " + ex.Message);
				Console.WriteLine(ex.StackTrace);
			}

			ShowDebug = showDebug;
		}

		public void Dispose()
		{
			try
			{
				_writer.Flush();
				_writer.Close();
			}
			catch (IOException ex)
			{
				Console.WriteLine("Failed to flush and close log file: " + ex.Message);
				Console.WriteLine(ex.StackTrace);
			}
		}

		private struct LogColor
		{
			public ConsoleColor Foreground { get; set; }
			public ConsoleColor Background { get; set; }

			public LogColor(ConsoleColor foreground, ConsoleColor background)
			{
				Foreground = foreground;
				Background = background;
			}
		}

		private enum LogLevel
		{
			Info,
			Warn,
			Error,
			Debug
		}

		private void Log(LogLevel level, params string[] lines)
		{
			if (level == LogLevel.Debug && !ShowDebug)
				return;

			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < lines.Length; i++)
			{
				sb.Append(lines[i]);

				if (i < lines.Length - 1)
					sb.AppendLine();
			}

			string msg = sb.ToString();

			string text = "";
			switch (level)
			{
				case LogLevel.Info:
					text = msg;
					break;
				case LogLevel.Warn:
					text = "[WARNING]: " + msg;
					break;
				case LogLevel.Error:
					text = "[ERROR]: " + msg;
					break;
				case LogLevel.Debug:
					text = "[DEBUG]: " + msg;
					break;
				default:
					throw new ArgumentOutOfRangeException(nameof(level), level, null);
			}

			_writer.WriteLine(text);

			WriteLine(GetLogLevelColor(level), text);
		}

		private LogColor GetLogLevelColor(LogLevel level)
		{
			switch (level)
			{
				case LogLevel.Warn:
					return new LogColor(ConsoleColor.Yellow, ConsoleColor.Black);
				case LogLevel.Error:
					return new LogColor(ConsoleColor.Black, ConsoleColor.Red);
				case LogLevel.Debug:
					return new LogColor(ConsoleColor.Green, ConsoleColor.Black);
				default:
					return new LogColor(ConsoleColor.White, ConsoleColor.Black);
			}
		}

		private void SetTextColor(LogColor color)
		{
			Console.ForegroundColor = color.Foreground;
			Console.BackgroundColor = color.Background;
		}

		private void ResetTextColor()
		{
			SetTextColor(GetLogLevelColor(LogLevel.Info));
		}

		private void WriteLine(LogColor color, string text)
		{
			SetTextColor(color);
			Console.WriteLine(text);
			ResetTextColor();
		}

		public void Info(params string[] lines)
		{
			Log(LogLevel.Info, lines);
		}

		public void Warn(params string[] lines)
		{
			Log(LogLevel.Warn, lines);
		}

		public void Error(params string[] lines)
		{
			Log(LogLevel.Error, lines);
		}

		public void Error(Exception ex, string msg = "")
		{
			if (!msg.Equals(""))
			{
				//Error(msg + ": (" + ex + ")", ex.Message, ex.StackTrace);
				Error(msg, ex.ToString());
			}
			else
			{
				//Error(ex.Source, ex.Message, ex.StackTrace);
				Error(ex.ToString());
			}
		}

		public void Debug(params string[] lines)
		{
			Log(LogLevel.Debug, lines);
		}
	}
}