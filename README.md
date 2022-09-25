# LGC
Large Glider Collider project

Read LGC.ipynb for more information about the project.

To compile the program, while in `/build` directory run `cmake .`, then follow with `cmake build .`.

This will create three programs in the `/bin` directory - `Rules`, `Background` and `LGC`.

`Rules` is a preview of all the rules that can be applied to the simulation.

`Background` is a program that takes one argument (selected rule) and finds a background for it, prints it's parameters and how it behaves in the simulation. Example of use: `Background 110`.

`LGC` is the main program that takes one argument (selected rule) and attempts to find as many backgrounds for it as possible. Example of use: `LGC 110`.