import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class GUIHelloWorld  { // Just the one class
	public static void main(String[] args)  { // Same main function as before static
		JFrame frame = new JFrame();
		frame.setLayout(new BorderLayout(2,2));
		frame.add( new ColorLabel( 20, 20, Color.RED, 2, Color.GRAY ),
				BorderLayout.NORTH );

		JPanel panel1 = new JPanel();
		panel1.setLayout(new BorderLayout(2,2)); // 2 pixel gaps

		frame.add(panel1, BorderLayout.CENTER);

		JPanel panel2 = new JPanel();
		JPanel panel3 = new JPanel();

		frame.add( new ColorLabel( 20, 20, Color.BLUE, 2, Color.GRAY ),
		BorderLayout.EAST );
		frame.add( new ColorLabel( 20, 20, Color.GREEN, 2, Color.GRAY ),
		BorderLayout.SOUTH );
		frame.add( new ColorLabel( 20, 20, Color.BLUE, 2, Color.GRAY ),
		BorderLayout.WEST );

		panel1.add(panel2, BorderLayout.NORTH);
		panel1.add(panel3, BorderLayout.CENTER);

		panel2.setLayout(new FlowLayout()); // Let them appear 1 at a time
		panel3.setLayout(new FlowLayout()); // 5x5 grid
//		panel3.setLayout(new GridLayout(5,5)); // 5x5 grid
//
//
//
//

		panel2.add(new ColorLabel(100,100, Color.YELLOW, 2,Color.BLACK ));
		panel2.add( new ColorLabel(200,100, Color.PINK, 2,Color.BLACK ));
		panel2.add( new ColorLabel(100,100, Color.YELLOW, 2,Color.BLACK));
//
		// Add 25 panels
		for ( int i = 0 ; i < 12 ; i++ )
		{
			panel3.add( new ColorLabel( 100, 100, Color.BLUE ) );
			panel3.add( new ColorLabel( 100, 100, Color.BLACK ) );
		}
		panel3.add( new ColorLabel( 100, 100, Color.BLUE ) );

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("My GUI demo");
		frame.pack();
		frame.setVisible(true);
	}
}
