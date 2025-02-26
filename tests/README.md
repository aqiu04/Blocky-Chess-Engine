## Running Tests

In order to get started making changes to Blocky, you need to be able to run the unit tests and check that they are passing.
 
If you are on Linux, the following commands will build and run the tests.

```
cmake -S . -B build
cmake --build build
( cd build ; ctest )
```

If you are on Windows, the following commands will work instead:

```
cmake -S . -B build -DMAKE_EXE=ON
cmake --build build
( cd build ; ctest )
```

CTest has a variety of options to customize output. If you want to use console logging for debugging, you need to add an output on failure flag to the ctest command. For example:

```
ctest --output-on-failure
```
