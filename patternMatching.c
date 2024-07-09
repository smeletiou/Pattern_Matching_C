/**
 * @file patternMatching.c
 * @author Sotiris Rafail Meletiou
 * @brief Pattern Matching HW2 project for EPL232
 * @version 1.0
 * This program contains three different pattern searching algorithms 
 * Brute-Force , Karp-Rabin and Z
 * depending on the choice of the user each algorithm finds with different
 * ways the patters from the files that the user gave.
 * @copyright Copyright (c) 2021
 * @bug Z-algorithm for the swineflu Sequence takes a little bit to run 
 */

/* definition of libs*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* definition of the functions */
int algChoose(char *argv[]);
int karp(const char *, const char *);
int z(const char *, const char *);
int bruteForce(const char *, const char *);
void algCall(int opt, char *, char *);
void importFiles(FILE *, char *, int);
void Z_array(char *str, int *Z);
void orderCheck(int sizeS ,int sizeP);

/**
 * @brief Main function.
 * Open files , creates the string and import the files to the strings
 * calls the algorithms.
 * 
 * @param argc length of input.
 * @param argv files and algorithm
 * @return int 
 */
int main(int argc, char *argv[])
{
  FILE *Seq, *Patt;
  if (argc != 4)
  {
    printf("Usage: \n");
    printf("./<calling-name> -algorithm <TextFile> <PatternFile>\n");
    exit(1);
  }
  if ((Seq = fopen(argv[2], "r")) == NULL)
  {
    printf("ERROR :Sequence File cannot be opened\n");
    exit(-1);
  }
  if ((Patt = fopen(argv[3], "r")) == NULL)
  {
    printf("ERROR :Pattern File cannot be opened\n");
    exit(-1);
  }



  fseek(Seq, 0, SEEK_END);              //finds the end of the file
  int sizeS = ftell(Seq);               //saves the size of the file
  fseek(Seq, 0, SEEK_SET);              //resets the file to the beggining
  char *SeqTXT = (char *)malloc(sizeof(char)*sizeS); //creates a tab with the size of the file
  importFiles(Seq, SeqTXT, sizeS);

  fseek(Patt, 0, SEEK_END);             //finds the end of the file
  int sizeP = ftell(Patt);              //saves the size of the file
  fseek(Patt, 0, SEEK_SET);             //resets the file to the beggining
  char *PatTXT = (char *)malloc(sizeof(char)*sizeP); //creates a tab with the size of the file
  importFiles(Patt, PatTXT, sizeP);

  orderCheck(sizeS,sizeP);

  algCall(algChoose(argv), SeqTXT, PatTXT); //calls the corresponding algorithm that user chose
  return 0;
}

/**
 * @brief Checks the order of files.
 * a small check to see if the files are in correct
 * order because the pattern can not be larger than the text
 * @param sizeS size of txt
 * @param sizeP size of pattern
 */
void orderCheck(int sizeS ,int sizeP){
   if(sizeP >sizeS){
     printf("ERROR :Wrong order of files\n");
     printf("The pattern cannot be larger than the txt file\n");
     exit(1);
   }
}

/**
 * @brief import files to the strings.
 * 
 * @param fp file
 * @param tab string
 * @param size size of file
 */
void importFiles(FILE *fp, char *tab, int size)
{
  int i;
  fgets(tab, size, fp); //inputs the txt from fp to a tab[size]
  for (i = 0; i < size; i++)
    if (*(tab + i) == '\n') //incase there are new line char as a char
      *(tab + i) = '\0';

  fclose(fp);
}

/**
 * @brief calls the algorithms and prints the results
 * 
 * @param opt option given from user in terminal(flag)
 * @param str1 //Sequence txt
 * @param str2 //Pattern txt
 */
void algCall(int opt, char *str1, char *str2)
{
  switch (opt)
  {
  case 0:
    printf("Pattern \"%s\" was found %d times\n", str2 ,bruteForce(str1, str2));
    break;
  case 1:
    printf("Pattern \"%s\" was found %d times\n",str2 , karp(str1, str2));
    break;
  case 2:
    printf("Pattern \"%s\" was found %d times\n",str2 , z(str1, str2));
    break;
  }
}

/**
 * @brief finds the algorithm that matches the user input
 * 
 * @param argv choice of algorithm in index 1
 * @return int returns the number of matching the algorithm
 */
int algChoose(char *argv[])
{
  if (strcmp(argv[1], "-bf") == 0)
    return 0;
  else if (strcmp(argv[1], "-kp") == 0)
    return 1;
  else if (strcmp(argv[1], "-z") == 0)
    return 2;
  else
  {
    printf("ERROR 404 :Algorithm does not exist\n");
    printf("Please choose one of the following\n");
    printf("Brute-Force -bf\n");
    printf("Karp-Rabin -kp\n");
    printf("Z -z\n");
    exit(1);
  }
}

/**
 * @brief Algorithm Z.
 * algorithm Z finds patters by creating a new table by calling the Z_array 
 * function and creates a array with lengths in it and then it compares
 * these numbers with parts of the lengths of the concatenated string(P$T)
 * that was created
 * @param txt 
 * @param patt 
 * @return int the number of patterns in the txt
 */
