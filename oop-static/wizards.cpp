#include<iostream>
using namespace std;

void handleChars(char*& destination, const char* source) {
	destination = new char[strlen(source) - 1];
	strcpy(destination, source);
}

void handleFloats(float*& destination, const float* source) {
	//TODO
}

template<class T>
int ArraySize(T& arr) {
	return sizeof(arr) / sizeof(*arr);
}

class Spell {
private:
	char* name;
	int power;
public:
	Spell(const char* _name, int _power) {
		handleChars(name, _name);
		if (_power < 1 || _power > 10)
			throw exception("Power must be between 1 and 10");
		power = _power;
	}
	~Spell() {
		//delete[] name;
	}
	Spell(Spell& s) {
		handleChars(name, s.name);
		power = s.power;
	}

	char* getName() {
		return name;
	}
	void setName(char* _name) {
		//delete[] name;
		handleChars(name, _name);
	}
	int getPower() {
		return power;
	}
	void setPower(int _power) {
		if (_power < 1 || _power > 10)
			throw exception("Power must be between 1 and 10");
		power = _power;
	}
};

ostream& operator<< (ostream& os, Spell& s) {
	os << "===Spell===" << endl
		<< "Name: " << s.getName() << endl
		<< "Power: " << s.getPower() << endl;
	return os;
}

class Wizard {
private:
	char* name;
	Spell** spells;
	int noSpells;
	static int wizardsAllAroundTheWorld;
public:
	Wizard(const char* _name, Spell** _spells, int _noSpells) {
		handleChars(name, _name);
		noSpells = _noSpells;
		spells = new Spell*[sizeof(_spells)];
		for (int i = 0; i < noSpells; i++) {
			spells[i] = new Spell(*_spells[i]); //deep copy
		}
		Wizard::wizardsAllAroundTheWorld++;
	}
	Wizard(Wizard &wiz) {
		handleChars(name, wiz.name);
		noSpells = wiz.noSpells;
		spells = new Spell*[sizeof(wiz.spells)];
		for (int i = 0; i < noSpells; i++) {
			spells[i] = new Spell(*wiz.spells[i]);
		}
		Wizard::wizardsAllAroundTheWorld++;
	}
	~Wizard() {
		for (int i = 0; i < noSpells; i++) {
			delete spells[i];
		}
		delete[]spells;
		//delete[]name;
		Wizard::wizardsAllAroundTheWorld--;
	}
	char* getName() {
		return name;
	}
	void setName(const char* _name) {
		//delete[] name;
		handleChars(name, _name);
	}
	int getNoSpells() {
		return noSpells;
	}
	Spell** getSpells() {
		return spells;
	}
	void setSpells(Spell** _spells, int _noSpells) { 
		delete[]spells;
		noSpells = _noSpells;
		for (int i = 0; i < _noSpells; i++) {
			spells[i] = new Spell(*_spells[i]);
		}
	}
	static int getWizardsAllAroundTheWorld() {
		return wizardsAllAroundTheWorld;
	}
};

int Wizard::wizardsAllAroundTheWorld = 0;

ostream& operator<< (ostream& os, Wizard& w) {
	os << "===Wizard===" << endl
		<< "Name: " << w.getName() << endl
		<< "#Spells: " << w.getNoSpells() << endl;
	for (int i = 0; i < w.getNoSpells(); i++) {
		Spell** spells = w.getSpells();
		os << *(spells)[i];
	}
	os << endl;

	return os;
}


int main() {
	Spell* hpSpells[] = {
		new Spell("Abracadabra!", 10),
		new Spell("Hocus Pocus!", 5),
		new Spell("Preparatus!", 7)
	};

	Spell* nostraSpells[] = {
		new Spell("Humanity shall reach the moon by 1969.", 6),
		new Spell("Humanity shall stagnate thereafter.", 8),
	};

	Wizard* wizards[] = {
		new Wizard("Harry Potter", hpSpells, ArraySize<>(hpSpells)),
		new Wizard("Nostradamus", nostraSpells, ArraySize<>(nostraSpells))
	};

	cout << "Wizards all arount the world: " << Wizard::getWizardsAllAroundTheWorld() << endl;
	Wizard* wizClone = new Wizard(*wizards[0]); cout << "Wizard summoned." << endl;
	cout << "Wizards all arount the world: " << Wizard::getWizardsAllAroundTheWorld() << endl << endl;

	for (int i = 0; i < ArraySize<>(wizards); i++) {
		cout << *wizards[i];
	}

	for (int i = 0; i < ArraySize<>(wizards); i++) {
		delete wizards[i];
	}
	delete wizClone;
	

	try {
		Spell* deplorableSpell = new Spell("Space-Time shall blow into pieces.", -1); //will throw exception
		delete deplorableSpell;
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	cout << "Press any key to continue...";
	cin.get();
}