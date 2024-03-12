# Get Next Line (GNL)

Welcome to Get Next Line (GNL)! This project focuses on creating a function that reads a line from a file descriptor. The function should be able to handle reading from multiple file descriptors without losing the reading thread on each of them. By completing this project, you'll enhance your understanding of file manipulation and dynamic memory allocation in C programming.

## Table of Contents

1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Function Description](#function-description)
4. [Building](#building)
5. [Contributing](#contributing)
6. [Credits](#credits)

## Introduction

The Get Next Line (GNL) function reads a line from a file descriptor (such as standard input, a file, or a network socket) and stores it in a buffer. It's capable of handling various line endings (e.g., `\n`, `\r\n`, or EOF) and supports reading from multiple file descriptors without blocking other file descriptors.

## Usage

To use the GNL function in your projects, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/adrgonza/get_next_line.git
    ```

2. Include the `get_next_line.h` header file in your source code:

    ```c
    #include "get_next_line.h"
    ```

3. Call the `get_next_line` function with the file descriptor you want to read from:

    ```c
    static char	*rem_txt;
    char		*line;
    char		buffer[BUFFER_SIZE + 1];
    int			i;

    while (1)
	  {
		  i = read(fd, buffer, BUFFER_SIZE);
		  if (i == -1)
			  return (free(rem_txt), rem_txt = NULL);
		  buffer[i] = 0;
		  rem_txt = concat_rem(rem_txt, buffer, 0, 0);
		  if (!rem_txt)
			  return (free(rem_txt), rem_txt = NULL);
		  if (i == 0)
			  break ;
		  i = -1;
		  while (buffer[++i] && buffer[i] != '\n')
			  if (buffer[i + 1] == '\n')
				  return (line = NULL, var_manage(line, &rem_txt, 0, 0));
	  }
	  if (!*rem_txt)
		  return (free(rem_txt), rem_txt = NULL);
	  return (line = NULL, var_manage(line, &rem_txt, 0, 0));
    ```

## Function Description

The `get_next_line` function reads a line from the specified file descriptor and stores it in the memory address pointed to by the `line` parameter. The function returns `1` if a line has been read, `0` if the end of file (EOF) has been reached, and `-1` if an error occurs.

## Building

To build the Get Next Line function, simply run:

```bash
make
```

## Contributing
Contributions are welcome! If you find any bugs or have suggestions for improvement, please open an issue or submit a pull request on GitHub.

## Credits
This project was created by adrgonza for the get_next_line project at 42Madrid.
