import java.util.EnumMap;

import javax.swing.JButton;
import javax.swing.JFrame;

import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.BorderLayout;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

class ColorButton extends JButton implements ActionListener {
  final public static int border = 10;
  public static enum State { HIDDEN, SHOWN, DONE };

  State state = State.HIDDEN; // 6

  public int       id;
  public PsywvMain parent;
  public Color     color;

  static EnumMap<State, Color> bgColors = new EnumMap<State, Color>( State.class ); {
    bgColors.put( State.HIDDEN, Color.darkGray );
    bgColors.put( State.SHOWN,  Color.darkGray );
    bgColors.put( State.DONE,   Color.black );
  }

  // 5
  public ColorButton( int newID, PsywvMain newParent, int w, int h ) {
    id = newID;
    parent = newParent;

    Dimension d = new Dimension( w, h );
    setPreferredSize( d );
    setMinimumSize( d );
    addActionListener( this );
  }

  // 7
  public void flip( boolean flipped ) {
    state = flipped ? State.SHOWN : State.HIDDEN;
    repaint();
  }

  public void setState( State s ) {
    state = s;
    repaint();
  }

  // 8
  void setColor( Color col ) {
    color = col;
  }

  // 9
	protected void paintComponent( Graphics g )	{
    g.setColor( bgColors.get( state ) );
    g.fillRect( 0, 0, getWidth(), getHeight() );

    if ( state == State.SHOWN && color != null ) {
			g.setColor( color );
			g.fillRect( border, border,	getWidth() -border *2, getHeight() -border *2 );
		}
	}

  // 10
  @Override
  public void actionPerformed( ActionEvent e ) {
    parent.buttonClicked( id );
  }
}
