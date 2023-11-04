#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include<numeric>
#include<string>
#include<map>
#include<set>


using namespace std;


class CheltuieliTotal {
private:
	int tip;
public:
	virtual int getValoare() = 0;
	virtual float getBuget() = 0;

};

class CheltuieliNecesare {
private:

	char * nume_cheltuieala;
	int valoare;
	const int cod;
	static int cod_initial;
	bool suma_achitata;

public:

	char * getNume()
	{
		return nume_cheltuieala;
	}

	virtual int getValoare()
	{
		return valoare;
	}

	CheltuieliNecesare operator=(const CheltuieliNecesare &cn) {  //operator =
		if (nume_cheltuieala != NULL)
			delete[]nume_cheltuieala;
		this->nume_cheltuieala = new char[strlen(cn.nume_cheltuieala) + 1];
		strcpy(this->nume_cheltuieala, cn.nume_cheltuieala);
		this->valoare = cn.valoare;
		this->suma_achitata = cn.suma_achitata;
		return *this;
	}

	CheltuieliNecesare(const CheltuieliNecesare &cn) :cod(cod_initial)  //constructor copiere
	{
		this->nume_cheltuieala = new char[strlen(cn.nume_cheltuieala) + 1];
		strcpy(this->nume_cheltuieala, cn.nume_cheltuieala);
		this->valoare = cn.valoare;
		this->suma_achitata = cn.suma_achitata;
		cod_initial++;

	}

	CheltuieliNecesare() :cod(cod_initial) {          //constructor fara parametrii
		this->nume_cheltuieala = new char[strlen("Utilitati") + 1];
		strcpy(this->nume_cheltuieala, "Utilitati");
		this->valoare = 25;
		this->suma_achitata = false;
		cod_initial++;
	}
	CheltuieliNecesare(char * nume_cheltuiala, int valoare, bool suma_achitata) :cod(cod_initial) {  //constructor cu parametrii
		this->nume_cheltuieala = new char[strlen(nume_cheltuiala) + 1];
		strcpy(this->nume_cheltuieala, nume_cheltuiala);
		this->valoare = valoare;
		this->suma_achitata = suma_achitata;
		cod_initial++;
	}
	~CheltuieliNecesare() //destructor
	{
		cod_initial--;
		if (this->nume_cheltuieala)
		{
			delete[]this->nume_cheltuieala;
		}
	}

	char * get_nume_cheltuieala()    //getter nume_cheltuieala
	{
		return nume_cheltuieala;
	}

	void set_nume_cheltuieala(char* noua_cheltuieala)  //setter nume_cheltuieala
	{
		if (strlen(noua_cheltuieala) > 1)
		{
			if (nume_cheltuieala != NULL)
				nume_cheltuieala = new char[strlen(noua_cheltuieala) + 1];
			strcpy(nume_cheltuieala, noua_cheltuieala);
		}
	}


	int get_valoare() {       //getter valoare
		return valoare;
	}

	void set_valoare(int noua_valoare)       //setter valoare
	{
		if (noua_valoare > 0)
			valoare = noua_valoare;
		else throw("Nu ai introdus o valoare valida! ");
	}


	CheltuieliNecesare operator+() {   // supraincarcare operator +
		CheltuieliNecesare cn = *this;
		cn.valoare += this->valoare;
		return cn;
	}

	CheltuieliNecesare operator()() {        // supraincarcare operator() fara parametru
		CheltuieliNecesare cn = *this;
		cn.valoare *= 2;
		return cn;
	}

	CheltuieliNecesare operator()(float buget) {   // supraincarcare operator() cu parametru
		CheltuieliNecesare cn = *this;
		buget = cn.suma_achitata + 200;
		return cn;

	}


	bool operator==(CheltuieliNecesare cn) {           //supraincarcare operator==
		return strcmp(this->nume_cheltuieala, cn.nume_cheltuieala) == 0 ? true : false;
	}

	CheltuieliNecesare operator!() {        //supraincarcare operator !
		CheltuieliNecesare cn = *this;
		cn.suma_achitata = !cn.suma_achitata;
		return cn;
	}

	CheltuieliNecesare operator++() { //supraincarcare operator post ++
		this->valoare += 100;
		return *this;
	}

	CheltuieliNecesare operator++(int) { // supraincarcare operator pre ++
		CheltuieliNecesare aux = *this;
		this->valoare += 20;
		return aux;
	}

	friend bool operator <(CheltuieliNecesare &cn1, CheltuieliNecesare &cn2) {  // supraincarcare operator <
		return cn1.valoare < cn2.valoare;
	}

	CheltuieliNecesare operator +(CheltuieliNecesare cn1)
	{
		CheltuieliNecesare cn2 = *this;;
		cn2.valoare = this->valoare + cn1.valoare;
		return cn2;
	}

	friend istream& operator >> (istream& consola, CheltuieliNecesare& cn);  //functie friend istream
	friend ostream& operator<<(ostream& consola, CheltuieliNecesare cn);
	friend ofstream& operator<<(ofstream& consola, CheltuieliNecesare cn);

	void afisare() {       //metoda afisare
		cout << "Cheltuieala: " << this->nume_cheltuieala << " in valoare de " << this->valoare << " lei cu codul:" << this->cod;
	}

	static int get_cod() {  //metoda prin care obtinem nr total de coduri 
		return CheltuieliNecesare::cod_initial;
	}
};

int CheltuieliNecesare::cod_initial = 1;

bool metodaComparareCheltuieliNecesare(CheltuieliNecesare cn1, CheltuieliNecesare cn2)
{
	return cn1.get_valoare() < cn2.get_valoare();
}

CheltuieliNecesare metodaAdunare(CheltuieliNecesare cn1, CheltuieliNecesare cn2)
{
	CheltuieliNecesare cn3 = cn1 + cn2;
	return cn3;
}

ostream& operator<<(ostream& consola, CheltuieliNecesare cn)  //supraincarcare operator <<
{
	consola << endl << "=================" << endl;
	consola << cn.nume_cheltuieala << endl;
	consola << cn.valoare << endl;
	consola << cn.suma_achitata << endl;
	consola << cn.cod << endl;
	consola << endl << endl;
	consola << endl << "=================" << endl;
	return consola;
}

ofstream& operator<<(ofstream& consola, CheltuieliNecesare cn)  //supraincarcare operator <<
{
	consola << "===================" << endl;
	consola << cn.nume_cheltuieala << endl;
	consola << cn.valoare << endl;
	consola << cn.suma_achitata << endl;
	consola << cn.cod << endl;
	consola << endl << endl;
	consola << "===================" << endl;
	return consola;
}

istream& operator >> (istream& consola, CheltuieliNecesare& cn)   //supraincarcare operator >>
{
	cout << "Tipul cheltuielii este:";
	char buffer[20];
	consola >> buffer;
	if (strlen(buffer) > 0) {
		if (cn.nume_cheltuieala)
			delete[]cn.nume_cheltuieala;
		cn.nume_cheltuieala = new char[strlen(buffer) + 1];
		strcpy(cn.nume_cheltuieala, buffer);
	}
	cout << "Suma de plata este:";
	consola >> cn.valoare;
	return consola;
}

class CheltuieliNeprevazute {
private:

	char* nume_cheltuieala;
	int nr_cheltuieli;
	int *valoare_cheltuieli;
	int buget_alocat;

public:

	int* getValoare()
	{
		return  valoare_cheltuieli;
	}

	CheltuieliNeprevazute() {      //constructor fara parametrii
		this->nume_cheltuieala = new char[strlen("Fond reparatii") + 1];
		strcpy(this->nume_cheltuieala, "Fond reparatii");
		this->nr_cheltuieli = 1;
		this->valoare_cheltuieli = new int[10];
		this->buget_alocat = 20;
	}

	CheltuieliNeprevazute(char* nume_cheltuieala, int nr_cheltuieli, int* valoare_cheltuieli, int buget_alocat) //constructor cu parametrii
	{
		this->nume_cheltuieala = new char[strlen(nume_cheltuieala) + 1];
		strcpy(this->nume_cheltuieala, nume_cheltuieala);
		this->nr_cheltuieli = nr_cheltuieli;
		this->valoare_cheltuieli = new int[nr_cheltuieli];
		for (int x = 0; x < nr_cheltuieli; x++)
		{
			this->valoare_cheltuieli[x] = valoare_cheltuieli[x];
		}
		this->buget_alocat = buget_alocat;

	}

	CheltuieliNeprevazute(CheltuieliNeprevazute &cnn) {  //constructor de copiere
		this->nume_cheltuieala = new char[strlen(cnn.nume_cheltuieala) + 1];
		strcpy(this->nume_cheltuieala, cnn.nume_cheltuieala);
		this->nr_cheltuieli = cnn.nr_cheltuieli;
		this->valoare_cheltuieli = new int[cnn.nr_cheltuieli];
		for (int i = 0; i < cnn.nr_cheltuieli; i++)
		{
			this->valoare_cheltuieli[i] = cnn.valoare_cheltuieli[i];
		}
		this->buget_alocat = cnn.buget_alocat;
	}

	CheltuieliNeprevazute operator=(const CheltuieliNeprevazute &cnn) //supraincarcare operator=
	{
		//delete[]nume_cheltuieala;
		this->nume_cheltuieala = new char[strlen(cnn.nume_cheltuieala) + 1];
		strcpy(this->nume_cheltuieala, cnn.nume_cheltuieala);
		this->nr_cheltuieli = cnn.nr_cheltuieli;
		if (valoare_cheltuieli)
			delete[]valoare_cheltuieli;
		this->valoare_cheltuieli = new int[cnn.nr_cheltuieli];
		for (int i = 0; i < cnn.nr_cheltuieli; i++) {
			this->valoare_cheltuieli[i] = cnn.valoare_cheltuieli[i];
		}
		this->buget_alocat = cnn.buget_alocat;
		return *this;
	}

