#include<iostream>
#include<stdbool.h>
#include<string.h>
#include<sstream>
#include<ctype.h>
using namespace std;

template<typename T>
void ascendingsort(T *arr, int n)
{
	for (int i = 0; i < n; i = i+1)                     
	{
		for (int j = 0; j < n; j = j+1)             
		{
			if (arr[j] > arr[i])               
			{
				T tmp = arr[i];         
				arr[i] = arr[j];            
				arr[j] = tmp;             
			}  
		}
	}
}

template<typename T>
void descendingsort(T *arr, int n)
{
	for (int i = 0; i < n; i = i+1)                     
	{
		for (int j = 0; j < n; j = j+1)             
		{
			if (arr[j] < arr[i])                
			{
				T tmp = arr[i];         
				arr[i] = arr[j];            
				arr[j] = tmp;             
			}
		}
	}
}

template<typename T>
void print(T *arr,int n)
{
	cout << "Sorted Array is: ";
	for(int i=0; i<n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
}

bool isallLen1(int argc, char *argv[]);
bool ischar(int argc, char *argv[]);
bool isint(int argc, char *argv[]);
bool isfloat(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		printf("Too few arguments passed\n");//cout << "Few arguments passed.\n";
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	int s = atoi(argv[2]);

	if(s != 1 && s != 2)
	{
		printf("Incorrect choice entered\n");//cout << "Incorrect choice entered.\n";
		exit(EXIT_FAILURE);
	}

	if(argc-3 != n)
	{
		printf("Enter array of specified size\n");//cout << "Enter array of specified size.\n";
		exit(EXIT_FAILURE);
	}

	int arr1[n];
	float arr2[n];
	char arr3[n];
	
	if(isallLen1(argc,argv))
	{
		if(ischar(argc,argv)) 
		{
			for(int i = 4; i <= argc; i = i+1)
				arr3[i-4] = argv[i-1][0];
			if(s == 1)
				ascendingsort<char>(arr3, n);
			if(s == 2)
				descendingsort<char>(arr3, n);
			print<char>(arr3, n);
			exit(EXIT_SUCCESS);
		}
		else
		{
			for(int i = 4; i <= argc; i = i+1) 
				arr1[i-4] = atoi(argv[i-1]);
			if(s == 1)
				ascendingsort<int>(arr1, n);
			if(s == 2)
				descendingsort<int>(arr1, n);
			print<int>(arr1, n);
			exit(EXIT_SUCCESS);
		}
	}

	else
	{
		if(isint(argc,argv))
		{
			for(int i = 4; i <= argc; i = i+1) 
				arr1[i-4] = atoi(argv[i-1]);
			if(s == 1)
				ascendingsort<int>(arr1, n);
			if(s == 2)
				descendingsort<int>(arr1, n);
			print<int>(arr1, n);
			exit(EXIT_SUCCESS);
		}
		else if(isfloat(argc,argv))
		{
			for(int i = 4; i <= argc; i = i+1) 
				arr2[i-4] = atof(argv[i-1]);
			if(s == 1)
				ascendingsort<float>(arr2, n);
			if(s == 2)
				descendingsort<float>(arr2, n);
			print<float>(arr2, n);
			exit(EXIT_SUCCESS);
		}
		else
			{
				printf("Input is invalid\n"); 
				exit(EXIT_FAILURE);
			}
	}

    return 0;
}		      

bool isallLen1(int argc, char *argv[])
{
	for (int i = 4; i <= argc; i = i+1)
	{
		if (strlen(argv[i-1]) != 1)
			return false;
	}
	return true;
}

bool ischar(int argc, char *argv[])
{
	for(int i = 4; i <= argc; i = i+1)
	{
		if(isalpha(argv[i-1][0]) != 0) 
			return true;
	}
	return false;
}

bool isint(int argc, char *argv[])
{
	int x;
    	string a;
    	for(int i = 4; i <= argc; i = i+1)
    	{
    	    x = atoi(argv[i-1]);
    	    a = to_string(x);
    	    string y = string(argv[i-1]);
    	    if(y.compare(a) != 0)
    	        return false;
 	}
    return true;
}

bool isfloat(int argc, char *argv[])
{
	float x;    
	string a;
	for(int i = 4; i <= argc; i = i+1)
	{
		x = atof(argv[i-1]);
		stringstream ss;
		ss << x;
		a = ss.str();
		string y = string(argv[i-1]);
		if(y.compare(a) != 0)
	        	return false;
	}
    return true;
}


