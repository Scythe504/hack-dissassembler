#ifndef CODE_H
#define CODE_H
#include <unordered_map>
#include <string>

void init_maps();
// dest bits [3..5]
std::unordered_map<std::string, std::string> destMap;
// jump bits [0..2]
std::unordered_map<std::string, std::string> jumpMap;
// bits a|c1|c2|c3|c4|c5|c6
std::unordered_map<std::string, std::string> compMap;
// comp bits C instruction[6..12]
std::string TranslateComp(std::string comp);

// jump bits C instruction [3..5]
std::string TranslateJump(std::string jump);

// jump bits C instruciton [0..2]
std::string TranslateDest(std::string dest);
int FromBinary15Bit(std::string addr);

std::string TranslateCInstruction(std::string instruction);

#endif