
#pragma once
#include <string>
class ZenityDialog {
public:
    // Basic Dialogs
    static bool question(const std::string& title, const std::string& text);
    static void info(const std::string& title, const std::string& text);
    static void error(const std::string& title, const std::string& text);

    // Input Dialogs
    static std::string entry(const std::string& title, const std::string& text);
    static std::string color_picker(const std::string& title);
    
    // File Dialogs
    static std::string file_selection(const std::string& title, bool directory_only = false);
    static std::string save_selection(const std::string& title, const std::string& default_filename = "");

private:
    // Helper to capture shell command output
    static std::string run_command(const std::string& command);
};
