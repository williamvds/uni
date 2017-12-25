import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.JLabel;

public class ColorLabel extends JLabel
{
	Color drawColor; 
	Color borderColor;
	int borderSize;
	 
	public ColorLabel( 
		int width, int height, 
		Color color, int borderWidth,
		Color borderCol )
	{
		borderSize = borderWidth;
		drawColor = color;
		borderColor = borderCol;
		setMinimumSize( 
			new Dimension(width, height) );
		setPreferredSize( 
			new Dimension(width, height) );
	}
	
	public ColorLabel( int width, int height, Color color )
	{
		// Call the other constructor
		this( width, height, color, 0, null );
	}

	protected void paintComponent(Graphics g)
	{
		//super.paintComponent(arg0);
		if ( borderColor != null )
		{
			g.setColor(borderColor);
			g.fillRect(0, 0, getWidth(), getHeight());
		}
		if ( drawColor != null )
		{
			g.setColor(drawColor);
			g.fillRect( borderSize, borderSize,
				getWidth()-borderSize*2,
				getHeight()-borderSize*2 );
		}
	}

	public static void main(String[] args)
	{
		// TODO Auto-generated method stub

	}

}
