#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <time.h>  
#include <math.h>       

using namespace std;

class GlobalSale{ // Sales class 

    string country;
    string item_type;
    string order_id;
    int units_sold;
    float total_profit;

	public:

    void setCountry(string); 
    void setType(string);
	void setorderID(string);
	void setUnit(int);
	void setTotalProfit(float);
	string get_country();
	string get_type();
	string get_ID();
	int get_unit();
	float get_totalProfit();
};

void GlobalSale::setCountry(string country){
	this->country = country;
}

void GlobalSale::setType(string type){
	this->item_type = type;
}

void GlobalSale::setorderID(string ID){
	this->order_id = ID;
}

void GlobalSale::setUnit(int unit){
	this->units_sold = unit;
}

void GlobalSale::setTotalProfit(float total_profit){
	this->total_profit = total_profit;
}

string GlobalSale::get_country(){
	return country;
}

string GlobalSale::get_type(){
	return item_type;
}

string GlobalSale::get_ID(){
	return order_id;
}

int GlobalSale::get_unit(){
	return units_sold;
}

float GlobalSale::get_totalProfit(){
	return total_profit;
}

void printArray(vector<GlobalSale> profits_array,int N){ //for printing array
	for(int i = 0; i<N; i++){
		cout << profits_array[i].get_country() << " "
			<< profits_array[i].get_type() << " "
			<< profits_array[i].get_ID() << " "
			<< profits_array[i].get_unit() << " "
			<< profits_array[i].get_totalProfit() << endl;
	}
}

void swap(GlobalSale &firstSale, GlobalSale &secondSale)  
{  
    GlobalSale tempSale = firstSale;  //temp sale
    firstSale = secondSale;  
    secondSale = tempSale;  
} 

int partition (vector<GlobalSale> &arr, int low, int high)  
{  
    string pivot = arr[high].get_country(); // pivot value 
    int i = low; // Index of first element will be the smaller element  
  
    for (int j = low; j < high; j++)  
    {  
        if (arr[j].get_country() < pivot) // If element is smaller than the pivot   
        {  
            swap(arr[i], arr[j]);
			i++; // increment index of smaller element 
        }  else if (arr[j].get_country() == pivot){
			if (arr[j].get_totalProfit() > arr[high].get_totalProfit()){ //put higher into the left of pivot
				swap(arr[i], arr[j]);
				i++; // increment index of smaller element 
			}
		}
    }  
    swap(arr[i], arr[high]); // put pivot at where it must be  
    return i;  //return pivots last index
} 

void quickSort(vector<GlobalSale> &arr, int left, int right) {  
    if (left < right) {
        int pivotIndex = partition(arr, left, right); //this will be used for next high and low index
        quickSort(arr, left, pivotIndex - 1);  //left part of pivot
        quickSort(arr, pivotIndex + 1, right);  //right part of pivot
    }  
}  

int main(int argc, char** argv){
	
	ifstream file;
	file.open("sales.txt");

	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}

	vector<GlobalSale> profits_array; // sales will be collected at this array
	
	int N = stoi(argv[1]); //you should read value of N from command line
	string line;
	
	getline(file, line); //this is the header line

	for(int i = 0; i<N; i++){
		GlobalSale new_sale;
		getline(file, line, '\t'); //country (string)
		new_sale.setCountry(line);
		getline(file, line, '\t'); //item type (string)
		new_sale.setType(line);
		getline(file, line, '\t'); //order id (string)
		new_sale.setorderID(line);
		file >> line; //units sold (integer)
		new_sale.setUnit(stoi(line));
		file >> line; //total profit (float)
		new_sale.setTotalProfit(stof(line));

	    getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
		profits_array.push_back(new_sale); //new sale is put into the array
	}
	//printArray(profits_array,N);
	clock_t t;
	t = clock();
		quickSort(profits_array,0,N-1); // run sorting algorithm
  	t = clock() - t; // calculate running time
  	printf ("It took %f seconds.\n",((float)t)/CLOCKS_PER_SEC);


//THIS PART WILL BE USED FOR WRITING TO TEXT CALLED 'sorted.txt'

	ofstream myfile;
  	myfile.open ("sorted.txt");
	if (!myfile){
		cerr << "File cannot be opened!";
		exit(1);
	}

	myfile << "Country" << "	" << "Item Type" << "	" << "Order ID" << "	" << "Units Sold" << "	" << "Total Profit" << endl; // put header line
	myfile << fixed;
	for(int i = 0; i<N; i++){ //writing sorted sales to file called sorted
		myfile << profits_array[i].get_country() << "	" << profits_array[i].get_type() << "	" << profits_array[i].get_ID() << "	" << profits_array[i].get_unit() << "	" << profits_array[i].get_totalProfit() << endl;
	}
	myfile.close();
	file.close();
	return 0;
}
