#include<iostream>
using namespace std;

double add(double x, double y){
   return x + y;
}

double subtract(double x, double y){
   return x - y;
}

double multiply(double x, double y){
   return x * y;
}

double divide(double x, double y){
   if(y == 0){
      cout << "Error! Division by zero is not allowed.";
      return 0;
   } else {
      return x / y;
   }
}

int main(){
   int choice;
   double num1, num2;

   cout << "Select operation:" << endl;
   cout << "1. Add" << endl;
   cout << "2. Subtract" << endl;
   cout << "3. Multiply" << endl;
   cout << "4. Divide" << endl;

   cout << "Enter choice(1/2/3/4): ";
   cin >> choice;

   cout << "Enter first number: ";
   cin >> num1;
   cout << "Enter second number: ";
   cin >> num2;

   switch(choice){
      case 1:
         cout << num1 << " + " << num2 << " = " << add(num1, num2);
         break;
      case 2:
         cout << num1 << " - " << num2 << " = " << subtract(num1, num2);
         break;
      case 3:
         cout << num1 << " * " << num2 << " = " << multiply(num1, num2);
         break;
      case 4:
         cout << num1 << " / " << num2 << " = " << divide(num1, num2);
         break;
      default:
         cout << "Invalid choice";
   }

   return 0;
}