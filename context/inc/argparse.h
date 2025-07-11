#pragma once

#include <string>
#include <vector>

namespace filesync::argparse {

class ArgumentParser {
private:
    std::string sourceDir;
    std::string destDir;
    bool verbose{false};
    bool dryRun{false};
    bool showDuplicates{false};

    void help(const char* exec) const;

public:
    ArgumentParser() {}
    ~ArgumentParser() = default;

    void parse_args(int argc, char *argv[]);

    std::string get_source_directory() const;
    std::string get_destination_directory() const;

    bool is_find_duplicates() const;
    bool is_verbose() const;
    bool is_dry_run() const;
};

}
