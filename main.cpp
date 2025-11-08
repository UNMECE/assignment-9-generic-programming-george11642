#include <iostream>
#include <stdexcept>

template <typename T>
class GenericArray {
public:
    GenericArray() : data_(nullptr), length_(0) {}

    GenericArray(const GenericArray& other) : data_(nullptr), length_(0) {
        copyFrom(other);
    }

    GenericArray(GenericArray&& other) noexcept : data_(other.data_), length_(other.length_) {
        other.data_ = nullptr;
        other.length_ = 0;
    }

    GenericArray& operator=(const GenericArray& other) {
        if (this != &other) {
            copyFrom(other);
        }
        return *this;
    }

    GenericArray& operator=(GenericArray&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            length_ = other.length_;
            other.data_ = nullptr;
            other.length_ = 0;
        }
        return *this;
    }

    ~GenericArray() {
        delete[] data_;
    }

    void addElement(const T& value) {
        T* newData = new T[length_ + 1];
        for (size_t i = 0; i < length_; ++i) {
            newData[i] = data_[i];
        }
        newData[length_] = value;

        delete[] data_;
        data_ = newData;
        ++length_;
    }

    T at(size_t index) const {
        if (index >= length_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t size() const {
        return length_;
    }

    T sum() const {
        T total = T();
        for (size_t i = 0; i < length_; ++i) {
            total += data_[i];
        }
        return total;
    }

    T max() const {
        ensureNotEmpty("max");
        T currentMax = data_[0];
        for (size_t i = 1; i < length_; ++i) {
            if (data_[i] > currentMax) {
                currentMax = data_[i];
            }
        }
        return currentMax;
    }

    T min() const {
        ensureNotEmpty("min");
        T currentMin = data_[0];
        for (size_t i = 1; i < length_; ++i) {
            if (data_[i] < currentMin) {
                currentMin = data_[i];
            }
        }
        return currentMin;
    }

    T* slice(size_t begin, size_t end) const {
        if (begin > end || end >= length_) {
            throw std::out_of_range("Invalid slice bounds");
        }

        size_t sliceLength = end - begin + 1;
        T* sliceResult = new T[sliceLength];
        for (size_t i = 0; i < sliceLength; ++i) {
            sliceResult[i] = data_[begin + i];
        }
        return sliceResult;
    }

private:
    T* data_;
    size_t length_;

    void ensureNotEmpty(const char* functionName) const {
        if (length_ == 0) {
            throw std::runtime_error(std::string("Cannot call ") + functionName + " on an empty array");
        }
    }

    void copyFrom(const GenericArray& other) {
        T* newData = nullptr;
        if (other.length_ > 0) {
            newData = new T[other.length_];
            for (size_t i = 0; i < other.length_; ++i) {
                newData[i] = other.data_[i];
            }
        }

        delete[] data_;
        data_ = newData;
        length_ = other.length_;
    }
};

template <typename T>
void printArray(const T* array, size_t length) {
    std::cout << "[";
    for (size_t i = 0; i < length; ++i) {
        std::cout << array[i];
        if (i + 1 < length) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

int main() {
    try {
        GenericArray<int> intArray;
        for (int i = 1; i <= 10; ++i) {
            intArray.addElement(i * 2);
        }

        std::cout << "Integer array contents: ";
        for (size_t i = 0; i < intArray.size(); ++i) {
            std::cout << intArray.at(i) << " ";
        }
        std::cout << "\n";

        std::cout << "Size of integer array: " << intArray.size() << "\n";
        std::cout << "Sum of integer array: " << intArray.sum() << "\n";
        std::cout << "Max of integer array: " << intArray.max() << "\n";
        std::cout << "Min of integer array: " << intArray.min() << "\n";

        size_t begin = 2;
        size_t end = 5;
        int* slice = intArray.slice(begin, end);
        size_t sliceLength = end - begin + 1;
        std::cout << "Slice from index " << begin << " to " << end << ": ";
        printArray(slice, sliceLength);
        std::cout << "\n";
        delete[] slice;

        GenericArray<double> doubleArray;
        doubleArray.addElement(3.14);
        doubleArray.addElement(2.71);
        doubleArray.addElement(1.41);

        std::cout << "Double array size: " << doubleArray.size() << "\n";
        std::cout << "Double array sum: " << doubleArray.sum() << "\n";
        std::cout << "Double array max: " << doubleArray.max() << "\n";
        std::cout << "Double array min: " << doubleArray.min() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}

