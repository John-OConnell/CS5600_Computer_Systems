#! /bin/bash#

echo "----Testing the -u Argument----"

echo "Input:"
echo "hello world!"
echo "Output:"
if ./arger-oconnell -u hello world!;
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "Input:"
echo "TeSt CaSe"
echo "Output:"
if ./arger-oconnell -u TeSt CaSe
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "Input:"
echo "abc123 456DEF"
echo "Output:"
if ./arger-oconnell -u abc123 456DEF
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "----Testing the -l Argument----"

echo "Input:"
echo "hello world!"
echo "Output:"
if ./arger-oconnell -l hello world!
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "Input:"
echo "TeSt CaSe"
echo "Output:"
if ./arger-oconnell -l TeSt CaSe
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "Input:"
echo "abc123 456DEF"
echo "Output:"
if ./arger-oconnell -l abc123 456DEF
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "----Testing the -cap Argument----"

echo "Input:"
echo "hello world!"
echo "Output:"
if ./arger-oconnell -cap hello world!
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "Input:"
echo "TeSt CaSe"
echo "Output:"
if ./arger-oconnell -cap TeSt CaSe
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "Input:"
echo "abc123 456DEF"
echo "Output:"
if ./arger-oconnell -cap abc123 456DEF
then
	echo
else
	echo "Something went wrong"
	echo
fi	

echo "----Testing Too Few Arguments----"
if ! ./arger-oconnell;
then
	echo
	echo "Call succesfully returned -1"
fi
echo 

echo "----Testing incorrect Argument----"
if ! ./arger-oconnell -p hello world;
then
	echo
	echo "Call succesfully returned -1"
fi
echo

