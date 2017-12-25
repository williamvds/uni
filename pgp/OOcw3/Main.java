import java.util.Random;
import java.util.ArrayList;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JPanel;

public class Main implements ActionListener { // 2

  // 3
  private JFrame guiFrame = new JFrame();
  private java.util.Random rand = new java.util.Random();
  public ArrayList<ColorLabel> arrayLabels = new ArrayList<ColorLabel>();

	public static void main( String[] args ) { 
		new Main().createGUI();
	}

  public void createGUI() { // 4
    guiFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE ); 
		guiFrame.setTitle( "Label demo" );
    guiFrame.setLayout( new BorderLayout( 0, 5 ) );

    JPanel pnl = new JPanel();
    pnl.setLayout( new GridLayout( 8, 8 ) );
    guiFrame.add( pnl, BorderLayout.CENTER );

    for ( int i = 0; i < 64; i++ ) {
      ColorLabel lbl = new ColorLabel( 50, 50, 
        new Color( rand.nextInt( 256 ), rand.nextInt( 256 ), rand.nextInt( 256 ) )
      );
      pnl.add( lbl );
      arrayLabels.add( lbl );
    }

    JButton but = new JButton( "Press me to refresh labels" );
    but.addActionListener( this );
    guiFrame.add( but, BorderLayout.SOUTH );

    guiFrame.pack();
    guiFrame.setVisible( true );
  }

  public void actionPerformed( ActionEvent e ) {
    for ( ColorLabel lbl : arrayLabels ) {
      lbl.drawColor = new Color( rand.nextInt( 256 ), rand.nextInt( 256 ), rand.nextInt( 256 ) );
    }

    guiFrame.repaint();
  }
}
