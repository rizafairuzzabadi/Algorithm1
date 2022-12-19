// Muhammad Riza Fairuzzabadi
// 1501870908

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // std::setprecision
#include <math.h>  //pi
#include <ctime>

using namespace std;

class BinaryHeap
{
private:
    vector<double> heap;
    vector<double> heap_max;     // for max heap, may be redundant
    double Left(double parent);  // left child
    double Right(double parent); // right child
    double Parent(double child); // parent
    void heapup(int index);      // heap upperward (to parents) "Decrease"
    void heapdown(int index);    // downward, swapping childs

public:
    BinaryHeap() {}
    void Insert(double element); // insert element
    void DeleteMin();            // delete min element

    // Estimate function, functions as the 'printer' of the outputted data
    string Estimate(string starting_date, string starting_time, string latest_date, string latest_time, int n_estimators, string *estimators);

    void heapify_max(vector<double> &maxheap, int N, int i);

    double ExtractMin();                                   // extract min element
    double MeanofHeap();                                   // mean of heap
    double stdDevofHeap();                                 // standard deviation of heap
    double MedianofHeap(vector<double> sortedheap);        // median of heap
    double minofHeap();                                    // min  of heap
    double maxofHeap();                                    // max of heap
    double firstquartileofHeap(vector<double> sortedheap); // first quartile of heap
    double thirdquartileofHeap(vector<double> sortedheap); // third quartile of heap
};

void BinaryHeap ::Insert(double ele)
{
    heap.push_back(ele);     // insert new value at the end of the heap
    heapup(heap.size() - 1); // heapup the element
}
void BinaryHeap ::DeleteMin()
{
    if (heap.size() == 0)
    {
        cout << "Heap is Empty" << endl; // Just an error message, redundant
        return;
    }
    heap[0] = heap.at(heap.size() - 1); // replace the root with the last element
    // heap[0] = heap.at(heap.size() - 1);
    heap.pop_back(); // delete the last element
    heapdown(0);     // heapdown the root
}
string BinaryHeap ::Estimate(string st_date, string st_time, string l_date, string l_time, int n_est, string *esti)
{
    // In this function we call the operation functions according to the request,
    //  convert them to string in the specified format, and return them back to main
    string Result; // string to be returned
    Result = st_date + ',' + st_time + ',' + l_date + ',' + l_time;
    for (int i = 0; i < n_est; i++)
    {
        // Check whichever operation is requested, and call the respective function
        if (esti[i] == "median" || esti[i] == "firstq" || esti[i] == "thirdq")
        {
            // only sort the heap when the operation is median, firstq or thirdq
            // Because the other operations do not require the heap to be sorted
            heap_max = heap; // copy the heap to heap_max
            int n = heap_max.size();
            for (int y = n / 2 - 1; y >= 0; y--) // build max heap
                heapify_max(heap_max, n, y);
            for (int z = n - 1; z >= 0; z--)
            {
                swap(heap_max[0], heap_max[z]); // Heap Sort,  swap the root with the last element
                heapify_max(heap_max, z, 0);    // heapify the root
            }
        }

        if (esti[i] == "mean")
        {
            ostringstream os;   // convert double to string using ostringstream
            os << MeanofHeap(); // because to_string creates unnecesssary extra zeros
            Result += ',' + os.str();
        }
        else if (esti[i] == "std")
        {
            ostringstream os; // continues similarly for the other operations
            os << stdDevofHeap();
            Result += ',' + os.str();
        }
        else if (esti[i] == "median")
        {
            ostringstream os;
            os << MedianofHeap(heap_max);
            Result += ',' + os.str();
        }
        else if (esti[i] == "min")
        {
            ostringstream os;
            os << ExtractMin();
            Result += ',' + os.str();
        }
        else if (esti[i] == "max")
        {
            ostringstream os;
            os << maxofHeap();
            Result += ',' + os.str();
        }
        else if (esti[i] == "firstq")
        {
            ostringstream os;
            os << firstquartileofHeap(heap_max);
            Result += ',' + os.str();
        }
        else if (esti[i] == "thirdq")
        {
            ostringstream os;
            os << thirdquartileofHeap(heap_max);
            Result += ',' + os.str();
        }
    }
    return Result; // return the string after all format is created by appending
}

void swap(double *a, double *b) // swap function between two elements
{
    double temp = *a; // simple swap operation
    *a = *b;
    *b = temp;
}

