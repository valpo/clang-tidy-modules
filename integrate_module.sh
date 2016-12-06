#!/bin/sh

cat <<EOF | git apply valpo/integrate_module.sh
diff --git a/clang-tidy/CMakeLists.txt b/clang-tidy/CMakeLists.txt
index 73a475c..c9054d5 100644
--- a/clang-tidy/CMakeLists.txt
+++ b/clang-tidy/CMakeLists.txt
@@ -39,3 +39,4 @@ add_subdirectory(mpi)
 add_subdirectory(performance)
 add_subdirectory(readability)
 add_subdirectory(utils)
+add_subdirectory(valpo)
diff --git a/clang-tidy/plugin/CMakeLists.txt b/clang-tidy/plugin/CMakeLists.txt
index 5106d3f..37770cc 100644
--- a/clang-tidy/plugin/CMakeLists.txt
+++ b/clang-tidy/plugin/CMakeLists.txt
@@ -14,6 +14,7 @@ add_clang_library(clangTidyPlugin
   clangTidyGoogleModule
   clangTidyLLVMModule
   clangTidyMiscModule
+  clangTidyValpoModule
   clangTidyModernizeModule
   clangTidyMPIModule
   clangTidyPerformanceModule
diff --git a/clang-tidy/tool/CMakeLists.txt b/clang-tidy/tool/CMakeLists.txt
index 682d5eb..c7feb90 100644
--- a/clang-tidy/tool/CMakeLists.txt
+++ b/clang-tidy/tool/CMakeLists.txt
@@ -19,6 +19,7 @@ target_link_libraries(clang-tidy
   clangTidyGoogleModule
   clangTidyLLVMModule
   clangTidyMiscModule
+  clangTidyValpoModule
   clangTidyModernizeModule
   clangTidyMPIModule
   clangTidyPerformanceModule
diff --git a/clang-tidy/tool/ClangTidyMain.cpp b/clang-tidy/tool/ClangTidyMain.cpp
index fd53c4e..99a0412 100644
--- a/clang-tidy/tool/ClangTidyMain.cpp
+++ b/clang-tidy/tool/ClangTidyMain.cpp
@@ -455,6 +455,11 @@ extern volatile int MiscModuleAnchorSource;
 static int LLVM_ATTRIBUTE_UNUSED MiscModuleAnchorDestination =
     MiscModuleAnchorSource;
 
+// This anchor is used to force the linker to link the ValpoModule.
+extern volatile int ValpoModuleAnchorSource;
+static int LLVM_ATTRIBUTE_UNUSED ValpoModuleAnchorDestination =
+  ValpoModuleAnchorSource;
+
 // This anchor is used to force the linker to link the ModernizeModule.
 extern volatile int ModernizeModuleAnchorSource;
 static int LLVM_ATTRIBUTE_UNUSED ModernizeModuleAnchorDestination =
EOF

