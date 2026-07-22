# pipex

A C recreation of shell piping (`cmd1 | cmd2`) between two commands, built together with `ychattou`. It reimplements what the shell does when you run `< file1 cmd1 | cmd2 > file2`, using low-level Unix process/file-descriptor calls directly instead of relying on the shell.

## What it does

Run as:

```bash
./pipex file1 cmd1 cmd2 file2
```

which is equivalent to:

```bash
< file1 cmd1 | cmd2 > file2
```

Internally:

1. **`main.c`** validates the argument count (exactly 4 arguments expected) and creates a pipe (`pipe(fd)`) plus a child process (`fork`).
2. **`child_process.c`** (the child): opens `file1` read-only, redirects it to `stdin`, redirects the pipe's write end to `stdout`, closes the unused pipe end, then executes `cmd1`.
3. **`parent_process.c`** (the parent, after waiting on the child): opens `file2` for writing (creating/truncating it), redirects it to `stdout`, redirects the pipe's read end to `stdin`, then executes `cmd2`.
4. **`command_exec.c`** splits a command string into arguments and runs it via `execve`.
5. **`pathfinder.c`** resolves the command name against the directories listed in the `PATH` environment variable (mimicking how a shell finds executables), returning the first matching absolute path.
6. A small set of custom libc-like helpers (`ft_split`, `ft_strjoin`, `ft_strlen`, `ft_strnstr`, `ft_putstr_fd`) support string handling and error reporting, since the project avoids relying on non-standard convenience functions.

## Project structure

```
pipe/
├── include/
│   └── pipex.h            # struct-free prototypes for the whole project
├── srcs/
│   ├── main.c              # arg parsing, pipe + fork setup
│   ├── child_process.c     # infile → cmd1 → pipe write end
│   ├── parent_process.c    # pipe read end → cmd2 → outfile
│   ├── command_exec.c      # splits a command string and execve()s it
│   ├── pathfinder.c        # resolves a command against $PATH
│   ├── ft_split.c / ft_strjoin.c / ft_strlen.c / ft_strnstr.c / ft_putstr_fd.c
└── Makefile
```

## Building and running

```bash
make
./pipex infile "cmd1 with args" "cmd2 with args" outfile
```

Example:

```bash
./pipex infile "grep foo" "wc -l" outfile
# equivalent to: < infile grep foo | wc -l > outfile
```

## Notes

- Commands are executed directly via `fork`/`execve` — no `system()` or shell delegation.
- Only handles a single pipe between exactly two commands (no support for chains of more than two, or for `here_doc`/append-mode variants sometimes added as a bonus to this project).
- Errors (missing file, unresolved command, failed `fork`/`pipe`) are reported to `stderr` and exit the program, mirroring how a shell reports a failed pipeline stage.
