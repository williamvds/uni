<?php require 'views/header.php'; ?>
    <h1><?php echo PAGE_TITLE; ?></h1>
    <a href="/tracks/add" class="button">Add a track</a>
    <form id="search" method="post" action="/tracks/search">
      <label>Search
        <input id="name" name="Title" placeholder="Track title">
      </label>
    </form>
<?php
  global $res;

  if ( count( $res ) < 1 ) {
    echo '<p>No tracks found</p>';
    return;
  }

  // Headings
  echo "<table><thead><tr>";
  foreach ( ['ID', 'Title' => '25%', 'Artist', 'Album', 'Length', ''] as $key => $val ) {
    if ( is_numeric( $key ) ) {
      echo "<th>$val</th>";
      continue;
    }

    echo "<th width=\"$val\">$key</th>";
  }
  echo "</tr></thead><tbody>";

  // Rows
  foreach ( $res as $track ) {
    $id = $track['ID'];

    echo "<tr>\n";
    foreach ( ['ID', 'Title', 'ArtistName', 'CDTitle', 'Length'] as $f ) {
      $val = $track[$f];
      echo "<td>$val</td>\n";
    }
    echo "<td>
      <a href=\"/tracks/edit/$id\">Edit</a>
      <a href=\"/tracks/delete/$id\">Delete</a>
    </td>";
    echo "</tr>";
  }

  echo "</tbody></table>";
?>
<?php require 'views/footer.php'; ?>
