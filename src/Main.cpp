#include <argparse/argparse.hpp>

int main(int argc, char* argv[])
{
    argparse::ArgumentParser argParser{"cet"};
    argParser.add_argument("config").default_value(std::string{"cet.yml"});

    try
    {
        argParser.parse_args(argc, argv);
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << argParser;
    }
    return 0;
}
