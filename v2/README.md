<p align="center">
    <img width="100%" src="https://raw.githubusercontent.com/metasophiea/riomhaireRua/master/banner.png">
</p>
 
## Contents
- [Contents](#contents)

## The Riomhaire
riomhaireRua uses a simple 'worker' and 'worktop' model for getting stuff done. The program you write is given to the worker, which goes through each command one after another, following each instruction wherever it may lead; which is sometimes to other parts of the program. 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The worker uses the worktop to do jobs. The worktop is firstly a place to put bytes down. Bytes are like numbers; but they store a state, which is like a way of being, for example; "oh the sea is blue" = the sea's colour state is blue. "hay, I'm 12 years old" = this persons age state is 12. So if we said that the colour red is state 1, green is 2 and blue is 3; then the sea's colour state is 3, because 3 = blue.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This worktop is 8bit; so each byte has any one of 256 states. A 1bit worktop could only have one of 2 states per byte. ( number of states = 2^(number of bits) ) So on this worktop, there can only be 256 colour states, or 256 age states. Bytes are made of bits, hence why we use "8bit" to describe the worktop and what the bytes are like. Bits are like switches, they can be on or off (1 or 0) so each bit only has 2 states. By putting bits together, we can make a byte and get more states.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Most of the time, bytes store a number state (0 1 2 3 4...) or a collection of smaller bytes with their own states. Like if I said "this 8bit byte tells us what food is available -> Banana, Pizza, Milk, Carrot, Pasta, Apple, Doughnut, Tomato" then if the byte was 10101001, we would know that Bananas, Milk, Pasta and Tomatoes are available. This binary number (00101001) can be split into groups of four (1010 1001) then changed to regular numbers (10 9) or hexadecimal numbers (a 9). We use hexadecimal all the time because they are smaller to write than regular numbers.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;So the worktop is a place where the worker can put bytes. This worktop only has 256 places to put bytes, and some of those places are used for other things.

For example, places 0 and 1 on the worktop are used to show which instruction on the program the worker is going to do next. The program can be longer than 256 instructions (it can be 65536 instructions infact) but a byte can only hold 256 states (256 different locations on the program) so the machine puts the two bytes together to make a 16bit byte, which can hold 65536 different states. 

Location 2 on the worktop contains the calculation indicators. Whenever the worker does work with a byte, some information about that job is written here. Only three of the bits are used to indicate things. 

    not used, not used, not used, not used, not used, Underflow, Overflow, Zero

- Zero - This indicator is set to 1 when the byte was 0 when they were done with it.
- Overflow - Means that the byte was being used in a job where it was like a number, and the byte's value grew above the maximum value
- Underflow - Means that like before, it was being used in a job where it was like a number, and that the byte's value shrunk below 0

#### Technical Machine Layout
    |----programManager-------------------------------------------------------------------| |-displayUnit---|
    | program  |----executer------------------------------------------------------------| | |               |
    |    -     | |--logicUnit--| |--accessManager-------------------------------------| | | |               |
    |    -     | |             | | |-memoryBlock-| |-consoleAccess-| |-visualDisplay-|| | | |------|--------|
    |    -     | |             | | |             | |               | |               || | |        |
    |    -     | |             | | |             | |               | |       ----------------------|
    |    -     | |             | | |             | |               | |               || | |
    |    -     | |             | | |-------------| |---------------| |---------------|| | |
    |    -     | |-------------| |----------------------------------------------------| | |
    |    -     |------------------------------------------------------------------------| |
    |-------------------------------------------------------------------------------------|

## Rua.2 Language Reference
|Command Name                           |Command    |Description                                                         |Example Usage
|:-------------------------------------:|:---------:|:------------------------------------------------------------------:|:--------
| Comment                               | //        | All text after a double slash, will be removed during compilation  | //Hello
| Include file                          | #         | A file's contents will replace this code                           | #otherFile.rr
| Tag                                   | ::        | Used with goto commands. Tags must have no spaces in them          | ::loop
| Do nothing                            | nop       | No action will be taken (useful for timing)                        | nop
| Goto tag                              | goto      | Goes to the command following the named tag                        | goto:loop
| If bit in byte is set; continue       | ifBitFlow | Tests value of a selected bit in the chosen byte. If this bit is '1' execution continues as normal. If not, the command that follows this one is skipped.| ifBitFlow:10:4
| If bit in byte is set; skip next line | ifBitSkip | Tests value of a selected bit in the chosen byte. If this bit is '0' execution continues as normal. If not, the command that follows this one is skipped.| ifBitSkip:12:4
| Clear byte                            | clear     | Sets the value of a byte to zero                                                      | clear:29
| Set byte                              | set       | Sets the value of a byte to the provided value                                        | set:20:5f
| Flip byte's bits                      | flip      | Flips the bits in a byte                                                              | flip:0a
| Increment byte                        | inc       | Adds 1 to a byte                                                                      | inc:f4
| Decrement byte                        | dec       | Subtracts 1 from a byte                                                               | dec:11
| Left rotate byte                      | lRotate   | Left rotates a byte                                                                   | lRotate:67
| Right rotate byte                     | rRotate   | Right rotates a byte                                                                  | rRotate:aa
| Copy byte into another byte           | copy      | Copies the value of one byte into another                                             | copy:30:40
| NAND byte with another byte           | nand      | Nands the bits of a byte with those of another, placing the result in the second byte | nand:40:50
| Add byte to byte                      | add       | Adds two bytes together, placing the result in the second byte                        | add:50:60

## Visual Display Guide
The two Visual Display Access Ports (address and access) are used to work with the display. The pixels are stored sequentially, and one can use the address port to select a pixel to work with. Then using the access port; one can read or modify the pixel value. The first pixel is in the top left of the screen, the last pixel is in the bottom right.

...or you can look at the address byte as two half bytes; with the first half being the Y number, and the second being X. And then you can move through the display vertically by changing the first half of the address, and horizontally by changing the second half.

The display is 16x16 pixels and can show 256 colours. Each pixel is one byte (8 bits / 2 hex numbers)

#### The Display's Memory/Pixel Layout

    00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f
    10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f
    20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f
    30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f
    40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f
    50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f
    60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f
    70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f
    80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
    90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f
    a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af
    b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf
    c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf
    d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 da db dc dd de df
    e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eb ec ed ee ef
    f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fb fc fd fe ff
    
## Console Guide
The console can be used to print messages to the user, or take in values. When you attempt to read a byte or bit from the console port, execution will stop and the console will ask the user to enter a byte (in hex) or bit (as a 1 or 0). Writing a bit to the port prints a 1 or 0 to the console. Writing a byte is more complicated.

When you write a byte, the corresponding ASCII character is printed to the console. All the available symbols are shown below.

#### Console Character Codes
| number | code | symbol
|:------:|:----:|:-------:
| 1      |  01  | NUL (null)
| 2      |  02  | SOH (start of header)
| 3      |  03  | STX (start of text)
| 4      |  04  | ETX (end of text)
| 5      |  05  | ENQ (enquiry)
| 6      |  06  | ACK (acknowledge)
| 7      |  07  | BEL (bell)
| 8      |  08  | BS (baskspace)
| 9      |  09  | HT (horizontal tab)
| 10     |  0a  | LF (line feed/new line)
| 11     |  0b  | VT (vertical tab)
| 12     |  0c  | FF (form feed / new page)
| 13     |  0d  | CR (carriage return)
| 14     |  0e  | SO (shift out)
| 15     |  0f  | SI (shift in)
| 16     |  10  | DLE (data link escape)
| 17     |  11  | DC1 (data control 1)
| 18     |  12  | DC2 (data control 2)
| 19     |  13  | DC3 (data control 3)
| 20     |  14  | DC4 (data control 4)
| 21     |  15  | NAK (negative acknowledge)
| 22     |  16  | SYN (synchronous idle)
| 23     |  17  | ETB (end of transmission block)
| 24     |  18  | CAN (cancel)
| 25     |  19  | EM (end of medium)
| 26     |  1a  | SUB (substitute)
| 27     |  1b  | ESC (escape)
| 28     |  1c  | FS (file separator)
| 29     |  1d  | GS (group separator)
| 30     |  1e  | RS (record separator)
| 31     |  1f  | US (unit separator)
| 32     |  20  | (space)
| 33     |  21  | !
| 34     |  22  | "
| 35     |  23  | #
| 36     |  24  | $
| 37     |  25  | %
| 38     |  26  | &
| 39     |  27  | '
| 40     |  28  | (
| 41     |  29  | )
| 42     |  2a  | *
| 43     |  2b  | +
| 44     |  2c  | ,
| 45     |  2d  | -
| 46     |  2e  | .
| 47     |  2f  | /
| 48     |  30  | 0
| 49     |  31  | 1
| 50     |  32  | 2
| 51     |  33  | 3
| 52     |  34  | 4
| 53     |  35  | 5
| 54     |  36  | 6
| 55     |  37  | 7
| 56     |  38  | 8
| 57     |  39  | 9
| 58     |  3a  | :
| 59     |  3b  | ;
| 60     |  3c  | <
| 61     |  3d  | =
| 62     |  3e  | >
| 63     |  3f  | ?
| 64     |  40  | @
| 65     |  41  | A
| 66     |  42  | B
| 67     |  43  | C
| 68     |  44  | D
| 69     |  45  | E
| 70     |  46  | F
| 71     |  47  | G
| 72     |  48  | H
| 73     |  49  | I
| 74     |  4a  | J
| 75     |  4b  | K
| 76     |  4c  | L
| 77     |  4d  | M
| 78     |  4e  | N
| 79     |  4f  | O
| 80     |  50  | P
| 81     |  51  | Q
| 82     |  52  | R
| 83     |  53  | S
| 84     |  54  | T
| 85     |  55  | U
| 86     |  56  | V
| 87     |  57  | W
| 88     |  58  | X
| 89     |  59  | Y
| 90     |  5a  | Z
| 91     |  5b  | [
| 92     |  5c  | \
| 93     |  5d  | ]
| 94     |  5e  | ^
| 95     |  5f  | _
| 96     |  60  | `
| 97     |  61  | a
| 98     |  62  | b
| 99     |  63  | c
| 100    |  64  | d
| 101    |  65  | e
| 102    |  66  | f
| 103    |  67  | g
| 104    |  68  | h
| 105    |  69  | i
| 106    |  6a  | j
| 107    |  6b  | k
| 108    |  6c  | l
| 109    |  6d  | m
| 110    |  6e  | n
| 111    |  6f  | o
| 112    |  70  | p
| 113    |  71  | q
| 114    |  72  | r
| 115    |  73  | s
| 116    |  74  | t
| 117    |  75  | u
| 118    |  76  | v
| 119    |  77  | w
| 120    |  78  | x
| 121    |  79  | y
| 122    |  7a  | z
| 123    |  7b  | {
| 124    |  7c  | |
| 125    |  7d  | }
| 126    |  7e  | ~
| 127    |  7f  | DEL (delete)
| 128    |  80  | prints: "riomhaireRua"
| 129    |  81  | ? (unused)
| 130    |  82  | ? (unused)
| 131    |  83  | ? (unused)
| 132    |  84  | ? (unused)
| 133    |  85  | ? (unused)
| 134    |  86  | ? (unused)
| 135    |  87  | ? (unused)
| 136    |  88  | ? (unused)
| 137    |  89  | ? (unused)
| 138    |  8a  | ? (unused)
| 139    |  8b  | ? (unused)
| 140    |  8c  | ? (unused)
| 141    |  8d  | ? (unused)
| 142    |  8e  | ? (unused)
| 143    |  8f  | ? (unused)
| 144    |  90  | ? (unused)
| 145    |  91  | ? (unused)
| 146    |  92  | ? (unused)
| 147    |  93  | ? (unused)
| 148    |  94  | ? (unused)
| 149    |  95  | ? (unused)
| 150    |  96  | ? (unused)
| 151    |  97  | ? (unused)
| 152    |  98  | ? (unused)
| 153    |  99  | ? (unused)
| 154    |  9a  | ? (unused)
| 155    |  9b  | ? (unused)
| 156    |  9c  | ? (unused)
| 157    |  9d  | ? (unused)
| 158    |  9e  | ? (unused)
| 159    |  9f  | ? (unused)
| 160    |  a0  | ? (unused)
| 161    |  a1  | ? (unused)
| 162    |  a2  | ? (unused)
| 163    |  a3  | ? (unused)
| 164    |  a4  | ? (unused)
| 165    |  a5  | ? (unused)
| 166    |  a6  | ? (unused)
| 167    |  a7  | ? (unused)
| 168    |  a8  | ? (unused)
| 169    |  a9  | ? (unused)
| 170    |  aa  | ? (unused)
| 171    |  ab  | ? (unused)
| 172    |  ac  | ? (unused)
| 173    |  ad  | ? (unused)
| 174    |  ae  | ? (unused)
| 175    |  af  | ? (unused)
| 176    |  b0  | ? (unused)
| 177    |  b1  | ? (unused)
| 178    |  b2  | ? (unused)
| 179    |  b3  | ? (unused)
| 180    |  b4  | ? (unused)
| 181    |  b5  | ? (unused)
| 182    |  b6  | ? (unused)
| 183    |  b7  | ? (unused)
| 184    |  b8  | ? (unused)
| 185    |  b9  | ? (unused)
| 186    |  ba  | ? (unused)
| 187    |  bb  | ? (unused)
| 188    |  bc  | ? (unused)
| 189    |  bd  | ? (unused)
| 190    |  be  | ? (unused)
| 191    |  bf  | ? (unused)
| 192    |  c0  | ? (unused)
| 193    |  c1  | ? (unused)
| 194    |  c2  | ? (unused)
| 195    |  c3  | ? (unused)
| 196    |  c4  | ? (unused)
| 197    |  c5  | ? (unused)
| 198    |  c6  | ? (unused)
| 199    |  c7  | ? (unused)
| 200    |  c8  | ? (unused)
| 201    |  c9  | ? (unused)
| 202    |  ca  | ? (unused)
| 203    |  cb  | ? (unused)
| 204    |  cc  | ? (unused)
| 205    |  cd  | ? (unused)
| 206    |  ce  | ? (unused)
| 207    |  cf  | ? (unused)
| 208    |  d0  | ? (unused)
| 209    |  d1  | ? (unused)
| 210    |  d2  | ? (unused)
| 211    |  d3  | ? (unused)
| 212    |  d4  | ? (unused)
| 213    |  d5  | ? (unused)
| 214    |  d6  | ? (unused)
| 215    |  d7  | ? (unused)
| 216    |  d8  | ? (unused)
| 217    |  d9  | ? (unused)
| 218    |  da  | ? (unused)
| 219    |  db  | ? (unused)
| 220    |  dc  | ? (unused)
| 221    |  dd  | ? (unused)
| 222    |  de  | ? (unused)
| 223    |  df  | ? (unused)
| 224    |  e0  | ? (unused)
| 225    |  e1  | ? (unused)
| 226    |  e2  | ? (unused)
| 227    |  e3  | ? (unused)
| 228    |  e4  | ? (unused)
| 229    |  e5  | ? (unused)
| 230    |  e6  | ? (unused)
| 231    |  e7  | ? (unused)
| 232    |  e8  | ? (unused)
| 233    |  e9  | ? (unused)
| 234    |  ea  | ? (unused)
| 235    |  eb  | ? (unused)
| 236    |  ec  | ? (unused)
| 237    |  ed  | ? (unused)
| 238    |  ee  | ? (unused)
| 239    |  ef  | ? (unused)
| 240    |  f0  | ? (unused)
| 241    |  f1  | ? (unused)
| 242    |  f2  | ? (unused)
| 243    |  f3  | ? (unused)
| 244    |  f4  | ? (unused)
| 245    |  f5  | ? (unused)
| 246    |  f6  | ? (unused)
| 247    |  f7  | ? (unused)
| 248    |  f8  | ? (unused)
| 249    |  f9  | ? (unused)
| 250    |  fa  | ? (unused)
| 251    |  fb  | ? (unused)
| 252    |  fc  | ? (unused)
| 253    |  fd  | ? (unused)
| 254    |  fe  | ? (unused)
| 255    |  ff  | ? (unused)