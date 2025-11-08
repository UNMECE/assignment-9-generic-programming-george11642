[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/08fMgpC0)
# ECE231_Assignment9-GenericProgramming
# Lab Assignment 9
Create a general class using templates that mimics some behavior of the vector class in the standard template library.  This class will manage an array of any basic numerical data type (e.g. int, float, etc).  This class should have the following functionality:

  - add an element to the end of the array - .addElement(<T> param).
  - implement a function called .at(int param) that returns the value in the array at the location param.
  - .size() function that returns the size of the array.
  - implement a .sum() function that returns the sum of the entire array.
  - implement a .max() and .min() function that finds the maximum and minimum of the entire array.
  - Create a .slice(int begin, int end) function that returns a slice of the array between and including elements begin to end.  For example, if the array is [0,2,4,6,8] and the function is called as .slice(2,4) it returns the array [2,4,8] as a new array pointer - it is not a pointer to the underlying data but a new array.  Check the bounds of the slice.
  
You should use dynamic memory allocation to store data elements.  You should use delete and new keywords.  Everytime you add an element you should allocate new space in memory for the new size.  Copy over the previous array to the new array with the new element to add.  Delete the old array.

# Code Usage
The main function should do something like the following to test your template class

```
int main()
{
  GenericArray<int> int_array;
  int_array.addElement(10);
  ....
  ....
  std::cout << "size of array is " << int_array.size() << std::endl;
  std::cout << "sum of the array is " << int_array.sum() << std::endl;
  std::cout << "maximum and minimum of array is " << int_array.max() << "\t" << int_array.min() << std::endl;
  int *sliced_array = int_array.slice(5,10);
  // print sliced_array...
  return 0;
}
```

# Grading Scale
- 20% Template Made
- 20% Basic Functions Implemented
- 20% Dynamic memory allocation and clean up
- 20% .slice() function working properly
- 20% code produces expected output
