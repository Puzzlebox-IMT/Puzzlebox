<?php
session_start();
$id_theme = $_SESSION['id_theme'];
include 'config.php';

$query = "DELETE FROM Theme WHERE ID_THEME='$id_theme'";
if($result = mysqli_query($conn,$query))
{
  $query2 = "DELETE FROM themes_questions WHERE ID_THEME='$id_theme'";
  if($result2 = mysqli_query($conn,$query2))
  {
    header('location:themes.php');
  }
  else
  {
    echo "Un problème est survenu au moment de la requête 2";
  }
}
else
{
  echo "Un problème est survenu au moment de la requête 1";
  
}

?>
