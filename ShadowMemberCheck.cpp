//===--- ShadowMemberCheck.cpp - clang-tidy--------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ShadowMemberCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/DeclCXX.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace valpo {

void ShadowMemberCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(fieldDecl().bind("field"), this);
}

void ShadowMemberCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *field = Result.Nodes.getNodeAs<FieldDecl>("field");
  if (field == nullptr) {
      diag(SourceLocation(),"no match", DiagnosticIDs::Fatal);
      return;
  }
  else {
      const auto fieldClass = dyn_cast<CXXRecordDecl>(field->getParent());
      if (fieldClass == nullptr) {
          return;
      }
      fieldClass->forallBases(
          [field,this](const CXXRecordDecl *baseDef){
            for (const auto& f : baseDef->fields()) {
                if (f->getName() == field->getName() && f->getAccess() != AS_private) {
                    diag(field->getLocation(), "field %0 shadows member in base class %1") << field << baseDef;
                    diag(f->getLocation(), "previously declared here", DiagnosticIDs::Note) << f;
                }
            }

            return true; },
          false);
  }
}

} // namespace valpo
} // namespace tidy
} // namespace clang
