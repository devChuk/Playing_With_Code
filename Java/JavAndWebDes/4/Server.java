import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashSet;


public class Server {

    static HashSet<String> userNames = new HashSet<String>();
    static HashSet<PrintWriter> writers = new HashSet<PrintWriter>();
    static final int PORT = 5190;

    private static class serverHandler extends Thread {
        private String userName;
        private Socket serverSocket;
        private BufferedReader readInput;
        private PrintWriter printOutput;

        public serverHandler(Socket serverSocket) {
            this.serverSocket = serverSocket;
        }

        public void run() {
            try {
                readInput = new BufferedReader(new InputStreamReader(
                    serverSocket.getInputStream()));
                printOutput = new PrintWriter(serverSocket.getOutputStream(), true);

                while (true) {
                    printOutput.println("nameisinserted");
                    userName = readInput.readLine();
                    if (userName == null) {
                        return;
                    }
                    synchronized (userNames) {
                        if (!userNames.contains(userName)) {
                            userNames.add(userName);
                            break;
                        }
                    }
                }

                printOutput.println("nameisaccepted");
                writers.add(printOutput);

                while (true) {
                    String input = readInput.readLine();
                    if (input == null) {
                        return;
                    }
                    for (PrintWriter writer : writers) {
                        writer.println("messageissent " + userName + ": " + input);
                    }
                }
            } catch (IOException e) {
                System.out.println(e);
            } finally {
                // Remove client when its down
                if (userName != null) {
                    userNames.remove(userName);
                }
                if (printOutput != null) {
                    writers.remove(printOutput);
                }
                try {
                    serverSocket.close();
                } catch (IOException e) {
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        System.out.println("Chat server is running");
        ServerSocket serverSocket = new ServerSocket(PORT);
        try {
            while (true) {
                new serverHandler(serverSocket.accept()).start();
            }
        } finally {
            serverSocket.close();
        }
    }
}