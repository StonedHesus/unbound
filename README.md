# unbounded-int
This repository contains the second year project I had to do as a student in Computer Science, at the University of Paris( now known as the Université Paris Cité), enrolled in the LC4 module, a module which deals with low level programming and the C language.

Thus far the main logic for the unbounded_int data type can be found inside the ***unbounded-int.h*** file, in addition to that there also exists a test file which contains tests which are bound to ensure the proper functionality of the data type, and, in case any extra functionality will be added in the future to allow the developer to easily determine whether the changes will permit backward compatibility with previous versions of the software.

In order to run the test file, type or copy into your terminal the following the command( make sure that the gcc compiler is installed on your system and that the shell is able to access it, and also that you poise yourself in the directory containing the scripts):

```shell

foo@example:~$ gcc -Wall test.c -o test

foo@example:~$ ./test

```

**! Important**: We recommend using your terminal in fullscreen mode when running the test program, if by any chance your resolution does not allow the rendering of a visible output do redirect your attention to the file test-results.txt in which you will be able to find the same results only in a format which is bound to scale more nicely with your resolution to the magic of text-editors.
