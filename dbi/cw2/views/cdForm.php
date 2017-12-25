<?php require 'views/header.php'; global $params; ?>
  <h1><?php echo PAGE_TITLE; ?></h1>

    <form id="details" method="post" action="/albums/<?php echo EDIT? 'edit' : 'add'; ?> ">
    <label>Title
      <input maxlength="100" id="name" name="Title"
<?php if ( EDIT ) echo ' value="'. $params['Title'] .'"'; ?>
    required pattern=".*[^\s].*">
    </label><br>

    <label>Artist
      <select name="Artist" required>
        <option value="" disabled selected hidden>Select</option>
<?php
// Dropdown selection for all existing artists
global $res;
foreach ( $res as $art ) {
  extract( $art );
  $selected = EDIT && $ID == $params['Artist']? ' selected' : '';
  echo "<option value=\"$ID\"$selected>$ArtName</option>";
}
?>
      </select>
    </label><br>

    <label>Price
    <input name="Price" type="number" min="0" step="any"
      value="<?php echo EDIT? $params['Price'] : 0.00?>" required>
    </label><br>

    <label>Genre
    <input name="Genre" <?php echo EDIT? 'value="'. $params['Genre'] .'"' : ''; ?>>
    </label><br>

    <label>No. of tracks
      <input name="Tracks" type="number" min="1" step="1"
        value="<?php echo EDIT? $params['Tracks'] : 1?>" required>
    </label><br>

<?php
// Hide the related ID for the POST request
if ( EDIT ) {
  $id = $params['ID'];
  echo "<input type=\"hidden\" name=\"ID\" value=\"$id\">";
}
?>
    <br><button type="submit" value="submit">Submit</button>
  </form>
  <br><a href="/albums">Return to albums</a>
<?php require 'views/footer.php'; ?>
