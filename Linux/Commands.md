# Linux Commands

This file contains Linux commands that I have learned, their purpose, and examples of how to use them.

---

# pwd

## Purpose

Print the current working directory.

Shows where I currently am in the filesystem.

## Example

```bash
pwd
```

Output:

```text
/home/omega_089
```

---

# ls

## Purpose

List files and folders.

## Examples

### List files

```bash
ls
```

### Detailed list

```bash
ls -l
```

### Show hidden files

```bash
ls -a
```

### Detailed list including hidden files

```bash
ls -la
```

---

# cd

## Purpose

Change directory.

## Examples

### Enter a folder

```bash
cd Downloads
```

### Go back one level

```bash
cd ..
```

### Go to home directory

```bash
cd ~
```

### Go to root directory

```bash
cd /
```

---

# mkdir

## Purpose

Create a directory.

## Example

```bash
mkdir Projects
```

Creates:

```text
Projects/
```

---

# touch

## Purpose

Create an empty file.

## Example

```bash
touch notes.txt
```

Creates:

```text
notes.txt
```

---

# clear

## Purpose

Clear the terminal screen.

## Example

```bash
clear
```

Shortcut:

```text
Ctrl + L
```

---

# cat

## Purpose

Display file contents.

## Example

```bash
cat notes.txt
```

---

# cp

## Purpose

Copy files and directories.

## Examples

### Copy file

```bash
cp file1.txt file2.txt
```

### Copy directory

```bash
cp -r Folder Backup
```

---

# mv

## Purpose

Move or rename files.

## Examples

### Rename file

```bash
mv old.txt new.txt
```

### Move file

```bash
mv file.txt Documents/
```

---

# rm

## Purpose

Delete files and directories.

## Examples

### Delete file

```bash
rm file.txt
```

### Delete directory

```bash
rm -r Folder
```

## Warning

Deleted files usually cannot be recovered.

Use carefully.

---

# sudo

## Purpose

Run commands with administrator privileges.

## Example

```bash
sudo dnf update
```

## What I Learned

Normal users have limited permissions.

sudo temporarily grants elevated privileges.

---

# man

## Purpose

Open manual pages for commands.

## Example

```bash
man ls
```

Exit manual:

```text
q
```

---

# history

## Purpose

Show previously executed commands.

## Example

```bash
history
```

---

# uname

## Purpose

Display system information.

## Example

```bash
uname -r
```

Output:

```text
Kernel Version
```

---

# free

## Purpose

Display memory usage.

## Example

```bash
free -h
```

---

# df

## Purpose

Display disk usage.

## Example

```bash
df -h
```

---

# Important Locations

## Home Directory

```text
~
```

Example:

```text
/home/omega_089
```

---

## Root Directory

```text
/
```

Top-level directory of Linux.

---

# Notes

Linux commands are case-sensitive.

Example:

```text
Downloads
```

is different from:

```text
downloads
```

---

# Lessons Learned

* Linux can be controlled entirely from the terminal.
* Commands usually follow a simple structure:

```text
command [options] [arguments]
```

Example:

```bash
ls -la
```

where:

* ls = command

* -la = options

* The terminal becomes faster and more powerful as command knowledge grows.

* Understanding commands is more useful than memorizing large command lists.