	CheltuieliNeprevazute operator+(CheltuieliNeprevazute cnn2) {  //supraincarcare operator+
		CheltuieliNeprevazute cnn3 = *this;
		cnn3.nr_cheltuieli = this->nr_cheltuieli + cnn2.nr_cheltuieli;
		if (cnn3.valoare_cheltuieli != NULL)
			delete[]cnn3.valoare_cheltuieli;
		cnn3.valoare_cheltuieli = new int[cnn3.nr_cheltuieli];
		for (int i = 0; i < this->nr_cheltuieli; i++)
			cnn3.valoare_cheltuieli[i] = this->valoare_cheltuieli[i];
		cnn3.buget_alocat = this->buget_alocat + cnn2.buget_alocat;
		return cnn3;
	}

	operator int() {      //cast implicit
		return this->nr_cheltuieli;
	}

	explicit operator float() {  //cast explicit
		return buget_alocat / nr_cheltuieli;

	}

	CheltuieliNeprevazute operator++() { //operator ++ post incrementare
		this->valoare_cheltuieli += 20;
		return *this;
	}

	CheltuieliNeprevazute operator++(int) {  //operator ++ pre incrementare
		CheltuieliNeprevazute aux = *this;
		this->buget_alocat *= 2;
		return aux;
	}

	~CheltuieliNeprevazute() {  //destructor
		if (this->nume_cheltuieala)
			delete[] this->nume_cheltuieala;
		if (this->valoare_cheltuieli)
			delete[] this->valoare_cheltuieli;
	}
	char* get_nume_cheltuieala() //getter nume_cheltuieala
	{
		return nume_cheltuieala;
	}

	void set_nume_cheltuieala(char * nume_nou_cheltuieala)   //setter nume_cheltuieala
	{
		if (strlen(nume_nou_cheltuieala) > 1)
		{
			if (nume_cheltuieala != NULL)
				nume_cheltuieala = new char[strlen(nume_nou_cheltuieala) + 1];
			strcpy(nume_cheltuieala, nume_nou_cheltuieala);
		}
	}

	int* get_valoare_cheltuieala() //getter valoare_cheltuieala
	{
		return valoare_cheltuieli;
	}

	void set_valoare_cheltuieala(int*vector, int nr_cheltuieli) //setter valoare_cheltuieala
	{
		if (valoare_cheltuieli)
			delete[]valoare_cheltuieli;
		valoare_cheltuieli = new int[nr_cheltuieli];
		for (int j = 0; j < nr_cheltuieli; j++)
		{
			valoare_cheltuieli[j] = vector[j];
		}
		this->nr_cheltuieli = nr_cheltuieli;

	}

	int get_nr_cheltuieli() //getter cheltuieli
	{
		return nr_cheltuieli;
	}

	void set_nr_cheltuieli(int noul_nr_cheltuieli)  //setter nr_cheltuieli
	{
		if (noul_nr_cheltuieli > 0)
			nr_cheltuieli = noul_nr_cheltuieli;
		else throw exception("Numarul introdus este prea mic!");
	}


	int get_buget_alocat()  //getter buget_alocat
	{
		return buget_alocat;
	}

	void set_buget_alocat(int noul_buget)  //setter buget_alocat
	{
		if (noul_buget > 0)
			buget_alocat = noul_buget;
		else throw "Suma introdusa este prea mica";
	}

	void afisare()  //metoda afisare
	{
		cout << "Numele cheltuielii este " << this->nume_cheltuieala <<
			" in numar de " << this->nr_cheltuieli << "si in valoarea/valorile de:" << endl;
		for (int i = 0; i < nr_cheltuieli; i++)
		{
			cout << (i + 1) << valoare_cheltuieli[i] << endl;
		}
		cout << "Bugetul alocat fiind de:" << this->buget_alocat;
	}

	int& operator[](int index) {   //supraincarcare operator de indexare []
		if (index >= 0 && index < this->nr_cheltuieli)
		{
			return valoare_cheltuieli[index];
		}
		else
		{
			throw new exception("Indexul depaseste spatiul alocat!");
		}
	}

	friend bool operator < (CheltuieliNeprevazute &cnn, CheltuieliNeprevazute &cnn1) { // supraincarcare operator <
		return cnn1.buget_alocat < cnn.buget_alocat;
	}

	CheltuieliNeprevazute operator()() {  //supraincarcare operator() fara parametrii
		CheltuieliNeprevazute cnn = *this;
		cnn.buget_alocat *= 2;
		return cnn;
	}

	CheltuieliNeprevazute operator()(float total) { //supraincarcare operator() cu parametrii
		CheltuieliNeprevazute cnn = *this;
		cnn.buget_alocat += total;
		return cnn;
	}

	friend istream& operator >> (istream& afisaj, CheltuieliNeprevazute& cnn);
	friend ostream& operator<<(ostream& afisaj, CheltuieliNeprevazute cnn);
	friend ifstream& operator >> (ifstream& afisaj, CheltuieliNeprevazute& cnn);
};

istream& operator >> (istream& afisaj, CheltuieliNeprevazute& cnn) //operator >>
{
	cout << "Numele cheltuielii:";
	char buffer[30];
	afisaj >> buffer;
	if (strlen(buffer) > 0) {
		if (cnn.nume_cheltuieala)
			delete[]cnn.nume_cheltuieala;
		cnn.nume_cheltuieala = new char[strlen(buffer) + 1];
		strcpy(cnn.nume_cheltuieala, buffer);
	}
	cout << "Numar de cheltuieli:";
	afisaj >> cnn.nr_cheltuieli;
	if (cnn.valoare_cheltuieli)
		delete[]cnn.valoare_cheltuieli;
	cnn.valoare_cheltuieli = new int[cnn.nr_cheltuieli];
	for (int i = 0; i < cnn.nr_cheltuieli; i++)
	{
		cout << "Valoare cheltuieli:" << (i + 1) << ":";
		afisaj >> cnn.valoare_cheltuieli[i];
	}
	cout << "Buget alocat:";
	afisaj >> cnn.buget_alocat;
	return afisaj;
}

ifstream& operator >> (ifstream& afisaj, CheltuieliNeprevazute& cnn)
{
	cout << "Numele cheltuielii:";
	char buffer[30];
	afisaj >> buffer;
	if (strlen(buffer) > 0) {
		if (cnn.nume_cheltuieala)
			delete[]cnn.nume_cheltuieala;
		cnn.nume_cheltuieala = new char[strlen(buffer) + 1];
		strcpy(cnn.nume_cheltuieala, buffer);
	}
	cout << "Numar de cheltuieli:";
	afisaj >> cnn.nr_cheltuieli;
	if (cnn.valoare_cheltuieli)
		delete[]cnn.valoare_cheltuieli;
	cnn.valoare_cheltuieli = new int[cnn.nr_cheltuieli];
	for (int i = 0; i < cnn.nr_cheltuieli; i++)
	{
		cout << "Valoare cheltuieli:" << (i + 1) << ":";
		afisaj >> cnn.valoare_cheltuieli[i];
	}
	cout << "Buget alocat:";
	afisaj >> cnn.buget_alocat;
	return afisaj;
}

ostream& operator<<(ostream& afisaj, CheltuieliNeprevazute cnn) {  //operator <<
	afisaj << "====================" << endl;
	afisaj << cnn.get_nume_cheltuieala() << endl;
	afisaj << cnn.get_nr_cheltuieli() << endl;
	for (int i = 0; i < cnn.get_nr_cheltuieli(); i++)
	{
		afisaj << cnn.get_valoare_cheltuieala()[i] << " " << endl;
	}
	afisaj << cnn.get_buget_alocat() << endl;
	afisaj << "====================" << endl;
	afisaj << endl;
	return afisaj;
}

ofstream& operator<<(ofstream& afisaj, CheltuieliNeprevazute cnn) {
	afisaj << "================" << endl;
	afisaj << cnn.get_nume_cheltuieala() << endl;
	afisaj << cnn.get_nr_cheltuieli() << endl;
	for (int i = 0; i < cnn.get_nr_cheltuieli(); i++)
	{
		afisaj << cnn.get_valoare_cheltuieala()[i] << " " << endl;
	}
	afisaj << cnn.get_buget_alocat() << endl;
	afisaj << "===============" << endl;
	afisaj << endl;
	return afisaj;
}

class CheltuieliOcazionale {
private:
	char* nume;
	int suma_de_plata;
	int buget;
	const int cod;
	static int nrcheltuieli;
	bool existenta;
public:

	int getValoare()
	{
		return suma_de_plata;
	}

	char* get_nume() { //getter nume 
		return nume;
	}

	void set_nume(char* noul_nume) { //setter nume
		if (strlen(noul_nume) > 0)

			if (nume != NULL)
			{
				{
					delete[]nume;
				}
				nume = new char[strlen(noul_nume) + 1];
				strcpy(nume, noul_nume);
			}
	}

	int get_suma_de_plata() { //getter suma_de_plata
		return suma_de_plata;
	}

	void set_suma_de_plata(int noua_suma) {  //setter suma_de_plata
		if (noua_suma > 0)
			suma_de_plata = noua_suma;
		else throw("Suma introdusa nu este valida");
	}

	int get_buget() //getter buget
	{
		return buget;
	}

	void set_buget(int noul_buget)  //setter buget
	{
		if (noul_buget > 0)
			buget = noul_buget;
		else throw("Valoarea este negativa!");
	}

	CheltuieliOcazionale() :cod(nrcheltuieli) { //constructor fara parametrii 
		this->nume = new char[strlen("Vacanta") + 1];
		strcpy(nume, "Vacanta");
		this->suma_de_plata = 200;
		this->buget = 400;
		nrcheltuieli++;
	}

