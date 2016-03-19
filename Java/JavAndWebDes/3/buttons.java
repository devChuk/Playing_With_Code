import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.Timer;



public class buttons {

	static JFrame jf;
	static JPanel jp;
	static ArrayList<JButton> buttonList;
	static ArrayList<JButton> pausedList;
	static Random rand;

	public static void main(String[] args) {
		jf = new JFrame("Twelve Buttons");
        jf.setSize(600, 450);
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.setResizable(false);
        jp = new JPanel();
        jp.setLayout(new GridLayout(3,4));
		jf.add(jp);

		rand = new Random();
		buttonList = new ArrayList<JButton>();
		pausedList = new ArrayList<JButton>();


        for (int i = 0; i < 12; i++) {
        	buttonList.add(new JButton());

			Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
			buttonList.get(i).setBackground(randomColor);
			buttonList.get(i).addActionListener(new ButtonPress());
        	jp.add(buttonList.get(i));
        }

		jf.setVisible(true);

		ActionListener timerListener = new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				for (int i = 0; i < buttonList.size(); i++) {
					if (!pausedList.contains(buttonList.get(i))) {
						Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
						buttonList.get(i).setBackground(randomColor);
					}
	        	}
			}
		};

		Timer timer = new Timer(1000, timerListener);

		timer.start();
	}

    static class ButtonPress implements ActionListener{
        public void actionPerformed(ActionEvent ae) {
        	if (pausedList.contains(ae.getSource())) {
        		pausedList.remove(ae.getSource());
        	} else {
        		pausedList.add((JButton)ae.getSource());
        	}
        }
    }
}
