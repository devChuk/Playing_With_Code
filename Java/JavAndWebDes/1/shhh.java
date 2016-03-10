import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class shhh {
  static String addLine(String line, int[] key) {
    String tempLine = "";
    for (int i = 0; i < line.length(); ++i) {
      char letter;
      char outputLetter = letter = line.charAt(i);
      if (letter >= 'a' && letter <= 'z') {
        outputLetter = (char)((letter - 97 + key[i]) % 26 + 97);
      } else if (letter >= 'A' && letter <= 'Z') {
        outputLetter = (char)((letter - 65 + key[i]) % 26 + 65);
      }
      tempLine = tempLine + outputLetter;
    }
    return tempLine;
  }

  static String subtractLine(String line, int[] key) {
    String tempLine = "";
    for (int i = 0; i < line.length(); ++i) {
      char letter;
      char outputLetter = letter = line.charAt(i);
      if (letter >= 'a' && letter <= 'z') {
        outputLetter = (char)((letter - 97 - key[i] + 26) % 26 + 97);
      } else if (letter >= 'A' && letter <= 'Z') {
        outputLetter = (char)((letter - 65 - key[i] + 26) % 26 + 65);
      }
      tempLine = tempLine + outputLetter;
    }
    return tempLine;
  }

  static int[] convertKey(String Key, int length) {
    int[] result = new int[length];
    int keyPos = 0;
    int i = 0;
    while (i < length) {
      char letter;
      if (keyPos >= Key.length()) {
        keyPos = 0;
      }
      if ((letter = Key.charAt(keyPos)) >= 'a' && letter <= 'z') {
        result[i] = letter - 97;
      } else if (letter >= 'A' && letter <= 'Z') {
        result[i] = letter - 65;
      }
      ++i;
      ++keyPos;
    }
    return result;
  }

  static void encrypt(String key, String inputFileName, String outputFileName) throws IOException {
    Scanner inFile = new Scanner(new File(inputFileName));
    PrintStream outFile = new PrintStream(outputFileName);
    while (inFile.hasNext()) {
      String line = inFile.nextLine();
      int[] tempKey = shhh.convertKey(key, line.length());
      outFile.println(shhh.addLine(line, tempKey));
    }
  }

  static void decrypt(String key, String inputFileName, String outputFileName) throws IOException {
    Scanner inFile = new Scanner(new File(inputFileName));
    PrintStream outFile = new PrintStream(outputFileName);
    while (inFile.hasNext()) {
      String line = inFile.nextLine();
      int[] tempKey = shhh.convertKey(key, line.length());
      outFile.println(shhh.subtractLine(line, tempKey));
    }
  }

  public static void main(String[] args) throws IOException {
    int action;
    Scanner sin = new Scanner(System.in);
    System.out.println("Welcome to the encryption problem!");
    do {
      System.out.println("What would you like to do? ");
      System.out.println("1 - Encrypt a file");
      System.out.println("2 - Decrypt a file");
      System.out.println("0 - Exit");
      System.out.print("Your choice: ");
      action = sin.nextInt();
      if (action != 1 && action != 2) continue;
      System.out.print("Enter your key: ");
      sin.nextLine();
      String key = sin.nextLine();
      System.out.print("Enter your input filename: ");
      String inputFileName = sin.nextLine();
      while (!new File(inputFileName).canRead()) {
        System.out.println("Bad filename");
        System.out.print("Enter your input filename: ");
        inputFileName = sin.nextLine();
      }
      System.out.print("Enter your output filename: ");
      String outputFileName = sin.nextLine();
      if (action == 1) {
        shhh.encrypt(key, inputFileName, outputFileName);
        continue;
      }
      shhh.decrypt(key, inputFileName, outputFileName);
    } while (action != 0);
  }
}