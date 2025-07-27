#include <iostream>

#include "../inc/argparse.h"
#include <sys/inc/log.h>

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

    void ArgumentParser::help(const char* exec) const {
        std::cout << "Usage: " << exec << " source destination" << std::endl;
        for (auto it : ARGS) {
            std::cout << format("%20s\t%s", it.first.c_str(), it.second.c_str()).c_str() << std::endl;
        }
        exit(0);
    }

    void ArgumentParser::parse_args(int argc, char *argv[]) {
        if (argc < 3) {
            help(argv[0]);
        }

        sourceDir = {argv[1]};
        destDir = {argv[2]};

        for (int i = 3; i < argc; ++i) {
            bool argRecognized = false;
            char* arg = argv[i];
            for (size_t argIter = 2; argIter < ARGS.size(); ++argIter) {
                if (ARGS.at(argIter).first.compare(arg) != 0) {
                    continue;
                }
                switch (argIter)
                {
                case 2: // find-duplicates
                    showDuplicates = true;
                    break;
                case 3: // verbose
                    verbose = true;
                    break;
                case 4: // dry-run 
                    dryRun = true;
                    break;
                default:
                    help(argv[0]);
                    break;
                }
                argRecognized = true;
            }
            if (!argRecognized) {
                std::cout << format("Argument %s not recognized", arg).c_str() << std::endl;
                help(argv[0]);
            }
        }
    }

    const std::string& ArgumentParser::get_source_directory() const {
        return sourceDir;
    }

    const std::string& ArgumentParser::get_destination_directory() const {
        return destDir;
    }

    bool ArgumentParser::is_find_duplicates() const {
        return showDuplicates;
    }

    bool ArgumentParser::is_verbose() const {
        return verbose;
    }

    bool ArgumentParser::is_dry_run() const {
        return dryRun;
    }
}
