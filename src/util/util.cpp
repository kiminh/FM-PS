#include"util.h"

size_t hash_string_to_int(const std::string& s){
  unsigned int h = 0;
  const size_t len = s.length();
  for(size_t i = 0; i < len; i++){
    h = (h << 5) | (h>>27);
    h += (int)s[i];
  }
  return (size_t)h;
}