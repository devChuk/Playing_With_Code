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
// PART TWO
int main()
{
  // The initialization phase

  Drum drum;
  Cello cello(673);
  Cymbal cymbal;
  Trombone tbone( 4 );
  Trumpet trpt( 12 ) ;
  Violin violin( 567 ) ;

  MILL mill;
  mill.receiveInstr( trpt );
  mill.receiveInstr( violin );
  mill.receiveInstr( tbone );
  mill.receiveInstr( drum );
  mill.receiveInstr( cello );
  mill.receiveInstr( cymbal );

  Musician bob;
  Musician sue;
  Musician mary;
  Musician ralph;
  Musician jody;
  Musician morgan;

  // Orch orch;



  // // THE SCENARIO

  // //Bob joins the orchestra without an instrument.
  // orch.addPlayer(bob);

  // //The orchestra performs
  // cout << "orch performs\n";
  // orch.play();

  // //Sue gets an instrument from the MIL2 and joins the orchestra.
  // sue.acceptInstr( *mill.loanOut() );
  // orch.addPlayer(sue);

  // //Ralph gets an instrument from the MIL2.
  // ralph.acceptInstr( *mill.loanOut() );

  // //Mary gets an instrument from the MIL2 and joins the orchestra.
  // mary.acceptInstr( *mill.loanOut() );
  // orch.addPlayer(mary);

  // //Ralph returns his instrument to the MIL2.
  // mill.receiveInstr( *ralph.giveBackInstr() );

  // //Jody gets an instrument from the MIL2 and joins the orchestra.
  // jody.acceptInstr( *mill.loanOut() );
  // orch.addPlayer(jody);

  // // morgan gets an instrument from the MIL2
  // morgan.acceptInstr( *mill.loanOut() );

  // //The orchestra performs.
  // cout << "orch performs\n";
  // orch.play();

  // //Ralph joins the orchestra.
  // orch.addPlayer(ralph);

  // //The orchestra performs.
  // cout << "orch performs\n";
  // orch.play();
  
  // // bob gets an instrument from the MIL2
  // bob.acceptInstr( *mill.loanOut() );

  // // ralph gets an instrument from the MIL2
  // ralph.acceptInstr( *mill.loanOut() );

  // //The orchestra performs.
  // cout << "orch performs\n";
  // orch.play();

  // //Morgan joins the orchestra.
  // orch.addPlayer(morgan);

  // //The orchestra performs.
  // cout << "orch performs\n";
  // orch.play();

} // main