#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <sstream>
#include <ctime>

using namespace std;

struct dataset{
    string country;
    string item_type;
    string order_id;
    int units_sold;
    double profit;
};

int partition(vector<dataset>&dataSet, int l, int r){
    int pivot  = r;
    int i = l - 1;

    for(int a = l; a <= r-1 ; a++) {
        if (dataSet.at(a).country < dataSet.at(pivot).country){
                i++;
                swap(dataSet.at(i), dataSet.at(a));
        }
        else if(dataSet.at(a).country == dataSet.at(pivot).country){
            if(dataSet.at(pivot).profit <= dataSet.at(a).profit){
                    i++;
                    swap(dataSet.at(i), dataSet.at(a));
            }
        }
    }
    swap(dataSet.at(i+1), dataSet.at(pivot));
    return i + 1;
}

void quicksort(vector<dataset> &sorted_data, int lhs, int rhs){
    if (lhs < rhs) {
        int p = partition(sorted_data, lhs, rhs);
        quicksort(sorted_data, lhs, p-1);
        quicksort(sorted_data, p+1, rhs);
    }
}

int main(int argc,char *argv[1]){

	ifstream file;
	file.open("sales.txt");
	
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}

	int N;          //vector capacity, number of data to take
	stringstream in(argv[1]);
	in >> N;
	vector<dataset> data;
	clock_t start;

    string line;
    getline(file, line); //this is the header line
	for(int i = 0; i<N; i++){
	    dataset add;

	    getline(file, line, '\t'); //country (string)
        add.country = line;
		getline(file, line, '\t'); //item type (string)
        add.item_type = line;
		getline(file, line, '\t'); //order id (string)
        add.order_id = line;
		file >> line; //units sold (integer)
        add.units_sold = stoi(line);
		file >> line; //total profit (float)
        add.profit = stof(line);

	    data.push_back(add);
        getline(file, line, '\n'); //this is for reading the \n character into dummy variable.

	}

    int a = 0;  //lowest index
    int b = N-1;//highest index
    start = clock();    //start counting the elapsed time
    quicksort(data, a, b);
    double elapsed_time = (clock() - start)/(double) CLOCKS_PER_SEC;
    cout << "Elapsed time of execution - "<< elapsed_time << endl;

    ofstream datafile("sorted.txt");        //creates and opens sorted.txt
    datafile << "Country\tItem Type\tOrder ID\tUnits Sold\tTotal Profit" << endl;
    for (int i = 0; i < N; i++){
        datafile<< data.at(i).country << '\t' << data.at(i).item_type << '\t' << data.at(i).order_id << '\t' << data.at(i).units_sold << '\t' << data.at(i).profit << endl;
    }
    datafile.close();
	
	return 0;
}
