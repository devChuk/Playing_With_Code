import java.util.Scanner;
import java.io.File;
import java.io.PrintStream;
import java.io.IOException;

public class CaesarCipher {

	public static void encrypt(String key, String inputFilename, String outputFilename) throws IOException {
		System.out.println("encrypting");
		Scanner inputFile = new Scanner(new File(inputFilename));
		PrintStream outputFile = new PrintStream(outputFilename);
		while (inputFile.hasNext()) {
			String line = inputFile.nextLine();
			int[] lineKey = getTempKey(key, line.length());
			outputFile.println(shiftRight(line, lineKey));
		}
	}

	public static void decrypt(String key, String inputFilename, String outputFilename) throws IOException {
		System.out.println("decrypting");
		Scanner inputFile = new Scanner(new File(inputFilename));
		PrintStream outputFile = new PrintStream(outputFilename);
		while (inputFile.hasNext()) {
			String line = inputFile.nextLine();
			int[] lineKey = getTempKey(key, line.length());
			outputFile.println(shiftLeft(line, lineKey));
		}
	}
	
	static int[] getTempKey(String key, int length) {
        int[] ans = new int[length];
        int index = 0, i = 0;
        while (i < length) {
            if (index >= key.length()) {
                index = 0;
            }
            char letter= key.charAt(index);
            if (letter >= 'A' && letter <= 'Z') {
                ans[i] = letter - 65;
            } else if (letter >= 'a' && letter <= 'z') {
                ans[i] = letter - 97;
            }
            i++;
            index++;
        }
        return ans;
    }

    public static String shiftRight(String line, int[] key) {
        String tempLine = "";
        for (int i = 0; i < line.length(); ++i) {
            char letter, resultLetter;
            resultLetter = letter = line.charAt(i);

            if (letter >= 'A' && letter <= 'Z') {
                resultLetter = (char)((letter - 65 + key[i]) % 26 + 65);
            } else if (letter >= 'a' && letter <= 'z') {
                resultLetter = (char)((letter - 97 + key[i]) % 26 + 97);
            }
            tempLine = tempLine + resultLetter;
        }
        return tempLine;
    }

    public static String shiftLeft(String line, int[] key) {
        String tempLine = "";
        for (int i = 0; i < line.length(); ++i) {
            char letter, resultLetter;
            resultLetter = letter = line.charAt(i);

            if (letter >= 'A' && letter <= 'Z') {
                resultLetter = (char)((letter - 65 - key[i] + 26) % 26 + 65);
            } else if (letter >= 'a' && letter <= 'z') {
                resultLetter = (char)((letter - 97 - key[i] + 26) % 26 + 97);
            }
            tempLine = tempLine + resultLetter;
        }
        return tempLine;
    }

	public static void main(String[] args) throws IOException {
		int selection = 3;
		Scanner input = new Scanner(System.in);

		System.out.println("What would you like to do?");
		System.out.println("1 - Encrypt a file");
        System.out.println("2 - Decrypt a file");
        System.out.println("0 - Exit");
        System.out.print("Your choice: ");

        while (selection != 0) {
        	selection = input.nextInt();
        	if (selection == 1 || selection == 2) {
        		System.out.println("Enter your key: ");
        		input.nextLine();
        		String key = input.nextLine();
        		System.out.print("Enter your input filename: ");
        		String filename = input.nextLine();
        		while (!new File(filename).canRead()) {
        			System.out.println("Cannot find file, please try again");
        			System.out.print("Enter your input filename: ");
        			filename = input.nextLine();
        		}
        		System.out.print("Enter your output filename: ");
        		String outputFilename = input.nextLine();

        		switch (selection) {
        			case 1:
        				encrypt(key, filename, outputFilename);
        				break;
        			case 2:
        				decrypt(key, filename, outputFilename);
        				break;
        		}
        	}
        }
	}
}