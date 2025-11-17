#include <iostream>
#include <fstream>
#include <string>
#include "code.h"
#include <filesystem>

int readHackFile(std::string filepath)
{
  std::ifstream inputFile(filepath);

  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open file " << filepath << std::endl;
    return 1;
  }
}

int main(int argc, char *argv[])
{
  CODE_H::init_maps();

  std::filesystem::path currentPath = std::filesystem::current_path();

  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <input_file> [-o <output_file>]" << std::endl;
    return 1;
  }

  std::string inFilename = "";
  std::string outFilename = "";

  if (argc == 2)
  {
    // Single argument: same in = out
    inFilename = argv[1];
    outFilename = inFilename;

    if (!inFilename.ends_with(".hack"))
    {
      std::cerr << "error: invalid hack binary file" << std::endl;
      return 1;
    }
  }
  else
  {
    for (int i = 1; i < argc; i++)
    {
      std::string arg = argv[i];

      if (arg == "-o")
      {
        if (i + 1 >= argc)
        {
          std::cerr << "error: missing filename after -o" << std::endl;
          return 1;
        }
        outFilename = argv[++i]; // take next argument
        continue;
      }

      // First non -o argument becomes input
      if (inFilename.empty())
        inFilename = arg;
    }
  }

  if (inFilename.empty())
  {
    std::cerr << "error: no input file supplied" << std::endl;
    return 1;
  }

  if (!inFilename.ends_with(".hack"))
  {
    std::cerr << "error: invalid hack binary file" << std::endl;
    return 1;
  }

  if (outFilename.empty())
  {
    outFilename = inFilename; // default
  }

  std::filesystem::path filepath = currentPath / inFilename;
  int errcode = readHackFile(filepath.string());

  return errcode;
}