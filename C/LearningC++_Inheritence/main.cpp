class Animal
{
  public:
  Animal();
  ~Animal();
  void eat();
  void sleep();
  void drink();

private:
  int legs;
  int arms;
  int age;
};
//The class Animal contains information and functions
//related to all animals (at least, all animals this lesson uses)
class Cat : public Animal
{
  public:
  int fur_color;
  void purr();
  void fish()
  {
      int caught = 1;
  }
  void markTerritory();
};
//each of the above operations is unique
//to your friendly furry friends
//(or enemies, as the case may be)
