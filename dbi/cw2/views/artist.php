<?php require 'views/header.php'; ?>
    <h1><?php echo PAGE_TITLE; ?></h1>
    <a href="/artists/add" class="button">Add an artist</a>
    <form id="search" method="post" action="/artists/search">
      <label>Search
        <input id="name" name="ArtName" placeholder="Artist name">
      </label>
    </form>
<?php
  global $res;

  if ( count( $res ) < 1 ) {
    echo '<p>No artists found</p>';
    return;
  }

  echo "<table><thead><tr>
    <th>ID</th>
    <th width=\"65%\">Name</th>
    <th></th>
  </tr></thead><tbody>";

  foreach ( $res as $art ) {
    $id = $art['ID'];
    echo "<tr>\n";
    foreach ( $art as $field => $value ) {
      echo "<td>$value</td>\n";
    }
    echo "<td>
      <a href=\"/artists/$id\">Albums</a>
      <a href=\"/artists/edit/$id\">Edit</a>
      <a href=\"/artists/delete/$id\">Delete</a>
    </td>";
    echo "</tr>";
  }

  echo "</tbody></table>";
?>
<?php require 'views/footer.php'; ?>
