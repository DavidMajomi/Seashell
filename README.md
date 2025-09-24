# Sea Shell - Man Page

## NAME
**Sea Shell** - a simple command-line shell with basic file system manipulation commands

## DESCRIPTION
**Sea Shell** is a basic command-line shell program that allows users to interact with the file system. It supports a subset of commands similar to typical UNIX shell commands, including:
- `cd`: Change the current working directory.
- `pwd`: Print the current working directory.
- `ls`: List the contents of the current directory.
- `mkdir`: Create a new directory.
- `rmdir`: Remove an empty directory.
- `help`: Display help information for available commands.

This shell can be extended with additional commands if needed. It implements error handling for various commands and provides feedback when invalid commands or arguments are encountered.

## COMMANDS

### `help [command]`
Prints help information for the given command or a list of all available commands.

- **Description:**
Displays the help message describing the usage of each command. If no argument is passed, it will list the available commands. If a command is provided, it will give a detailed description of how to use that command.

### `cd <directory>`
Changes the current working directory.

- **Usage:**

- **Description:**
- If no directory is specified, the shell changes to the user's home directory.
- If the argument is `..`, it will change to the parent directory.
- If an invalid directory is provided or if permission is denied, an appropriate error message will be displayed.

### `pwd`
Prints the absolute path of the current working directory.

- **Usage:**

- **Description:**
Displays the current working directory. If there is an error, an error message is displayed.

### `ls`
Lists the contents of the current directory.

- **Description:**
Lists all files and directories in the current working directory. If the current directory cannot be opened, an error message is displayed.

### `mkdir <directory>`
Creates a new directory.

- **Description:**
- Creates a directory with the specified name.
- If the directory already exists or if an error occurs, an error message will be displayed.

### `rmdir <directory>`
Removes an empty directory.

- **Description:**
- Removes the specified empty directory.
- If the directory is not empty or does not exist, an error message will be displayed.


## FILES
- **No external files** are used by this shell, as it operates entirely within the user's current environment and interacts with the file system through system calls like `chdir`, `getcwd`, `opendir`, etc.



## LICENSE
This software is released under the MIT License.
