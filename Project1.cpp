#include<iostream>
 
using namespace std;
 
class Laptop {
 
private:
 
	char * name;
	int ram_memory;
	float price;
	bool broken;
	const int code;
	static int number_id;
 
public:
 
	Laptop():code(number_id) //constructor without parameters
	{
		this->name = new char[strlen("not found") + 1];
		strcpy(this->name, "not found");
		this->ram_memory = 0;
		this->price = 0;
		this->broken = false;
		number_id++;
	}
 
 
	Laptop(char* name, int ram_memory, float price, bool broken):code(number_id) //constructor with parameters (polymorphism concept)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->ram_memory = ram_memory;
		this->price = price;
		this->broken = broken;
		number_id++;
	}
 
	Laptop(const Laptop &l1) :code(number_id) //copy constructor(makes an exact copy of an existing one)
	{
		this->name = new char[strlen(l1.name) + 1];
		strcpy(this->name, l1.name);
		this->ram_memory = l1.ram_memory;
		this->price = l1.price;
		this->broken = l1.broken;
		number_id++;
	}
 
	Laptop operator=(const Laptop&l1)  // overwriting operator =(for making to object equal or not)
	{
		if (name != NULL)
			this->name = new char [strlen(l1.name) + 1];
		strcpy(this->name, l1.name);
		this->ram_memory = l1.ram_memory;
		this->price = l1.price;
		this->broken = l1.broken;
		number_id++;
		return *this; //adress of the object
 
 
	}
 
 
	friend bool operator>(Laptop &l1, Laptop &l2) { //overloading operator >
		return l1.price > l2.price;
	}
	Laptop operator+(const Laptop &l2)  //overloading operator+ (adding two objects)
	{
		Laptop l3 = *this;
		l3.price = this->price + l2.price;
		return l3;
	}
 
	Laptop operator-(const Laptop&l2) // overloading operator -
	{
		Laptop l3 = *this;
		l3.price = this->price - l2.price;
		return l3;
	}
 
	Laptop operator*(const Laptop&l2)  // overloading operator *
	{
		Laptop l3 = *this;
		l3.price = this->price*l2.price;
		return l3;
	}
 
	Laptop operator/(const Laptop&l2)  // overloading operator -
	{
		Laptop l3 = *this;
		l3.price = this->price / l2.price;
		return l3;
	}
 
 
		~Laptop() 	//destructor (used only for * type so that we can prevent memory leaks)
	{
			if (this->name) {
				delete[]this->name;
			}
		}
 
 
	char * get_name()   //getter for name (allows us to read the attributes values from outside the class)
	{
		return name;
	}
 
	void set_name(char * new_name)  //setter for name(allows us to modify attributes values from outside the class)
	{
		if (strlen(new_name) > 1)
		{
			if (name != NULL) 
			{
				delete[]name;//for preventing memory leaks
				name = new char[strlen(new_name) + 1];
				strcpy(name, new_name);
			}
		}
 
	}
 
	int get_ram_memory()  //getter for ram_memory
	{
		return ram_memory;
	}
 
	void set_ram_memory(int new_ram_memory) //setter pentru ram
	{
		if (new_ram_memory > 0)
			ram_memory = new_ram_memory;
		else throw "Wrong value!";
	}
 
	float get_price() //getter for price
	{
		return price;
	}
 
	void set_price(int new_price) //setter for price
	{
		if (new_price > 0)
			price = new_price;
		else throw "Price should be higher than 0!";
	}
 
	bool get_broken() //getter for broken
	{
 
		return broken;
	}
 
	void set_broken(bool _broken)  //setter for broken
	{
		broken = _broken;
	}
 
	void show() {    //show method
		cout << "The laptops name is " << this->name << " and it has " << this->ram_memory << " GB ram  " << "and it's valued at " << this->price << " euros " << " and is ok/broken(1/0)" << this->broken << " with the code " << endl << this->code;
	}
 
	bool operator==(Laptop &l2)  // overloading operator ==
	{
		return strcmp(this->name, l2.name) == 0 ? true : false; //true if the both laptops have the same name
	}
 
	Laptop operator!()  // overloading operator !
	{
		Laptop l1 = *this;
		l1.broken = !l1.broken;
		return l1;
	}
 
	Laptop operator()()  //overloading function operator without parameters
	{
		Laptop l1 = *this;
		this->price *= 2;
		return l1;
	}
 
	Laptop operator()(float sum)  //overloading function operator with parameters
	{
		Laptop l1 = *this;
		this->price += sum;
		return l1;
	}
 
	Laptop operator++()  // overloading pre increment ++ operator
	{ 
		this->price *= 2;
		return *this;
	}
 
	Laptop operator++(int)  //overloading post increment ++ operator(we use int as parameters to realise polymophism)
	{
		Laptop aux = *this;
		this->price *= 2;
		return aux;
	}
 
	Laptop operator --() {  //overloading pre increment -- operator
 
		this->price += 1000;
		return *this;
 
	}
 
	Laptop operator--(int)  //overloading post increment -- operator(we use int as parameters to realise polymophism)
	{
		Laptop temp = *this;
		this->price -= 100;
		return temp;
	}
 
	static int get_number_id() {  //getter for the static method
		return Laptop::number_id;
	}
 
 
 
 
	friend  istream& operator >> (istream& intrare, Laptop &l1); 
	//we use friend before the function's signature/header to allow a function to use directly the class atributes instead of using getters and setters
 
};
 
