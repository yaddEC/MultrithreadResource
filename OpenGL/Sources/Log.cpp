#include <Log.h>

using namespace std;

using namespace Core;
using namespace Debug;
void Log::DebugLog(const char* file,int line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    Log debugLog;
    debugLog.OpenFile("log.txt");
    debugLog.Print(file);
    debugLog.Print("(%i):", line);
    debugLog.Print(format, args);
    char buffer[100];
    sprintf_s(buffer, "%s(%i):%s\n", file,line,format);
    OutputDebugStringA(buffer);
}

void Log::OpenFile(std::filesystem::path const& filename)
{
    logFile.open(filename);
    if (logFile.fail())
        Print("File can't be opened");
}

Log::~Log()
{
    logFile.close();
}

void Log::Print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    bool isOpen=false;

    if (logFile.is_open())
        isOpen = true;



    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'i')
            {
                int i = va_arg(args, int);
                std::cout << i;
                if (isOpen)
                {
                    logFile << i;
                }
            }
            else if (*format == 'f')
            {
                float i = va_arg(args, double);
                std::cout << i;
                if (isOpen)
                {
                    logFile << i;
                }
            }
            else if (*format == 'c')
            {
                char i = va_arg(args, char);
                std::cout << static_cast<char>(i);
                if (isOpen)
                {
                    logFile << i;
                }
            }
            else
            {
                std::cout << *format;
                if (isOpen)
                {
                    logFile << *format;
                }
            }
        }
        else
        {
            std::cout << *format;
            if (isOpen)
            {
                logFile << *format;
            }
        }
        format++;
    }
  
    va_end(args);
}