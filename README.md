# K-Largest Element

The main algorithm is written in C++ using STL. The core idea of this algorithm is to find the `k-th` largest element in the list using `selection algorithm` that is `median-of-medians` in linear time. Once the `k-th` largest element is found, then the top-k elements are found by looping the list and extracting all values greater than `k`.

### Requirements
The project should build on Linux or MacOS (tested on MacPort) with following installed

- `cmake`
- `C++11`

### Project Structure
The folder has following files
```bash
include/klargest/
	- constants.hpp # global contants
	- pairs.hpp # struct for custom data structure
	- parser_helper.hpp
	- klargest.hpp
scripts/
   	- compare_results.py # script to evaluate the results
   	- test_data.generator.py # script to generate dummy test data
src/
	- main.cpp # main entry point
	- parser_helper.cpp # helper class for handling all command line operations
	- klargest.cpp # algorithm file
tests/ # directory containing test data. (see below)
CMakeLists.txt
run.sh # automated script to build and run the program
```


### Compile, Build and Run Script

For easy usage just run `run.sh` script on the parent directory will build and run the test. The data for testing can be found in `test` directory.

```bash
$ ./run.sh
```

--
OR
--

#### Building the project
To build the project run the following commands
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

#### Running the program
You can run the program as follows

```bash
# running with data from file
$ ./klargest <path_to_test_file> <value_of_X>

# running with data input from command line
$./klargest

# sample out
Enter input thru console infile the following format
<unique identifier><white_space><numeric value>	 [eg: 1426828011 9]
To signal end of input, press c
--------------------------------------------------------------------------------

   1| # data goes here

```
the program will prompt to enter data and you can terminate end of list with `c or C`.

After each execution, the program will loop over and ask for new value of `k` for testing. You can enter `C or c` to stop execution.

```bash
Enter X for another test or C(c) to end.
--------------------------------------------------------------------------------
Enter a value for X: [0 < X < 11] : c # enter c or C to terminate

```

### Testing

Sample test data in `.txt` format can be found under `tests` directory. The files are as follows:

1. `test_00000010.txt` - *file containing the data unsorted. 00000010 represents number of sampels in the file*
2. `test_00000010_actual.txt` - *file with sorted data. The data is sorted using normal sorting algorithm in* `NLogN`.
3. `test_00000010_result_k5.txt` -  *file output of the program. k5 means file has top 5 values.* 


### Evaluation
In the `scripts` folder there are two python files
1. `test_data_generator.py` - File used for generating data for testing. 
	```bash
    $ python test_data_generator.py 5000 # number of samples to generate
    ```
    This script will output two files:
    `test_00005000.txt` and `test_00005000_actual.txt`
    
2. `compare_results.py` - File to read the `test_00000010_actual.txt` and the output of the program `test_00005000_result_k50.txt` and compare the result.
It will terminate if there is a error i.e., when the results doesnt match
	```bash
    $ python compare_results.py ../tests/test_00000010_result_k3.txt # result file
	```
    You only need to provide the result file and the `compare_result` script will automatically locate the `test_00000010_actual.txt` containing the actual result for comparision.
    
    Note that this scripts is only for data stored in the file. Please run (1) before (2)
    
    
### Sample Output
The following is the sample output of the program
```bash
./klargest ../tests/test_00000010.txt 5

Results for X=5
000000000004
000000000003
000000000007
000000000008
000000000000


Enter X for another test or C(c) to end.
--------------------------------------------------------------------------------
Enter a value for X: [0 < X < 11] : 3

Results for X=3
000000000004
000000000003
000000000007


Enter X for another test or C(c) to end.
--------------------------------------------------------------------------------
Enter a value for X: [0 < X < 11] : c
```

