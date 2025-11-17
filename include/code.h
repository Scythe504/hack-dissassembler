#ifndef CODE_H
#include <string>
#include <unordered_map>
namespace CODE_H {

  extern std::unordered_map<std::string, std::string> destMap;
  extern std::unordered_map<std::string, std::string> compMap;
  extern std::unordered_map<std::string, std::string> jumpMap;

  void init_maps();

  std::string TranslateComp(const std::string &);
  std::string TranslateDest(const std::string &);
  std::string TranslateJump(const std::string &);

  int FromBinary15Bit(const std::string &);
  std::string TranslateCInstruction(const std::string &);

} // namespace CODE_H

#endif