int z(const char *txt, const char *patt)
{
  printf("You chose the Z algorithm :\n");
  int i, j;
  int found = 0;
  int size = strlen(patt) + strlen(txt) + 2; //size of the two strings + the $ symbol % \0
  char *Zstr = (char *)malloc(size);         //allocates the size to the starting

  for (i = 0; i < strlen(patt); i++) //adds the pattern to the Zstr
    *(Zstr+i) = *(patt+i);

  Zstr[strlen(patt)] = '$'; //then adds the dollar $

  for (j = strlen(patt) + 1, i = 0; i < strlen(txt); i++, j++) //then adds the text we are searching through
    *(Zstr+j) = *(txt+i);
  // final form  (pat)$(txt)
  Zstr[size] = '\0'; // adds null pointer

  int len = strlen(Zstr); //finds the length of the length of Zsrt
  // Creates Z array with the length of the concatanated string
  int *Z;
  Z=(int *)malloc(sizeof(int)*len);
  Z_array(Zstr, Z); //calls the function to create the Z string

  int p;
  // now iterating through Z array for matching condition
  for (p = 0; p < len; ++p)
  {
    // if Z[i] is equal to pattern length we found the pattern we were looking for
    if (*(Z+p) == strlen(patt))
      found++;
  }
  return found;
}

/**
 * @brief Creates the Z array 
 * For the string str[0..n-1], Z array is the same length as the string. 
 * An element Z[i] of Z array stores length of the longest substring
 * starting from str[i] which is also a prefix of str[0..n-1].
 * The first entry of Z array is meaning less as complete 
 * string is always prefix of itself. 
 * @param str the concatenated string
 * @param Z array
 */
void Z_array(char *str, int *Z)
{
  int n = strlen(str);
  int L, R, k;

  // [L,R] make a window which matches with prefix of str
  L = R = 0;
  Z[0] = -1; //we dont need the first index of the string
  int i;
  for (i = 1; i < n; i++)
  {
    // if i>R nothing matches so we will calculate.
    if (i > R)
    {
      L = R = i;
      // first R-L = 0 , so it will start
      // checking from 0'th index.
      while (R < n && str[R - L] == str[R])
        R++;
      *(Z+i) = R - L;
      R--;
    }
    else
    {
      // k = i-L so k corresponds to number which
      // matches in [L,R] interval.
      k = i - L;
      // if Z[k] is < than remaining interval
      // then Z[i] will be equal to Z[k].
      if (*(Z+k) < R - i + 1)
        *(Z+i) = *(Z+k);
      else
      { // else start from R and check one by one
        L = i;
        while (R < n && str[R - L] == str[R])
          R++;
        *(Z+i) = R - L;
        R--;
      }
    }
  }
}

/**
 * @brief Karp-Rabin Algorithm
 * Karp-Rabin algorithm creates a number from the characters in pattern using 
 * the equaion (x0*2M-1+ x1*2M-2 + ...+ xM-1*20) mod q 
 * then for the length of pattern iterates the txt and takes the same length of chars
 * as the pattern to create the same number using the same equation and
 * if the numbers are the same then it compares this small "window" of chars with
 * the pattern.
 * @param txt 
 * @param patt 
 * @return int the number of patterns in the txt
 */
int karp(const char *txt, const char *patt)
{
  printf("You chose the Karp-Rabin algorithm :\n");
  int patt_Len = strlen(patt);
  int txt_Len = strlen(txt);
  int d = 256, q = INT_MAX;// int 2147483647
  int i, j, found = 0;
  int hash_patt = 0, hash_txt = 0, hash = 1; // hash value for pattern

  // The value of h would i "pow(d, M-1)%q"
  for (i = 0; i < patt_Len - 1; i++)
    hash = (hash * d) % q;

  // Calculate the hash value of pattern and first
  // window of text
  for (i = 0; i < patt_Len; i++)
  {
    hash_patt = (d * hash_patt + *(patt+i)) % q;
    hash_txt = (d * hash_txt + *(txt+i)) % q;
  }

  // iterate the pattern over text one by one
  for (i = 0; i <= txt_Len - patt_Len; i++)
  {
    // Check the hash values of current window of text
    // and pattern. If the hash values match then only
    // check for characters on by one
    if (hash_patt == hash_txt)
    {
      /* Check for characters one by one to be sure they are the same*/
      for (j = 0; j < patt_Len; j++)
        if (*(txt+i + j) != *(patt+j))
          break;

      // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
      if (j == patt_Len)
        found++;
    }
    // Calculate hash value for next window of text
    if (i < txt_Len - patt_Len)
    {
      hash_txt = (d * (hash_txt - *(txt+i) * hash) + *(txt+i + patt_Len)) % q;
      //incase the hash is negative
      if (hash_txt < 0)
        hash_txt = (hash_txt + q);
    }
  }
  return found;
}

/**
 * @brief Brute-Force Algorithm
 * the bf algorithm iterates the txt string one by one 
 * checking the current index with the first character of the pattern
 * if the characters are the same then it moves to the next characters of
 * the text.if the second character is the same with the second character of the
 * pattern this routine goes on until all the characters are in a continous line 
 * if not the it starts again with the first character of the pattern to the next 
 * index of the txt 
 * @param txt 
 * @param patt 
 * @return int number of patterns found in txt
 */
int bruteForce(const char *txt, const char *patt)
{
  printf("You chose the brute force algorithm :\n");
  int patt_Len = strlen(patt);
  int txt_Len = strlen(txt);
  int found = 0, i;
  /* A loop to iterate patt one by one */
  for (i = 0; i <= txt_Len - patt_Len; i++) //subtract the pattern length because theres no
  {                                         // need to search it if there is not enough space
    int j;
    /* For current index i, check for pattern match */
    for (j = 0; j < patt_Len; j++)
      if (*(txt + i + j) != *(patt + j))
        break;

    if (j == patt_Len)
      found++;
  }
  return found;
}
