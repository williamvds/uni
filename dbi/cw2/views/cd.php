<?php require 'views/header.php'; ?>
    <h1><?php echo PAGE_TITLE; ?></h1>
    <a href="/albums/add" class="button">Add an album</a>
    <form id="search" method="post" action="/albums/search">
      <label>Search
        <input id="name" name="Title" placeholder="Album title">
      </label>
    </form>
<?php
  global $res;

  if ( count( $res ) < 1 ) {
    echo '<p>No albums found</p>';
    return;
  }

  // Headings
  echo "<table><thead><tr>";
  foreach ( ['ID', 'Title' => '20%', 'Artist', 'Genre', 'Price', 'Tracks', ''] as $key => $val ) {
    if ( is_numeric( $key ) ) {
      echo "<th>$val</th>";
      continue;
    }

    echo "<th width=\"$val\">$key</th>";
  }
  echo "</tr></thead><tbody>";

  // Rows
  foreach ( $res as $cd ) {
    $id = $cd['ID'];

    echo "<tr>\n";
    foreach ( ['ID', 'Title', 'ArtistName', 'Genre', 'Price', 'Tracks'] as $f ) {
      $val = $cd[$f];
      echo "<td>$val</td>\n";
    }
    echo "<td>
      <a href=\"/albums/$id\">Tracks</a>
      <a href=\"/albums/edit/$id\">Edit</a>
      <a href=\"/albums/delete/$id\">Delete</a>
    </td>";
    echo "</tr>";
  }

  echo "</tbody></table>";
?>
<?php require 'views/footer.php'; ?>
