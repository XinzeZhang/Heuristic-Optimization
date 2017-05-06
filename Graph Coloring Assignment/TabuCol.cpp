                                                                                /*
 *  Algorithme ITS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This program demonstrates the use of the heuristic algorithm for solving
 * the problem of graph coloring. For more information about this algorithm,
 * email to: lu@info-univ.angers.fr.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <ctime>
#include <vector>
#include<math.h>
#include<conio.h>
#include<ctype.h>
#define VN 2000

using namespace std;

char * File_Name;
FILE *fp ;
char outfilename[30];
int Seed ;
int Total_Iterations ;
int Max_Non_Improv_One = 200000 ;
double starting_time, finishing_time, once_total_time, total_time ;

typedef struct Adjacent_Matrix{
         int neighbor ;
         struct Adjacent_Matrix *next ;
         }Adjacent ;
Adjacent * *A_Matrix ;
Adjacent *p1, *q1;

int N, K, G_K;  // node number and color number
int f, f_best, global_f_best;
int * Color; // color array for each vertex
int * Best_Color, * Global_Best_Color; // color array for each vertex
int ** Delta_Matrix;  // incremental matrix for each vertex being colored each color
int ** Edge;   // adjacent matrix
int ** TabuTenure;  // tabu tenure

/*****************************************************************************/
/*****************          1. Initializing           ************************/
/*****************************************************************************/
//1.1 Intializations
void Initializing()
{
     int i, j, x, y, x1, x2;
	 ifstream FIC;
     FIC.open(File_Name);
     if ( FIC.fail() )
     {
           cout << "### Erreur open, File_Name " << File_Name << endl;
           exit(0);
     }
     char StrReading[100];
     FIC >> StrReading;
     if ( FIC.eof() )
     {
           cout << "### Error open, File_Name " << File_Name << endl;
           exit(0);
     }
     //int nb_vtx=0 ;
     int nb_edg=-1, max_edg=0;
     while ( ! FIC.eof() )
     {
           char bidon[50];
           if ( strcmp(StrReading, "p" )==0 )
           {
              FIC >> bidon >> N >> nb_edg;
              cout << "Number of vertexes = " << N << endl;
              cout << "Number of edges = " << nb_edg << endl;

              Color = new int[N];
              Best_Color = new int[N];
              Global_Best_Color = new int[N];
           //   Move_Freq = new int[N];

              for( x = 0 ; x < N ; x++ )
                 {
                   Color[x] = rand() % K ;
            //       Move_Freq[ x ] = 0 ;
                 }

              Edge=new int*[N];
              for (x = 0 ; x < N ; x++ )
                  Edge[x]= new int[N];

              Colored = new int [N];
              Coloring_Cost = new int*[N];
              for (x = 0 ; x < N ; x++ )
                    Coloring_Cost[x]= new int[K];
              Num_Avail_Colors = new int [N];

              A_Matrix = new Adjacent *[N];
              for( i = 0 ; i < N; i ++ )
                 {
                   A_Matrix[ i ] = new Adjacent ;
                   A_Matrix[ i ]->neighbor = 0 ;
                   A_Matrix[ i ]->next = NULL ;
                 }

              Delta_Matrix=new int*[N];
              for (x=0;x<N;x++) Delta_Matrix[x]=new int[K];
                  TabuTenure=new int*[N];

              for (x=0;x<N;x++) TabuTenure[x]=new int[K];

              for (x=0;x<N;x++)
                   for (y=0;y<N;y++)
                            {
                               Edge[x][y]=0;
                            }
              break ;
			}
			FIC >> StrReading;
        }

      while ( ! FIC.eof() )
         {
		   if ( strcmp(StrReading, "e")==0 )
           {
                 FIC >> x1 >> x2;
                 // cout << x1 << x2 << endl;
                 x1--; x2--;
                 if ( x1<0 || x2<0 || x1>=N || x2 >=N )
                 {
                       cout << "### Error of node : x1="
                            << x1 << ", x2=" << x2 << endl;
                       exit(0);
                 }
                 Edge[x1][x2]=Edge[x2][x1]=1;
                 max_edg++;
                 // add x2 to x1's neighbor list
                 p1 = A_Matrix[ x1 ] ;
                 A_Matrix[ x1 ]->neighbor ++ ;
                 while( p1->next != NULL )
                      p1 = p1->next;
                 q1 = new Adjacent ;
                 q1->neighbor = x2 ;
                 q1->next = NULL ;
                 p1->next = q1 ;

                 // add x1 to x2's neighbor list
                 p1 = A_Matrix[ x2 ] ;
                 A_Matrix[ x2 ]->neighbor ++ ;
                 while( p1->next != NULL )
                    p1 = p1->next;
                 q1 = new Adjacent ;
                 q1->neighbor = x1 ;
                 q1->next = NULL ;
                 p1->next = q1 ;
           }
           FIC >> StrReading;
     }
     cout << "Density = " << (float) 2 * max_edg/(N*(N-1)) << endl;
     if ( 0 && max_edg != nb_edg )
     {
           cout << "### Error de lecture du graphe, nbre aretes : annonce="
                 << nb_edg << ", lu=" << max_edg  << endl;
           exit(0);
     }

     FIC.close();
}

/*****************************************************************************/
/*****************            Main Function           ************************/
/*****************************************************************************/
int main(int argc, char **argv)
{

     return 1;
}

