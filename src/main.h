#include <getopt.h>

/**
 * @brief The obelisk namespace contains everything needed to compile obelisk
 * code.
 *
 */
namespace obelisk
{
    /**
     * @brief The usage messsage displayed during help or incorrect usage.
     *
     */
    std::string usageMessage = R"(Usage: obelisk [OPTION]... [FILE]...
Compile the obelisk source FILE(s) into knoweldge base and library.

Options:
  -h, --help            shows this help/usage message
  -k, --kb=FILENAME     output knowldege base filename
  -v, --version         shows the version of obelisk)";

    /**
     * @brief The command line arguments that obelisk accepts.
     *
     */
    static struct option long_options[] = {
        {"help",    no_argument,       0, 'h'},
        {"kb",      required_argument, 0, 'k'},
        {"version", no_argument,       0, 'v'},
        {0,         0,                 0, 0  }
    };

    /**
     * @brief Prints out the usage of obelisk to the stdin.
     *
     */
    static void showUsage();

    /**
     * @brief This is the main loop for obelisk.
     *
     * This loop handles lexing and parsing of obelisk source code.
     *
     * @return int Returns EXIT_SUCCESS or EXIT_FAILURE.
     */
    int mainLoop(const std::vector<std::string> &sourceFiles,
        const std::string &kbFile);
} // namespace obelisk
