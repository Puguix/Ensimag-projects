#include "characters_to_base.h"

void ManageBaseError(char c)
{ 
   #ifdef BASE_ERROR_TREATMENT
   {  if (isBase(c)) return ; // no error
      if (isspace(c)) return ; // \n or \t or ' ' etc are  ignored 
      switch ( BASE_ERROR_TREATMENT )
      {  case BASE_WARNING : 
            fprintf(stderr, "Warning: character %c=0x%xc not matching a base is skipped.\n", c, c ) ;
            break;
         case BASE_ERROR :
            fprintf(stderr, 
               "Error: character %c=0x%xc  not matching a base is skipped.\n"
               "   Expected bases:A=0x%xc, a=0x%xc, C=0x%xc, c=0x%xc, G=0x%xc, g=0x%xc, T=0x%xc, t=0x%xc, U0x%xc, u=0x%xc\n",
               c, c, 'A', 'a', 'C', 'c', 'G', 'g', 'T', 't', 'U', 'u' 
            ) ;
            exit(EXIT_FAILURE) ;
         default: break ;
      }
   }
   #endif
   /* else no errors are managed */
   return;
}