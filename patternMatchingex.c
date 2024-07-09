#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lcase(x) ((x) >= 'A' && (x) <= 'Z' ? (x) + ('a' - 'A') : (x))

int algChoose(int argc, char *argv[]);
int karp(const char *, const char *);
int z(char *,char *);
int bruteForce(char *, char *);
void algCall(int opt,char *,char *);
void importFiles(FILE *, char *, int);
void getZarr(char *str, int *Z);

int main(int argc, char *argv[])
{
  FILE *Seq, *Patt;
  int alg;

  if (argc < 4)
  {
    printf("Usage: \n");
    printf("./patterMatching -alg <inputfile1> <inputfile2>\n");
    exit(1);
  }
  if ((Seq = fopen(argv[2], "r")) == NULL)
  {
    printf("Error:Sequence File cannot be opened\n");
    exit(-1);
  }
  if ((Patt = fopen(argv[3], "r")) == NULL)
  {
    printf("Error:Pattern File cannot be opened\n");
    exit(-1);
  }
 
  fseek(Seq, 0, SEEK_END); //finds the end of the file
  int size1 = ftell(Seq)+1;  //saves the size of the file
  fseek(Seq, 0, SEEK_SET); //resets the file to the beggining
  char str1[size1];        //creates a tab with the size of the file
  importFiles(Seq, str1, size1);

  fseek(Patt, 0, SEEK_END); //finds the end of the file
  int size2 = ftell(Patt);  //saves the size of the file
  fseek(Patt, 0, SEEK_SET); //resets the file to the beggining
  char str2[size2];         //creates a tab with the size of the file
  importFiles(Patt, str2, size2);
  printf("%d size of file",size2);

   //printf("%s\n", str1);
  // printf("%s\n", str2);
  algCall(algChoose(argc, argv), str1, str2);
}
void importFiles(FILE *fp,char *tab, int size)
{
  fgets(tab, size, fp);
  fclose(fp);
}

void algCall(int opt,char *str1,char *str2)
{
  switch (opt)
  {
  case 0:
    printf("Pattern was found %d times\n", bruteForce(str1, str2));
    break;
  case 1:
    printf("Pattern was found %d times\n", karp(str1, str2));
    break;
  case 2:
    printf("Pattern was found %d times\n", z(str1, str2));
    break;
  }
}

int algChoose(int argc, char *argv[])
{
  if (strcmp(argv[1], "-bf") == 0)
    return 0;
  else if (strcmp(argv[1], "-kp") == 0)
    return 1;
  else if (strcmp(argv[1], "-z") == 0)
    return 2;
  else
  {
    printf("Algorithm doesn't exist\n");
    exit(1);
  }
}

int z(char *txt,char *patt)
{
  // char *p=patt;
  // printf("inside z\n");
  // printf("%d", strlen(p));
  // int found = 0;
  // char *concat = p;
  // printf("%d", strlen(p));
  // strcat(concat, "$");
  // strcat(concat, txt);
  // int l = strlen(concat);
  // // Construct Z array
  // int Z[l];
  // getZarr(concat, Z);
  // // for (int i = 0; i < l; i++)
  // //   printf("%d", Z[i]);

  // // now looping through Z array for matching condition
  // for (int i = 0; i < l; ++i)
  // {
  //   // if Z[i] (matched region) is equal to pattern
  //   // length we got the pattern
  //  // printf("%d - %d\n",Z[i],strlen(p));
  //   if (Z[i] == *p)
  //     found++;
  // }
  // return found;
}

void getZarr (char *str, int *Z)
{
  int n = strlen(str);
  int L, R, k;

  // [L,R] make a window which matches with prefix of s
  L = R = 0;
  Z[0] =-1;
  for (int i = 1; i < n; i++)
  {
    // if i>R nothing matches so we will calculate.
    // Z[i] using naive way.
    if (i > R)
    {
      L = R = i;

      // R-L = 0 in starting, so it will start
      // checking from 0'th index. For example,
      // for "ababab" and i = 1, the value of R
      // remains 0 and Z[i] becomes 0. For string
      // "aaaaaa" and i = 1, Z[i] and R become 5
      while (R < n && str[R - L] == str[R])
        R++;
      Z[i] = R - L;
      R--;
    }
    else
    {
      // k = i-L so k corresponds to number which
      // matches in [L,R] interval.
      k = i - L;

      // if Z[k] is less than remaining interval
      // then Z[i] will be equal to Z[k].
      // For example, str = "ababab", i = 3, R = 5
      // and L = 2
      if (Z[k] < R - i + 1)
        Z[i] = Z[k];

      // For example str = "aaaaaa" and i = 2, R is 5,
      // L is 0
      else
      {
        // else start from R and check manually
        L = i;
        while (R < n && str[R - L] == str[R])
          R++;
        Z[i] = R - L;
        R--;
      }
    }
  }
}

int karp(const char *txt, const char *patt)
{
  printf("inside karp-r\n");
  int patt_Len = strlen(patt);
  int txt_Len = strlen(txt);
  int d = 256, q = 1009;
  int i, j, found = 0;
  int hash_patt = 0, hash_txt = 0, hash = 1; // hash value for pattern

  // The value of h would be "pow(d, M-1)%q"
  for (i = 0; i < patt_Len - 1; i++)
    hash = (hash * d) % q;

  // Calculate the hash value of pattern and first
  // window of text
  for (i = 0; i < patt_Len; i++)
  {
    hash_patt = (d * hash_patt + patt[i]) % q;
    hash_txt = (d * hash_txt + txt[i]) % q;
  }

  // Slide the pattern over text one by one
  for (i = 0; i <= txt_Len - patt_Len; i++)
  {
    // Check the hash values of current window of text
    // and pattern. If the hash values match then only
    // check for characters on by one
    if (hash_patt == hash_txt)
    {
      /* Check for characters one by one */
      for (j = 0; j < patt_Len; j++)
        if (txt[i + j] != patt[j])
          break;

      // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
      if (j == patt_Len)
        found++;
    }
    // Calculate hash value for next window of text: Remove
    // leading digit, add trailing digit
    if (i < txt_Len - patt_Len)
    {
      hash_txt = (d * (hash_txt - txt[i] * hash) + txt[i + patt_Len]) % q;

      // We might get negative value of t, converting it
      // to positive
      if (hash_txt < 0)
        hash_txt = (hash_txt + q);
    }
  }
  return found;
}

int bruteForce(char *txt,char *patt)
{
  printf("inside brute force\n");
  int patt_Len = strlen(patt);
  int txt_Len = strlen(txt);
  int found = 0, i;
  /* A loop to slide pat[] one by one */
  for (i = 0; i <= txt_Len - patt_Len; i++)
  {
    int j;
    /* For current index i, check for pattern match */
    for (j = 0; j < patt_Len; j++)
      if (*(txt + i + j) != *(patt + j))
        break;

    if (j == patt_Len) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
      found++;
  }
  return found;
}