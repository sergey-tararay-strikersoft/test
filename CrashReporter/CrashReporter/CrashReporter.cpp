// CrashReporter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <dbghelp.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "CrashReporter.h"

#pragma comment(lib, "Dbghelp.lib")

namespace
{
	extern "C" 
	{
		typedef const char* (*getVersion_t)(void);
		typedef const char* (*getLogFilename_t)(void);
		typedef void(*enableLogfile_t)(const char *, const char *);
		typedef void(*disableLogfile_t)(void);
		typedef bool(*start_t)(const char *, const char *, const char *, const char *, const char *, const bool);
		typedef void(*stop_t)(void);
		typedef bool(*sendPageview_t)(const char *, const char *);
		typedef bool(*sendEvent_t)(const char *, const char *, const int);
		typedef bool(*sendScreenview_t)(const char *);
		typedef bool(*sendException_t)(const char *, const bool);
	}

	class SoftMeterLib
	{
	public:
		SoftMeterLib(const std::string& name)
		{
			m_module = ::LoadLibraryA(name.c_str());
			if (!m_module)
				throw std::runtime_error("Failed to load SoftMeter library");

			try
			{
				getVersion_ptr = GetFunction<getVersion_t>("getVersion");
				getLogFilename_ptr = GetFunction<getLogFilename_t>("getLogFilename");
				enableLogfile_ptr = GetFunction<enableLogfile_t>("enableLogfile");
				start_ptr = GetFunction<start_t>("start");
				stop_ptr = GetFunction<stop_t>("stop");
				sendPageview_ptr = GetFunction<sendPageview_t>("sendPageview");
				sendEvent_ptr = GetFunction<sendEvent_t>("sendEvent");
				sendScreenview_ptr = GetFunction<sendScreenview_t>("sendScreenview");
				sendException_ptr = GetFunction<sendException_t>("sendException");
			}
			catch (...)
			{
				::FreeLibrary(m_module);
				throw;
			}			
		}

		~SoftMeterLib()
		{
			FreeLibrary(m_module);
		}
		
		const char*	GetVersion() const
		{
			return getVersion_ptr();
		}

		const char*	GetLogFilename() const
		{
			return getLogFilename_ptr();
		}

		void EnableLogfile(const char *appName, const char *macBundleId)
		{
			enableLogfile_ptr(appName, macBundleId);
		}

		void DisableLogfile()
		{
			disableLogfile_ptr();
		}

		bool Start(const char *appName, const char *appVersion, const char *appLicense, const char *appEdition, const char *propertyID, const bool disabledByTheUser)
		{
			return start_ptr(appName, appVersion, appLicense, appEdition, propertyID, disabledByTheUser);
		}

		void Stop()
		{
			stop_ptr();
		}

		bool SendPageview(const char *pagePath, const char *pageTitle)
		{
			return sendPageview_ptr(pagePath, pageTitle);
		}

		bool SendEvent(const char *eventAction, const char *eventLabel, const int eventValue)
		{
			return sendEvent_ptr(eventAction, eventLabel, eventValue);
		}

		bool SendScreenview(const char *screenName)
		{
			return sendScreenview_ptr(screenName);
		}

		bool SendException(const char *exceptionDescription, bool isFatal)
		{
			return sendException_ptr(exceptionDescription, isFatal);
		}

	private:
		SoftMeterLib(const SoftMeterLib&);
		SoftMeterLib& operator = (const SoftMeterLib&);

		template<typename TFunc>
		TFunc GetFunction(const char* name) const
		{
			if (void* ptr = (void *)GetProcAddress(m_module, name))
				return (TFunc)ptr;

			std::string errorText("Function '");
			errorText += name;
			errorText += "' not found in SoftMeter library";
			throw std::runtime_error(errorText);
		}
	private:
		HMODULE m_module;

		getVersion_t getVersion_ptr;
		getLogFilename_t getLogFilename_ptr;
		enableLogfile_t enableLogfile_ptr;
		disableLogfile_t disableLogfile_ptr;
		start_t start_ptr;
		stop_t stop_ptr;
		sendPageview_t sendPageview_ptr;
		sendEvent_t sendEvent_ptr;
		sendScreenview_t sendScreenview_ptr;
		sendException_t sendException_ptr;
	};

	struct StackFrame
	{
		StackFrame() : address(0), lineNumber(0) { }

