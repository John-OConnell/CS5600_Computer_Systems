#!/bin/bash

# Test performing WRITE operation
echo "----------Test WRITE Command----------"
echo "Writing foo.txt :"
./rfs WRITE foo.txt
if [ -e rfsys/foo.txt ]; then
        echo "File foo.txt exists on remote server"
fi

echo
echo "Writing foo.txt to folder new/ :"
./rfs WRITE foo.txt new/foo.txt
if [ -e rfsys/new/foo.txt ]; then
        echo "File foo.txt exists in folder new/ on remote server"
fi
echo

# Test performing GET operation
echo "----------Test GET Command----------"
echo "Getting foo.txt, saving to myFoo.txt :"
./rfs GET foo.txt myFoo.txt
if [ -e myFoo.txt ]; then
        echo "File myFoo.txt exists locally"
fi

echo
echo "Getting new/foo.txt, saving to myNewFoo.txt :"
./rfs GET new/foo.txt myNewFoo.txt
if [ -e myNewfoo.txt ]; then
        echo "File myNewFoo.txt exists locally"
fi
echo

# Test performing versioned GET operation
echo "----------Test GET Command - VERSIONED----------"
echo "Currently foo.txt contains the following :"
cat foo.txt
echo
echo
echo "We will write this new version to foo.txt :"
cat newfoo.txt
echo
echo
echo "Writing new version of foo.txt :"
./rfs WRITE newfoo.txt foo.txt
echo "Here is the latest version using the GET command :"
./rfs GET foo.txt getVersFoo.txt
cat getVersFoo.txt
echo
echo
echo "And here is the original version using the GET command :"
./rfs GET foo.txt getVersFoo.txt 0
cat getVersFoo.txt
echo
echo

# Test performing LS operation
echo "----------Test LS Command----------"
./rfs LS foo.txt
echo
./rfs LS new/foo.txt
echo

# Test performing RM operation
echo "----------Test RM Command----------"
echo "Removing foo.txt :"
./rfs RM foo.txt
if [ ! -e rfsys/foo.txt ]; then
        echo "File foo.txt does NOT exist on remote server"
fi

echo
echo "Removing foo.txt from folder new/ :"
./rfs RM new/foo.txt
if [ ! -e rfsys/new/foo.txt ]; then
        echo "File foo.txt does NOT exist in folder new/ on remote server"
fi
echo