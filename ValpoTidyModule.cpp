//===--- MiscTidyModule.cpp - clang-tidy ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "ShadowMemberCheck.h"

namespace clang {
namespace tidy {
namespace valpo {

class ValpoModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<ShadowMemberCheck>("valpo-shadow-member");
  }
};

} // namespace valpo

// Register the MiscTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<valpo::ValpoModule>
    X("valpo-module", "Adds valpo lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the MiscModule.
volatile int ValpoModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
