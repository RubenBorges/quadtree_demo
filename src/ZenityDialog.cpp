#include <ZenityDialog.hpp>
#include <sys/wait.h>
#include <string>
#include <array>
#include <iostream>
#include <memory>
#include <cstdio>
#include <cerrno>

// Internal helper to execute command and capture stdout
std::string ZenityDialog::run_command(const std::string& command) {
    try {
        std::array<char, 128> buffer{};
        std::string result;

        if (command.empty()) {
            return "";
        }

        // Open pipe to read the command output
        // Use a lambda as deleter to avoid attribute warnings with pclose
        auto pipe_deleter = [](FILE* f) { if (f) pclose(f); };
        std::unique_ptr<FILE, decltype(pipe_deleter)> pipe(popen(command.c_str(), "r"), pipe_deleter);
        if (!pipe) {
            return "";
        }

        // Read from pipe with error checking
        while (true) {
            errno = 0;  // Clear errno before the call
            if (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) == nullptr) {
                // Check if EOF or error occurred
                if (ferror(pipe.get())) {
                    // Error occurred, but we return what we have so far
                    break;
                }
                // EOF reached normally
                break;
            }

            // Safely append to result, checking for buffer validity
            if (buffer.data() != nullptr) {
                result += buffer.data();
            }

            // Prevent unbounded growth
            if (result.size() > 1000000) {  // 1MB limit
                break;
            }
        }

        // Strip trailing newline added by Zenity - safe check
        while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
            result.pop_back();
        }

        return result;
    } catch (const std::exception& e) {
        std::cerr << "Error in run_command: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Unknown error in run_command" << std::endl;
        return "";
    }
}

bool ZenityDialog::question(const std::string& title, const std::string& text) {
    std::string cmd = "zenity --question --title='" + title + "' --text='" + text + "' --no-wrap";
    int status = std::system(cmd.c_str());
    if (status == -1) {
        std::cerr << "Failed to launch zenity question dialog." << std::endl;
        return false;
    }

    if (!WIFEXITED(status)) {
        std::cerr << "Zenity question dialog did not exit normally." << std::endl;
        return false;
    }

    return WEXITSTATUS(status) == 0;
}

void ZenityDialog::info(const std::string& title, const std::string& text) {
    std::string cmd = "zenity --info --title='" + title + "' --text='" + text + "' --width=300";
    std::system(cmd.c_str());
}

void ZenityDialog::error(const std::string& title, const std::string& text) {
    std::string cmd = "zenity --error --title='" + title + "' --text='" + text + "'";
    std::system(cmd.c_str());
}

std::string ZenityDialog::entry(const std::string& title, const std::string& text) {
    return run_command("zenity --entry --title='" + title + "' --text='" + text + "'");
}

std::string ZenityDialog::color_picker(const std::string& title) {
    return run_command("zenity --color-selection --title='" + title + "' --show-palette");
}

std::string ZenityDialog::file_selection(const std::string& title, bool directory_only) {
    std::string cmd = "zenity --file-selection --title='" + title + "'";
    if (directory_only) cmd += " --directory";
    return run_command(cmd);
}

std::string ZenityDialog::save_selection(const std::string& title, const std::string& default_filename) {
    std::string cmd = "zenity --file-selection --save --confirm-overwrite --title='" + title + "'";
    if (!default_filename.empty()) cmd += " --filename='" + default_filename + "'";
    return run_command(cmd);
}