	CheltuieliOcazionale(char * nume, int suma_de_plata, int buget) :cod(nrcheltuieli) {  //constructor cu parametrii
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->suma_de_plata = suma_de_plata;
		this->buget = buget;
		nrcheltuieli++;
	}

	CheltuieliOcazionale(CheltuieliOcazionale &co) :cod(nrcheltuieli) {  //constructor de copiere
		this->nume = new char[strlen(co.nume) + 1];
		strcpy(this->nume, co.nume);
		this->suma_de_plata = co.suma_de_plata;
		this->buget = co.buget;
		nrcheltuieli++;

	}

	CheltuieliOcazionale operator=(const CheltuieliOcazionale &co) { // supraincarcare operator =
		if (nume != NULL)
			delete[]nume;
		this->nume = new char[strlen(co.nume) + 1];
		strcpy(this->nume, co.nume);
		this->suma_de_plata = co.suma_de_plata;
		this->buget = co.buget;
		return *this;
	}

	~CheltuieliOcazionale() { //destructor
		nrcheltuieli--;
		if (this->nume)
		{
			delete[]this->nume;
		}
	}
	CheltuieliOcazionale operator+(CheltuieliOcazionale co2) { // supraincarcare operator+
		CheltuieliOcazionale co3 = *this;
		co3.suma_de_plata = this->suma_de_plata + co2.suma_de_plata;
		co3.buget = this->buget + co3.buget;
		return co3;
	}

	CheltuieliOcazionale operator+(int x) {  // supraincare operator + cu variabila
		CheltuieliOcazionale co = *this;
		co.buget = this->buget + x;
		return co;
	}

	void afisare() {
		cout << "NUMELE CHELTUIELII ESTE:" << this->nume << " IN VALOARE DE:" << this->suma_de_plata << " IAR BUGETUL DISPONIBIL ESTE DE:" << this->buget << "-CU CODUL:" << this->cod;
	}

	CheltuieliOcazionale operator--() { // supraincarcare operator -- post 
		this->buget -= 200;
		return *this;
	}

	CheltuieliOcazionale operator--(int) { // supraincarcare operator -- pre
		CheltuieliOcazionale temp = *this;
		this->suma_de_plata -= 250;
		return temp;
	}


	CheltuieliOcazionale operator!() {  // supraincarcare operator !
		CheltuieliOcazionale co = *this;
		co.existenta = !co.existenta;
		return co;
	}
	friend bool operator>=(CheltuieliOcazionale &co1, CheltuieliOcazionale &co2) { //supraincarcare operator >=
		return co1.buget >= co2.buget;
	}

	bool operator==(CheltuieliOcazionale &co)  //supraincarcare operator ==
	{
		return strcmp(this->nume, co.nume) == 0 ? true : false;
	}


	explicit operator float() { //supraincarcare operator cast explicit
		return buget / cod;
	}

	CheltuieliOcazionale operator()() {  //supraincarcare operator() fara parametrii
		CheltuieliOcazionale co = *this;
		co.suma_de_plata += 200;
		return co;
	}

	CheltuieliOcazionale operator()(float suma) { //supraincarcare operator() cu parametrii
		CheltuieliOcazionale co = *this;
		co.suma_de_plata += suma;
		return co;
	}

	friend istream& operator>>(istream& ecran, CheltuieliOcazionale &co);
	friend ifstream& operator>>(ifstream& ecran, CheltuieliOcazionale &co);
};

int CheltuieliOcazionale::nrcheltuieli = 1;

ostream& operator<<(ostream& ecran, CheltuieliOcazionale co) //supraincarcare <<
{
	cout << "=============================" << endl;
	ecran << co.get_nume() << endl;
	ecran << co.get_suma_de_plata() << endl;
	ecran << co.get_buget() << endl;
	cout << "============================" << endl;
	return ecran;

}

ofstream& operator<<(ofstream& ecran, CheltuieliOcazionale co)
{
	ecran << co.get_nume() << endl;
	ecran << co.get_suma_de_plata() << endl;
	ecran << co.get_buget() << endl;
	return ecran;

}

istream& operator>>(istream& ecran, CheltuieliOcazionale &co)  //supraincarcare >>
{
	cout << "Nume:";
	char buffer[20];
	ecran >> buffer;
	if (strlen(buffer) > 0)
	{
		if (co.nume)
			delete[]co.nume;
		co.nume = new char[strlen(buffer) + 1];
		strcpy(co.nume, buffer);
	}
	cout << "Buget alocat:";
	ecran >> co.buget;
	cout << "Valoare cheltuieala:";
	ecran >> co.suma_de_plata;
	return ecran;
}

ifstream& operator>>(ifstream& ecran, CheltuieliOcazionale &co)
{
	cout << "Nume:";
	char buffer[20];
	ecran >> buffer;
	if (strlen(buffer) > 0)
	{
		if (co.nume)
			delete[]co.nume;
		co.nume = new char[strlen(buffer) + 1];
		strcpy(co.nume, buffer);
	}
	cout << "Buget alocat:";
	ecran >> co.buget;
	cout << "Valoare cheltuieala:";
	ecran >> co.suma_de_plata;
	return ecran;
}

class CheltuieliAnuale {

private:

	int an_cheltuieala;
	char* denumire;
	int suma;
	bool achitat;

public:

	int get_an_cheltuieala() {  //getter an_cheltuieala
		return an_cheltuieala;
	}

	void set_an_cheltuieala(int an) {  //setter an_cheltuieala
		if (an > 0)
			an_cheltuieala = an;
		else throw ("Anul introdus nu este valid!");
	}

	char * get_denumire() { //gettter_denumire
		return denumire;
	}

	void set_denumire(char* noua_denumire) { //setter_denumire
		if (strlen(noua_denumire) > 1)
		{
			if (denumire != NULL)
				delete[]denumire;
		}
		denumire = new char[strlen(noua_denumire) + 1];
		strcpy(denumire, noua_denumire);
	}

	int get_suma() //getter suma
	{
		return suma;
	}

	void set_suma(int noua_suma) { //setter suma
		if (noua_suma > 0)
			suma = noua_suma;
		else throw("Suma este incorecta");
	}

	bool get_achitat() //getter achitat
	{
		return achitat;
	}

	void set_achitat(bool _achitat) //setter achitat
	{
		achitat = _achitat;
	}

	CheltuieliAnuale() {  //constructor fara parametrii
		this->an_cheltuieala = 0;
		this->denumire = new char[strlen("Indisponibil") + 1];
		strcpy(denumire, "Indisponibil");
		this->suma = 0;
		this->achitat = false;
	}

	CheltuieliAnuale(int an_cheltuieala, char* denumire, int suma, bool achitat) { //constructor cu parametrii
		this->an_cheltuieala = an_cheltuieala;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->suma = suma;
		this->achitat = achitat;
	}

	CheltuieliAnuale(CheltuieliAnuale& ca) {  //constructor de copiere
		this->an_cheltuieala = ca.an_cheltuieala;
		this->denumire = new char[strlen(ca.denumire) + 1];
		strcpy(this->denumire, ca.denumire);
		this->suma = ca.suma;
		this->achitat = ca.achitat;
	}

	CheltuieliAnuale operator=(const CheltuieliAnuale &ca)  //supraincarcare operator=
	{
		this->an_cheltuieala = ca.an_cheltuieala;
		this->denumire = new char[strlen(ca.denumire) + 1];
		strcpy(this->denumire, ca.denumire);
		this->suma = ca.suma;
		this->achitat = ca.achitat;
		return *this;

	}

	CheltuieliAnuale operator+(CheltuieliAnuale ca2) {  // supraincarcare operator +
		CheltuieliAnuale ca3 = *this;
		ca3.suma = this->suma + ca2.suma;
		return ca3;
	}

	bool operator==(CheltuieliAnuale ca) { // supraincarcare operator ==
		return strcmp(this->denumire, ca.denumire) == 1 ? true : false;
	}

	CheltuieliAnuale operator++() { // supraincarcare operator pre ++
		this->suma += 250;
		return *this;
	}

	CheltuieliAnuale operator++(int) { // supraincarcare operator post ++
		CheltuieliAnuale alt = *this;
		this->suma -= 150;
		return alt;
	}

	~CheltuieliAnuale()  //destructor
	{
		if (this->denumire)
			delete[]this->denumire;
	}

	void afisare() {  //metoda afisare
		cout << "IN ANUL:" << this->an_cheltuieala << " S-A INREGISTRAT O CHELTUIALA SUB DENUMIREA DE:"
			<< this->denumire << " IN VALOARE DE:" << this->suma << "lei" << " SI CARE ESTE ACHITATA/NEACHITATA(1/0):" << this->achitat;
	}

	CheltuieliAnuale operator!() { //supraincarcare operator !
		CheltuieliAnuale ca = *this;
		ca.achitat = !ca.achitat;
		return ca;
	}

	CheltuieliAnuale operator()() {  //supraincarcare operator() fara parametrii
		CheltuieliAnuale ca = *this;
		ca.an_cheltuieala += 1;
		return ca;
	}

	CheltuieliAnuale operator()(int comision)  //supraincarcare operator() cu parametrii
	{
		CheltuieliAnuale ca = *this;
		ca.suma += comision;
		return ca;
	}

	operator int() //supraincarcare operator cast implicit
	{
		return this->suma;
	}

	explicit operator float() //supraincarcarea operator cast explicit
	{
		return suma*1.8;
	}

	int an_diferenta(CheltuieliAnuale &ca1, CheltuieliAnuale &ca2)  //metoda an_diferenta
	{
		if (ca1.an_cheltuieala > ca2.an_cheltuieala)
			return ca1.an_cheltuieala - ca2.an_cheltuieala;
		else cout << "Nu este posibil";
	}

