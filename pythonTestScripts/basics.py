"""echo hello
echo hello world
type echo
type ls
comando_invalido_xyz
exit 0"""

from doctest import master
import os
import pty
import re
import json
import time
import select
from pathlib import Path



def deleteAnsi(text):
    return re.sub(r"\x1b\[[0-9;?]*[ -/]*[@-~]", "", text)

def read(masterFileDescriptor, timeout):
    
    chunks = []
    end = time.time() + timeout

    while time.time() < end:
        remaining = max(0.0, end - time.time())
        r, _, _ = select.select([masterFileDescriptor], [], [], remaining)
        if not r:
            break
        try:
            data = os.read(masterFileDescriptor, 4096) 
        except OSError:
            break
        if not data:
            break
        chunks.append(data.decode("utf-8", errors="replace"))
    
    return "".join(chunks)

def writeToTerminal(masterFileDescriptor, string):
    os.write(masterFileDescriptor, string.encode("utf-8"))

def runShell(shell_path: Path, commands: list[str]) -> tuple[str, int]:
    pid, master_fd = pty.fork()

    if pid == 0:
        
        os.execv(str(shell_path), [str(shell_path)])

    output = []
    try:
    
        output.append(read(master_fd, timeout=0.5))

        for cmd in commands:
            writeToTerminal(master_fd, cmd + "\r")
            output.append(read(master_fd, timeout=0.4))
 
        writeToTerminal(master_fd, "exit\r")
        output.append(read(master_fd, timeout=0.5))

    finally:
        try:
            os.close(master_fd)
        except OSError:
            pass

        _, status = os.waitpid(pid, 0)

   
    exit_code = os.waitstatus_to_exitcode(status)
    return "".join(output), exit_code

script_dir = Path(__file__).resolve().parent
shell_path = script_dir.parent / "shell"
commands_path = script_dir / "commands.json"

with open(commands_path, "r", encoding="utf-8") as f:
    data = json.load(f)

commands = data["stage1"]["commands"]

raw_out, code = runShell(shell_path, commands)

print("==== OUTPUT ====")
print(deleteAnsi(raw_out))

print(f"\nExit code: {code}")