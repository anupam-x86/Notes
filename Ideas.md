# Project Ideas

## (1) Smart Code Search / Symbol Finder

**One line:** A lightweight code-intelligence engine that parses C++ projects, maintains a symbol index, ranks results using heuristics and learned behavior, and provides near-instant search without rescanning the entire codebase every query.

**Target level:** Ch 15-20 of learncpp

### Core Architecture
```
Project Files
↓
File Watcher (detects changes)
↓
Parser (extracts symbols)
↓
Symbol Index (HashMap based)
↓
Search Query → Ranking Engine → Results
```

### Key Concepts Involved
- HashMaps, indexing, ranking/scoring
- Incremental updates
- Cold start problem
- RAG-like retrieval

### UI
TUI (Terminal User Interface) using `ftxui` or `ncurses` — dynamic results, arrow key navigation, live search

### Optimizations
- Incremental reindexing (only reparse modified files)
- Priority ranking over hard filtering
- Usage-based learning (with static analysis as primary, learning as secondary)

### Version Roadmap
- **V1** → Find symbol names fast
- **V2** → References, definitions, rename symbols
- **V3** → Semantic search ("inventory system" finds items/loot/equipment)
- **V4** → AI assisted search

### Resources
- [ftxui](https://github.com/ArthurSonzogni/FTXUI) — Modern C++ TUI library
- [ncurses](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/) — Classic TUI library
- [clangd](https://clangd.llvm.org) — Inspiration / reference

---

## Expense Tracker CLI (C++ Rebuild)

**One line:** Rebuild of Python/MySQL expense tracker in C++ using JSON storage — a known project in a new language.

**Target level:** Ch 8-10 of learncpp

### Storage
JSON via `nlohmann/json` library — existing `data.json` structure as reference

### Features
- Add / remove / filter expenses
- Filter by date, amount, category, payee, payment mode
- Export / backup
- Budget management

### Why this project
- Already built in Python so logic is known — focus is on C++ not problem solving
- File I/O is a core Ch 8 skill
- Can be made showcase-worthy this time (complete, README, no hardcoded credentials)

### Resources
- [nlohmann/json](https://github.com/nlohmann/json) — JSON library for C++

---

## Audio System with Self-Made Library

**Status:** Long term / post-college idea

**One line:** A C++ audio system with a self-made abstraction library over ALSA (Linux audio), and potentially a custom driver.

**Target level:** Post degree, 2-3 years experience minimum

### Research Path
- Understand audio digitally first (sample rate, bit depth, buffers)
- Experiment with Audacity to understand params
- Read ALSA documentation
- Study laptop hardware audio system

### Key Concepts to Understand First
- Digital audio basics (44.1kHz, 16bit, channels)
- Buffer management and latency
- ALSA (Advanced Linux Sound Architecture)
- Threading (audio runs on separate thread)
- Linux kernel modules (for driver)

### Note
Driver level = kernel programming in C, not C++. One wrong pointer = kernel panic.
