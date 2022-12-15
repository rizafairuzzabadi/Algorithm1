// Muhammad Riza Fairuzzabadi
//1501870908

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // std::setprecision
#include <ctime>   //clock

using namespace std;

struct vehicle{         //to preserve the values of speed, ID, etc.
    int vehicle_ID;     //the heaps are in 'struct' form. 
    int speed_vh;       //vh = vehicle
    double distance_vh;
    double time;
    string location_vh;
};

class BinaryHeap
{
private:
    vector<vehicle> heap;
    double Left(double parent);     //left child     //Return Indexes
    double Right(double parent);    //right child
    double Parent(double child);    //parent      
    void heapup(int index);         //heap upperward (to parents) "Decrease"
    void heapdown(int index);       //downward, swapping childs
    
public:
    BinaryHeap() {}
    void Insert(vehicle element);
    void LuckyExtract(int requested);
    void ExtractVehicle();
    void updaterandom(int number);
    vehicle ExtractMin();
    void showHeap();
    int Size();

    int ExtractSpeed(int in) {return heap[in].speed_vh; };
    double ExtractDistance(int in) {return heap[in].distance_vh; }
    double ExtractTime(int in) {return heap[in].time; }
    int ExtractID(int in) { return heap[in].vehicle_ID; };

};

double time_to_destination(double dist_to_hotel, double speed_vh)
{   //Calculate the time to destination according to the formula
    double time_vh;     
    time_vh = dist_to_hotel / speed_vh;
    return time_vh;
}

int BinaryHeap ::Size()
{   //return heap size
    return heap.size();
}
void BinaryHeap ::Insert(vehicle vhc)
{
    heap.push_back(vhc);     //add new vehicle to heap
    heapup(heap.size() - 1); //look for suitable place
}
void BinaryHeap ::LuckyExtract(int requested)
{   //Extract when Lucky != 0
    if (heap.size() == 0)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    if(heap[requested].time > ExtractMin().time){
        if(ExtractMin().time > 1){
            heap[requested].time = ExtractMin().time - 1;   //decrease
        }
        else{
            heap[requested].time = 0;   //time is set > 0 so its time 
        }                               //would be the least -> minimum. This way it'll be extracted in the below function
        heapdown(0);    //rebuild the heap after the requested became 0
        ExtractVehicle(); //extract the minimum
    }

    else if(heap[requested].time == ExtractMin().time){
        return ;
    }
}
void BinaryHeap ::ExtractVehicle()
{
    if (heap.size() == 0)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    //cout << ExtractMin().vehicle_ID << " Extracted" << endl;
    heap[0] = heap.at(heap.size() - 1); //max assigned to first
    heap.pop_back();  //delete from the last index
    heapdown(0); //rebuild the heap from down
}
vehicle BinaryHeap ::ExtractMin()
{
    if (heap.size() == 0)
    {
        vehicle x;
        x.time = -1;
        return x;
    }
    else
        return heap.front();    //return the front, which in this case, min.
}
double BinaryHeap ::Left(double parent)
{   //return left id
    double l = 2 * parent + 1;
    if (l < heap.size())
        return l;
    else        
        return -1;
}
double BinaryHeap ::Right(double parent)
{   //return right id
    double r = 2 * parent + 2;
    if (r < heap.size())
        return r;
    else{
        return -1;
    }
}
double BinaryHeap ::Parent(double child)
{   //return parent id
    double p = (child - 1) / 2;
    if (child == 0){
        return -1;
    }
    else
        return p;
}
void BinaryHeap ::heapup(int in)
{
    if (in >= 0 && Parent(in) >= 0 && heap[Parent(in)].time > heap[in].time)
    {   //find the correct place to the updated distance
        vehicle temp;   
        temp = heap[in];
        heap[in] = heap[Parent(in)];
        heap[Parent(in)] = temp;
        heapup(Parent(in)); //swap the time of i with time of parent
    }
}
void BinaryHeap ::heapdown(int in)
{
    double child = Left(in);    //rebuild the heap down after extracts
    double child1 = Right(in);  
    if (child >= 0 && child1 >= 0 && heap[child].time > heap[child1].time)
    {
        child = child1; //look which child to go
    }
    if (child > 0 && heap[in].time > heap[child].time)
    {
        vehicle temp;
        temp = heap[in];
        heap[in] = heap[child];
        heap[child] = temp;//swap heap[i] with child
        heapdown(child);    
    }
}

