<p align="center">
    <img width="100%" src="https://raw.githubusercontent.com/metasophiea/riomhaireRua/master/images/banner.png">
</p>

A fun little virtual machine project with the custom language 'Rua', a little console access and some graphical ability

## The Riomhaire
riomhaireRua uses a simple 'worker' and 'worktop' model for getting stuff done. The program you write is given to the worker, which goes through each command one after another, following each instruction wherever it may lead. Once the worker runs out of instructions, they will stop and the machine will switch off.

<p align="center">
    <img width="640" height="360" src="https://raw.githubusercontent.com/metasophiea/riomhaireRua/master/images/0.png">
</p>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The worker uses the worktop to do jobs. The worktop is firstly a place to put bytes down. It is secondly somewhere to find connections to other tools. These connections are called ports. Tools can have different amounts of ports depending on their designs.

<p align="center">
    <img width="640" height="376" src="https://raw.githubusercontent.com/metasophiea/riomhaireRua/master/images/1.png">
</p>

## Tools
### Program Position Locator
These ports are used to show which instruction on the program the worker is going to do next. The number of ports used depends on how long the instruction program is allowed to be.

### Machine Status
The ports here are used to interact with some of the machine's special functions, and learn about the current goings on. For example, you can check to see if the most recent calculation resulted in a zero or not.

### Console
Console ports are used to communicate with the user console. With this tool, you can print messages to the user, or ask for input.

### Visual Display
Display connections are used to work with the visual display module. This module can contain a simple array of pixel bytes, or a more complicated list of shapes, with their size, coloring, position, etc.
