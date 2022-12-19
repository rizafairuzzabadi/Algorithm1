// BLG 335E - Analysis of Algorithms
// Homework 1
// Muhammad Rıza Faıruzzabadı
// 150170908

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

// int total_partitions = 0;       // to calculate the total number of partitions
// int total_swap = 0;              // to calculate the total number of swaps

struct dataset // the dataset columns defined as a struct.
{
    int bookID;
    string title;
    string authors;
    double average_rating;
    string isbn;   // added as a string as its value is large even for 'long long'
    string isbn13; // added as string due to its format being non-convertible
    string language_code;
    int num_pages; // Actually not necessary to be stored as ints because we only use average_rating for calculations
    int ratings_count;
    int text_reviews_count;
    string publication_date;
    string publisher;
};

int partition_I(vector<dataset> &thedata, int lhs, int rhs)
{
    int Low = lhs;
    int High = rhs; // max element / index
    int i = Low;    // defining i and j
    int j = Low;

    double pivot = thedata.at(High).average_rating; // highest as pivot, according to Psuedocode

    while (i <= j)
    {
        if (thedata.at(i).average_rating <= pivot && thedata.at(j).average_rating <= pivot)
        { // while both are less than pivot, increment i and j
            j++;
            i++;
        }
        if (thedata.at(j).average_rating > pivot) // if j is greater than pivot,
        {
            j++; // increment it so it can be swapped with i.
            // total_swap++;           //increment swap counter - global variable
            swap(thedata.at(i), thedata.at(j)); // swap i and j
            if (thedata.at(i).average_rating <= pivot)
            {
                i++; // only when i is less than pivot, it is incremented
            }
        }
        if (j == High)
        {
            // total_swap++;           //increment swap counter - global variable
            swap(thedata.at(i), thedata.at(High)); // swap i and High
            break;                                 // break out while loop, so current i value's returned
        }
    }
    return i;
}

void quicksort_I(vector<dataset> &sorted_data, int Low, int High)
{
    if (Low < High)
    {
        // total_partitions++;          //increment partition counter - global variable
        int i = partition_I(sorted_data, Low, High); // receives returned i for partitioning
        quicksort_I(sorted_data, Low, i - 1);        // repeat sorting for left sub array
        quicksort_I(sorted_data, i + 1, High);       // repeat for right sub array
    }
}

// Implementation for QuickSort II/2nd Pseudocode. Turned out unneccesary, but kept anyway.
int partition_II(vector<dataset> &thedata, int lhs, int rhs)
{
    int Low = lhs;  // definitions according to pseudocode, may not be necessary, but done regardless so it's more similar to the pseudocode
    int High = rhs; // max element / index
    int i = Low;
    int j = High;
    int random_num = rand() % (High - Low + 1) + Low;     // random number betweeen Low and High (includes them)
    double pivot = thedata.at(random_num).average_rating; // highest as pivot, according to Psuedocode

    while (i < j) // under the condition  j>i
    {
        if (thedata.at(i).average_rating <= pivot)
        {
            i++; // increment i while it is less than pivot
        }
        if (thedata.at(j).average_rating >= pivot)
        {
            j--; // decrement j while it is greater than pivot
        }
        else
        {
            swap(thedata.at(i), thedata.at(j)); // otherwise swap i and j
        }
        if (i >= j)
        {
            break; // break out of while loop so i is retuned
        }
    }
    return i;
}

void quicksort_II(vector<dataset> &sorted_data, int Low, int High)
{
    if (Low < High)
    {
        int j = partition_I(sorted_data, Low, High); // receives returned i for partitioning
        quicksort_I(sorted_data, Low, j - 1);        // repeat sorting for left sub array
        quicksort_I(sorted_data, j + 1, High);       // repeat for right sub array
    }
}