		void* address;
		uint32_t lineNumber;
		std::string functionName;
		std::string fullFunctionName;
		std::string modulePath;
		std::string filePath;
	};

	class StackTrace
	{
	public:
		StackTrace(std::vector<StackFrame> frames)
		{
			m_frames.swap(frames);
		}

		const std::vector<StackFrame>& GetFrames() const { return m_frames; }

		size_t GetSize() const { return m_frames.size(); }

	private:
		std::vector<StackFrame> m_frames;
	};

	class SymManager
	{
	public:
		SymManager()
		{
			::SymSetOptions(SYMOPT_PUBLICS_ONLY);
			m_process = GetCurrentProcess();
			char path[MAX_PATH] = "";
			GetModuleFileNameA(NULL, path, MAX_PATH);
			char* pLast = strrchr(path, '\\');
			*pLast = 0;
			if (!::SymInitialize(m_process, path, TRUE))
				throw std::runtime_error("Failed to initilize symbol handler");			
		}
		~SymManager()
		{
			SymCleanup(m_process);
		}

		__declspec(noinline) StackTrace GetStackTrace()
		{
			// Windows Server 2003 and Windows XP:  The sum of the FramesToSkip and FramesToCapture parameters must be less than 63.
			const DWORD framesToSkip = 1;
			const DWORD framesToCapture = 61;
			DWORD hash = 0;
			PVOID addresses[framesToCapture - framesToSkip];
			WORD count = ::CaptureStackBackTrace(framesToSkip, framesToCapture, addresses, &hash);

			std::vector<StackFrame> frames;
			frames.resize(count);
			for (int i = 0; i < count; ++i)
			{
				frames[i] = GetStackFrame(addresses[i]);
			}

			return StackTrace(frames);
		}

	private:

		StackFrame GetStackFrame(PVOID address)
		{
			StackFrame frame;
			DWORD64 address64 = reinterpret_cast<DWORD64>(address);

			frame.address = address;
			// get source code file name and line number
			ImageHelpLine64 line;
			DWORD offset = 0;

			if (::SymGetLineFromAddr64(m_process, address64, &offset, &line))
			{
				if (line.FileName)
					frame.filePath = line.FileName;

				frame.lineNumber = line.LineNumber;
			}

			// get decorated function name
			SymbolInfo symbol;
			if (SymFromAddr(m_process, address64, NULL, &symbol))
			{
				char buffer[4096] = "";
				UnDecorateSymbolName(symbol.Name, buffer, sizeof(buffer), UNDNAME_NAME_ONLY);
				frame.functionName = buffer;

				UnDecorateSymbolName(symbol.Name, buffer, sizeof(buffer), UNDNAME_COMPLETE);
				frame.fullFunctionName = buffer;
			}

			// get module info
			ImageHelpModule64 module;
			if (SymGetModuleInfo64(m_process, address64, &module))
				frame.modulePath = module.ImageName;

			return frame;
		}

	private:
		struct ImageHelpLine64 : IMAGEHLP_LINE64
		{
			ImageHelpLine64()
			{
				ZeroMemory(this, sizeof(*this));
				SizeOfStruct = sizeof(*this);
			}
		};

		struct SymbolInfo : SYMBOL_INFO
		{
			uint8_t buffer[4096];
			SymbolInfo()
			{
				ZeroMemory(this, sizeof(*this));
				SizeOfStruct = sizeof(SYMBOL_INFO);
				MaxNameLen = 4096;
			}
		};

		struct ImageHelpModule64 : IMAGEHLP_MODULE64
		{
			ImageHelpModule64()
			{
				ZeroMemory(this, sizeof(*this));
				SizeOfStruct = sizeof(*this);
			}
		};

	private:
		HANDLE m_process;
	};

}

void Test()
{
	SoftMeterLib smlib("libSoftMeter.dll");
	SymManager symManager;
	StackTrace st = symManager.GetStackTrace();
	for (int i = 0; i < st.GetSize(); ++i)
	{
		const StackFrame& f = st.GetFrames()[i];
		std::ostringstream stream;
		stream << "0x" << f.address << ": ";
		if (f.modulePath.empty())
		{
			stream << "<unknown module>";
		}
		else
		{
			stream << f.modulePath;
		}
		stream << "!" << f.functionName;
		if (!f.filePath.empty())
		{
			stream << ' ' << f.filePath << '(' << f.lineNumber << ')';
		}
		std::cout << stream.str() << '\n';
	}

}
