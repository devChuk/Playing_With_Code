import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class buttons {

	static JFrame jf;
	static JPanel jp;
	static ArrayList<JButton> buttonList;
	static Random rand;

	public static void main(String[] args) {
		jf = new JFrame("Twelve Buttons");
        jf.setSize(220, 100);
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.setResizable(false);
        jp = new JPanel();
		jf.add(jp);

		rand = new Random();
		buttonList = new ArrayList<JButton>();

        for (int i = 0; i < 12; i++) {
        	buttonList.add(new JButton("  "));

			Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
			buttonList.get(i).setBackground(randomColor);
			buttonList.get(i).addActionListener(new ButtonPress());
        	jp.add(buttonList.get(i));
        }

		jf.setVisible(true);
	}

    static class ButtonPress implements ActionListener{
        public void actionPerformed(ActionEvent ae){
        	for (int i = 0; i < buttonList.size(); i++) {
        		if (ae.getSource() != buttonList.get(i)) {
					Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
					buttonList.get(i).setBackground(randomColor);
        		}
        	}
        }    
    }
}
