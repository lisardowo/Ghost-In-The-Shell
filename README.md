# DVshell - DAMN Vulnerable Shell

> A linux shell intentionally vulnerable to practice cybersecurity, pentesting and anlysis of C code

---

## Disclaimer

This code contains intentionally introduced vulnerabilities. DO NOT, BY ANY MEANS use this program in production neither expose it to the internet. Use it just in your own, controlled local environment

---

## But, what is this?

DVShell is a vulnerable version of [GIshell](https://github.com/lisardowo/Ghost-In-The-Shell.git), my own linux shell written from scratch. As you should already notice `main` branch contains the good, patched and audited code. The branch you are currently in (`DamnVulnerableShell`) I on purpose took some steps backs in this patches in order to introduce vulnerabilities organized by difficulty/expertise needed.

The objective is that YOU, user, can practice real techniques of exploitation/pentesting in a production environment. No abstract exercises, no artificial vulnerabilites just actual, simple, bugs that real software can have (most of the vulnerabilities here are some bugs that I had while developing the original branch)

---

## Setup 

### Dependencies

 * makefile
 * gcc
 * gdb
 * valgrind

 # recommended for level 2+
 * python
 * pwntools
 * checksec

### Compiling

# No protection - if you're new to pentesting, this is where you start

make easy

# ASLR active, not canary - You feel comfortable with the problems?, then is moment to be a big boy

make hard

# All modern protection - You want some real challenges? try breaking code compiled with all modern securities

make expert

# This is an utility module to see protection levels of each binary 

make verify

## Vulnerabilities

For each vulnerability, theres an Issue in this repository with hints, and solutions. Open the issue only if you need it

Behind is all known vulnerabilites to this day, if you found another and want to contribute, please refeer to [contributing][contributing.md]

