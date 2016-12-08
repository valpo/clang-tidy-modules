//===--- ShortMemberNamesCheck.cpp - clang-tidy----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ShortMemberNamesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace valpo {

void ShortMemberNamesCheck::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(fieldDecl().bind("field"), this);
}

void ShortMemberNamesCheck::check(const MatchFinder::MatchResult &Result) {
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
        if (field->getAccess() != AS_private && field->getName().size() < 3) {
            diag(field->getLocation(), "non private member %0 has a very short name") << field;
        }
    }
}

} // namespace valpo
} // namespace tidy
} // namespace clang
