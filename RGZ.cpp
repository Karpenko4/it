#include <iostream>   
#include <chrono>      
#include <cstring>     
#include <cstdlib>     
#include <ctime>       
#include <limits>      
#include <iomanip>    

using namespace std; 
using namespace std::chrono;

const int num_iterations = 10000; 

// Bubble Sort 
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//Radix Sort 
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp) {
    int output[n]; 
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void printArray(int arr[], int n) {
    int i;
    cout << "(";
    for (i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << ")";
}

int main() {
    srand(time(NULL)); 

    int size = 5;
    int max_size = 45;
    int arr_orig[max_size]; 
    int arr_copy[max_size]; 

    cout << fixed << setprecision(2); 

    cout << " Порівняння сортування (середнє арифметичне в мікросекундах)\n";

    while (size <= max_size) {

        // 1. Впорядкований
        // for (int i = 0; i < size; i++) {
        //     arr_orig[i] = i + 1; 
        // }

        // 2. Зворотній порядок
        for (int i = 0; i < size; i++) {
            arr_orig[i] = size - i;
        }
        
        // 3. Випадкова перестановка чисел 
        // for (int i = 0; i < size; i++) {
        //     arr_orig[i] = i + 1; // спочатку заповнюємо послідовністю 1..size
        // }
        // // Перемішуємо у випадковому порядку
        // for (int i = size - 1; i > 0; i--) {
        //     int j = rand() % (i + 1); // випадковий індекс від 0 до i
        //     int tmp = arr_orig[i];
        //     arr_orig[i] = arr_orig[j];
        //     arr_orig[j] = tmp;
        // }

        cout << " Кількість елементів: " << size << "\n";
        cout << " Масив: ";
        printArray(arr_orig, size);
        cout << "\n";

        // Bubble Sort
        long long total_nanos_bubble = 0;
        
        for(int k = 0; k < num_iterations; k++) {
            memcpy(arr_copy, arr_orig, size * sizeof(int)); 
            
            auto start = high_resolution_clock::now();
            bubbleSort(arr_copy, size);
            auto end = high_resolution_clock::now();
            
            total_nanos_bubble += duration_cast<nanoseconds>(end - start).count();
        }

        double avg_bubble_micros = (double)total_nanos_bubble / num_iterations / 1000.0;
        
        cout << "1. Bubble Sort: " << avg_bubble_micros << " мкс\n"; 

        // Radix Sort
        long long total_nanos_radix = 0;

        for(int k = 0; k < num_iterations; k++) {
            memcpy(arr_copy, arr_orig, size * sizeof(int)); 
            
            auto start = high_resolution_clock::now();
            radixSort(arr_copy, size);
            auto end = high_resolution_clock::now();

            total_nanos_radix += duration_cast<nanoseconds>(end - start).count();
        }

        double avg_radix_micros = (double)total_nanos_radix / num_iterations / 1000.0;

        cout << "2. Radix Sort : " << avg_radix_micros << " мкс\n";

        if (size == max_size) break;

        cout << "\n Натисніть Enter для збільшення масиву...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        size = size + 5;
    }

    cout << "\n Програма завершена \n";
    return 0;
}
