
#include <iostream>
using namespace std;


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


// PART ONE
int main()
{

  // cout << "Define some instruments ----------------------------------------\n";
  // Drum drum;
  // Cello cello(673);
  // Cymbal cymbal;
  // Trombone tbone( 4 );
  // Trumpet trpt( 12 ) ;
  // Violin violin( 567 ) ;
  
  // // use the debugger to look at the mill
  // cout << "Define the MILL ------------------------------------------------\n";
  // MILL mill;
  
  // cout << "Put the instruments into the MILL ------------------------------\n";
  // mill.receiveInstr( trpt );
  // mill.receiveInstr( violin );
  // mill.receiveInstr( tbone );
  // mill.receiveInstr( drum );
  // mill.receiveInstr( cello );
  // mill.receiveInstr( cymbal );
  
  // cout << "Daily test -----------------------------------------------------\n";
  // cout << endl;
  // cout << "dailyTestPlay()" << endl;
  // mill.dailyTestPlay();
  // cout << endl;
  
  // cout << "Define some Musicians-------------------------------------------\n";
  // Musician j;
  // Musician jj;
  // Musician q;
  	
  // cout << "TESTING: q.acceptInstr( *mill.loanOut() );-----------------------\n";
  // q.testPlay();	
  // cout << endl;
  // q.acceptInstr( *mill.loanOut() );
  // cout << endl;
  // q.testPlay();
  // cout << endl;
  // cout << "dailyTestPlay()" << endl;
  // mill.dailyTestPlay();
  
  // cout << endl << endl;
  
  // q.testPlay();	
  // cout << endl;
  // mill.receiveInstr( *q.giveBackInstr() );
  // j.acceptInstr( *mill.loanOut() );
  // q.acceptInstr( *mill.loanOut() );
  // cout << endl;
  // q.testPlay();
  // cout << endl;
  // j.testPlay();
  // cout << endl;
  // cout << "dailyTestPlay()" << endl;
  // mill.dailyTestPlay();
  
  // cout << "TESTING: mill.receiveInstr( *q.giveBackInstr() ); -------------\n";
  
  // // fifth
  // mill.receiveInstr( *q.giveBackInstr() );
  // cout << "TESTING: mill.receiveInstr( *j.giveBackInstr() ); -------------\n";
  // mill.receiveInstr( *j.giveBackInstr() );

  
  // cout << endl;
  // cout << "dailyTestPlay()" << endl;
  // mill.dailyTestPlay();
  // cout << endl;
  
  // cout << endl;

}

