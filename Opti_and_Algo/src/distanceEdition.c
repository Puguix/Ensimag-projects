/**
 * \file distanceEdition.c
 * \brief compute edit distance between two strings each one being a substring of consecutive characters (eg in a FNA file) 
 * \version 0.1
 * \date 30/09/2022 
 * \author Jean-Louis Roch (Ensimag, Grenoble-INP, University Grenoble-Alpes) jean-louis.roch@grenoble-inp.fr
 * Usage : distanceEdition file1 b1 L1 file2 b2 L2
 * cf function usage_and_spec below.
NAME
     distanceEdition - compute edit distance between two substrings, each from a file
SYNOPSIS
     distanceEdition file_1 b1 L_1 file_2 b_2 L_2
DESCRIPTION
     distanceEdition computes the edit distance between two arrays of 
     characters array_file_1[b_1, b_1+L_1( and array_file2[b_2,b_2+L_2( where:
     array_F[b,b+L( : denotes in file F the sequence of L consecutive characters starting at position b.
     The progam is designed for direct access to genetic subsequences stored in FASTA format file (.fna) .
     Execution performs the following actions:
     1. maps file_1 in an array array_file_1 in virtual memory using standard C libray function: mmap 
     2. prints on stderr if (L_1 <= 40)  the content of array_file_1[b_1 .. b_1+L_1-1] 
        or else the first and last 20 characters of array_file_1 
     3. if file_2 and file_1 are the same pathname, than array_file_2 = array_file_1;
        else do for file_2 the same as file_1 (replacing _1 by _2 in both previous actions above) 
     4. prints on stdout the output (type long) of the following call :
           editDistance( array_file_1 + b_1, L_1, array_file_2, + b_2, L_2 )  
        where the extern C function has prototype :
           editDistance( char* A, size_t lengthA, char* B, size_t lengthB);
EXIT STATUS
     The program exits 0 on success, and >0 if an error occurs.
EXAMPLE
           distanceEdition  f1.fna 0 5 f2.fna 42 7  
    where f1.fna contains =\"CAcgT\" 
      and f2.fna contains \"<cette premiere ligne est un commentaire.\\nacaCGTACNNNAT\" \n"
    prints the output of editDistance on the two following char arrays : 
    {'C', 'A', 'c', 'G', 'T'} extracted from f1.fna
    {'a', 'c', 'a', 'C', 'G', 'T', 'A'} extracted from f2.fna
    and prints 4 on stdout.
*/ 
/**
 * \file distanceEdition.c
 * \brief Primitives pour mapper en mémoire virtuelle une sous-séquence d'un fichier de caractères
 * \author Jean-Louis Roch jean-louis.roch@grenoble-inp
 * \date 30/10/2012
 * \brief Primitives pour mapper en mémoire virtuelle une sous-séquence d'un fichier de caractères
 */

#include "Needleman-Wunsch-recmemo.h" // Recursive implementation of NeedlemanWunsch with memoization

#include <stdio.h>  
#include <stdlib.h> 
#include <err.h> 
#include <string.h> /* for strchr */
#include <fcntl.h> /* for open */
#include <unistd.h> /* for close */
#include <sys/mman.h> /* for mmap and munmap */
#include <sys/stat.h> /* for file length */
#include "AOD.h"
/******************************************************************************/

/**
 * \fn void usage_and_spec(int argc, char *argv[]) 
 * \brief prints how to use the program 
 * \param argc : argc from main
 * \param argv : argv from main (the caller given parameters)
 */
void usage_and_spec(int argc, char *argv[]) // spécification du programme
{ fprintf ( stderr,
    "%s : bad number of arguments: 6 are required (but this execution is with %d instead).\n"
    "Usage:   %s  file_1 begin_1 length_1 file_2 begin_2 length_2 \n\n"
    "%s prints the edit distance between two genetic sequences seq[i] for i=1..2  where \n"
    "seq[i] denotes the sequence of <length_i> char in <file_i> from position <begin_i>." 
    , argv[0], argc-1, argv[0], argv[0] 
  ) ;
  
  fprintf ( stderr, "\n"
"\nNAME"
"\n     distanceEdition - compute edit distance between two substrings, each from a file"
"\nSYNOPSIS"
"\n     distanceEdition file_1 b1 L_1 file_2 b_2 L_2"
"\nDESCRIPTION"
"\n     distanceEdition computes the edit distance between two arrays of"
"\n     characters array_file_1[b_1, b_1+L_1( and array_file2[b_2,b_2+L_2( where:"
"\n     array_F[b,b+L(  denotes in file F the sequence of L consecutive characters starting at position b."
"\n     The progam is designed for direct access to genetic subsequences stored in FASTA format file (.fna) ."
"\n     Execution performs the following actions:"
"\n     1. maps file_1 in an array array_file_1 in virtual memory using standard C libray function: mmap"
"\n     2. prints on stderr if (L_1 <= 40)  the content of array_file_1[b_1 .. b_1+L_1-1]"
"\n        or else the first and last 20 characters of array_file_1"
"\n     3. if file_2 and file_1 are the same pathname, than array_file_2 = array_file_1;"
"\n        else do for file_2 the same as file_1 (replacing _1 by _2 in both previous actions above)"
"\n     4. prints on stdout the output (type long) of the following call :"
"\n           editDistance( array_file_1 + b_1, L_1, array_file_2, + b_2, L_2 )"
"\n        where the extern C function has prototype :"
"\n           editDistance( char* A, size_t lengthA, char* B, size_t lengthB);"
"\nEXIT STATUS"
"\n     The program exits 0 on success, and >0 if an error occurs."
"\nEXAMPLE"
"\n           distanceEdition  f1.fna 0 5 f2.fna 42 7  "
"\n    where f1.fna contains =\"CAcgT\""
"\n      and f2.fna contains \"<cette premiere ligne est un commentaire.\\nacaCGTACNNNAT\" \n"
"\n    prints the output of editDistance on the two following char arrays :"
"\n    {'C', 'A', 'c', 'G', 'T'} extracted from f1.fna"
"\n    {'a', 'c', 'a', 'C', 'G', 'T', 'A'} extracted from f2.fna"
"\n    and prints 4 on stdout."
"\n"
 );
}    


