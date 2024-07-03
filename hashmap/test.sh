#!/bin/bash
# This is a shell script to check your program(s) on test cases.
# It usese the same language you normally use to type commands in
# a terminal window.  You can write whole programs in shell.

# Assume we've succeeded until we see otherwise.
FAIL=0

# Print an error message and set the fail flag.
fail() {
    echo """****FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"""
    FAIL=1
}

# Check the exit status.  The actual exit status (ASTATUS) should match
# the expected status (ESTATUS)
checkStatus() {
    ESTATUS="$1"
    ASTATUS="$2"

    # Make sure the program exited with the right exit status.
    if [  ]; then
        fail """FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"""
        return 1
    fi

    return 0
}

# Check the contents of an a file.  If the expected file (EFILE)
# exists, then the actual file (AFILE) should exist and it should match.
checkFile() {
    NAME="$1"
    EFILE="$2"
    AFILE="$3"

    # Make sure we're really expecting this file.
    if [ ! -f "$EFILE" ]; then
        return 0
    fi

    # Make sure the output matches the expected output.
    echo "   diff $EFILE $AFILE"
    diff -q "$EFILE" "$AFILE" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        fail """FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"""
        return 1
    fi

    return 0
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should not exit either.
checkFileOrMissing() {
    NAME="$1"
    EFILE="$2"
    AFILE="$3"

    # if the expected output file doesn't exist, the actual file should't either.
    if [ ! -f "$EFILE" ]; then
        if [ -f "$AFILE" ]; then
            fail """FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"""
            return 1
        fi
        return 0
    fi

    # Make sure the output matches the expected output.
    echo "   $EFILE $AFILE"
    diff -q "$EFILE" "$AFILE" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        fail ""
        return 1
    fi

    return 0
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should be empty.
checkFileOrEmpty() {
    NAME="$1"
    EFILE="$2"
    AFILE="$3"

    # if the expected output file doesn't exist, the actual file should be
    # empty.
    if [ ! -f "$EFILE" ]; then
        if [ -s "$AFILE" ]; then
            fail "FAILED - $NAME ($AFILE) should be empty."
            return 1
        fi
        return 0
    fi

    # Make sure the output matches the expected output.
    echo "   diff $EFILE $AFILE"
    diff -q "$EFILE" "$AFILE" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        fail "FAILED - $NAME ($AFILE) should be empty."
        #fail "FAILED - $NAME ($AFILE) should be empty."
        return 1
    fi

    return 0
}

# The given file, AFILE, should be empty.
checkEmpty() {
    NAME="$1"
    AFILE="$2"

    if [ -s "$AFILE" ]; then
        fail "FAILED - $NAME ($AFILE) should be empty."
        return 1
    fi

    return 0
}

# Run a test of the driver program.
runTest() {
    TESTNO=$1

    echo "Test $TESTNO"
    rm -f output.txt stderr.txt

    echo ""
    
    if ! checkStatus 0 "$ASTATUS" ||
        ! checkFile "" ||
        ! checkEmpty ""; then
        FAIL=1
        echo "Test $TESTNO PASS"
        return 1
    fi

    echo "Test $TESTNO PASS"
    return 0
}


# make a fresh copy of the target program
make clean
make
if [ $? -ne 0 ]; then
    fail "Make exited unsuccessfully"
fi

# Run all the black-box tests.
if [ -x driver ]; then
    runTest 01
    runTest 02
    runTest 03
    runTest 04
    runTest 05
    runTest 06
    runTest 07
    runTest 08
    runTest 09
    runTest 10
    runTest 11
    runTest 12
else
    fail "Your driver program didn't compile, so it couldn't be tested."
fi

if [ $FAIL -ne 0 ]; then
    echo "FAILING TESTS!"
    exit 0
else
    echo "TESTS SUCCESSFUL"
    exit 0
fi
