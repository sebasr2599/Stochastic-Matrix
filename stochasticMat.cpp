/*
 *  Stochastic matrix
 *
 *  Created on: 26.11.21
 *      Author: Sebastian Resendiz Chavez
 *		ID: A01701111
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <cmath>

int usages(char *flag, char *filename);
int user(char *rows, char *columns);
int automaticMat();
double** Make2DDoubleArray(int arraySizeX, int arraySizeY);
void print_arr(double **arr, int rows, int columns);
bool isStochastic(double **arr, int rows, int columns);
void printMenu();
void powMat(double **arr, double **powArr, int rows, int columns, int pow);
void matMul(double **arr, double **arr2, double **arrRet, int rows, int columns);
void matIni(double **arr, int rows, int columns);
bool isRegular(double **arr, int rows, int columns);

int main(int argc, char *argv[]){
    if (argc < 2) {
        return usages((char *)"", argv[0]);
    }
    if (strcmp(argv[1], "-u") == 0 && argc == 3)
        return user(argv[2],argv[2]);
    if (strcmp(argv[1], "-a") == 0 && argc == 2)
        return automaticMat();
    

    return usages(argv[1], argv[0]);
}

int usages(char *flag, char *filename){
    if(strcmp(flag, "-u") == 0){
        printf("usage: %s -u [number of rows and columns] \n", filename);
        return -2;
    }
    if(strcmp(flag, "-a") == 0){
        printf("usage: %s -a\n", filename);
        return -2;
    }
    printf("unknown option: %s\n", flag);
    printf("usage:\n%s", filename);
    printf(" -u [number of rows and columns]\n");
    printf("or\n");
    printf("%s -a\n",filename);
    return -2;
}
int user(char *rows, char *columns){
    std::cout<<"Please Enter a stochastic matrix"<<std::endl;
    int r = atoi(rows);
    int c = atoi(columns);
    double **arr = Make2DDoubleArray(r,c);
    for(int i =0; i<r; i++){
        for(int j = 0; j<c;j++){
            std::cin>>arr[i][j];
        }
    }
    while(!isStochastic(arr,r,c)){
        std::cout<<"The matrix is not stochastic please enter a stochastic matrix"<<std::endl;
        for(int i =0; i<r; i++){
            for(int j = 0; j<c;j++){
                std::cin>>arr[i][j];
            }
        } 
    }
    int des;
    do{
        printMenu();
        std::cin>>des;
        double **arrTemp = Make2DDoubleArray(r,c);
        switch(des){
            case 1:
                std::cout<<"Enter the direction i j of the matrix and the power"<<std::endl;
                int n,m,p;
                std::cin>>n>>m>>p;
                powMat(arr,arrTemp,r,c,p);
                std::cout<<"The probability is: "<<arrTemp[n][m]<<std::endl;
                for (int i = 0; i < r; i++){
                    free(arrTemp[i]);
                }
                free(arrTemp);
                break;
            case 2:
                powMat(arr,arrTemp,r,c,100);
                std::cout<<"The long term of the matrix is"<<std::endl;
                print_arr(arrTemp,r,c);
                for (int i = 0; i < r; i++){
                    free(arrTemp[i]);
                }
                free(arrTemp);
                break;
            case 3:
                powMat(arr,arrTemp,r,c,100);
                isRegular(arrTemp,r,c)?std::cout<<"The matrix is regular": std::cout<<"The matrix is not regular";
                for (int i = 0; i < r; i++){
                    free(arrTemp[i]);
                }
                free(arrTemp);
                break;
            case 4:
                std::cout<<"Goodbye!"<<std::endl;
                break;
            default:
                break;
        }
    }while(des!=4);
    
    //free the allocated memory
    for (int i = 0; i < r; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}

int automaticMat(){
    int rows = 3, columns = 3;
    double **arr = Make2DDoubleArray(rows,columns);
    srand( (unsigned)time( NULL ) );

    for(int i = 0; i< rows; i++){
        int a = rand();
        int b = rand()%a/2;
        // printf("a: %d\tb: %d\n",a,b);
        float numA = (float) a/RAND_MAX;
        float numB = (float) b/RAND_MAX;
        float numC = 1.0 - (numA + numB);

        numA = floor(numA * 100.0) / 100.0;
        numB = floor(numB * 100.0) / 100.0;
        numC = floor(numC * 100.0) / 100.0;

        // printf("a: %f\tb: %f\tc: %f\n\n",numA,numB,numC);
        arr[i][0] = numA;
        arr[i][1] = numB;
        arr[i][2] = numC;
        // for(int j = 0; j<columns; i++){
        //     arr[i][j] = 
        // }
    }
    std::cout<<"The stochastic Matrix is: "<<std::endl;
    print_arr(arr,rows, columns);
    
    int des;
    do{
        printMenu();
        std::cin>>des;
        int r = rows, c = columns;
        double **arrTemp = Make2DDoubleArray(r,c);
        switch(des){
            case 1:
                std::cout<<"Enter the direction i j of the matrix and the power"<<std::endl;
                int n,m,p;
                std::cin>>n>>m>>p;
                powMat(arr,arrTemp,r,c,p);
                std::cout<<"The probability is: "<<arrTemp[n][m]<<std::endl;
                for (int i = 0; i < r; i++){
                    free(arrTemp[i]);
                }
                free(arrTemp);
                break;
            case 2:
                powMat(arr,arrTemp,r,c,100);
                std::cout<<"The long term of the matrix is"<<std::endl;
                print_arr(arrTemp,r,c);
                for (int i = 0; i < r; i++){
                    free(arrTemp[i]);
                }
                free(arrTemp);
                break;
            case 3:
                powMat(arr,arrTemp,r,c,100);
                isRegular(arrTemp,r,c)?std::cout<<"The matrix is regular": std::cout<<"The matrix is not regular";
                for (int i = 0; i < r; i++){
                    free(arrTemp[i]);
                }
                free(arrTemp);
                break;
            case 4:
                std::cout<<"Goodbye!"<<std::endl;
                break;
            default:
                break;
        }
    }while(des!=4);
    
    //memory cleanup
    for (int i = 0; i < rows; i++){
        free(arr[i]);
    }

    free(arr);
    return 0;
}

void print_arr(double **arr, int rows, int columns){
    for(int i =0; i<rows; i++){
        for(int j = 0; j<columns;j++){
            std::cout<<arr[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

double** Make2DDoubleArray(int arraySizeX, int arraySizeY){
    double** theArray;
    theArray = (double**) malloc(arraySizeX*sizeof(double*));
    for (int i = 0; i < arraySizeX; i++)
    theArray[i] = (double*) malloc(arraySizeY*sizeof(double));
    return theArray;
}

bool isStochastic(double **arr, int rows, int columns){
    for(int i =0; i<rows; i++){
        double sum_colum = 0;
        for(int j = 0; j<columns;j++){
            sum_colum += arr[i][j];
        }
        if(sum_colum != 1.0)
            return false;
    }
    return true;
}

void printMenu(){
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<<"Option Menu with the stochastic matrix"<<std::endl;
    std::cout<<"Enter the desired option"<<std::endl;
    std::cout<<"1. Calculate the probability from going to one state to another in n steps"<<std::endl;
    std::cout<<"2. Calculate the long-term state (steady) of the matrix"<<std::endl;
    std::cout<<"3. Identify if the matrix is regular or not"<<std::endl;
    std::cout<<"4. Quit"<<std::endl;

    std::cout<<std::endl;
}

void powMat(double **arr, double **powArr, int rows, int columns, int p){
    matIni(powArr, rows, columns);
    double **arrTemp = Make2DDoubleArray(rows,columns);
    for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns;j++){
                arrTemp[i][j] = arr[i][j];
            }
        }
    for(int x = 0; x<p; x++){
        matMul(arr, arrTemp, powArr, rows, columns);
        for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns;j++){
                arrTemp[i][j] = powArr[i][j];
            }
        }
        print_arr(powArr,rows,columns);
        printf("\n");
    }
    
    
    for (int i = 0; i < rows; i++){
        free(arrTemp[i]);
    }
    free(arrTemp);
}

void matMul(double **arr, double **arr2, double **arrRet, int rows, int columns){
    matIni(arrRet, rows, columns);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            for(int k = 0; k < columns; ++k)
            {
                arrRet[i][j] += arr[i][k] * arr2[k][j];
                // std::cout<<arr[i][k]<<" * " <<arr2[k][j]<<std::endl;
            }
}

void matIni(double **arr,int rows, int columns){
    for(int i =0; i<rows; i++){
        for(int j = 0; j<columns;j++){
            arr[i][j] = 0;
        }
    }
}
bool isRegular(double **arr, int rows, int columns){
     for(int i =0; i<rows; i++){
        for(int j = 0; j<columns;j++){
            if(arr[i][j]<=0){
                return false;
            }
        }
        
    }
    return true;
}