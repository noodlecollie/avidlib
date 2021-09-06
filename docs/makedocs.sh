SCRIPT_DIR=`dirname "$(readlink -f "$0")"`

mkdir -p "$SCRIPT_DIR/../build/docs"

if [ $? != 0 ]
then
	echo "Could not create docs output directory."
	exit 1
fi

mono "$SCRIPT_DIR/../.naturaldocs/NaturalDocs.exe" "$SCRIPT_DIR"

if [ $? != 0 ]
then
	echo "Failed to run NaturalDocs."
	exit 1
fi
