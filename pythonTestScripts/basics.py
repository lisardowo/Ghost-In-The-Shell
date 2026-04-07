"""echo hello
echo hello world
type echo
type ls
comando_invalido_xyz
exit 0"""

import subprocess
import json
import subprocess
from pathlib import Path

with open("commands.json") as comandsFile:
    data = json.load(comandsFile)

commands = data["stage1"]["commands"]

scriptInput = "\n".join(commands + ["exit"]) + "\n" #TODO i can probably  delete the hardocded exit by ensuring to run the exit command in each stage at the end
shellPath = Path(__file__).resolve().parent.parent / "shell"

testResults = subprocess.run([str(shellPath)], input = scriptInput, capture_output = True, text = True)

print(f"stdOut : {testResults.stdout}")
print(f"stdErr : {testResults.stderr}")
print(f"Exit code : {testResults.returncode}")
