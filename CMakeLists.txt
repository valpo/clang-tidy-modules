set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyValpoModule
  ValpoTidyModule.cpp
  ShadowMemberCheck.cpp

  LINK_LIBS
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  clangTooling
  )
