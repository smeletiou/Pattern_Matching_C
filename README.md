/**
@mainpage EPL232 HomeWork2 

@author Sotiris Rafail Meletiou 

@File patternMatching
A pattern finder program.
The program starts by calling it in terminal with the following command
./<name> -alg <SequenceFile.txt> <PatternFile.txt>

@Bug Z-algorithm for the swineflu Sequence takes a little bit to run .And i had a problem after i transfered my files from the windows to the pcs of the lab.One character got corrupted in the file and it was messing up with the lengths and a way to fix it is to create a new txt file.

There are 3 options for the algorithm -bf (Brute-Force) -kp (Karp-Rabin) -z 
Each one of them are excecute differently but all of theme should have the same result.
The first file that you have to enter is the txt that you want to find a pattern inside and the second file is the pattern tha you want to be searched.

The algorithms:
Brute-Force: 
Brute force algorithm takes the two files and iterates the txt string one by one checking the current index with the first character of the pattern
if the characters are the same then it moves to the next characters of
the text.if the second character is the same with the second character of the
pattern this routine goes on until all the characters are in a continous line 
if not the it starts again with the first character of the pattern to the next 
index of the txt. 

Karp-Rabin: 
Karp-Rabin algorithm takes both files reates a number from the characters in pattern using the equaion (x0*2M-1+ x1*2M-2 + ...+ xM-1*20) mod q 
then for the length of pattern iterates the txt and takes the same length of chars as the pattern to create the same number using the same equation and if the numbers are the same then it compares this small "window" of chars with
the pattern.

Z:
algorithm Z takes both files and finds patters by creating a new table by calling the Z_array function and creates a array with lengths in it and then it compares these numbers with parts of the lengths of the concatenated string(P$T)
that was created.
The Z_array function creates the Z array tha is needed for the pattern finding.
For the string str[0..n-1], Z array is the same length as the string. 
The element Z[i] of Z array stores length of the longest substring
starting from str[i] which is also a prefix of str[0..n-1].
The first entry of Z array is meaning less as complete string is always prefix of itself. 

The output of the file is the number of times the pattern was found inside the txt sequence.
**/