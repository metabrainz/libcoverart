FILE(REMOVE_RECURSE
  "CMakeFiles/example_c.dir/example_c.c.o"
  "example_c.pdb"
  "example_c"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/example_c.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
