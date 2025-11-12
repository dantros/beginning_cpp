# Building a program and a library with Clang

In this tutorial, we want to use the C++ compiler and linker from clang/llvm project. Check out their website for more detailed information: https://clang.llvm.org/

In this current version of the tutorial, we will be using windows, but the steps for linux are equivalent.

Do note that you can build clang with your own compiler,  but in this tutorial we will be using the pre-compiled binaries.

## Setup

1. Download clang from the oficial git release repository https://github.com/llvm/llvm-project/releases . Find the link to the latest version (20.1.0) for windows, it is called `clang+llvm-20.1.0-x86_64-pc-windows-msvc.tar.xz`
2. Use 7zip to extract the software. We are interested in the content of the bin folder.
3. Move the folder to a convenient location such as `C:\stable\clang+llvm-20.1.0-x86_64-pc-windows-msvc`
4. Add the bin folder path to your user or system path. *Side note:* Personally, I like to create a small batch file to simply add the bin folder, so I just call it when needed... this way, I do not modify neither the user nor system path.
   - Type: Win key + "environment var", then select "Edit the system environment variables".
   - Go to tab "Advanced" and then clic on "Environment Variables".
   - In the first list (for user variables), select "Path" and then clic on the corresponding Edit.
   - Each row is a directory to look for executables. Add a new value with the desired path such as: `C:\stable`. Then save.
   - Double check that the new path remains in the environment variable when you enter again.
   - At `C:\stable`, create a text file called `init_clang.bat`, with the following content `set PATH=%PATH%;C:\stable\clang+llvm-20.1.0-x86_64-pc-windows-msvc\bin`
5. Open cmd on a terminal. In a Powershell, you can type cmd, it will open cmd inside the same poweshell terminal.
6. Type `init_clang`, so the bin folder is added to the path for the current session of the terminal, and all files there will be available for our current terminal.
7. Test that clang is available entering `clang`, you should see an error message: `clang: error: no input files`.

## Building a single file

1. Create a basic hello world file called `main.cpp`

```
//main.cpp

#include <iostream>

int main()
{
    std::cout << "Welcome to clang!" << std:: endl;
}
```

2. build this file with `clang++ -o hello.exe main.cpp`
3. Run your new executable with `hello.exe`
4. Most likely, you need to compile more than 1 file, just list all required .cpp files. Headers are not required, but they must be there for the correct linking.

## Building a static library

1. Create a header file with your library declarations (and template definitions, if any), such as:

```
//mylib.h
#pragma once

int add(int a, int b);
```

2. Create a source file with your library definitions, such as:

```
//mylib.cpp

#include "mylib.h"

int add(int a, int b)
{
    return a + b;
}
```

3. Compile each source file individually with commands like: `clang++ -c -o mylib.obj mylib.cpp`. You should get the `mylib.obj` binary object file.
4. Generate the static library (objects file archive), with `llvm-ar r mylib.lib mylib.obj`. Congratulations!, you got your first static library!.
5. If you have more than one object file (*.obj), just list all of them after the .lib.
6. Most likely, you want to use your library in an executable program. Let's do it with a simple program:

```
// main.cpp

#include <iostream>
#include "mylib.h"

int main()
{
    std::cout << "Using my custom lib: " << add(100, 1) << std:: endl;
}
```

7. Just compile and link your program with the static library with `clang++ -o test.exe mylib.lib main.cpp`. Congrats!, you should get a new executable file `test.exe`
8. Run your new executable with `test.exe`

**Congrats!, hopefully you've learnt something new :)**
