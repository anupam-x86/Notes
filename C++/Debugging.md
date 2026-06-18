# Debugging
## Chapter 3 — learncpp

---

## 3.1 — Syntax and Semantic Errors

**Syntax error** — violates grammar rules of the language. Compiler catches it, won't compile.
```cpp
int x = 5  // missing semicolon → syntax error
```

**Semantic error** — code is grammatically valid, compiles fine, but produces wrong/undefined behavior.
```cpp
int a = 10, b = 0;
std::cout << a / b;  // compiles fine, UB at runtime (division by zero)
```

Semantic errors are harder because the compiler gives no warning — the program looks correct on the surface.

---

## 3.2 — The Debugging Process

General debugging loop:
```
1. Understand the problem
2. Determine a fix
3. Repair the issue
4. Retest
```

Skipping step 1 (understanding) and jumping straight to random changes often creates new bugs instead of fixing the original one.

---

## 3.3 — A Strategy for Debugging

### Reproduction Steps
A precise set of steps that reliably triggers the bug. The more reproducible (ideally 100%), the easier to diagnose.

```
100% reproducible → easy to debug, every test run gives info
50% reproducible  → twice as slow to debug, half the runs give nothing
```

### UB and Reproducibility
C++ undefined behavior makes some bugs inconsistently reproducible — may crash on one machine, not another; in debug build but not release; sometimes but not always. This is a key reason C++ bugs can be harder than Python bugs (Python fails loudly and consistently — exceptions; C++ UB fails unpredictably).

### Narrowing Down the Bug
Same principle as binary search — narrow down the location of a bug by checking midpoints rather than checking every line sequentially.

---

## 3.4 — Basic Debugging Tactics

### Tactic 1: Commenting out code
Temporarily disable sections to isolate where a bug is. `#if 0` is a cleaner alternative to commenting since C++ comments don't nest.

### Tactic 2: Print/output statements
Add temporary debug output to trace program flow and variable values.

**Problems with this approach:**
1. Clutters code
2. Clutters output
3. Requires modification to add/remove — can introduce new bugs
4. Must be removed when done — not reusable

### Use std::cerr, not std::cout, for debug output
- `std::cout` is **buffered** — output may be delayed; if program crashes before flush, you lose that output and get a misleading picture of where it died
- `std::cerr` is **unbuffered** — outputs immediately, accurate picture even right before a crash
- Also signals "this is debug/error info" not normal output

```cpp
std::cerr << "reached function X\n";  // immediate, safe for debugging
```

Python has the same buffering issue — use `print(..., flush=True)` or `sys.stderr` for the same effect.

### Tactic 3: Conditionalizing debug code (#ifdef)
```cpp
#ifdef DEBUG
    std::cerr << "x = " << x << '\n';
#endif
```
Compile with `-DDEBUG` to enable, omit to disable completely (zero runtime cost in release).

`-D` is the compiler flag meaning "define this macro" — `-DDEBUG` is shorthand for `#define DEBUG` passed from the command line.

**Downsides:** still clutters code, typo in macro name (e.g. `DEUBG`) silently disables debugging with no error.

### Tactic 4: Logging
Writing timestamped records of program events to a separate log file, instead of mixing debug output with normal program output.

**Advantages:**
- Separated from program output — no clutter
- Persistent — can be reviewed later
- Shareable — users can send log files to help diagnose issues they hit in production

`std::clog` exists in C++ but defaults to stderr; for real file logging, third-party libraries are typically used.

**plog** — example header-only logging library:
```cpp
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

plog::init(plog::debug, "Logfile.txt");
PLOGD << "debug message";  // D = Debug level
PLOGI << "info message";   // I = Info
PLOGW << "warning message"; // W = Warning
PLOGE << "error message";  // E = Error
PLOGF << "fatal message";  // F = Fatal
```
"Rolling" file = creates new log file when current one gets too large, preventing disk space issues on long-running programs.

Header-only library — just point compiler to include directory:
```bash
g++ main.cpp -I/path/to/plog-master/include
```

Logging serves two audiences: developers (tracing bugs during development) and production/clients (diagnosing issues without direct access to the system, monitoring, audit trails).

---

## 3.5 — More Debugging Tactics