	friend bool operator<(CheltuieliAnuale &ca1, CheltuieliAnuale &ca2) //supraincarcare operator <
	{
		return ca1.suma < ca2.suma;
	}

	friend istream& operator >> (istream& intrare, CheltuieliAnuale& ca);
	friend ifstream& operator >> (ifstream& intrare, CheltuieliAnuale& ca);

};

ostream& operator<<(ostream& iesire, CheltuieliAnuale ca) { //supraincarcare operator <<
	cout << "============================" << endl;
	iesire << ca.get_an_cheltuieala() << endl;
	iesire << ca.get_denumire() << endl;
	iesire << ca.get_suma() << endl;
	iesire << ca.get_achitat() << endl;
	cout << "=============================" << endl;
	iesire << endl;
	return iesire;
}

ofstream& operator<<(ofstream& iesire, CheltuieliAnuale ca) {
	iesire << ca.get_an_cheltuieala() << endl;
	iesire << ca.get_denumire() << endl;
	iesire << ca.get_suma() << endl;
	iesire << ca.get_achitat() << endl;
	iesire << endl;
	return iesire;
}

istream& operator >> (istream& intrare, CheltuieliAnuale& ca)  //  supraincarcare operator >>
{

	cout << "Anul in care a fost facuta cheltuieala:";
	intrare >> ca.an_cheltuieala;
	cout << "Numele cheltuielii:";
	char buffer[30];
	intrare >> buffer;
	if (strlen(buffer) > 0) {
		if (ca.denumire)
			delete[]ca.denumire;
		ca.denumire = new char[strlen(buffer) + 1];
		strcpy(ca.denumire, buffer);
	}
	cout << "Suma achitata:";
	intrare >> ca.suma;
	cout << "Achitat/Neachitat(1/0):";
	intrare >> ca.achitat;
	return intrare;
}

ifstream& operator >> (ifstream& intrare, CheltuieliAnuale& ca)
{

	cout << "Anul in care a fost facuta cheltuieala:";
	intrare >> ca.an_cheltuieala;
	cout << "Numele cheltuielii:";
	char buffer[30];
	intrare >> buffer;
	if (strlen(buffer) > 0) {
		if (ca.denumire)
			delete[]ca.denumire;
		ca.denumire = new char[strlen(buffer) + 1];
		strcpy(ca.denumire, buffer);
	}
	cout << "Suma achitata:";
	intrare >> ca.suma;
	cout << "Achitat/Neachitat(1/0):";
	intrare >> ca.achitat;
	return intrare;
}


enum  TipuriCheltuieli { prioritate_mica, prioritate_medie, prioritate_mare };

class AlteCheltuieli {

private:

	char * denumire;
	int luna;
	int suma;
	TipuriCheltuieli cheltuieli;

public:

	int getValoare()
	{
		return suma;
	}


	char* get_denumire() { //getter denumire
		return denumire;
	}

	void set_denumire(char * noua_denumire) //setter denumire
	{
		if (strlen(noua_denumire) > 1)
		{
			if (denumire != NULL)
				denumire = new char[strlen(noua_denumire) + 1];
			strcpy(denumire, noua_denumire);
		}
	}

	int get_luna() //getter luna
	{
		return luna;
	}

	void set_luna(int noua_luna) //setter luna
	{
		if (noua_luna >= 1 && noua_luna <= 12)
			luna = noua_luna;
		else throw("Nr introdus nu este in intervalul 1-12");
	}

	TipuriCheltuieli get_cheltuieli() { //getter cheltuieli
		return this->cheltuieli;
	}

	void set_cheltuieli(TipuriCheltuieli c_cheltuieli)  //setter cheltuieli
	{
		this->cheltuieli = c_cheltuieli;
	}

	int get_suma() {   //getter suma
		return suma;
	}

	void set_suma(int noua_suma) {  //setter suma;
		if (noua_suma > 0)
			suma = noua_suma;
		else throw("Suma introdusa este incorecta!");
	}

	AlteCheltuieli() {  //constructor fara parametrii
		this->denumire = new char[strlen("Reparatii") + 1];
		strcpy(this->denumire, "Reparatii");
		this->suma = 50;
		this->cheltuieli = prioritate_mica;
	}

	AlteCheltuieli(char * denumire, int suma, TipuriCheltuieli cheltuieli) //constructor cu parametrii
	{

		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->suma = suma;
		this->cheltuieli = cheltuieli;
	}

	AlteCheltuieli operator=(const AlteCheltuieli &ca) { // supraincare operator =
		if (denumire != NULL)
			delete[]denumire;
		this->denumire = new char[strlen(ca.denumire) + 1];
		strcpy(this->denumire, ca.denumire);
		this->suma = ca.suma;
		this->cheltuieli = ca.cheltuieli;
		return *this;
	}

	~AlteCheltuieli() {  //destructor
		if (this->denumire)
			delete[]this->denumire;
	}

	AlteCheltuieli(AlteCheltuieli &ca) {  //constructor de copiere
		this->denumire = new char[strlen(ca.denumire) + 1];
		strcpy(this->denumire, ca.denumire);
		this->suma = ca.suma;
		this->cheltuieli = ca.cheltuieli;
	}

	AlteCheltuieli operator+(AlteCheltuieli ca2) {  // supraincarcare operator+
		AlteCheltuieli ca3 = *this;
		ca3.suma = this->suma + ca2.suma;
		return ca3;
	}

	AlteCheltuieli operator--() { // supraincarcare operator pre --
		this->suma -= 20;
		return *this;
	}

	AlteCheltuieli operator--(int) {  //supraincarcare operator post --
		AlteCheltuieli temp = *this;
		this->suma -= 20;
		return temp;
	}

	explicit operator float() { // supraincarcare operator cast explicit
		return suma*1.5;
	}

	operator int()  //supraincarcare operator cast implicit
	{
		return this->cheltuieli;
	}

	AlteCheltuieli operator()(float suma) {  //operator() cu parametrii
		AlteCheltuieli ca = *this;
		ca.suma = suma + 100;
		return ca;
	}
	AlteCheltuieli operator()() { // supraincarcare operator() fara parametrii
		AlteCheltuieli ca = *this;
		ca.suma *= 3;
		return ca;
	}

	AlteCheltuieli operator !() { //supraincarcare operator !
		AlteCheltuieli ca = *this;
		ca.suma = !ca.suma;
		return ca;

	}

	friend  bool operator > (AlteCheltuieli &ca1, AlteCheltuieli &ca2) {  // supraincarcare operator >
		return ca1.suma > ca2.suma;
	}

	friend istream& operator>>(istream& input, AlteCheltuieli& ca)  //supraincarcare operator >>
	{
		cout << "Numele cheltuielii:" << endl;
		char buffer[20];
		input >> buffer;
		if (strlen(buffer) > 0) {
			if (ca.denumire)
				delete[]ca.denumire;
			ca.denumire = new char[strlen(buffer) + 1];
			strcpy(ca.denumire, buffer);
		}
		cout << "Suma de plata:" << endl;
		input >> ca.suma;
		cout << "Importanta cheltuileii? 0-prioritate_mica,1-prioritate_medie si 2-prioritate_mare: " << endl;
		int change;
		input >> change;
		switch (change) {
		case 0:
			ca.cheltuieli = prioritate_mica;
			break;
		case 1:
			ca.cheltuieli = prioritate_medie;
			break;
		case 2:
			ca.cheltuieli = prioritate_mare;
			break;
		default:
			ca.cheltuieli = prioritate_mica;
			break;
		}
		return input;
	}

	friend ifstream& operator>>(ifstream& input, AlteCheltuieli& ca)
	{
		cout << "Numele cheltuielii:" << endl;
		char buffer[20];
		input >> buffer;
		if (strlen(buffer) > 0) {
			if (ca.denumire)
				delete[]ca.denumire;
			ca.denumire = new char[strlen(buffer) + 1];
			strcpy(ca.denumire, buffer);
		}
		cout << "Suma de plata:" << endl;
		input >> ca.suma;
		cout << "Importanta cheltuileii? 0-prioritate_mica,1-prioritate_medie si 2-prioritate_mare: " << endl;
		int change;
		input >> change;
		switch (change) {
		case 0:
			ca.cheltuieli = prioritate_mica;
			break;
		case 1:
			ca.cheltuieli = prioritate_medie;
			break;
		case 2:
			ca.cheltuieli = prioritate_mare;
			break;
		default:
			ca.cheltuieli = prioritate_mica;
			break;
		}
		return input;
	}


	void afisare() //metoda afisare
	{
		cout << "Cheltuieala: " << this->denumire << " are o valoare de:" << this->suma << "lei fiind de tipul:" << this->cheltuieli;
	}

};

ostream& operator<<(ostream& output, AlteCheltuieli ca) {  //operator <<
	output << ca.get_denumire() << endl;
	output << ca.get_suma() << endl;
	output << ca.get_cheltuieli() << endl;
	output << endl;
	return output;
}

ofstream& operator<<(ofstream& output, AlteCheltuieli ca) {
	output << ca.get_denumire() << endl;
	output << ca.get_suma() << endl;
	output << ca.get_cheltuieli() << endl;
	output << endl;
	return output;
}

class CheltuieliSuplimentare : public CheltuieliNecesare {

private:
	float suma_de_plata;

public:

	float get_suma()
	{
		return suma_de_plata;
	}

	void set_suma(int noua_suma)
	{
		if (noua_suma > 0)
			suma_de_plata = noua_suma;
		else throw "Valoare incorecta";
	}


	CheltuieliSuplimentare() :CheltuieliNecesare()
	{
		this->suma_de_plata = 100;
	}

