#include "MultiExtend.h"

int main(int argc, char* argv[])
{
	MultiExtend::Message::Init();

	MULTIEXTEND_MESSAGE_TERMINAL_DEBUG("Template01 DEBUG T");
	MULTIEXTEND_MESSAGE_TERMINAL_WARN("Template01 WARN T");
	MULTIEXTEND_MESSAGE_CLIENT_DEBUG("Template01 DEBUG C");
	MULTIEXTEND_MESSAGE_CLIENT_WARN("Template01 WARN C");

	MultiExtend::File file("./Template01/Template01.log");

	file.Open(true);
	file.Open(true);
	file.Open(true);
	file.Open(true);
	file.Open(true);
	file.Open(true);

	file.Clear();

	file.Write("Template01.");
	file.Write("Test file.");
	file.Write("A new line.");

	file.Print();
	file.Close();

	file.Open("./Template01/Template01.txt",true);
	file.Open("./Template01/Template01.log",true);

	file.Clear();

	file.Write("Template01.");
	file.Write("Test file text file.");
	file.Write("A new line.");

	file.Print();
	file.Close();

	std::cin.get();

	MultiExtend::Log Logfile1("Terminal", "./Log/Default.log");
	MultiExtend::Log Logfile2("Client", "./Log/Default.log");

	Logfile1.Write("Test Log01",MultiExtend::LogLevel::Trace);
	Logfile2.Write("Test Log01",MultiExtend::LogLevel::Trace);
	Logfile1.Write("Test Log02",MultiExtend::LogLevel::Trace);
	Logfile2.Write("Test Log02",MultiExtend::LogLevel::Trace);
}