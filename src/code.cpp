#include <iostream>
#include <string>
#include "code.h"

// Initializes the C instruction - maps for the XXX bits to the specific hack(asm) syntax
void init_maps()
{
  destMap = {
      {"000", ""},
      {"001", "M"},
      {"010", "D"},
      {"011", "MD"},
      {"100", "A"},
      {"101", "AM"},
      {"110", "AD"},
      {"111", "AMD"}};

  compMap = {
      {"0101010", "0"},
      {"0111111", "1"},
      {"0111010", "-1"},
      {"0001100", "D"},
      {"0110000", "A"},
      {"1110000", "M"},
      {"0001101", "!D"},
      {"0110001", "!A"},
      {"1110001", "!M"},
      {"0001111", "-D"},
      {"0110011", "-A"},
      {"1110011", "-M"},
      {"0011111", "D+1"},
      {"0110111", "A+1"},
      {"1110111", "M+1"},
      {"0001110", "D-1"},
      {"0110010", "A-1"},
      {"1110010", "M-1"},
      {"0000010", "D+A"},
      {"1000010", "D+M"},
      {"0010011", "D-A"},
      {"1010011", "D-M"},
      {"0000111", "A-D"},
      {"1000111", "M-D"},
      {"0000000", "D&A"},
      {"1000000", "D&M"},
      {"0010101", "D|A"},
      {"1010101", "D|M"}};

  jumpMap = {
      {"000", "JUMP_NULL"},
      {"001", "JGT"},
      {"010", "JEQ"},
      {"011", "JGE"},
      {"100", "JLT"},
      {"101", "JNE"},
      {"110", "JLE"},
      {"111", "JMP"}};
}

std::string TranslateComp(std::string comp)
{
  return compMap[comp];
}
std::string TranslateJump(std::string jump)
{
  return jumpMap[jump];
}

std::string TranslateDest(std::string dest)
{
  return destMap[dest];
}

int FromBinary15Bit(std::string addr)
{
  return 0;
}

std::string TranslateCInstruction(std::string instruction)
{
  return std::string();
}
