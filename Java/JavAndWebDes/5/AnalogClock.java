import java.awt.*;
import java.util.Calendar;
import javax.swing.*;

public class AnalogClock {

    public static void main(String[] args) {
        JFrame jf = new JFrame("Analog Clock");
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.setSize(400,400);
        GraphicsPanel gp= new GraphicsPanel();
        new UpdatePanel(gp).start();
        jf.add(gp);
        jf.setVisible(true);
    }
    
}

class UpdatePanel extends Thread{
    GraphicsPanel jp;
    UpdatePanel(GraphicsPanel newjp){jp=newjp;}
    public void run(){
        try{
            while(true){
                jp.move();
                sleep(100);
            }
        } catch(Exception e){}
    }
}

class GraphicsPanel extends JPanel{
	int middleWidth;
	int middleHeight;

    void move(){
        repaint();
    }

    int getHandXPosition(int angle, int handDiameter) {
    	return (int) (middleWidth + (0.9*handDiameter/2)*(Math.sin(2*Math.PI*(angle/60.0))));
    }

    int getHandYPosition(int angle, int handDiameter) {
    	return (int) (middleHeight - (0.9*handDiameter/2)*(Math.cos(2*Math.PI*(angle/60.0))));
    }

    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        double height = getSize().getHeight();
        double width = getSize().getWidth();
        middleWidth=(int)width/2;
        middleHeight=(int)height/2;
        
        // DRAW DIGITAL TIME
        Calendar c = Calendar.getInstance();
        String time =""+c.get(Calendar.HOUR);
        time+=":"+c.get(Calendar.MINUTE)+":"+c.get(Calendar.SECOND);
        g.drawString(time, middleWidth-20, middleHeight-5);
        
        //DRAW SECOND HAND
        g.setColor(Color.RED);
		g.drawLine(middleWidth,middleHeight, getHandXPosition(c.get(Calendar.SECOND),150), getHandYPosition(c.get(Calendar.SECOND),150));
        g.drawLine(middleWidth,middleHeight, getHandXPosition(c.get(Calendar.SECOND),150), getHandYPosition(c.get(Calendar.SECOND),150));
        g.setColor(Color.BLACK);

        //DRAW MINUTE HAND
		g.drawLine(middleWidth,middleHeight, getHandXPosition(c.get(Calendar.MINUTE),200), getHandYPosition(c.get(Calendar.MINUTE),200));
        g.drawLine(middleWidth,middleHeight, getHandXPosition(c.get(Calendar.MINUTE),200), getHandYPosition(c.get(Calendar.MINUTE),200));

		//DRAW HOUR HAND
		g.drawLine(middleWidth,middleHeight, getHandXPosition(c.get(Calendar.HOUR)*5,140), getHandYPosition(c.get(Calendar.HOUR)*5,140));
        g.drawLine(middleWidth,middleHeight, getHandXPosition(c.get(Calendar.HOUR)*5,140), getHandYPosition(c.get(Calendar.HOUR)*5,140));
    }    
}
