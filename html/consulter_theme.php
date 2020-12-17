
<!-- Bootstrap -->
<link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.min.css" rel="stylesheet" media="screen">


<?php

$id_theme = $_GET['id_theme'];
include 'config.php';
$query="SELECT * FROM Theme WHERE ID_THEME='$id_theme'";
if($result=mysqli_query($conn,$query))
{
   while ($ligne = mysqli_fetch_assoc($result))
   {
      $titre = $ligne['titre'];
      $categorie = $ligne['categorie'];
      $descriptif =  $ligne['descriptif'];
      ?>
      <h2>THEME : <?php echo $titre; ?></h2>
      <p>Catégorie : <?php echo $categorie; ?></p>
      <p>Descriptif : <?php echo $descriptif; ?></p>
      <?php
   }
   $query2="SELECT enonce, proposition1, proposition2, proposition3, proposition4, reponse FROM Question INNER JOIN themes_questions ON Question.ID_QUESTION = themes_questions.ID_QUESTION WHERE ID_THEME=1";
   if($result2=mysqli_query($conn,$query2))
   {
       ?>
       <table class="table">
           <tr>
              <th>Enonce</th>
              <th>Proposition 1</th>
              <th>Proposition 2</th>
              <th>Proposition 3</th>
              <th>Proposition 4</th>
              <th>Reponse</th>
           </tr>
        <?php
        while ($ligne = mysqli_fetch_assoc($result2))
        {
           $enonce = $ligne['enonce'];
           $proposition1 = $ligne['proposition1'];
           $proposition2 = $ligne['proposition2'];
           $proposition3 = $ligne['proposition3'];
           $proposition4 = $ligne['proposition4'];
           $reponse = $ligne['reponse'];
           ?>
           <tr>
              <td><?php echo $enonce; ?> </td>
              <td><?php echo $proposition1; ?> </td>
              <td><?php echo $proposition2; ?> </td>
              <td><?php echo $proposition3; ?> </td>
              <td><?php echo $proposition4; ?> </td>
              <td><?php echo $reponse; ?> </td>
           </tr>
           <?php
        }
        ?>
        </table>
        <?php
   }
   else
   {
     echo "Problème au niveau de la requête";
     ?>
     <a href="themes.php">Retour</a>
     <?php
   }

}
else
{
  echo "Problème au niveau de la requête";
}

?>

<a href="themes.php">Retour</a>
