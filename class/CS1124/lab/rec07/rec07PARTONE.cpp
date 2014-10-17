#include <iostream>
#include <vector>
#include <string>
        using namespace std;

class Instrument {
public:
  Instrument() {}
  virtual void makeSound() const = 0;
private:
};

class Brass : public Instrument {
public:
  Brass(int newSize) : Instrument(), size(newSize) {}
  virtual void makeSound() const {
    cout << "To make a sound... blow on a mouthpiece of size " << size << endl;
//"To make a sound... blow on a mouthpiece of size 9"
  }
private:
  int size;
};

class String : public Instrument {
public:
  String(unsigned newPitch) : Instrument(),  pitch(newPitch) {}
  virtual void makeSound() const {
    cout << "To make a sound... bow a string with pitch " << pitch << endl;
  }
private:
  unsigned pitch;
};

class Percussion : public Instrument {
public:
  Percussion() : Instrument() {}
  virtual void makeSound() const {
    cout << "To make a sound... hit me!" << endl;
  }
private:
};

class Drum : public Percussion {
public:
  Drum() : Percussion() {}
};

class Cello : public String {
public:
  Cello(unsigned pitch) : String(pitch) {}
};

class Cymbal : public Percussion {
public:
  Cymbal() : Percussion() {}
};

class Trombone : public Brass {
public:
  Trombone(int size) : Brass(size) {}
};

class Trumpet : public Brass {
public:
  Trumpet(int size) : Brass(size) {}  
};

class Violin : public String {
public:
  Violin(unsigned pitch) : String(pitch) {}
};

class Musician {
public:
	Musician() : instr( NULL ) {}
	void acceptInstr( Instrument & i ) { instr = &i; }
	Instrument* giveBackInstr( ) { 
		Instrument* tmp(instr); 
		instr = NULL;
		return tmp;
	}
	void testPlay() const {
		if( instr )
			instr->makeSound(); 
		else
			cerr << "have no instr\n";
	}
private:
	Instrument* instr;
};

class MILL {
public:
  MILL() {}
  void receiveInstr(Instrument& instrument) {
    instrument.makeSound();
    Instrument* pInstrument = &instrument;
    for (int i = 0; i < inventory.size(); i++) {
      if (inventory[i] == NULL) {
        inventory[i] = pInstrument;
        return;
      }
    }
    inventory.push_back(pInstrument);
  }
  Instrument* loanOut() {
    for (int i = 0; i < inventory.size(); i++) {
      if (inventory[i] != NULL) {
        Instrument* tempPtr = inventory[i];
        inventory[i] = NULL;
        return tempPtr;
      }
    }
    //tempPtr, set index to ull, return tempPtr
  }

  void dailyTestPlay() const {
    for (int i = 0; i < inventory.size(); i++) {
      if (inventory[i] != NULL) {
        inventory[i]->makeSound();
      }
    }
  }
private:
  vector<Instrument*> inventory;
};
// PART ONE
int main()
{

  cout << "Define some instruments ----------------------------------------\n";
  Drum drum;
  Cello cello(673);
  Cymbal cymbal;
  Trombone tbone( 4 );
  Trumpet trpt( 12 ) ;
  Violin violin( 567 ) ;
  
  // use the debugger to look at the mill
  cout << "Define the MILL ------------------------------------------------\n";
  MILL mill;
  
  cout << "Put the instruments into the MILL ------------------------------\n";
  mill.receiveInstr( trpt );
  mill.receiveInstr( violin );
  mill.receiveInstr( tbone );
  mill.receiveInstr( drum );
  mill.receiveInstr( cello );
  mill.receiveInstr( cymbal );
  
  cout << "Daily test -----------------------------------------------------\n";
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  cout << endl;
  
  cout << "Define some Musicians-------------------------------------------\n";
  Musician j;
  Musician jj;
  Musician q;
  	
  cout << "TESTING: q.acceptInstr( *mill.loanOut() );-----------------------\n";
  q.testPlay();	
  cout << endl;
  q.acceptInstr( *mill.loanOut() );
  cout << endl;
  q.testPlay();
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  
  cout << endl << endl;
  
  q.testPlay();	
  cout << endl;
  mill.receiveInstr( *q.giveBackInstr() );
  j.acceptInstr( *mill.loanOut() );
  q.acceptInstr( *mill.loanOut() );
  cout << endl;
  q.testPlay();
  cout << endl;
  j.testPlay();
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  
  cout << "TESTING: mill.receiveInstr( *q.giveBackInstr() ); -------------\n";
  
  // fifth
  mill.receiveInstr( *q.giveBackInstr() );
  cout << "TESTING: mill.receiveInstr( *j.giveBackInstr() ); -------------\n";
  mill.receiveInstr( *j.giveBackInstr() );

  
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  cout << endl;
  
  cout << endl;

}
