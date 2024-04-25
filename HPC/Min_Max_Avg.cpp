#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to find the minimum element in an array
int parallelMin(const vector<int> &arr)
{
    int min_val = arr[0];
#pragma omp parallel for reduction(min : min_val)
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    return min_val;
}

// Function to find the maximum element in an array
int parallelMax(const vector<int> &arr)
{
    int max_val = arr[0];
#pragma omp parallel for reduction(max : max_val)
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    return max_val;
}

// Function to find the sum of elements in an array
int parallelSum(const vector<int> &arr)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < arr.size(); ++i)
    {
        sum += arr[i];
    }
    return sum;
}

// Function to find the average of elements in an array
double parallelAverage(const vector<int> &arr)
{
    int sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main()
{
    // Example array
    // vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> arr = {5, 7, 8, 4, 3, 9, 1, 6, 2, 10, 15, 12, 18, 11, 13, 16, 14, 17, 20, 19,
                    25, 23, 24, 22, 21, 30, 28, 26, 27, 29, 35, 32, 33, 36, 34, 31, 40,
                    37, 38, 39, 45, 43, 42, 44, 41, 50, 47, 49, 48, 46, 55, 51, 54, 53,
                    52, 60, 56, 57, 58, 59, 65, 63, 62, 61, 64, 70, 67, 68, 69, 66, 75,
                    71, 72, 73, 74, 80, 78, 77, 79, 76, 85, 83, 81, 82, 84, 90, 87, 89,
                    88, 86, 95, 92, 94, 93, 91, 100, 97, 99, 98, 96};;

    // Minimum element
    cout << "Minimum element: " << parallelMin(arr) << endl;

    // Maximum element
    cout << "Maximum element: " << parallelMax(arr) << endl;

    // Sum of elements
    cout << "Sum of elements: " << parallelSum(arr) << endl;

    // Average of elements
    cout << "Average of elements: " << parallelAverage(arr) << endl;

    return 0;
}
