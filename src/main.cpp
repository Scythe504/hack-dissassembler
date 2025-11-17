#include <iostream>
#include <fstream>
#include <string>
#include "code.h"
#include <algorithm>
#include <filesystem>
#include <vector>

std::string parseAInstruction(std::string instruction)
{
  // A instrution opcode[15], addrBit[0..14]
  // @(decimal(addrBits))
  std::string line = "@";
  std::string addrBits = "";
  for (int i = 1; i < instruction.length(); i++)
  {
    addrBits += instruction[i];
  }

  int addr = CODE_H::FromBinary15Bit(addrBits);
  line += std::to_string(addr);

  return line;
}

std::string parseCInstruction(std::string instruction)
{
  if (instruction.length() != 16)
  {
    return "err";
  }

  // skip "111"
  std::string body = instruction.substr(3); // 13 bits

  if (body.length() != 13)
  {
    return "err";
  }

  return CODE_H::TranslateCInstruction(body);
}

int disassembleHack(std::string infName, std::string outfName)
{
  // If output filename ends with .hack, replace with .asm
  if (outfName.ends_with(".hack"))
  {
    outfName = outfName.substr(0, outfName.size() - 5) + ".asm";
  }
  std::ifstream inputFile(infName);

  if (!inputFile.is_open())
  {
    std::cerr << "Error: Could not open file " << infName << std::endl;
    return -1;
  }

  std::string line;
  std::string code;
  std::vector<std::string> asmCode;

  while (std::getline(inputFile, line))
  {
    // remove whitespace like \r or spaces
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.empty())
      continue; // skip blank lines

    // decode whether a instruction or c instruction
    bool isAInstruction = line[0] == '0';

    if (isAInstruction)
    {
      code = parseAInstruction(line);
    }
    else
    {
      code = parseCInstruction(line);
    }

    if (code == "err")
    {
      inputFile.close();
      std::cerr << "error: invalid hack file" << std::endl;
      return 1;
    }

    asmCode.push_back(code);
  }

  // output
  std::ofstream outputFile(outfName);

  if (outputFile.is_open())
  {
    for (const auto &code : asmCode)
    {
      outputFile << code << std::endl;
    }
  }
  else
  {
    std::cerr << "error: failed to disassesmbler hack file" << std::endl;
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  CODE_H::init_maps();

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

  int errcode = disassembleHack(inFilename, outFilename);

  return errcode;
}