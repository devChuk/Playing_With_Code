import java.util.*;

public class HelloWorld
{

	public static int methodName(int a, int b) {
   		// body
	}

	public static void main(String[] args) {
		System.out.println("Hello World!");

		for(int x = 10; x < 20; x = x + 1) {
         System.out.print("value of x : " + x );
	    }

	    while (false) {

	    }

		do {
		    System.out.print("value of x : " + x );
		    x++;
		    System.out.print("\n");
		}while( x < 20 );

		break;

		for( String name : names ) {
	        System.out.print( name );
	        System.out.print(",");
	    }

	    int[] anArray;
	    anArray = new int[10];
	    // initialize first element
        anArray[0] = 100;
        // initialize second element
        anArray[1] = 200;

        ArrayList al = new ArrayList();
        al.add("C");
		al.add("A");
		al.add("E");
		al.add("B");
		al.add("D");
		al.add("F");
		al.add(1, "A2");
		al.size();
		//Contents of al: [C, A2, A, E, B, D, F]
		al.remove("F");
		al.remove(2);
		al.removeRange(2,9);
		al.clone();
		al.contains("F");
		al.get(2);
		al.indexOf("E");
		al.lastIndexOf("E");
		al.isEmpty();
		al.set(0,"B");

		int month = 8;
        String monthString;
        switch (month) {
            case 1:  monthString = "January";
                     break;
            case 2:  monthString = "February";
                     break;
            case 3:  monthString = "March";
                     break;
            case 4:  monthString = "April";
                     break;
            case 5:  monthString = "May";
                     break;
            case 6:  monthString = "June";
                     break;
            case 7:  monthString = "July";
                     break;
            case 8:  monthString = "August";
                     break;
            case 9:  monthString = "September";
                     break;
            case 10: monthString = "October";
                     break;
            case 11: monthString = "November";
                     break;
            case 12: monthString = "December";
                     break;
            default: monthString = "Invalid month";
                     break;
        }

        LinkedList bal = new LinkedList();






	}

}