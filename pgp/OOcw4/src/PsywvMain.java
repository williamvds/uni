import java.util.ArrayList;
import java.util.EnumMap;
import java.util.Collections;
import java.util.Iterator;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JOptionPane;

class PsywvMain implements Iterable<ColorButton> {

  // 3 - Static options
  final static int WIDTH          = 4;
  final static int HEIGHT         = 4;
  final static int COLOURS        = 8;
  final static int MAX_PER_COLOUR = 2;
  final static int BUT_SIZE       = 135;

  final static Color[] cardColors = new Color[]{ Color.blue, Color.cyan, Color.green,
    Color.magenta, Color.orange, Color.pink, Color.red, Color.white, Color.yellow, Color.gray };

  // 11 - GUI element references
  private JFrame        frame   = new JFrame();
  private JLabel        p1Label = new JLabel();
  private JLabel        p2Label = new JLabel();
  private JPanel        grid    = new JPanel();
  private ColorButton[] cards   = new ColorButton[WIDTH*HEIGHT];

  // 13 - Game state variables
  private int activePlayer = 0;
  private int[] scores = new int[]{0,0};
  private ColorButton firstCard;
  private ColorButton sndCard;

  public static enum TurnState { FIRST, SECOND, MATCH, NOMATCH };
  TurnState turnState = TurnState.FIRST;

  static EnumMap<TurnState, String> hints = new EnumMap<TurnState, String>( TurnState.class ); {
    hints.put( TurnState.FIRST,   "Choose your first square" );
    hints.put( TurnState.SECOND,  "Choose your second square" );
    hints.put( TurnState.MATCH,   "Match! Click a square to continue..." );
    hints.put( TurnState.NOMATCH, "No match, click a square to end your turn" );
  }

  public PsywvMain() {
    frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		frame.setTitle( "My Game" );
    frame.setLayout( new BorderLayout( 0, 5 ) );

    // 12
    frame.add( p1Label, BorderLayout.NORTH );
    p1Label.setOpaque( true );
    p1Label.setForeground( Color.black );

    frame.add( p2Label, BorderLayout.SOUTH );
    p2Label.setOpaque( true );
    p2Label.setForeground( Color.black );

    // 17
    frame.add( grid, BorderLayout.CENTER );
    grid.setLayout( new GridLayout( WIDTH, HEIGHT ) );
    for ( int i = 0; i < cards.length; i++ ) {
      ColorButton b = new ColorButton( i, this, BUT_SIZE, BUT_SIZE );
      grid.add( b );
      cards[i] = b;
    }

    // 18, 19, 20
    setupGame();

    frame.pack();
    frame.setVisible( true );
  }

  // 4
  public void buttonClicked( int id ) {
    ColorButton b = cards[ id ];

    // Mark cards as done / Reflip cards and move to other player / ignore invalid cards
    if ( turnState == TurnState.MATCH || turnState == TurnState.NOMATCH ) {
      if ( turnState == TurnState.MATCH ) {
        // 24
        firstCard.setState( ColorButton.State.DONE );
        sndCard.setState( ColorButton.State.DONE );
        scores[ activePlayer ] += 2;

      } else {
        // 26
        firstCard.flip( false );
        sndCard.flip( false );
        activePlayer = activePlayer == 0? 1 : 0;
      }

      // Determine if game is over
      if ( scores[0] +scores[1] == cards.length ) {
        // 27
        JOptionPane.showMessageDialog( frame,
          scores[0] == scores[1]? "Both players draw"
          : String.format( "Player %d wins! Congratulations!", scores[0] > scores[1]? 1 : 2 )
        );

        setupGame(); // 28
        return;
      }

      firstCard = null;
      turnState = TurnState.FIRST; // 26
      updateLabels();

      return;

    } else if ( b.state != ColorButton.State.HIDDEN ) { // 22
      return;
    }

    b.flip( true ); // 21, 22

    // Save selected cards / decide success/failure
    switch ( turnState ) {
      case FIRST:
        firstCard = b;
        turnState = TurnState.SECOND;
        break;

      case SECOND: // 22
        sndCard = b;
        // 23 - turnState determines what message should be shown
        turnState = b.color == firstCard.color? TurnState.MATCH : TurnState.NOMATCH;
    }

    // Update hints for next round
    updateLabels();
  }

  // 14
  private void updateLabels() {
    for ( int i= 0; i < 2; i++ ) {
      JLabel lbl = i == 0? p1Label : p2Label;

      lbl.setBackground( activePlayer == i? Color.green : Color.red );
      lbl.setText( String.format( "%sPlayer %d    Score: %d - %s",
        activePlayer == i? "*** " : "", i +1, scores[i], // Asterisks, player #, player score
        activePlayer == i? hints.get( turnState ) // Hint or 'Please wait' message
          : String.format( "Player %d's turn. Please wait.", activePlayer +1 )
      ) );
    }

  }

  private void setupGame() {
    activePlayer = 0;
    scores[0] = scores[1] = 0;
    turnState = TurnState.FIRST;
    firstCard = sndCard = null;

    // 18, 19, 20
    ArrayList<Color> cols = new ArrayList<Color>();
    for ( int i= 0; i < COLOURS; i++ ) {
      for ( int n= 0; n < MAX_PER_COLOUR; n++ ) {
        cols.add( cardColors[i] );
      }

    }
    Collections.shuffle( cols );

    // 17
    int i = 0;
    for ( ColorButton c : this ) { // 30
      c.setColor( cols.get(i++) );
      c.setState( ColorButton.State.HIDDEN );
    }

    updateLabels();
  }

  // 29
  @Override
  public Iterator<ColorButton> iterator() {
    return new Iterator<ColorButton>() {
      private int index = 0;

      @Override
      public boolean hasNext() {
        return index < cards.length;
      }

      @Override
      public ColorButton next() {
        return cards[ index++ ];
      }
    };
  }

  // 2
  public static void main( String args[] ) {
    new PsywvMain();
  }
}
