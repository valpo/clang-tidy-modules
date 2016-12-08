//===--- NonConstCharPtrArgCheck.cpp - clang-tidy--------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "NonConstCharPtrArgCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace valpo {

void NonConstCharPtrArgCheck::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(functionDecl().bind("function"), this);
}

void NonConstCharPtrArgCheck::check(const MatchFinder::MatchResult &Result) {
    const auto func = Result.Nodes.getNodeAs<FunctionDecl>("function");
    if (func) {
        for (const auto& p : func->parameters()) {
            const auto& t = p->getType(); // QualType
            auto typeName = t.getAsString();
            auto typePtr = t.getTypePtrOrNull();
            if (typeName.find("char") != std::string::npos && typePtr && typePtr->isPointerType()) {
                auto sType{t};
                while (sType->isPointerType()) sType = sType->getPointeeType();
                if (!sType.isConstQualified()) {
                    //diag(func->getLocStart(), "scalar type: %0") << sType;
                    diag(func->getLocStart(), "function taking non-const char pointer parameter");
                }
            }
        }
    }
    else
        diag(SourceLocation(), "no method");
}

} // namespace valpo
} // namespace tidy
} // namespace clang
