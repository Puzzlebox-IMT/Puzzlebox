<?php
session_start();
$id_face = $_SESSION['id_face'];
include 'config.php';

$query = "DELETE FROM Face WHERE id_face = '$id_face'";
if($result = mysqli_query($conn,$query))
{
  header('location:faces.php');
}
else
{
  echo "Un problème est survenu au moment de la requête";
}


?>

