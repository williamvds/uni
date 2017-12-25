<?php require 'views/header.php'; global $params; ?>
    <h1><?php echo PAGE_TITLE; ?></h1>

    <form id="details" method="post" action="/artists/<?php echo EDIT? 'edit' : 'add'; ?> ">
    <label>Name
      <input maxlength="100" id="name" name="ArtName"
<?php if ( EDIT ) echo ' value="'. $params['ArtName'] .'"'; ?>
    pattern=".*[^\s].*">
    </label>

<?php
// Hide the related ID for the POST request
if ( EDIT ) {
  $id = $params['ID'];
  echo "<input type=\"hidden\" name=\"ID\" value=\"$id\">";
}
?>

    <br><button type="submit" value="submit">Submit</button>
  </form>
  <br><a href="/artists">Return to artists</a>
<?php require 'views/footer.php'; ?>
