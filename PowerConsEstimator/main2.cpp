#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // std::setprecision
#include <math.h>  //pi
#include <ctime>

using namespace std;

struct household
{
    string day;
    string time;
    double gap;
    double grp;
    double voltage;
    double gi;
};

class Heap
{
private:
    vector<double> heap;
    double l(double parent);
    double r(double parent);
    double par(double child);
    void heapup(int index);
    void heapdown(int index);
    int heap_size = 0;
    int heapvalue_total;

public:
    BinaryHeap() {}
    void Insert(double element);
    void DeleteMin();
    double ExtractMin();
    // int Size();
};

int main(int argc, char *argv[1])
{
    string name_file;
    stringstream in(argv[1]);
    in >> name_file;

    ifstream file;
    file.open(name_file);

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    vector<household> data;
    BinaryHeap heap;
    clock_t start;
    start = clock();

    int n_estimators = 0;
    int i = 0;
    string line;
    getline(file, line, '\n');
    n_estimators = stoi(line);
    string *estimators = new string[n_estimators];
    while(i < n_estimators){
        getline(file, estimators[i]);
        i++;
    }

    int n_operations = 0;
    string operated_data;
    getline(file, line);    //empty line
    getline(file, line, ',');
    n_operations = stoi(line);
    // cout << n_operations << endl;
    getline(file, operated_data);
    
    i = 0;
    while(i < n_operations){
        getline(file, line);
        i++;
        if(line == "add"){
            cout << line << endl;
            string day, time;
            double gap, grp, voltage, gi;
            getline(file, day,',');
            getline(file, time, ',');
            getline(file, line, ',');
            gap = stod(line);
            getline(file, line, ',');
            grp = stod(line);
            getline(file, line, ',');
            voltage = stod(line);
            getline(file, line);
            gi = stod(line);

            household h;
            h.day = day;
            h.time = time;
            h.gap = gap;
            h.grp = grp;
            h.voltage = voltage;
            h.gi = gi;
            data.push_back(h);
            i++;

            if(operated_data == "gap"){
                heap.Insert(gap);
            }
            else if(operated_data == "grp"){
                heap.Insert(grp);
            }
            else if(operated_data == "voltage"){
                heap.Insert(voltage);
            }
            else if(operated_data == "gi"){
                heap.Insert(gi);
            }
            // cout << day << ' ' << time << ' ' << gap << ' ' << grp << ' ' << voltage << ' ' << gi << endl;
        }
        else if(line == "print"){
            heap.DeleteMin();
            // cout << line << endl;
        }
    }
    cout << i;



    }