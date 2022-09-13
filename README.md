# JSIS-Engine
Engine to run instructions compiled together from JSIS code by the JSIS compiler

## For anyone interrested in how fast this engine actually is
I ran a test of printing 1000001 chars 100 times and these were the average times on my M1 macbook air:
  ### C++20(clang 13):  62ms(compare/cpp.txt)
  ### JSIS 1.0:         93ms(compare/JSIS.txt)
  ### Java 8:           787ms
feel free to run the tests yourself
  - java main
  - make compare(adust paths in makefile first)
