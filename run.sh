#!/usr/bin/env bash

PROJECT_NAME=${PWD##*/}
BUILD="build/"
SCRIPTS="../scripts/"
TESTS="../tests/"

echo "Running project $PROJECT_NAMEXSXS "

if [ ! -d $BUILD ]
   then
       mkdir $BUILD
fi

_run() {
    filename="${2%.*}" # get the filename
    k=$3

    DATA_FILENAME=$1$2
    RESULT_FILENAME=${TESTS}${filename}_result_k${3}.txt
    
    echo -e 'c' | ./$PROJECT_NAME $DATA_FILENAME $k

    printf "\n\nComparing results\n"
    python ${SCRIPTS}compare_results.py $RESULT_FILENAME

    # delete the results files
    rm -rf $RESULT_FILENAME
}

# temp method use lenght to filename
LENGHT=17
k=5
get_test_files() {
    for entry in ${TESTS}*;
    do
	fn=`basename "$entry"`
	if [ ${#fn} -eq $LENGHT ]
	then
	    _run ${TESTS} $fn $k
	fi
    done
}

# build the project
echo "Building Project"
cd $BUILD
cmake ..
make

get_test_files