int main()
{

    ifstream file;          // file stream object
    file.open("books.csv"); // opens the books.csv file

    if (!file) // Error message if file isn't acccesible
    {
        cerr << "File cannot be opened!";
        exit(1);
    }
    cout << "Type and Enter 1 for Quicksort-I or 2 for Quicksort-II:" << endl; // Prompt message

    int user_input;    // vector capacity, number of data to take
    cin >> user_input; // takes user input

    vector<dataset> data; // vector of struct dataset
    clock_t start;        // clock object for time calculation, only a definition, doesn't start here.

    string line;         // string variable for lines that are read from the file
    getline(file, line); // initial reading of the header line

    int N = 11128 - 1; // Total rows, minus the first line - which is the header
    // int N = 11128 / 2; // Half of Data       //UNCOMMENT these for Partial data read
    // int N = 11128 / 4; // Quarter of Data

    for (int i = 0; i < N; i++) // while (!file.eof()) or read until the end-of-line isn't used instead, because it is buggy.
    {
        dataset add; // read the lines from comma to comma, and store them in "add"
        getline(file, line, ',');
        add.bookID = stoi(line);
        getline(file, add.title, ',');
        getline(file, add.authors, ',');
        getline(file, line, ',');
        if (!line.empty())
        {
            add.average_rating = stod(line); // stod and stoi to convert string to double and int
        }
        getline(file, add.isbn, ','); // isbns have very long values, hence stored as string
        getline(file, add.isbn13, ',');
        getline(file, add.language_code, ',');
        getline(file, line, ',');
        if (!line.empty())
        {
            add.num_pages = stol(line); // stod and stoi to convert string to double and int
        }
        getline(file, line, ',');
        if (!line.empty())
        {
            add.ratings_count = stol(line); // stod and stoi to convert string to double and int
        }
        getline(file, line, ',');
        if (!line.empty())
        {
            add.text_reviews_count = stol(line); // stod and stoi to convert string to double and int
        }
        getline(file, add.publication_date, ',');
        getline(file, add.publisher);
        // cout << add.bookID << " " << add.average_rating << " " << add.isbn << " " << add.isbn13 << " " << add.num_pages << endl; // was used for debugging stoi/stol/stod
        data.push_back(add); // push the read data into the vector
    }

    int a = 0;     // lowest index
    int b = N - 1; // highest index (minus one as it starts from 0)

    if (user_input == 1) // if user types 1, then Quicksort-I is used
    {
        start = clock(); // start counting the elapsed time
        quicksort_I(data, a, b);
    }
    else if (user_input == 2) // if user types 2, then Quicksort-II is used
    {
        start = clock(); // start counting the elapsed time
        quicksort_II(data, a, b);
    }
    else
    {
        cout << "Error, wrong input" << endl; // if user types anything else, error message is displayed
    }
    // Note : It doesn't loop, so if user wants to do a second run, the program has to be re-run again

    double elapsed_time = (clock() - start) / (double)CLOCKS_PER_SEC;                            // time since clock() was called, divided by CLOCKS_PER_SEC to convert to seconds
    cout << "Elapsed time of execution Quicksort-" << user_input << ":" << elapsed_time << endl; // printing the calculated time
    // cout << "Total number of partitions: " << total_partitions << endl;  //For additional statistics, Uncomment alongside the global variable declaration + incrementations above to implement this.
    // cout << "Total number of swaps: " << total_swap << endl;

    ofstream datafile("sorted.txt"); // creates and opens sorted.txt
    datafile << "bookID,title,authors,average_rating,isbn,isbn13,language_code,num_pages,ratings_count,text_reviews_count,publication_date,publisher" << endl;

    for (int i = 0; i < N; i++) // writes the sorted data one by one to the file
    {
        datafile << data.at(i).bookID << "," << data.at(i).title << "," << data.at(i).authors << "," << data.at(i).average_rating << "," << data.at(i).isbn << "," << data.at(i).isbn13 << "," << data.at(i).language_code << "," << data.at(i).num_pages << "," << data.at(i).ratings_count << "," << data.at(i).text_reviews_count << "," << data.at(i).publication_date << "," << data.at(i).publisher << endl;
    }

    datafile.close(); // closes the file, automatically done otherwise, but written just in case.

    return 0;
}