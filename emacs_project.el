
(setq cpp-test_code-project
      (ede-cpp-root-project "WProtect"
			    :file "~/Project/WProtect/src/main.cpp"
			    :include-path '(
"~/Project/WProtect/src/AsmJit"
"~/Project/WProtect/src/WProtect/PE"
"~/Project/WProtect/src/WProtect/Protect/OutOfOrder"
"~/Project/WProtect/build"
"~/Project/WProtect/"
"~/Project/WProtect/inc"
"~/Project/WProtect/src/"
"~/Project/WProtect/src/Libudis86"
"~/Project/WProtect/src/WProtect"
"~/Project/WProtect/src/DataStruct"
"~/Project/WProtect/src/WProtect/ELF"
"~/Project/WProtect/src/WProtect/Protect/EquivalentReplacement"
"~/Project/WProtect/src/WProtect/Protect/Encryption"
"~/Project/WProtect/src/WProtect/Protect/VirtualMachine"
"~/Project/WProtect/src/WProtect/Protect/Algorithms")))



(setq compile-command "make -f ~/Project/WProtect/build/Makefile")

