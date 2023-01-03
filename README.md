Due to the fact that I use `windows.h` this program only works on windows and generating an executable in Qt creator may give problems. You can easily compile using g++:
```
g++ -o Gobblets *.cpp
```

However, this prevents you from being able to print colors in the console. To generate a fully functional executable you must use a Qt Creator kit that uses Microsoft Visual C++ Compiler.