	CheltuieliSuplimentare(float suma_de_plata, char * nume_cheltuiala, int valoare, bool suma_achitata) :CheltuieliNecesare(nume_cheltuiala, valoare, suma_achitata)
	{
		this->suma_de_plata = suma_de_plata;
	}

	CheltuieliSuplimentare(CheltuieliSuplimentare &cs) :CheltuieliNecesare(cs)
	{
		suma_de_plata = cs.suma_de_plata;
	}

	CheltuieliSuplimentare operator =(CheltuieliSuplimentare &cs)
	{
		CheltuieliNecesare::operator=(CheltuieliNecesare(cs));
		suma_de_plata = cs.suma_de_plata;
	}
	friend ostream& operator<<(ostream& console, CheltuieliSuplimentare cs)
	{
		console << (CheltuieliNecesare)cs;
		console << cs.get_suma() << endl;
		console << endl;
		return console;
	}
};

class CheltuieliPeTermenLung :public CheltuieliAnuale {

private:

	int nr_luni;
	int *cheltuieli;

public:

	int get_nr_luni() {
		return nr_luni;
	}

	void set_luni(int luni) {
		if (luni > 0 && luni <= 12)
			nr_luni = luni;
		else
			throw "Valoare incorecta!";
	}

	int* get_cheltuieli() {
		return cheltuieli;
	}

	void set_cheltuieli(int* vector, int luni) {
		if (cheltuieli)
			delete[]cheltuieli;
		cheltuieli = new int[luni];
		for (int i = 0; i < luni; i++)
		{
			this->cheltuieli[i] = vector[i];
		}
		this->nr_luni = luni;
	}

	CheltuieliPeTermenLung() :CheltuieliAnuale()
	{
		this->nr_luni = 0;
		this->cheltuieli = NULL;
	}

	CheltuieliPeTermenLung(int nr_luni, int * cheltuieli, int an_cheltuieala, char* denumire, int suma, bool achitat) :CheltuieliAnuale(an_cheltuieala, denumire, suma, achitat)
	{
		this->nr_luni = nr_luni;
		this->cheltuieli = new int[nr_luni];
		for (int i = 0; i < nr_luni; i++)
		{
			this->cheltuieli[i] = cheltuieli[i];
		}
	}

	CheltuieliPeTermenLung(CheltuieliPeTermenLung &cpt) :CheltuieliAnuale(cpt)
	{
		this->nr_luni = cpt.nr_luni;
		this->cheltuieli = new int[cpt.nr_luni];
		for (int j = 0; j < cpt.nr_luni; j++)
		{
			this->cheltuieli[j] = cpt.cheltuieli[j];
		}
	}

	CheltuieliPeTermenLung operator =(CheltuieliPeTermenLung &cpt)
	{
		CheltuieliAnuale::operator=((CheltuieliAnuale)cpt);
		this->nr_luni = cpt.nr_luni;
		if (cheltuieli)
			delete[]cheltuieli;
		cheltuieli = new int[nr_luni];
		for (int k = 0; k < nr_luni; k++)
		{
			this->cheltuieli[k] = cpt.cheltuieli[k];
		}
	}

	friend ostream& operator << (ostream & exit, CheltuieliPeTermenLung cpt)
	{
		exit << (CheltuieliAnuale)cpt;
		exit << cpt.get_nr_luni() << endl;
		for (int i = 0; i < cpt.get_nr_luni(); i++)
		{
			exit << cpt.cheltuieli[i] << " ";
		}
		return exit;
	}

	~CheltuieliPeTermenLung()
	{
		if (this->cheltuieli)
			delete[]this->cheltuieli;
	}

};


