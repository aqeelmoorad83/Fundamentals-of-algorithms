// Multiplication of two numbers using the naive approach.
// Time Complexitiy: O(n^2)
// TODO: Proper Comments and formatting according to style guide.
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Add user desired zeros at the end of a number.
vector <int> ShiftLeft(vector <int> number , int shifts){
  for (int i=0; i<shifts ; i++){
    number.push_back(0);
  }
  return number;
}

// Convert the integer into a vector where each member represent the digits of the number.
vector <int> CreateVector(int number){
  int remainder;
  stack <int> number_stack;
  while (number != 0 ){
    remainder = number % 10;
    number_stack.push(remainder);
    number = number/10;
  }
  vector <int> number_vector;
  while (!number_stack.empty()){
    number_vector.push_back(number_stack.top());
    number_stack.pop();
  }
  return number_vector;
}

// Adds two vector properly.
vector <int> Addition (vector <int> small_vector , vector <int> big_vector){
  if (small_vector.size() == 0){
    return big_vector;
  }
  int difference = big_vector.size() - small_vector.size();
  if (difference < 0){
    // Add 0 in front of big vector to make it equal size of big vector.
    for (int i=difference ; i<0 ; i++){
      big_vector.insert(big_vector.begin(),0);
  }
  }
  else{
  // Add 0 in front of small vector to make it equal size of big vector.
  for (int i=0 ; i<difference ; i++){
    small_vector.insert(small_vector.begin(),0);
  }
  }
  vector <int> sum;
  int carry_over = 0;
  int temp_sum;
  for (int i = big_vector.size()-1 ; i>=0 ; i--){
    temp_sum = small_vector[i] + big_vector[i];
    temp_sum += carry_over;
    int remainder;
    if (temp_sum > 9){
      remainder = temp_sum % 10;
      carry_over = temp_sum / 10;
      temp_sum = remainder;
    }
    else{
      carry_over = 0;
    }
    sum.insert(sum.begin() , temp_sum);
    }
    if (carry_over != 0){
      sum.insert(sum.begin(), carry_over);
    }
  return sum;
}

// Subtract two vectors.
vector <int> Subtract (vector <int> small_vector , vector <int> big_vector){
  int difference = big_vector.size() - small_vector.size();
  bool swap_needed = false;
  // Add 0 in front of small vector to make it equal size of big vector.
  if (difference < 0){
     for (int i=difference ; i<0 ; i++){
        big_vector.insert(big_vector.begin(),0);
       
     }
        swap_needed = true;
  }
  else if (difference > 0){
    for (int i=0 ; i<difference ; i++){
      small_vector.insert(small_vector.begin(),0);
  }
      swap_needed = false;
  }
  else{
    for (int i=0 ; i<big_vector.size();i++){
      if (small_vector[i] < big_vector[i]){
        swap_needed = false;
        break;
      }
      else if (small_vector[i] > big_vector[i]){
        swap_needed = true;
        break;
      }
      else{
        continue;
      }
    }
  }
  if (swap_needed){
    small_vector.swap(big_vector);
  }
  vector <int> subtract;
  int carry_over = 0;
  int temp_sub;
  for (int i = big_vector.size()-1 ; i>=0 ; i--){
    temp_sub = big_vector[i] - small_vector[i];
    temp_sub += carry_over;
    if (temp_sub > 9){
      carry_over = 1;
      temp_sub -= 10;
    }
    else if (temp_sub <0){
      carry_over = -1;
      temp_sub += 10;
    }
    else{
      carry_over = 0;
    }
    subtract.insert(subtract.begin() , temp_sub);
    }
    if (carry_over == 1){
      subtract.insert(subtract.begin(), carry_over);
    }
  return subtract;
}

// Helper function to assist with multiplication.
vector <int> Multiply(vector <int> first_vector , int number){
  int carry_over = 0;
  vector <int> result;
  int product;
  for (int i = first_vector.size()-1 ; i >=0 ; i--){
    product = number * first_vector[i];
    product += carry_over;
    int remainder;
    if (product > 9){
      remainder = product % 10;
      carry_over = product / 10;
      product = remainder;
    }
    else{
      carry_over = 0;
    }
    result.insert(result.begin(),product);
  }
  if (carry_over != 0){
    result.insert(result.begin(), carry_over);
  }
  return result;
}

vector <int> MuliplyLargeNumbers(vector <int> first_vector , vector <int> second_vector){
  int shifter = 0;
  vector <int> result;
  vector <int> temp;
  cout << endl;
  for (int i = second_vector.size()-1 ; i >=0 ; i--){
    temp = ShiftLeft(Multiply(first_vector , second_vector[i]), shifter);
    result = Addition(result , temp);
    shifter += 1;
  }
  return result;
}

int main(){
  int first_number , second_number;
  cout << "Enter the first number: ";
  cin >> first_number;
  cout << "Enter the second number: ";
  cin >> second_number;
  vector <int> first_vector = CreateVector(first_number);
  vector <int> second_vector = CreateVector(second_number);
  vector <int> result = MuliplyLargeNumbers (first_vector , second_vector);
  cout << endl;
  cout << "**** Using Naive Approach ****" << endl;
  cout << "The product is ";
  for (int i=0 ; i<result.size();i++){
    cout << result[i];
  }
  return 0;
}

/* Output: 
Enter the first number:  98765
Enter the second number:  56789


**** Using Naive Approach ****
The product is 5608765585    */