int main(int argc, char *argv[1])
{
    ofstream filehistory("call_history.txt", ofstream::out);
    ofstream theheap("theheap.txt", ofstream::out);

    ifstream filereq, filehicle;
    //filehist.open("call_history_1000.txt");
    filereq.open("requests.txt");
    filehicle.open("vehicles.txt");
    //filehistory.open("call_history.txt")

    if (!filereq || !filehicle) 
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    int N; //total number of extract, decrease and insert operations

    stringstream number(argv[1]);
    vector<vehicle> data;
    BinaryHeap heap;

    number >> N; //probability

    clock_t start;

    string line1;   //line for filehicle
    string line2;   //line for filereq

    getline(filehicle, line1); //this is the header line
    for (int i = 0; i < 1642; i++)
    {
        vehicle add;

        filehicle >> line1; //reads space by space until \n
        int ID_vehicle = stof(line1);
        filehicle >> line1;
        string vehicle_loc = line1;
        filehicle >> line1;
        double vh_distance = stof(line1);
        filehicle >> line1;
        int vh_speed = stof(line1);

        add.time = time_to_destination(vh_distance, vh_speed);  //calculate time
        add.distance_vh = vh_distance;  //add to struct before inserting
        add.speed_vh = vh_speed;
        add.vehicle_ID = ID_vehicle;
        add.location_vh = vehicle_loc;

        heap.Insert(add); //adding a taxi
        getline(filehicle, line1, '\n'); //this is for reading the \n character into dummy variable.

        //cout << vehicle_ID << " " << vehicle_loc << " " << vh_distance << " " << vh_speed << endl;
    }

    start = clock();

    getline(filereq, line2);    //read first header line
    int i = 0;
    while(i < N){
        vehicle add;

        filereq >> line2;   //read word by word till newline
        string reqd_vh_loc = line2;
        filereq >> line2;
        double reqd_dist = stof(line2);
        filereq >> line2;
        int reqd_Lucky = stof(line2);

        add.location_vh = reqd_vh_loc;  //add location and distance beforewards for time calculation
        add.distance_vh = reqd_dist;

        if(reqd_Lucky == 0){ //if 0, the front / min is extracted. Therefore its speed and vehicle datas are taken
            add.speed_vh = heap.ExtractMin().speed_vh;
            add.vehicle_ID = heap.ExtractMin().vehicle_ID;
            add.time = time_to_destination(reqd_dist, add.speed_vh);

            filehistory << add.vehicle_ID << endl;

            heap.ExtractVehicle();
            i++; //extract = +1 operation
            heap.Insert(add);
            i++; //insert = +1 operation
        }
        else if(reqd_Lucky != 0){ //in this condition, speed and id of the requested index is taken with the functions
            add.speed_vh = heap.ExtractSpeed(reqd_Lucky);
            add.vehicle_ID = heap.ExtractID(reqd_Lucky);
            add.time = time_to_destination(reqd_dist, add.speed_vh);

            filehistory << add.vehicle_ID << endl;

            heap.LuckyExtract(reqd_Lucky);
            i = i+2; //Lucky = 1 extract and 1 decrease = +2 operation
            heap.Insert(add);
            i++; //Insert = +1 operation
        }
        getline(filehicle, line2, '\n'); //this is for reading the \n character into dummy variable.
    }
    start = clock() - start; // Time of operations
    cout << "Elapsed time of operations: " << ((double)start) / CLOCKS_PER_SEC << setprecision(10) << " seconds" << endl;
}