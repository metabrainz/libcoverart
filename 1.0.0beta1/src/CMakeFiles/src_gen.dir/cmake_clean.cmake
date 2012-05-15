FILE(REMOVE_RECURSE
  "CMakeFiles/src_gen"
  "caa_c.cc"
  "caa_c.h"
  "../include/coverart/caa_c.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/src_gen.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
