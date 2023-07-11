# External-MergeSort
Assignment of the course Fundamentals of Database Systems(CS315)

# Documentation
Simulation of the external mergesort by defining the appropiate functions.

## How to run the Code

Input Expected: 
1. File: Should contain interger/long long with line separated(Example file is provided in the submission named test)
2. m: integer (memory in blocks)
3. k: integer (key size in bytes)
4. n: integer (number of keys)
5. b: integer (Size of disk block in bytes)

```
g++ prog.cpp -o prog
./prog inputfile m k n b > out.txt
```

Example instance is:
```
g++ prog.cpp -o prog
./prog inputfile test 3 8 100 16 > out.txt
```

## How to Interpret the output

1. Sortet pass will be present in outfile1
2. Subsequent merge pass lets say i<sup>th</sup> merge pass will be present in outfile(i+1). Hence Merge pass 1 will be present in outfile2 and soon.
3. out.txt file which is formed after redirection of stdout will contain all the statistics and internal details of the execution.

## How to interpret the statistics in out.txt

It contain the detailed output of the externel mergesort. It also contain input to the i<sup>th</sup> merge pass and its output with all the internal details.

At the end of file it also contain the detailed statistics:

```
seeks in sorted pass: 8                 
blk transfers in sorted pass: 24       
Total number of merge passes: 2
Seek in one merge pass: 24
Blk transfers in one merge pass: 24
seeks in all merge pass: 48
blk transfers in all merge pass: 48
Overall seeks: 56
Overall blk transfers: 72
```
Printed names justifies the value corresponding to it.
We know that the in every merge pass we have same number of seeks and transfer so i only print it once.
If the input file format is not same as I expect then I also provide the program to generate the file with correct format which my program support.