void main(int argc, char* argv[])
{

	cout << "Numar argumente: " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "Argument: " << i + 1 <<" "<< argv[i] << endl;
	} 

	cout << "=======================ALEGE PROGRAMUL DORIT===========================" << endl;
	cout << "1-APLICATIE CU ROL IN GENERAREA CHELTUIELILOR SI A FISIERELOR TEXT" << endl;
	cout << "2-APLICATIE CU ROL IN GENERAREA CHELULTUIELOR SI A FISIERELOR BINARE" << endl;
	cout << "3-APLICATIE CU ROL IN GENERAREA RAPOARTELOR" << endl;
	cout << "4-IESIRE" << endl;
	cout << "=======================================================================" << endl;

	int varianta;
	cout << "Introduceti varianta dorita:";
	cin >> varianta;
	CheltuieliNecesare cn1, cn2, cn3, cn5, cn6, cn7;
	CheltuieliNeprevazute cnn1("nume", 2, new int[2]{ 10,20 }, 300), cnn2("Reparatii mobila", 3, new int[3]{ 100,105,200 }, 250);
	CheltuieliOcazionale co1, co2, co3;
	CheltuieliAnuale ca1, ca2, ca3;
	AlteCheltuieli ac1, ac2, ac3;

	switch (varianta)
	{
	case 1:
		cout << "<=================================================>" << endl;
		cout << "APLICATIE CU ROL IN GENERAREA CHELTUIELILOR SI A FISIERELOR TEXT:" << endl;
		cout << "1-Cheltuieli Necesare" << endl;
		cout << "2-Cheltuieli Neprevazute" << endl;
		cout << "3-Cheltuieli Ocazionale" << endl;
		cout << "4-Cheltuieli Anuale" << endl;
		cout << "5-Alte Cheltuieli" << endl;
		cout << "6-Iesire" << endl;
		cout << "<=================================================>" << endl;


		int optiune;
		cout << "Introduceti optiunea dorita:";
		cin >> optiune;

		switch (optiune)
		{
		case 1:
			bool statement, statement2;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> statement;
			if (statement == true)
			{
				cin >> cn1;
				cout << cn1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> statement2;
				if (statement2 == true)
				{
					ofstream f("CheltuieliNecesare.txt", ios::out);
					f << cn1 << endl;
					f.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a fost inregistrata!" << endl;
			}
			else cout << "Sfarsit program";
			break;

		case 2:
			bool statement3, statement4;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> statement3;
			if (statement3 == true)
			{
				cin >> cnn1;
				cout << cnn1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> statement4;
				if (statement4 == true)
				{
					ofstream q("CheltuieliNeprevazute.txt", ios::out);
					q << cnn1 << endl;
					q.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a fost inregistrata!";
			}
			else cout << "Sfarsit program";
			break;

		case 3:
			bool statement5, statement6;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> statement5;
			if (statement5 == true)
			{
				cin >> co1;
				cout << co1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> statement6;
				if (statement6 == true)
				{
					ofstream p("CheltuieliOcazionale.txt", ios::out);
					p << co1 << endl;
					p.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a fost inregistrata!";
			}
			else cout << "Sfarsit program";
			break;
		case 4:
			bool statement7, statement8;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> statement7;
			if (statement7 == true)
			{
				cin >> ca1;
				cout << ca1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> statement8;
				if (statement8 == true)
				{
					ofstream a("CheltuieliAnuale.txt", ios::out);
					a << ca1 << endl;
					a.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a fost inregistrata!";
			}
			else cout << "Sfarsit program";
			break;
		case 5:
			bool statement9, statement10;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> statement9;
			if (statement9 == true)
			{
				cin >> ac1;
				cout << ac1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> statement10;
				if (statement10 == true)
				{
					ofstream fac("AlteCheltuieli.txt", ios::out);
					fac << ac1 << endl;
					fac.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a fost inregistrata!";
			}
			else cout << "Sfarsit program";
			break;
		case 6:
			cout << "Aplicatia se inchide..." << endl;
			break;
		default:
			cout << "Optiune invalida!" << endl;
		}
		break;

	case 2:
		cout << endl << "<######################################################>" << endl;
		cout << "APLICATIE CU ROL IN GENERAREA CHELTUIELILOR SI A FISIERELOR BINARE:" << endl;
		cout << "1-Cheltuieli Necesare" << endl;
		cout << "2-Cheltuieli Neprevazute" << endl;
		cout << "3-Cheltuieli Ocazionale" << endl;
		cout << "4-Cheltuieli Anuale" << endl;
		cout << "5-Alte Cheltuieli" << endl;
		cout << "6-Iesire" << endl;
		cout << "<######################################################>" << endl;


		int optiune1;
		cout << "Introduceti optiunea dorita:";
		cin >> optiune1;

		switch (optiune1)
		{
		case 1:
			bool b1, b2;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> b1;
			if (b1 == true)
			{
				cin >> cn1;
				cout << cn1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier binar?(1-da/0-nu)";
				cin >> b2;
				if (b2 == true)
				{
					ofstream fisb("CheltuieliNecesare.bin", ios::binary | ios::out);
					fisb.write((char*)&cn1, sizeof(CheltuieliNecesare));
					fisb.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a putut fi inregistrata!" << endl;
			}
			else cout << "Sfarsit program...";
			break;

		case 2:
			bool b3, b4;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> b3;
			if (b3 == true)
			{
				cin >> cnn1;
				cout << cnn1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> b4;
				if (b4 == true)
				{
					ofstream fb("CheltuieliNeprevazute.bin", ios::binary | ios::out);
					fb.write((char*)&cnn1, sizeof(CheltuieliNeprevazute));
					fb.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a putut fi inregistrata!";
			}
			else cout << "Sfarsit program...";
			break;

		case 3:
			bool b5, b6;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> b5;
			if (b5 == true)
			{
				cin >> co1;
				cout << co1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> b6;
				if (b6 == true)
				{
					ofstream fo("CheltuieliOcazionale.bin", ios::binary | ios::out);
					fo.write((char*)&co1, sizeof(CheltuieliOcazionale));
					fo.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a putut fi inregistrata!";
			}
			else cout << "Sfarsit program";
			break;
		case 4:
			bool b7, b8;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> b7;
			if (b7 == true)
			{
				cin >> ca1;
				cout << ca1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> b8;
				if (b8 == true)
				{
					ofstream fca("CheltuieliAnuale.bin", ios::binary | ios::out);
					fca.write((char*)&ca1, sizeof(CheltuieliAnuale));
					fca.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu putut fi inregistrata!";
			}
			else cout << "Sfarsit program...";
			break;
		case 5:
			bool b9, b10;
			cout << "Doriti sa introduceti o cheltuieala noua?(1-da/0-nu)";
			cin >> b9;
			if (b9 == true)
			{
				cin >> ac1;
				cout << ac1;
				cout << "Doriti sa inregistrati cheltuieala intr-un fisier text?(1-da/0-nu)";
				cin >> b10;
				if (b10 == true)
				{
					ofstream fc("AlteCheltuieli.bin", ios::binary | ios::out);
					fc.write((char*)&ac1, sizeof(AlteCheltuieli));
					fc.close();
					cout << "Cheltuieala a fost inregistrata cu succes!";
					break;
				}
				else cout << "Cheltuieala nu a fost inregistrata!";
			}
			else cout << "Sfarsit program";
			break;
		case 6:
			cout << "Aplicatia se inchide..." << endl;
			break;
		default:
			cout << "Optiune invalida!" << endl;
		}
		break;
	case 3:
		cout << endl << "<######################################################>" << endl;
		cout << "APLICATIE CU ROL IN GENERAREA RAPOARTELOR:" << endl;
		cout << "1-Raport Cheltuieli Necesare" << endl;
		cout << "2-Raport Cheltuieli Neprevazute" << endl;
		cout << "3-Raport Cheltuieli Ocazionale" << endl;
		cout << "4-Raport Cheltuieli Anuale" << endl;
		cout << "5-Raport Alte Cheltuieli" << endl;
		cout << "6-Raport Total" << endl;
		cout << "7-Iesire" << endl;
		cout << "<#######################################################>" << endl;

		int optiune2;
		cout << "Alegerea facuta:";
		cin >> optiune2;

		switch (optiune2)
		{
		case 1:
			bool gen;
			cout << "Doresti generarea unui raport?(1/0)";
			cin >> gen;
			if (gen == 1)
			{
				cout << "Raportul a fost generat!";
				ofstream raportCheltuieliNecesare;
				raportCheltuieliNecesare.open("RaportCheltuieliNecesare.txt", ios::out | ios::trunc);
				if (raportCheltuieliNecesare.is_open()) {
					raportCheltuieliNecesare << "Lista Cheltuieli:" << endl;
					raportCheltuieliNecesare << cn2.get_nume_cheltuieala() << endl;
					raportCheltuieliNecesare << cn3.get_nume_cheltuieala() << endl;
					cout << endl;
					raportCheltuieliNecesare << "Detalii cheltuieli:" << endl;
					raportCheltuieliNecesare << cn2 << endl;
					raportCheltuieliNecesare << cn3 << endl;
				}


				else
					cout << endl << "Problema deschidere fisier!";
			}
			else cout << "Raportul nu a fost generat!";
			break;
		case 2:
			bool gen2;
			cout << "Doresti generarea unui raport?(1/0)";
			cin >> gen2;
			if (gen2 == 1)
			{
				cout << "Raport generat!";
				ofstream raportCheltuieliNeprevazute;
				raportCheltuieliNeprevazute.open("RaportCheltuieliNeprevazute.txt", ios::out | ios::trunc);
				if (raportCheltuieliNeprevazute.is_open()) {
					raportCheltuieliNeprevazute << "Lista Cheltuieli:" << endl;
					raportCheltuieliNeprevazute << cn5.get_nume_cheltuieala() << endl;
					raportCheltuieliNeprevazute << cn6.get_nume_cheltuieala() << endl;
					raportCheltuieliNeprevazute << cn7.get_nume_cheltuieala() << endl;
					raportCheltuieliNeprevazute << "Detalii cheltuieli:" << endl;
					raportCheltuieliNeprevazute << cn5;
					raportCheltuieliNeprevazute << cn6;
					raportCheltuieliNeprevazute << cn7;
				}
				else cout << "Raportul nu exista!";
			}
			else cout << "Nu ai ales crearea unui raport!";
			break;
		case 3:
			bool gen3;
			cout << "Doresti generarea unui raport?(1/0)";
			cin >> gen3;
			if (gen3 == 1)
			{
				cout << "Raport generat!";
				ofstream raportCheltuieliOcazionale;
				raportCheltuieliOcazionale.open("RaportCheltuieliOcazionale.txt", ios::out | ios::trunc);
				if (raportCheltuieliOcazionale.is_open()) {
					raportCheltuieliOcazionale << "Lista Cheltuieli:" << endl;
					raportCheltuieliOcazionale << co1.get_nume() << endl;
					raportCheltuieliOcazionale << co2.get_nume() << endl;
					raportCheltuieliOcazionale << co3.get_nume() << endl;
					raportCheltuieliOcazionale << "Detalii cheltuieli:" << endl;
					raportCheltuieliOcazionale << co1;
					raportCheltuieliOcazionale << co2;
					raportCheltuieliOcazionale << co3;
				}
				else cout << "Raportul nu exista!";
			}
			else cout << "Nu ai ales crearea unui raport!";
			break;
		case 4:
			bool gen4;
			cout << "Doresti generarea unui raport?(1/0)";
			cin >> gen4;
			if (gen4 == 1)
			{
				cout << "Raport generat!";
				ofstream raportCheltuieliAnuale;
				raportCheltuieliAnuale.open("RaportCheltuieliAnuale.txt", ios::out | ios::trunc);
				if (raportCheltuieliAnuale.is_open()) {
					raportCheltuieliAnuale << "Lista Cheltuieli:" << endl;
					raportCheltuieliAnuale << ca1.get_denumire() << endl;
					raportCheltuieliAnuale << ca2.get_denumire() << endl;
					raportCheltuieliAnuale << ca3.get_denumire() << endl;
					raportCheltuieliAnuale << "Detalii cheltuieli:" << endl;
					raportCheltuieliAnuale << ca1;
					raportCheltuieliAnuale << ca2;
					raportCheltuieliAnuale << ca3;
				}
				else cout << "Raportul nu exista!";
			}
			else cout << "Nu ai ales crearea unui raport!";
			break;
		case 5:
			bool gen5;
			cout << "Doresti generarea unui raport?(1/0)";
			cin >> gen5;
			if (gen5 == 1)
			{
				cout << "Raport generat!";
				ofstream raportAlteCheltuieli;
				raportAlteCheltuieli.open("RaportAlteCheltuieli.txt", ios::out | ios::trunc);
				if (raportAlteCheltuieli.is_open()) {
					raportAlteCheltuieli << "Denumire:" << endl;
					raportAlteCheltuieli << ac2.get_denumire() << endl;
					raportAlteCheltuieli << ac3.get_denumire() << endl;
					raportAlteCheltuieli << "Detalii despre cheltuieli:" << endl;
					raportAlteCheltuieli << ac2;
					raportAlteCheltuieli << ac3;
				}
				else cout << "Raportul nu a putut fi deschis!";
			}
			else cout << "Nu a fost generat!";
			break;
		case 6:
			bool gen6;
			cout << "Doresti generarea unui raport complet?(1/0)";
			cin >> gen6;
			if (gen6 == 1)
			{
				cout << "Raport generat!";
				ofstream raportCheltuieli;
				raportCheltuieli.open("RaportCheltuieliperTotal.txt", ios::out | ios::trunc);
				if (raportCheltuieli.is_open()) {
					raportCheltuieli << "Cheltuieli Necesare:" << endl;
					raportCheltuieli << cn1.get_nume_cheltuieala() << endl;
					raportCheltuieli << cn2.get_nume_cheltuieala() << endl;
					raportCheltuieli << "Cheltuieli Neprevazute:" << endl;
					raportCheltuieli << cnn1.get_nume_cheltuieala() << endl;
					raportCheltuieli << cnn2.get_nume_cheltuieala() << endl;
					raportCheltuieli << "Cheltuieli Ocazionale:" << endl;
					raportCheltuieli << co1.get_nume() << endl;
					raportCheltuieli << co2.get_nume() << endl;
					raportCheltuieli << "Cheltuieli Anuale:" << endl;
					raportCheltuieli << ca1.get_denumire() << endl;
					raportCheltuieli << ca2.get_denumire() << endl;
					raportCheltuieli << "Alte Cheltuieli:" << endl;
					raportCheltuieli << ac1.get_denumire() << endl;
					raportCheltuieli << ac2.get_denumire() << endl;
					raportCheltuieli << "LISTA TUTUROR CHELTUIELILOR:" << endl;
					raportCheltuieli << cn1;
					raportCheltuieli << cn2;
					raportCheltuieli << cnn1;
					raportCheltuieli << cnn2;
					raportCheltuieli << co1;
					raportCheltuieli << co2;
					raportCheltuieli << ca1;
					raportCheltuieli << ca2;
					raportCheltuieli << ac1;
					raportCheltuieli << ac2;
				}
				else cout << "Raportul nu exista!";
			}
			else cout << "Nu a fost generat!";

			break;
		case 7:
			cout << "Aplicatia se inchide..." << endl;
			break;
		default:
			cout << "Optiune invalida!";
		}
		break;
	case 4:
		cout << "Aplicatia se inchide...." << endl;
		break;
	default:
		cout << "Optiunea introdusa este invalida" << endl;
	}

	cout << "Vector de obiecte:" << endl;
	CheltuieliNecesare **cn;
	int nrCheltuieli = 5;
	cn = new CheltuieliNecesare*[nrCheltuieli];

	cn[0] = new CheltuieliNecesare("Apa calda", 200, true);
	cn[1] = new CheltuieliNecesare("Utilitati", 250, true);
	cn[2] = new CheltuieliNecesare("Mancare", 300, false);
	cn[3] = new CheltuieliNecesare("Imbracaminte iarna", 100, false);
	cn[4] = new CheltuieliNecesare("Gaze", 20, true);

	for (int i = 0; i < nrCheltuieli; i++)
	{
		cout << cn[i]->getValoare() << " " << cn[i]->getNume() << endl;
	}


	for (int i = 0; i < nrCheltuieli; i++)
	{
		delete cn[i];
	}
	delete[]cn;


	//testare CheltuieliSuplimentare
	//CheltuieliSuplimentare cs;
	//cs.set_suma(1240);
	//cout << cs.get_suma();

	//testareCheltuieliPeTermenLung
	/*CheltuieliPeTermenLung cpt;
	cpt.set_luni(3);
	cout << cpt.get_nr_luni();
	int vector[3] = { 10,20,30 };
	int luni = cpt.get_nr_luni();
	cpt.set_cheltuieli(vector, luni);
	cout << endl << cpt.get_cheltuieli()[0];
	cout << endl << cpt.get_cheltuieli()[1];
	cout << endl << cpt.get_cheltuieli()[2];*/


	////pentru clasa CheltuieliNecesare

	//CheltuieliNecesare cn2("Utilitati", 200, true);
	//ofstream f("CheltuieliNecesare.txt", ios::out);
	////cout << cn2 << endl;
	//f << cn2 << endl;
	//f.close();

	/*cout << "Scriere in fisier text pentru clasa CheltuieliNecesare:" << endl;
	ifstream g("CheltuieliNecesare_citire.txt", ios::in);
	CheltuieliNecesare cn4;
	g >> cn4;
	g.close();*/

	//ofstream fisb("CheltuieliNecesare.bin", ios::binary | ios::out);
	//fisb.write((char*)&cn2, sizeof(CheltuieliNecesare));
	//fisb.close();

	////cout << cn2 << endl;

	/*cout << "Scriere in fisier binar pentru clasa CheltuieliNecesare:" << endl;
	ifstream fbw("CheltuieliNecesaree.bin", ios::binary | ios::in);
	fbw.read((char*)&cn2, sizeof(CheltuieliNecesare));
	fbw.close();*/

	//CheltuieliNecesare cn;
	////cn.afisare();
	////cout << endl;
	//CheltuieliNecesare cn2("Apa", 200, true);  
	////	cn2.afisare();
	////	cn2.tva();
	////	cout << endl;
	////	cout << "Pretul cu TVA este:";
	////	cn2.afisare();
	////	cout << endl;
	////	cout << "Operator post ++:";
	//CheltuieliNecesare cn3("Gaze", 310, true);
	////	cn3 = cn++;
	////	cn.afisare();
	////	cout << endl;
	////	cout << "Operator pre ++:";
	////	CheltuieliNecesare cn4 = ++cn;
	////	cn.afisare();
	////	cout << endl;
	////	cout << "Operator >";
	////	if (cn2 < cn) cout << "Prima cheltuieala are o valoare mai mica";
	////	else cout << "A doua cheltuieala este mai mare";
	////	cout << endl;
	////	cout << "Testare metode statice:";
	////	cout << "In total in aplicatie sunt: " << CheltuieliNecesare::get_cod()
	////		<< " coduri" << endl;
	////	cout << "Operator () cu parametru:";
	////	cn2 = cn(100);
	////	cn2.afisare();
	////	cout << endl;
	////	cout << "Operator () cu parametru:";
	////	cn2 = cn();
	////	cn2.afisare();
	////	cout << endl;
	////	cout << "Operator==";
	////	if (cn2 == cn) cout << "sunt egale";
	////	else throw("Nu sunt egale");
	////	cout << endl;
	////	cout << "Tipul cheltuielii este:";
	////	cn.set_nume_cheltuieala(" Cheltuieala pentru Intretinere");
	////	cout << cn.get_nume_cheltuieala();
	////	cout << endl;
	////	cout << "Suma de plata este(in lei):";
	////	cn.set_valoare(120);
	////	cout << cn.get_valoare();
	////	cout << endl;

	////pentru clasa CheltuieliNeprevazute

	//CheltuieliNeprevazute cn4("Conducta sparta", 2, new int[2]{ 10,20 }, 300);
	//ofstream q("CheltuieliNeprevazute.txt", ios::out);
	////cout << cn4 << endl;
	//q << cn4 << endl;
	//q.close();

	/*cout << "Scriere in fisier text pentru clasa CheltuieliNeprevazute:" << endl;
	ifstream h("CheltuieliNeprevazute_citire.txt", ios::in);
	CheltuieliNeprevazute cn9;
	h >> cn9;
	h.close();*/

	//CheltuieliNeprevazute cn6("Usa defecta", 3, new int[3]{ 150,180,210 }, 180);

	//ofstream fb("CheltuieliNeprevazute.bin", ios::binary | ios::out);
	//fb.write((char*)&cn6, sizeof(CheltuieliNeprevazute));
	//fb.close();
	/*cout << "Scriere in fisier binar pt clasa Cheltuieli Neprevazute:"<<endl;
	CheltuieliNeprevazute cn8;
	ifstream fbi("fisier.bin", ios::binary | ios::in);
	fbi.read((char*)&cn8, sizeof(CheltuieliNeprevazute));
	fbi.close();*/
	//cout << cn7;

	//ofstream fcc("CheltuieliNeprevazute.csv", ios::out);
	//CheltuieliNeprevazute * cheltuieala;
	//cheltuieala = new CheltuieliNeprevazute[5];
	//for (int i = 0; i < 5; i++) {
	//	fcc << cheltuieala[i];
	//}
	//fcc.close();


	//CheltuieliNeprevazute cnn0;
	//CheltuieliNeprevazute cnn01("Instalatie gaze", 3, new int[3]{ 3,10,20 }, 2000);
	////cnn1.afisare();
	////cout << endl;
	//CheltuieliNeprevazute cnn2("Chiuveta infundata", 3, new int[3]{ 15,10,20 }, 2000);
	////cnn2.afisare();
	////cout << endl << "***************************************************" << endl;
	////cnn1 = cnn();
	////cnn1.afisare();
	////cout << endl;
	////cnn1 = cnn(100);
	////cnn1.afisare();
	////cout << endl;
	////cnn2.afisare();
	////cout << "Operator de indexare:";
	////cnn[1] = 1000;//operator indexare
	////cnn.afisare();
	////if (cnn > cnn1) cout << "Bugetul alocat primei cheltuieli este mai mare";
	////CheltuieliNeprevazute cnn3 = cnn + cnn2;
	////cnn3.afisare();
	////cout << endl;
	////cnn2 = cnn++;
	////cnn.afisare();
	////cout << endl;
	////CheltuieliNeprevazute cnn6 = cnn;//testarea constructor copiere
	////cnn6.afisare();
	////cout << endl;
	////cout << endl;
	////cnn6.afisare();
	////cout << endl;
	////cnn.set_nume_cheltuieala("Accident masina");
	////cout << cnn.get_nume_cheltuieala();
	////cout << endl;
	////int vector[3] = { 8,9,10 };
	////int lungime = 3;
	////
	////cnn.set_valoare_cheltuieala(vector, lungime);
	////cout << endl << cnn.get_valoare_cheltuieala()[1];
	////cout << cnn.get_valoare_cheltuieala();
	////cout << endl;
	////cnn.set_buget_alocat(1000);
	////cout << cnn.get_buget_alocat();
	////cout << endl;
	////cnn.afisare();

	////pentru clasa CheltuieliOcazionale

	//CheltuieliOcazionale co2("Cumparaturi Craciun", 200, 500);
	//ofstream p("CheltuieliOcazionale.txt", ios::out);
	////cout << co2 << endl;
	//p << co2 << endl;
	//p.close();


	/*cout << "Scriere in fisier text pentru clasa CheltuieliOcazionale:" << endl;
	CheltuieliOcazionale co4;
	ifstream l("CheltuieliOcazionale_citire.txt", ios::in);
	l >> co4;
	l.close();*/

	//CheltuieliOcazionale co4("Ornamente Craciun", 200, 500);
	//ofstream fo("CheltuieliOcazionale.bin", ios::binary | ios::out);
	//fo.write((char*)&co4, sizeof(CheltuieliOcazionale));
	//fo.close();

	/*cout << "Scriere in fisier binar pentru clasa CheltuieliOcazionale:" << endl;
	ifstream go("CheltuieliOcazionale_scriere.bin", ios::binary | ios::in);
	CheltuieliOcazionale co5;
	go.read((char*)&co5, sizeof(CheltuieliOcazionale));
	go.close();*/

	//CheltuieliOcazionale co01;
	///co1.afisare();
	//cout << endl;*/
	//CheltuieliOcazionale co02("Vacanta", 2000, 4500);
	///co2.afisare();
	//cout << endl;
	//CheltuieliOcazionale co3;
	//cout << endl;
	//CheltuieliOcazionale co4 = co2();
	//co4.afisare();
	//cout << endl;
	//CheltuieliOcazionale co5 = co2(150);
	//cout << endl;
	//co5.afisare();
	//cout << endl;
	//if (co2 == co1) cout << "Ambele cheltuieli au aceeasi denumire";
	//else cout << "Nu au aceeasi denumire!";
	//cout << endl;
	//cout << "Supraincare -- post:"<<endl;
	//CheltuieliOcazionale co6 = co2--;
	//co2.afisare();
	//cout <<endl<< "Supraincare -- pre:" << endl;
	//co6 = --co1;
	//co1.afisare();
	//cout << endl;
	//cout << "Operator !:";
	//co3 = !co2;
	//co3.afisare();
	//cout << endl;
	//float x = (float)co2;
	//cout << "Valoarea reala:" << endl;
	//if (co2 >= co1) cout << "Al doilea buget alocat este mai mare/egal";
	//cout << endl;
	//cout << "Operator +:";
	//co3 = co1 + co2;
	//co3.afisare();
	//cout << endl;
	//cout << "Constructor de copiere:";
	//CheltuieliOcazionale co7 = co2;
	//co7.afisare();
	//cout <<endl<< "Testare supraincarcare >> si <<:"<<endl;
	//cin >> co1;
	//cout << co1;
	//cout << endl;
	//cout << "Testare getteri si setteri:"<<endl;
	//co1.set_nume("Vacanta in Ibiza");
	//cout << co1.get_nume();
	//cout << endl;
	//co1.set_suma_de_plata(200);
	//cout << co1.get_suma_de_plata();
	//cout << endl;
	//co1.set_buget(350);
	//cout << co1.get_buget();
	//*/

	////pentru clasa CheltuieliAnuale

	//CheltuieliAnuale ca2(2016, "Impozit", 100, false);
	//ofstream a("CheltuieliAnuale.txt", ios::out);
	////cout << ca2 << endl;
	//a << ca2 << endl;
	//a.close();

	/*cout << "Scriere in fisier text pentru clasa CheltuieliAnuale:" << endl;
	CheltuieliAnuale ca5;
	ifstream lf("CheltuieliAnuale_citire.txt", ios::in);
	lf >> ca5;
	cout << endl << ca5;;
	lf.close();*/

	//CheltuieliAnuale ca4(2013, "Taxe speciale", 160, false);
	//ofstream fca("CheltuieliAnuale.bin", ios::binary | ios::out);
	//fca.write((char*)&ca4, sizeof(CheltuieliAnuale));
	//fca.close();
	/*cout << "Scriere in fisier binar pentru clasa CheltuieliNecesare:" << endl;
	ifstream gca("CheltuieliAnuale_scriere.bin", ios::binary | ios::in);
	CheltuieliAnuale ca8;
	gca.read((char*)&ca8, sizeof(CheltuieliAnuale));
	cout << ca8;
	gca.close();*/

	////cout << "Testare constructor fara parametrii:" << endl;
	//CheltuieliAnuale ca1;
	////ca1.afisare();
	////cout << endl;
	////cout << "Testare constructor cu parametrii:" << endl;
	//CheltuieliAnuale ca2(2013, "Impozit", 350, true);
	////ca2.afisare();
	////cout << endl;
	////cout << "Testare supraincarcare operator !:";
	//CheltuieliAnuale ca3;
	////ca3 = !ca1;
	////ca1.afisare();
	////cout << endl;
	////cout << "Testare operator () fara parametru:" << endl;
	////ca3 = ca2();
	////ca3.afisare();
	////cout << "Testare operator () cu parametru:" << endl;
	////ca3 = ca2(100);
	////ca3.afisare();
	////cout << endl << "Operator explicit de cast:" << endl;
	////int z;
	////z = (float)ca2;
	////cout << z << endl;
	////if (ca2 < ca1) cout << "Suma primei cheltuieli este mai mica";
	////else cout << "Suma celei de a doua cheltuieli este mai mica";
	////cout << "Testare operator+:" << endl;
	////ca3 = ca1 + ca2;
	////cout << "Testare operator ==:" << endl;
	////if (ca1 == ca2) cout << "Sunt egale";
	////else cout << "Nu sunt egale";
	////cout << "Testare operator ++ post:" << endl;
	////ca1 = ca2++;
	////ca2.afisare();
	////cout << "Testare operator ++ pre:" << endl;
	////ca1 = ++ca2;
	////ca2.afisare();
	////cout << "Testare operator >> si <<:" << endl;
	////cin >> ca1;
	////cout << ca1;
	////cout << endl << "Testare getteri si setteri:" << endl;
	////ca1.set_an_cheltuieala(2012);
	////cout << ca1.get_an_cheltuieala() << endl;
	////ca1.set_denumire("Impozit pe casa");
	////cout << ca1.get_denumire() << endl;
	////ca1.set_suma(140);
	////cout << ca1.get_suma() << endl;
	////ca1.set_achitat(true);
	////cout << ca1.get_achitat() << endl;

	////pentru clasa AlteCheltuieli

	//AlteCheltuieli ac2("Inchiere apartament", 1200, prioritate_medie);
	////ofstream fac("AlteCheltuieli.txt", ios::out);
	//////cout << ac2 << endl;
	////fac << ac2 << endl;
	////fac.close();

	/*cout << "Scriere in fisier text pentru clasa AlteCheltuieli:" << endl;
	AlteCheltuieli ac4;
	ifstream gac("AlteCheltuieli_citire.txt", ios::in);
	gac >> ac4;
	gac.close();*/

	//AlteCheltuieli ac4("Inchiriere teren", 100, prioritate_mica);
	////ofstream fc("AlteCheltuieli.bin", ios::binary | ios::out);
	////fc.write((char*)&ac4, sizeof(AlteCheltuieli));
	////fc.close();

	/*cout << "Scriere in fisier binar pentru clasa AlteCheltuieli:" << endl;
	ifstream gc("AlteCheltuieli_scriere.bin", ios::binary | ios::in);
	AlteCheltuieli ac5;
	gc.read((char*)&ac5, sizeof(AlteCheltuieli));
	gc.close();
*/
	//AlteCheltuieli ca1;
	//ca1.afisare();
	//cout << endl;
	//AlteCheltuieli ca2("Cumparare TV",540,prioritate_mica);
	//ca2.afisare();
	//cout << endl;
	//AlteCheltuieli ca3("Cumparare microunde",270,prioritate_medie);
	//cout << endl << "Testare operator !:" << endl;
	//ca2 = !ca1;
	//ca2.afisare();
	//cout << endl << "Testare operator +:" << endl;
	//AlteCheltuieli ca4 = ca3 + ca2;
	//ca4.afisare();
	//cout << endl << "Testare operator cast explicit:" << endl;
	//int m = (float)ca2;
	//cout << m<<endl;
	//cout << endl << "Testare operator -- post:" << endl;
	//ca2 = ca1--;
	//ca1.afisare();
	//cout << endl << "Testare operator -- pre:" << endl;
	//ca2 = --ca1;
	//ca1.afisare();
	//cout << endl << "Testare operator () fara parametru:" << endl;
	//ca3 = ca1();
	//ca1.afisare();
	//cout << endl << "Testare operator () cu parametru:" << endl;
	//ca2 = ca1(1000);
	//ca2.afisare();
	//cout << endl << "Testare operator >:" << endl;
	//if (ca2 > ca1) cout << "Aceeasi suma de plata!";

	//AlteCheltuieli ac;
	//ac.set_denumire("Cumparare DVD player");
	//cout << ac.get_denumire() << endl;
	//ac.set_luna(5);
	//cout << ac.get_luna() << endl;
	//ac.set_cheltuieli(prioritate_medie);
	//cout << ac.get_cheltuieli()<<endl;
	//*/
	//


	cout << endl << "STL" << endl;

	list<CheltuieliNecesare> Cheltuieli;
	Cheltuieli.push_back(CheltuieliNecesare("Alimente", 150, true));
	Cheltuieli.push_back(CheltuieliNecesare("Utilitati", 260, true));
	Cheltuieli.push_back(CheltuieliNecesare("Cablu TV", 240, false));
	Cheltuieli.sort(metodaComparareCheltuieliNecesare);
	for (list<CheltuieliNecesare>::iterator it = Cheltuieli.begin(); it != Cheltuieli.end(); it++)
	{
		cout << *it;
	}

	CheltuieliNecesare c = accumulate(Cheltuieli.begin(), Cheltuieli.end(), CheltuieliNecesare(), metodaAdunare);
	cout << "Cheltuielile: " << c << endl;
	vector<CheltuieliNecesare> v;
	v.push_back(CheltuieliNecesare("Utilitati", 100, true));
	v.push_back(CheltuieliNecesare("Reparatii", 150, true));

	sort(v.begin(), v.end());

	vector<CheltuieliNecesare>::iterator it;
	it = v.begin();
	while (it != v.end()) {
		cout << *it;
		it++;
	}

	list<CheltuieliNecesare> lista;
	lista.push_back(CheltuieliNecesare("Utililati", 10, true));
	lista.push_front(CheltuieliNecesare());
	lista.push_front(CheltuieliNecesare("Gaze", 120, false));
	lista.sort(metodaComparareCheltuieliNecesare);
	cout << endl;
	for (list<CheltuieliNecesare>::iterator i = lista.begin(); i != lista.end(); i++)
	{
		cout << *i << " ";
	}

	set<string> chelt;
	chelt.insert("CheltuieliAnuale");
	chelt.insert("Cheltuieli Ocazionale");
	chelt.insert("Alte Cheltuieli");
	chelt.insert("Cheltuieli Suplimentare");
     cout << endl << "Lista de cheltuieli:";
	for (set<string>::iterator it = chelt.begin(); it != chelt.end(); ++it) {
		cout << " " << *it;
	}

	map<int, CheltuieliNecesare> ch;
	ch.insert(pair<int, CheltuieliNecesare>(1, CheltuieliNecesare("Utilitati", 200, true)));
	ch.insert(pair<int, CheltuieliNecesare>(4, CheltuieliNecesare("Imbracaminte", 120, false)));
	ch.insert(pair<int, CheltuieliNecesare>(3, CheltuieliNecesare("Utilitati", 200, false)));
	ch.insert(pair<int, CheltuieliNecesare>(2, CheltuieliNecesare("Impozit", 350, true)));
	ch[6] = CheltuieliNecesare();
	map<int, CheltuieliNecesare>::iterator its = ch.begin();
	while (its != ch.end())
	{
		cout << "Cu codul: " << its->first << " si tipul" << its->second << endl;
		its++;
	}
}










