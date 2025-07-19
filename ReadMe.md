# Signal Parser Program

## Overview
Signal Parser is a simple C-based state machine parser for AT command-like protocols, designed to read and process character streams from devices or command line interfaces. It can handle both complete command responses and structured outputs, making it suitable for embedded systems or communication modules that use such protocols.

## Main Features
- Detects valid \r\nOK\r\n and \r\nERROR\r\n command responses.
- Supports multi-line structured outputs (e.g., +CMD:VALUE\r\n).
- Handles streamed character input, one byte at a time.
- Recognizes and reports malformed or incomplete sequences.
- Aggregates valid lines into a fixed-size matrix buffer.


## Structure of the test files:
The test files should contain lines of text that simulate the output of a device or command line interface. Each line can represent a command response, structured data, or error messages. The parser will read these lines and process them according to the defined rules.
Example of a test file (`test_signal.txt`):
```
\r\nOK\r\n
\r\nERROR\r\n
\r\n+CMD:TEST1\r\n\r\n+CMD:TEST2\r\n\r\nOK\r\n
\r\n+BAD?DATA\r
\r\nOK\n
```

## How to run the program
### Linux
``` bash
Compile: 
gcc -Wall -o signal_parser main.c parser.c ./signal_parser test_signal.txt

Execute:
./signal_parser test_signal.txt

```
### Windows
```bash
Compile:
cl /W4 /Fe:program.exe main.c parser.c

Execute:
program.exe test_signal.txt
```