int Laptop::number_id = 1; //initialising the id with 1(will be incremented int the constructors)
 
ostream& operator << (ostream& output, Laptop l1)  //overloading operator << to show an object initialised from the keyboard
{
	cout << "**********************************" << endl;
	output << l1.get_name() << endl;
	output << l1.get_ram_memory() << endl;
	output << l1.get_price() << endl;
	output << l1.get_broken() << endl;
	cout << "**********************************" << endl;
	cout << endl;
	return output; //using void instead ostream& in the function header doesn't allow the "cascade" reading(same for istream below)
}
 
 
istream& operator >> (istream& input, Laptop &l1)  //overloading operator >> to read an object initialised from the keyboard
{
 
	cout << "Laptop's name:";
	char buffer[20];
	input >> buffer;  
	if (strlen(buffer) > 0)  
	{
		if (l1.name)
			delete[]l1.name; //in order to avoid memory leaks because of pointer (*) structure
		l1.name = new char[strlen(buffer) + 1]; 
		strcpy(l1.name, buffer);
 
	}
	cout << "RAM Memory:";
	input >> l1.ram_memory;
	cout << "Price:";
	input >> l1.price;
	cout << "Working/broken(1/0):";
	input >> l1.broken;
	return input;
 
}
 
void main()
{
	Laptop l1("Asus", 8, 3500, true);
	Laptop l2("MacBook", 16, 4500, false);
	Laptop l3;
 
	cin >> l1 >> l2; //reading in cascade
	cout << l1 << l2 << endl; // showing in cascade
	cout << "Static method test:";
	cout << endl;
	cout << "We have" << Laptop::get_number_id() <<" id's in our program"<< endl;
	cout << endl;
	cout << "[overloading -- after]" << endl;
	l2 = l1--;
	l2.show();
	cout << endl;
	cout << "[overloading -- before]" << endl;
	cout << endl;
	l2 = --l1;
	l2.show();
	cout << endl;
    cout << "[overloading ++ after]" << endl;
	l2 = l1++; 
	l2.show();
	cout << endl;
	cout << "[overloading ++ before]" << endl;
	l2 = ++l1;
	l2.show();
	cout << endl;
	cout << "[overloading ()]" << endl;
	cout << endl;
	l2 = l1();
	l1.show();
	cout << endl;
	cout << "[overloading () with parameters]" << endl;
	cout << endl;
	l2 = l1(500);
	l1.show();
	cout << endl;
	if (l2 == !l1) cout << "Both laptops have different problems";
	else cout << "Both laptops have the same problem";
	cout << endl;
	cout << "[overloadin ==]" << endl;
	cout << endl;
	if (l1 == l2) cout << "Same name for both laptops";
	else cout << "Different names";
	cout << endl;
	cout << "[testing show function for l1]";
	cout << endl;
	l1.show();
	cout << endl;
	cout << "[testing show function for l2]";
	cout << endl;
	l2.show();
	cout << endl;
	cout << endl << "[oveloading >]" << endl;
	cout << endl;
	if (l1 > l2) cout << "The first laptop is costlier than the second one";
	else cout << "The second laptop is costlier than the first one";
	cout << endl;
	cout << endl << "[overloading +]" << endl;
	cout << endl;
	l3 = l1 + l2; //operator +
	cout << endl;
	l3.show();
	cout << endl;
	cout << endl << "[overloading -]" << endl;
	cout << endl;
	l3 = l2 - l1; //operator -  
	cout << endl;
	l3.show();
	cout << endl;
	cout << endl << "[overloading *]" << endl;
	cout << endl;
	l3 = l1*l2;  //operator *
	cout << endl;
	l3.show();
	cout << endl;
	cout << endl << "[overloading /]" << endl;
	cout << endl;
	l3 = l1 / l2; //operator /
	cout << endl;
	l3.show();
 
 
 
 
	cout << "<<<<<testing getters and setters>>>>>" << endl;
	l1.set_name("Asus");
	cout << l1.get_name();
	l1.set_price(2500);
	cout << "\n"; //switch to next row
	cout << l1.get_price();
	cout << "\n";
	l1.set_ram_memory(4);
	cout << l1.get_ram_memory();
	l1.set_broken(true);
	cout << l1.get_broken();
}