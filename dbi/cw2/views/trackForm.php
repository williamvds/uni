<?php require 'views/header.php'; global $params; ?>
  <h1><?php echo PAGE_TITLE; ?></h1>

    <form id="details" method="post" action="/tracks/<?php echo EDIT? 'edit' : 'add'; ?> ">
    <label>Title
      <input maxlength="100" id="name" name="Title"
<?php if ( EDIT ) echo ' value="'. $params['Title'] .'"'; ?>
    required pattern=".*[^\s].*">
    </label><br>

    <label>Album
      <select name="CD" required>
        <option value="" disabled selected hidden>Select</option>
<?php
// Dropdown selection for all existing artists
global $res;
foreach ( $res as $cd ) {
  extract( $cd );
  $selected = EDIT && $ID == $params['CD']? ' selected' : '';
  echo "<option value=\"$ID\"$selected>$Title ($ArtName)</option>";
}
?>
      </select>
    </label><br>

    <label>Length (secs)
      <input name="Length" type="number" min="1" step="1"
        value="<?php echo EDIT? $params['Length'] : 1?>" required>
    </label><br>

<?php
//
if ( EDIT ) {
  $id = $params['ID'];
  echo "<input type=\"hidden\" name=\"ID\" value=\"$id\">";
}
?>
    <br><button type="submit" value="submit">Submit</button>
  </form>
  <br><a href="/tracks">Return to tracks</a>
<?php require 'views/footer.php'; ?>
