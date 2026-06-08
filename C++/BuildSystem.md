# Build System Terminology

## Compile

Recompiles a single source file.

```text
main.cpp
↓
Compiler
↓
main.o
```

* Produces object files (`.o`)
* Does NOT link
* Does NOT create an executable

---

## Build

Compiles all modified source files and then links them.

```text
main.cpp
math.cpp
↓
Compile
↓
main.o
math.o
↓
Linker
↓
Executable
```

* Produces the final executable
* Skips files that haven't changed since the last build

---

## Clean

Removes generated build files.

Deletes things like:

```text
.o files
executables
temporary build files
```

Keeps:

```text
.cpp files
.h files
```

Purpose:

```text
Force a completely fresh build next time.
```

---

## Rebuild

Performs:

```text
Clean
↓
Build
```

Equivalent mental model:

```text
Delete everything generated
↓
Compile everything again
↓
Link again
```

Useful when build files become outdated or corrupted.

---

## Run / Start

Executes the program.

```text
Executable
↓
Operating System
↓
Program Runs
```

Some IDEs automatically perform:

```text
Build
↓
Run
```

before starting the program.

Others simply run the last built executable.

---

# Mental Model

```text
Compile
↓
Object Files

Build
↓
Compile + Link

Clean
↓
Delete Build Files

Rebuild
↓
Clean + Build

Run
↓
Execute Program
```
