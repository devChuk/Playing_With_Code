import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;
import javax.swing.*;

public class Client {

    BufferedReader input;
    PrintWriter output;
    JFrame frame = new JFrame("Java Chatbox");
    JTextField message = new JTextField(40);
    JTextArea conversation = new JTextArea(8, 40);
 
    public Client() {

        conversation.setEditable(false);
        message.setEditable(false);
        frame.getContentPane().add(message, "South");
        frame.getContentPane().add(new JScrollPane(conversation), "Center");
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);


        message.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                output.println(message.getText());
                message.setText("");
            }
        });
    }

    private String getUsername() {
        return JOptionPane.showInputDialog(
            frame,
            "Choose a username:",
            "username selection",
            JOptionPane.PLAIN_MESSAGE);
    }

    private void run() throws IOException {

        // Initialize connection and make streams
        Socket socket = new Socket("127.0.0.1", 5190);
        input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        output = new PrintWriter(socket.getOutputStream(), true);

        // Process messages from server, depending on the word in front.
        while (true) {
            String servermessage = input.readLine();
            if (servermessage.startsWith("nameisinserted")) {
                output.println(getUsername());
            } else if (servermessage.startsWith("nameisaccepted")) {
                message.setEditable(true);
            } else if (servermessage.startsWith("messageissent")) {
                conversation.append(servermessage.substring(14) + "\n");
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Client client = new Client();
        client.run();
    }
}