`std::unitbuf` — forces `std::cout` to flush immediately after every output, similar effect to `cerr`, useful for debugging:
```cpp
std::cout << std::unitbuf; // enable automatic flushing (debug only — remove for release, has perf cost)
```
Usually wrapped in `#ifdef DEBUG` so it's automatically excluded from release builds.

---

## 3.6 — Using an Integrated Debugger: Stepping

### What a Debugger Does
A program that lets you control execution of another program and examine its state while running. Two core powers:
1. **Control execution** — run line by line, pause anywhere
2. **Inspect state** — view (and modify) variable values at any point

### Types of Debuggers
- **CLI** — e.g. `gdb`, type commands, available even without GUI (embedded systems)
- **Integrated (IDE)** — graphical frontend, e.g. VSCode's debugger (built on gdb underneath on Linux)

### VSCode Setup (Fedora)
Requires `g++` and `gdb` installed (check with `g++ --version` / `gdb --version`).

1. Install "C/C++" extension by Microsoft in VSCode
2. Ctrl+Shift+P → "Tasks: Configure Default Build Task" → "C/C++: g++ build active file" (creates `.vscode/tasks.json`)
3. Open a `.cpp` file → press F5 → select "C++ (GDB/LLDB)" → "g++ build and debug active file" (creates `.vscode/launch.json`)
4. Click left of a line number to set a breakpoint (red dot)
5. Press F5 to start debugging — execution pauses at breakpoint

### Stepping Commands
```
F5            → Continue (run until next breakpoint)
F10           → Step Over (run current line, move to next — does NOT enter function calls)
F11           → Step Into (enters the function being called on this line)
Shift+F11     → Step Out (finish current function, return to caller)
Shift+F5      → Stop debugging
```

**Rule of thumb:** Use Step Over (F10) for standard library calls (`cout`, `cin`) — stepping into them takes you into library source code, which is rarely useful. Use Step Into (F11) only for your own functions.

If you accidentally step into a library function (e.g. `operator<<`), use Step Out (Shift+F11) to return.

### Step Too Far
No simple "rewind" in basic stepping — if you overstep your target line, the usual approach is to stop and restart debugging. (Some debuggers like gdb support `reverse-step` / `reverse-next` via `record` mode, but this isn't commonly exposed in IDEs like VSCode.)

### Why Learn This
Debugging via print statements doesn't scale. Time invested learning the debugger is small compared to time saved finding bugs in larger programs later.

---

## 3.7 — Using an Integrated Debugger: Running and Breakpoints

### Set Next Statement
Changes the point of execution to any line, WITHOUT running the code in between and WITHOUT changing program state. Variables keep whatever value they had before the jump.

```cpp
int x {};        // line 1
x = 5;           // line 2
std::cout << x;  // line 3 ← jump here from line 1, x is still 0, not 5
```

Risky, especially jumping backwards — program state may not match what it "should" be at that point in normal execution. Use judiciously.

### Step Back vs Set Next Statement (jumping backwards)
| | Step Back | Set Next Statement (backwards) |
|---|---|---|
| Execution pointer | moves back | moves back |
| Variable/program state | fully reverted (true undo) | unchanged — stays as it was before the jump |

Step Back = genuine reverse debugging (not always available — expensive to implement).
Set Next Statement = only moves the "cursor," state can become inconsistent.

---

## 3.8 — Watching Variables
Add variables to a "Watch" panel in the debugger to see their values update live while stepping through code. Can also hover over a variable while paused to see its current value.

---

## 3.9 — The Call Stack
Shows the chain of function calls that led to the current point of execution:
```
main() → getUserInput() → validateInput()  ← currently here
```
Useful for understanding how you arrived at the current point, especially in deeply nested function calls. Click any frame in the call stack to inspect that function's local variables and context.

---

## 3.10 — Finding Issues Before They Become Problems
General principle: catching bugs earlier (via good practices, warnings-as-errors, careful coding) is cheaper than finding them later through debugging. Connects back to good program structure and understanding flow before coding (covered earlier — what is the program for, who is the user, how does data flow).

---

## Quick Reference — Debugging Toolbox (least to most powerful)
```
Comment out code / #if 0   → isolate sections
print/cerr statements      → manual tracing
#ifdef DEBUG                → conditional, reusable, zero release cost
Logging (file-based)        → persistent, shareable, production-friendly
Integrated debugger         → most powerful: breakpoints, stepping, inspect state, call stack
```
