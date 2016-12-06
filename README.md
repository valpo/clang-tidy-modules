# clang-tidy-modules
Some very basic modules for [clang-tidy](http://clang.llvm.org/extra/clang-tidy/). The modules
which come with clang-tidy are very good, but I am missing some very basic checks
for the code I have to work with. So I have read this [perfect introduction](http://bbannier.github.io/blog/2015/05/02/Writing-a-basic-clang-static-analysis-check.html) and started to write
some modules just for my very own needs. 

## integration into clang-tidy
### check out the clang-tidy sources
You need some parts of the llvm sources:
```
cd
git clone http://llvm.org/git/llvm.git
cd llvm/tools/
git clone http://llvm.org/git/clang.git
cd clang/tools/
git clone http://llvm.org/git/clang-tools-extra.git extra
```
### compile clang-tidy
Now check if you are able to build these modules:
```
cd
mkdir llvm-build && cd llvm-build/
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make check-clang-tools
```
If you have problems compiling the beast, just checkout the [llvm docs](http://llvm.org/docs/CMake.html).

### integrate these modules
Now it is time to integrate these modules:
```
cd
cd llvm/tools/clang/tools/extra/clang-tidy
git clone https://github.com/valpo/clang-tidy-modules.git valpo
valpo/integrate_module.sh
```

The last line applies a patch to clang tidy which integrates the valpo module. Basically 
it changes the following files in llvm/tools/clang/tools/extra/clang-tidy:

1. CMakeList.txt: add a line ```add_subdirectory(valpo)``` just below the line ```add_subdirectory(utils)```
2. plugin/CMakeLists.txt: add a line ```clangTidyValpoModule``` just below ```clangTidyMiscModule```
3. clang-tidy/tool/CMakeLists.txt: add a line ```clangTidyValpoModule``` just below ```clangTidyMiscModule```
4. clang-tidy/tool/ClangTidyMain.cpp: add the lines
  ```
  // This anchor is used to force the linker to link the ValpoModule.
  extern volatile int ValpoModuleAnchorSource;
  static int LLVM_ATTRIBUTE_UNUSED ValpoModuleAnchorDestination =
      ValpoModuleAnchorSource;
  ```
  just below the line ```GoogleModuleAnchorSource;```

### check if it works
Recompile clang-tidy:
```
cd
mkdir llvm-build && cd llvm-build/
make check-clang-tools
```
Now check if our new modules are there:
```
bin/clang-tidy -list-checks --checks "-*,valpo*"
```
should print out some checks. 