/********************************************************************************/

/** \fn int main(int argc, char *argv[])
 * \brief main : see function usage_and_spec(argc, argv) for specification
 * \param argc : argc from main
 * \param argv : argv from main (the caller given parameters)
 */
int main(int argc, char *argv[])
{
   if (argc != 7)
   {   usage_and_spec(argc, argv) ;
       exit(EXIT_FAILURE);
   }

   int fd[2]; // The 2 fles descriptor correspoding for file1 and file2 
   char *mmap_fd[2] ; // adress in virtual memory of file fd[i] 
   long mmap_length[2] ; // length of the mapping in virtual memory of file fd[i] 
   char *seq[2] ; // corresponding genetic sequence to file[i]*/
   long length[2] ; // the length of corresponding genetic sequence seq[i] */

   for (int i=0 ; i < 2; ++i, argv+=3) // defines content and length of seq[i] for i=0..1 
   {
      fd[i] = open(argv[1], O_RDONLY);
      if (fd[i] == -1) err(1,"open");
      struct stat s;
      if (fstat(fd[i], &s) == -1) err(1, "fstat") ;
      mmap_fd[i] = (char *) mmap(NULL,  s.st_size, PROT_READ, MAP_PRIVATE, fd[i], 0);
      if (mmap_fd[i] == MAP_FAILED) err(1, "mmap") ;
      mmap_length[i] = (long) s.st_size ;
   

      {  // Assign seq[i] to the begining of the sequence, excluding comment lines starting by '<' 
         long debut; sscanf( argv[2], "%ld", &debut ) ; 
         seq[i] = mmap_fd[i] + debut ; // beginning of the sequence
         long n_exceed = mmap_length[i] - debut; 
         if ( n_exceed < 0) 
         {  fprintf( stderr, "Error: given sequence beginning %ld exceeds end of file of %ld bytes.\n",
                              debut, n_exceed ) ;
            exit( 1 ) ;
         }
         if (*seq[i] == '>') /* Skip and print the first line starting by '<' */
         {  char *endofline = strchr(seq[i], '\n' ) ;
            fprintf( stderr, "Sequence comment in preamble: " ) ;
            for( char* c = seq[i]; c <=  endofline; ++c) fprintf(stderr, "%c", *c );
            if (*endofline == '\n') seq[i] = endofline + 1; // first character of next line
         }
      }
 
      {  // assign length[i] to the given length for seq[i] 
         sscanf( argv[3], "%ld", &length[i] ) ;
         long n_exceed = mmap_fd[i] + mmap_length[i] -1 - ( seq[i] + length[i] )  ; 
         if ( n_exceed < 0) 
         {   fprintf( stderr, "Warning: given sequence length %ld exceeds end of file of %ld bytes; "
                              "sequence length is truncated to %ld.\n",
                              length[i], -n_exceed, length[i] + n_exceed ) ;
             length[i] = length[i] + n_exceed ;
         }
      }

      {  /* Print on stderr either the full sequence is length[i]<40 or the first twenty and last twenty characters of the sequence */ 
         if (length[i] <= 40)
         { for (char* c=seq[i]; (c < seq[i]+length[i]); ++c) fprintf(stderr, "%c", *c) ;
         }
         else
         { { for (char* c=seq[i]; (c < seq[i]+20); ++c) fprintf(stderr, "%c", *c) ; }
           fprintf(stderr, "..." );
           { for (char* c=seq[i]+length[i]-20; (c < seq[i]+length[i]); ++c) fprintf(stderr, "%c", *c) ; }
         }
         fprintf(stderr, "\n" );
      }
   } 

     
   //long res = EditDistance_NW_Rec(seq[0], length[0], seq[1], length[1]);
   //long res = edit_distance_NW_cache_aware(seq[0], length[0], seq[1], length[1], 4096);
   long res = edit_distance_NW_iteratif_direct(seq[0], length[0], seq[1], length[1]);
   //long res = edit_distance_NW_cache_oblivious(40, seq[0], length[0], seq[1], length[1]);
   //printf("CA : %ld, DIR : %ld\n", res, resd);
   //long res = 0;
   //fflush(stdout);
   {  for( int i = 0; i < 2; ++i ) 
      {  if (munmap( mmap_fd[i], (off_t) mmap_length[i]) != 0)  err(1, "munmap") ; 
         if (close( fd[i] ) != 0)  err(1, "close") ; 
      }
   }

   printf("%ld\n", res ) ; // print the distance on stdout
   return 0 ;
}

