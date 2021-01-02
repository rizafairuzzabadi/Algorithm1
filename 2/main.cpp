#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // std::setprecision
#include <math.h>  //pi
#include <ctime>

using namespace std;

struct taxis
{
    double distance;
};

class BinaryHeap

{
private:
    vector<double> heap;
    double l(double parent);
    double r(double parent);
    double par(double child);
    void heapup(int index);
    void heapdown(int index);

public:
    BinaryHeap() {}
    void Insert(double element);
    void DeleteMin();
    void updaterandom(int number);
    double ExtractMin();
    void showHeap();
    int Size();
};

long double toRadians(const long double degree)
{

    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double dist;

    dist = pow(dlong, 2) + pow(dlat, 2); //calculating Euclidean distance
    dist = sqrt(dist);
    if (dist < 0)
        dist = 0 - dist;

    return dist;
}

int BinaryHeap ::Size()
{
    return heap.size();
}
void BinaryHeap ::Insert(double ele)
{
    heap.push_back(ele);
    heapup(heap.size() - 1);
}
void BinaryHeap ::DeleteMin()
{
    if (heap.size() == 0)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    cout << "A new taxi has been called. It's distance is: " << ExtractMin() << endl;
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapdown(0);
}

double BinaryHeap ::ExtractMin()
{
    if (heap.size() == 0)
    {
        return -1;
    }
    else
        return heap.front();
}

void BinaryHeap ::updaterandom(int ele)
{
    vector<double>::iterator pos = heap.begin();
    int i = 0;
    while (pos != heap.end())
    {
        if (i == ele)
        {
            double temp = *pos - 0.01;
            if (temp < 0)
                temp = 0 - temp;
            *pos = temp;
        }
        i++;
        pos++;
    }
}

double BinaryHeap ::l(double parent)
{
    double l = 2 * parent + 1;
    if (l < heap.size())
        return l;
    else
        return -1;
}
double BinaryHeap ::r(double parent)
{
    double r = 2 * parent + 2;
    if (r < heap.size())
        return r;
    else
        return -1;
}
double BinaryHeap ::par(double child)
{
    double p = (child - 1) / 2;
    if (child == 0)
        return -1;
    else
        return p;
}
void BinaryHeap ::heapup(int in)
{
    if (in >= 0 && par(in) >= 0 && heap[par(in)] > heap[in])
    {
        double temp = heap[in];
        heap[in] = heap[par(in)];
        heap[par(in)] = temp;
        heapup(par(in));
    }
}
void BinaryHeap ::heapdown(int in)
{
    double child = l(in);
    double child1 = r(in);
    if (child >= 0 && child1 >= 0 && heap[child] > heap[child1])
    {
        child = child1;
    }
    if (child > 0 && heap[in] > heap[child])
    {
        double t = heap[in];
        heap[in] = heap[child];
        heap[child] = t;
        heapdown(child);
    }
}

int main(int argc, char *argv[2])
{

    ifstream file;
    file.open("locations.txt");

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    double hotelong = 33.40819; //Hotel's longitude
    double hotelat = 39.19001;  //Hotel's latitude
    int totalupdates = 0;
    int totaladditions = 0;

    double m; //operations
    double p;
    stringstream min(argv[1]);
    stringstream pin(argv[2]);
    min >> m; //operations
    pin >> p; //probability

    p = p * 100.0;

    vector<taxis> data;
    BinaryHeap heap;
    clock_t start;
    start = clock();

    string line;

    getline(file, line); //this is the header line
    for (int i = 0; i <= m; i++)
    {
        taxis add;
        file >> line; //longitude
        double longitude = stof(line);
        file >> line; //latitude
        double latitude = stof(line);
        add.distance = distance(hotelat, hotelong, latitude, longitude);
        data.push_back(add);
        bool Probability = (rand() % 100) < p;
        if (Probability == true)
        {
            heap.Insert(distance(hotelat, hotelong, latitude, longitude)); //adding a taxi
            totaladditions++;
        }
        else
        {
            if (totaladditions >= 1)
            {
                int random = rand() % totaladditions;
                heap.updaterandom(random);
                totalupdates++;
            }
        }
        if (i >= 100 && (i % 100) == 0)
        {
            heap.DeleteMin();
        }
        getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
    }
    double running_time = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "The total number of taxi additions is: " << totaladditions << endl;
    cout << "The total number of distance updates is: " << totalupdates << endl;
    cout << "The total running time of the application is: " << running_time << " seconds" << endl;
}