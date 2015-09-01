Project(AlgOrithmsApp)

include_directories(/home/lovewei/Project/WProtect/src/AsmJit)
add_executable(TestApp AlgorithmsTest.cpp)

target_link_libraries(TestApp /home/lovewei/Project/WProtect/bin/libAlgorithms_Static.a /home/lovewei/Project/WProtect/bin/libAsmJit_Static.a)
