#pragma once

#include <format>
#include <print>
#include <utility>

namespace Morgo
{
    enum class PrintColor
    {
        White, Yellow, Red, Gray
    };

    enum class LogLevel : unsigned int
    {
        Verbose = 0, Info, Warning, Error
    };

    extern LogLevel log_level;

    void print(std::string_view message, PrintColor color = PrintColor::White);

    template<typename... Args>
    void printError(std::format_string<Args...> message, Args&&... args)
    {
        if (static_cast<unsigned int>(log_level) > static_cast<unsigned int>(LogLevel::Error))
            return;

        print(std::format("ERROR: {}", std::format(message, std::forward<Args>(args)...)),
            PrintColor::Red);
    }

    template<typename... Args>
    void printWarning(std::format_string<Args...> message, Args&&... args)
    {
        if (static_cast<unsigned int>(log_level) > static_cast<unsigned int>(LogLevel::Warning))
            return;

        print(std::format("WARN: {}", std::format(message, std::forward<Args>(args)...)),
            PrintColor::Yellow);
    }

    template<typename... Args>
    void printInfo(std::format_string<Args...> message, Args&&... args)
    {
        if (static_cast<unsigned int>(log_level) > static_cast<unsigned int>(LogLevel::Info))
            return;

        print(std::format("INFO: {}", std::format(message, std::forward<Args>(args)...)));
    }

    template<typename... Args>
    void printVerbose(std::format_string<Args...> message, Args&&... args)
    {
        if (static_cast<unsigned int>(log_level) > static_cast<unsigned int>(LogLevel::Verbose))
            return;

        print(std::format("VERB: {}", std::format(message, std::forward<Args>(args)...)),
            PrintColor::Gray);
    }

#ifdef MORGOLOG_INIT 
    LogLevel log_level = LogLevel::Info;

    void print(std::string_view message, PrintColor color)
    {
        switch (color)
        {
            case PrintColor::White: std::println("{}", message); break;
            case PrintColor::Yellow: std::println("\033[33m{}\033[0m", message); break;
            case PrintColor::Red: std::println("\033[31m{}\033[0m", message); break;
            case PrintColor::Gray: std::println("\033[30m{}\033[0m", message); break;
        }
    }
#endif
}
