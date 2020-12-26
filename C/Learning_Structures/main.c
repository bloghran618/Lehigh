#include <stdio.h>

struct database {
  int id_number;
  int age;
  float salary;
};

int main()
{
  struct database employee;  //There is now an employee variable that has modifiable
                      // variables inside it.
  employee.age = 22;
  employee.id_number = 1;
  employee.salary = 12000.21;
  printf("The Employee's ID number is %d",employee.id_number);
  getchar();

}
