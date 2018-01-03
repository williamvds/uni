-- Lab 4
SELECT * FROM Artist; 
SELECT artName FROM Artist; 
SELECT cdGenre as genre FROM CD; 
SELECT cdTitle, cdPrice FROM CD; 
SELECT DISTINCT artID, cdGenre FROM CD;

SELECT * FROM CD WHERE cdGenre = "Electronica"; 
SELECT cdTitle from CD WHERE cdPrice < 10;
SELECT * FROM CD WHERE cdGenre = "Pop" OR cdPrice > 10;
SELECT cdTitle FROM CD WHERE cdGenre = "Rock" AND cdPrice > 10 AND cdPrice < 12;
SELECT cdTitle FROM CD WHERE cdPrice < 10 AND cdGenre IN ("Rock",  "Electronica");
SELECT * FROM ARTIST NATURAL JOIN CD;
SELECT cdTitle FROM CD NATURAL JOIN Artist WHERE artName = "Muse";
SELECT * FROM CD WHERE cdGenre = ( SELECT cdGenre FROM CD WHERE cdTitle = "The Resistance" );
SELECT cdTitle FROM CD WHERE cdPrice IN ( SELECT cdPrice FROM CD WHERE cdGenre = "Pop" );
SELECT cdTitle FROM CD WHERE cdPrice > ANY( SELECT cdPrice FROM CD );
SELECT cdTitle FROM CD WHERE cdPrice >= ALL( SELECT cdPrice FROM CD );
SELECT * FROM Artist WHERE EXISTS ( SELECT cdID FROM CD WHERE cdGenre = "Electronica" AND artID = Artist.artID );
SELECT artName FROM Artist WHERE EXISTS ( SELECT cdID FROM CD WHERE artID = Artist.artID AND cdPrice < 10 );
SELECT cdTitle FROM CD WHERE artID IN ( SELECT artID FROM Artist WHERE artName NOT LIKE "% %" );
SELECT * FROM CD WHERE cdGenre IN ("Rock", "Pop") AND cdPrice < ANY( SELECT cdPrice FROM CD WHERE cdGenre IN ("Rock", "Pop") );

-- Lab 5
SELECT cdTitle, cdPrice FROM CD ORDER BY cdPrice DESC;
SELECT cdTitle, cdPrice FROM CD ORDER BY cdPrice ASC;
SELECT cdTitle, cdPrice, cdGenre FROM CD ORDER BY cdGenre ASC, cdPrice DESC;
SELECT MIN( cdPrice ) FROM CD;
SELECT COUNT( * ) FROM CD WHERE cdPrice = 11.99;
SELECT cdTitle FROM CD WHERE cdGenre = 'Rock' AND cdPrice = ( SELECT MAX( cdPrice ) FROM CD WHERE cdGenre = 'Rock' );
SELECT COUNT( DISTINCT cdGenre ) FROM CD;
SELECT * FROM CD WHERE cdPrice = ( SELECT MIN( cdPrice ) FROM CD );
SELECT artName, COUNT( * ) AS Count, AVG( cdPrice ) FROM CD NATURAL JOIN Artist GROUP BY artID HAVING Count > 1;
SELECT artName, COUNT( * ) AS Count, AVG( cdPrice ) FROM CD NATURAL JOIN Artist WHERE cdGenre <> 'Electronica' GROUP BY artID;