double BinaryHeap::MedianofHeap(vector<double> sorted_heap)
{
    // Median. The heap is sorted earlier, so this just has to find the middle element

    int size = sorted_heap.size();
    if (size % 2 == 0)
    {
        // or do a simple average of the two middle elements when needed
        return (heap_max[size / 2 - 1] + heap_max[size / 2]) / 2;
    }
    else
    {
        return heap_max[size / 2];
    }
}

double BinaryHeap ::firstquartileofHeap(vector<double> sorted_heap)
{
    // Quartile calculation with Interpolation methods, N-1 Basis.
    double firstquartile = 0;
    int size = sorted_heap.size();

    if (size % 4 == 0 || size % 4 == 1 || size % 4 == 2 || size % 4 == 3)
    {
        double index = 0.25 * (size - 1); // calculating the index
        int fl_index = floor(index);      // floored/rounded down index
        if (index - floor(index) == 0)
        { // if exact
            sorted_heap[index];
        }
        else if ((index - floor(index)) > 0.5)
        { // if closer to the next element
            firstquartile = 0.25 * (sorted_heap[fl_index]) + 0.75 * (sorted_heap[fl_index + 1]);
        }
        else if ((index - floor(index)) < 0.5)
        { // if closer to the current element
            firstquartile = 0.75 * (sorted_heap[fl_index]) + 0.25 * (sorted_heap[fl_index + 1]);
        }
        else if ((index - floor(index)) == 0.5)
        { // if exactly in the middle
            firstquartile = 0.5 * (sorted_heap[fl_index]) + 0.5 * (sorted_heap[fl_index + 1]);
        }
    }
    return firstquartile;
}
double BinaryHeap ::thirdquartileofHeap(vector<double> sorted_heap)
{
    // Quartile calculation with Interpolation methods, N-1 Basis. Only difference being (0.75)
    double thirdquartile = 0;
    int size = sorted_heap.size();

    if (size % 4 == 0 || size % 4 == 1 || size % 4 == 2 || size % 4 == 3)
    {
        double index = 0.75 * (size - 1); // calculating the index
        int fl_index = floor(index);      // floored/rounded down index
        if (index - floor(index) == 0)
        { // if exact
            sorted_heap[index];
        }
        else if ((index - floor(index)) > 0.5)
        { // if closer to the next element
            thirdquartile = 0.25 * (sorted_heap[fl_index]) + 0.75 * (sorted_heap[fl_index + 1]);
        }
        else if ((index - floor(index)) < 0.5)
        { // if closer to the current element
            thirdquartile = 0.75 * (sorted_heap[fl_index]) + 0.25 * (sorted_heap[fl_index + 1]);
        }
        else if ((index - floor(index)) == 0.5)
        { // if exactly in the middle
            thirdquartile = 0.5 * (sorted_heap[fl_index]) + 0.5 * (sorted_heap[fl_index + 1]);
        }
    }
    return thirdquartile;
}

void BinaryHeap::heapify_max(vector<double> &maxheap, int N, int i)
{
    // Heapify function for max heap
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left
    int r = 2 * i + 2; // right

    // If left child is greater than root
    if (l < N && maxheap[l] > maxheap[largest])
        largest = l;

    // If right child is greater than current largest
    if (r < N && maxheap[r] > maxheap[largest])
        largest = r;

    // If largest != i
    if (largest != i)
    {
        swap(maxheap[i], maxheap[largest]);

        // Recursively heapify sub-tree
        heapify_max(maxheap, N, largest);
    }
}

double BinaryHeap ::ExtractMin() // getting the min value
{
    if (heap.size() == 0)
    {
        return -1;
    }
    else
        return heap.front(); // return the root, being a min-heap
}
double BinaryHeap ::Left(double parent)
{
    double l = 2 * parent + 1; // left child
    if (l < heap.size())
        return l;
    else
        return -1;
}
double BinaryHeap ::Right(double parent)
{
    double r = 2 * parent + 2; // right child
    if (r < heap.size())
        return r;
    else
        return -1;
}
double BinaryHeap ::Parent(double child)
{
    double p = (child - 1) / 2; // parent
    if (child == 0)
        return -1;
    else
        return p;
}
void BinaryHeap ::heapup(int in)
{
    if (in >= 0 && Parent(in) >= 0 && heap[Parent(in)] > heap[in])
    { // finding correct place
        double temp = heap[in];
        heap[in] = heap[Parent(in)];
        heap[Parent(in)] = temp;
        heapup(Parent(in)); // swap the value of i with value of parent
    }
}
void BinaryHeap ::heapdown(int in)
{
    double child = Left(in); // rebuild the heap down after extracts, redundant, written due to initial misunderstanding of 'flush', detail in the report
    double child1 = Right(in);
    if (child >= 0 && child1 >= 0 && heap[child] > heap[child1])
    {
        child = child1; // look which child to go
    }
    if (child > 0 && heap[in] > heap[child])
    {
        double t = heap[in];
        heap[in] = heap[child];
        heap[child] = t; // swap heap[i] with child
        heapdown(child);
    }
}
double BinaryHeap ::MeanofHeap()
{
    double mean = 0; // simple mean/average calculation
    int i = 0;
    for (i = 0; i <= heap.size(); i++)
    {
        mean += heap[i];
    }
    mean = mean / heap.size();
    return mean;
}
double BinaryHeap ::stdDevofHeap()
{
    double mean = MeanofHeap(); // standard deviation calculation
    double stdDev = 0;
    for (int i = 0; i < heap.size(); i++)
    {
        stdDev += pow((heap[i] - mean), 2); // sum of squares
    }
    stdDev = sqrt(stdDev / (heap.size() - 1.0)); // square root of sum of squares
    return stdDev;
}

