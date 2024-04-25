#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Merge function for merge sort
void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Sequential Merge Sort
void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSort(arr, l, m);
#pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main()
{
    vector<int> arr = {5, 7, 8, 4, 3, 9, 1, 6, 2, 10, 15, 12, 18, 11, 13, 16, 14, 17, 20, 19,
                       25, 23, 24, 22, 21, 30, 28, 26, 27, 29, 35, 32, 33, 36, 34, 31, 40,
                       37, 38, 39, 45, 43, 42, 44, 41, 50, 47, 49, 48, 46, 55, 51, 54, 53,
                       52, 60, 56, 57, 58, 59, 65, 63, 62, 61, 64, 70, 67, 68, 69, 66, 75,
                       71, 72, 73, 74, 80, 78, 77, 79, 76, 85, 83, 81, 82, 84, 90, 87, 89,
                       88, 86, 95, 92, 94, 93, 91, 100, 97, 99, 98, 96};

    cout << "Given Array: ";
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    vector<int> bubbleArr = arr;
    double startTime = omp_get_wtime();
    bubbleSort(bubbleArr);
    double endTime = omp_get_wtime();

    cout << "Sequential Bubble Sort Time: " << (endTime - startTime) << " seconds" << endl;
    cout << "Sorted Array (Bubble Sort): ";
    for (int i = 0; i < bubbleArr.size(); ++i)
    {
        cout << bubbleArr[i] << " ";
    }
    cout << endl;

    vector<int> parallelBubbleArr = arr;
    startTime = omp_get_wtime();
    parallelBubbleSort(parallelBubbleArr);
    endTime = omp_get_wtime();

    cout << "Parallel Bubble Sort Time: " << (endTime - startTime) << " seconds" << endl;
    cout << "Sorted Array (Parallel Bubble Sort): ";
    for (int i = 0; i < parallelBubbleArr.size(); ++i)
    {
        cout << parallelBubbleArr[i] << " ";
    }
    cout << endl;

    vector<int> mergeArr = arr;
    startTime = omp_get_wtime();
    mergeSort(mergeArr, 0, mergeArr.size() - 1);
    endTime = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << (endTime - startTime) << " seconds" << endl;
    cout << "Sorted Array (Merge Sort): ";
    for (int i = 0; i < mergeArr.size(); ++i)
    {
        cout << mergeArr[i] << " ";
    }
    cout << endl;

    vector<int> parallelMergeArr = arr;
    startTime = omp_get_wtime();
    parallelMergeSort(parallelMergeArr, 0, parallelMergeArr.size() - 1);
    endTime = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (endTime - startTime) << " seconds" << endl;
    cout << "Sorted Array (Parallel Merge Sort): ";
    for (int i = 0; i < parallelMergeArr.size(); ++i)
    {
        cout << parallelMergeArr[i] << " ";
    }
    cout << endl;

    return 0;
}
