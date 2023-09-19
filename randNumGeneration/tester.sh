#! /bin/bash#

echo "----Testing writing 10 numbers to file----"

if ./genRand 10 rand.txt;
then
	echo "Success!"
	echo "File Contents:"
	cat rand.txt
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "----Testing appending 5 additional  numbers----"

if ./genRand 5 rand.txt -a;
then
	echo "Success!"
	echo "File Contents:"
	cat rand.txt
	echo
else
	echo "Something went wrong"
	echo
fi

echo "----Testing overwriting file----"

if ./genRand 15 rand.txt;
then
	echo "Success!"
	echo "File Contents:"
	cat rand.txt
	echo
else
	echo "Something went wrong"
	echo
fi

echo "----Testing Too Few Arguments----"
if ! ./genRand;
then
	echo
	echo "Call succesfully returned -1"
fi
echo 

echo "----Testing incorrect Argument----"
if ! ./genRand 15 rand.txt -o;
then
	echo
	echo "Call succesfully returned -1"
fi
echo