double BinaryHeap ::maxofHeap()
{
    double maximum = heap[heap.size() / 2]; // finding max on min-heap, max is at leaves
    for (int i = 1 + heap.size() / 2; i < heap.size(); i++)
    {
        maximum = max(maximum, heap[i]);
    }
    return maximum;
}

int main(int argc, char *argv[1])
{
    string name_file; // file name inputted by user
    stringstream in(argv[1]);
    in >> name_file;

    ifstream file;
    file.open(name_file); // opening the file

    if (!file)
    {
        cerr << "File cannot be opened!"; // error message if file cannot be opened
        exit(1);
    }

    BinaryHeap heap; // creating a heap object
    clock_t start;   // clock to calculate time
    start = clock(); // start clock

    int n_estimators = 0; // number of estimators (mean, quartiles, etc)
    int i = 0;
    string line;                                   // line of file
    getline(file, line, '\n');                     // get the first line, estimator number
    n_estimators = stoi(line);                     // convert to int
    string *estimators = new string[n_estimators]; // array of estimators
    while (i < n_estimators)
    {
        getline(file, estimators[i]); // get the estimators
        i++;
    }

    int n_operations = 0;      // number of operations (add, print)
    string operated_data;      // data to be operated on
    getline(file, line);       // empty line
    getline(file, line, ',');  // get the n of operations
    n_operations = stoi(line); // convert to int
    // cout << n_operations << endl;
    getline(file, operated_data); // which data to be calculated

    i = 0;
    int count = 0; // counter of print operations
    string *prints = new string[n_operations];
    string starting_date; // starting date
    string starting_time; // starting time
    string latest_date;   // latest date
    string latest_time;   // latest time

    while (i < n_operations)
    {
        getline(file, line); // get the first operation
        i++;
        if (line == "add")
        {                                 // if add
            string day, time;             // day and time
            double gap, grp, voltage, gi; // gap, grp, voltage, gi
            getline(file, day, ',');      // read line by line
            getline(file, time, ',');
            getline(file, line, ',');
            gap = stod(line);
            getline(file, line, ',');
            grp = stod(line);
            getline(file, line, ',');
            voltage = stod(line);
            getline(file, line);
            gi = stod(line);

            if (i == 1)
            {
                starting_date = day;  // set the starting date, if it was the first add operation
                starting_time = time; // set the starting time
            }

            latest_date = day;  // set/update the latest date
            latest_time = time; // set/update the latest time

            if (operated_data == "gap")
            { // if gap is the operated data, insert gap to the heap
                heap.Insert(gap);
            }
            else if (operated_data == "grp")
            { // if grp is the operated data, insert grp to the heap
                heap.Insert(grp);
            }
            else if (operated_data == "voltage")
            { // if voltage is the operated data, insert voltage to the heap
                heap.Insert(voltage);
            }
            else if (operated_data == "gi")
            { // if gi is the operated data, insert gi to the heap
                heap.Insert(gi);
            }
            i++; // read counter incremenents
        }
        else if (line == "print")
        {
            prints[count] = heap.Estimate(starting_date, starting_time, latest_date, latest_time, n_estimators, estimators); // if print, call the function to do the calculations
            count++;
            // heap.DeleteMin(); // I initially thought 'flush' means deleting one element after each print
        }
    }

    string file_name2 = name_file.erase(0, 5); // erase the 'input' part of file name
    file_name2 = "output" + file_name2;        // and change to 'output'

    ofstream datafile(file_name2); // create a new file
    for (int i = 0; i < count; i++)
    {
        datafile << prints[i] << endl; // write the results to the file
    }

    return 0;
}