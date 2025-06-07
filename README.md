# mygit

I worked on a project at Intel where I was heavily involved with extending
git. The product's purpose was primarily to improve the possibilities to
aggregate git projects and use binary data, in a similar way to the Android
team's repo tool, but in Java instead of in Python.

I wanted to:
* extend my knowledge of git
* get some more practice with Modern C++
by writing a git client from first principles.

## Problem statement

`mygit` is a minimal Git client implemented from scratch. The goal is to
understand the internal mechanics of Git by re‑implementing a few core
commands in C++. Rather than replacing Git, this project serves as a learning
vehicle and a demonstration of how Git objects are created and read.

**Why create another Git client?**

* To gain a practical understanding of Git internals by writing them in C++.
* To demonstrate how common Git commands work under the hood.

## Quick start

Clone the repository and build the tool:
```bash
make
```

Hash a file:
```bash
./mygit hash-object <file>
```

This prints the file's SHA-1, mirroring Git's `hash-object` command.

## Current functionality

Implemented commands:

* `hash-object` – create a Git blob from a file and print its SHA‑1.
* `cat-file` – read and optionally decompress an object by SHA‑1.

These commands provide the very basics for working with Git objects. Features
such as commits, branches, or a full object database are not yet implemented.
`hash-object` only handles a single file and always writes output to stdout. The
`cat-file` implementation can output blob contents but lacks many options of the
real Git command.

Planned features are limited to expanding existing commands and experimenting
with additional plumbing operations. `mygit` is intentionally small and will not
attempt to match all of Git's functionality.

## Development status

This project is an early prototype. Only a few plumbing commands work, so expect missing features and potential bugs.

## Setup

### Prerequisites

* `make` and `g++`
* OpenSSL development libraries (for SHA‑1)
* `zlib` development libraries (for object compression)

Make sure these packages are installed **before** building. If you are using a
package manager, install the development headers for both OpenSSL and zlib and
verify the tools were added to the system by running `openssl version` and
`zlib-flate -help`.

### Build

```bash
make
```

This produces a `mygit` binary in the repository root.

## Usage

```bash
./mygit hash-object <file>
./mygit cat-file <sha>
```

The examples mirror the real Git commands but are limited to the small feature
set implemented here.
