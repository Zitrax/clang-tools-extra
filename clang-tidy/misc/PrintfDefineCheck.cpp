//===--- PrintfDefineCheck.cpp - clang-tidy--------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "PrintfDefineCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <locale>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrintfDefineCheck::registerMatchers(MatchFinder *Finder) {
  // Match all calls to printf
  Finder->addMatcher(callExpr(callee(functionDecl(hasName("printf")))).bind("call"), this);
}

void PrintfDefineCheck::check(const MatchFinder::MatchResult &Result) {
  clang::LangOptions LangOpts;
  LangOpts.CPlusPlus = true;
  clang::PrintingPolicy Policy(LangOpts);
  const auto *Call = Result.Nodes.getNodeAs<CallExpr>("call");

  // FIXME: Maybe just check argument 1 ?
  for(const auto arg : Call->arguments()) {
    //llvm::errs() << "argType: " << arg->getType().getAsString() << "\n";
    //llvm::errs() << "stmtClass: " << arg->IgnoreImpCasts()->getStmtClassName() << "\n";

    const auto* sl = dyn_cast<StringLiteral>(arg->IgnoreImpCasts());
    if(sl) {
      if(islower(sl->getString().str()[0])) {
        auto str = sl->getString().str();
        str[0] = toupper(sl->getString().str()[0], std::locale());
        diag(arg->getExprLoc().getLocWithOffset(1), "printf string should start with capital letter")
          << FixItHint::CreateReplacement(arg->getExprLoc().getLocWithOffset(1), str.c_str());
      }
    }
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
