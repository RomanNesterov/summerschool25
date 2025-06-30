void insertionSort(std::vector<int> arr) {
    size_t N = arr.size();
    for (size_t i = 1; i < N; ++i) {
        int key = arr[i];
        size_t j = i - 1;
      
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
      
        arr[j + 1] = key;
    }
    std::cout << "sorted!";
}
