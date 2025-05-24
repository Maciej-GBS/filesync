#pragma once

#include <string>
#include <vector>

namespace filesync::argparse {

namespace {
const std::vector<std::pair<std::string, std::string>> ARGS = {
    {"source", "Source directory to sync"},
    {"destination", "Destination directory to sync"},
    {"--find-duplicates", "List duplicate files at destination and exit"},
    {"--verbose", "Enable verbose mode"},
    {"--dry-run", "Perform a dry run (don't make any changes)"},
    {"--help", "Show this help message and exit"}
};
}

class ArgumentParser {
private:
    void help() const;

public:
    ArgumentParser() = default;
    ~ArgumentParser() = default;

    void parse_args(int argc, char *argv[]);

    char* get_source_directory() const;
    char* get_destination_directory() const;

    bool is_find_duplicates() const;
    bool is_verbose() const;
    bool is_dry_run() const;
};

}
