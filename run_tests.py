import os
import os.path
import glob
import subprocess
import sys


DIR = "tests/bin/*"

files = glob.glob(DIR)

glob_fail = False
for file in files:
    if sys.platform == "win32" and file.split(".")[-1] != "exe":
         continue
    if not os.path.isdir(file) and "test" in file:  # skip directories and unwanted files such as core dumps
        print("Running test %s:\n" % file)
        output = subprocess.run([file], stdout=subprocess.PIPE, universal_newlines=True)
        print(output.stdout)
        test_failed = False
        if output.returncode:
            test_failed = True
        if "fail" in output.stdout:
            test_failed = True
        if test_failed:
            print("\t\t\t outcome = failed")
            glob_fail = True
        else:
            print("\t\t\t outcome = passed")

if glob_fail:
    print("\nOne or more tests failed\n")
    sys.exit(1)
