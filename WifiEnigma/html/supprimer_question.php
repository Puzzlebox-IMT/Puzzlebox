<?php

session_start();
$id_theme = $_SESSION['id_theme'];
$id_question = $_SESSION['id_question'];
echo $id_theme;
echo $id_question;
include 'config.php';
$query = "DELETE FROM themes_questions WHERE ID_QUESTION='$id_question' AND ID_THEME='$id_theme'";
if($result = mysqli_query($conn,$query))
{
  $query2 = "DELETE FROM Question WHERE ID_QUESTION='$id_question'";
  if($result2 = mysqli_query($conn,$query2))
  {
     session_destroy();
     session_unset();
     header("location:consulter_theme.php?id_theme=$id_theme");
  }
  else
  {
     echo "Un problème est survenu lors de la requête 2";
  }
}
else
{
  echo "Un problème est survenu lors de la requête 1";
}


session_destroy();
session_unset();

?>

<a href="themes.php">Retour</a>
