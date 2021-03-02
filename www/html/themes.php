<head>
  <!-- Bootstrap -->
  <link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.min.css" 
  rel="stylesheet" media="screen">
  <link href="css/fontawesome-free-5.15.1-web/css/all.css" rel="stylesheet">
</head>

<h1>THEMES</h1></br>

<h5>Thèmes actuellement créés : </h5>
<?php

include 'config.php';

$query="SELECT * From Theme";


if ($result = mysqli_query($conn,$query))
{
    ?>
      <table class="table table-bordered">
         <tr>
           <th>Thème</th>
           <th>Catégorie</th>
           <th>Descriptif</th>
         </tr>
<?php
    while ($ligne = mysqli_fetch_assoc($result))
    {
       $id_theme =  $ligne['ID_THEME'];
       $titre = $ligne['titre'];
       $categorie = $ligne['categorie'];
       $descriptif = $ligne['descriptif'];
       ?>
         <tr>
           <td>
              <a href="EVS_supprimer_theme.php?id_theme=<?php echo $id_theme?>"><i class="fas fa-trash"></i></a>
              <a href="consulter_theme.php?id_theme=<?php echo $id_theme?>"><?php echo $titre; ?> </a>
           </td>
           <td><?php echo $categorie; ?> </td>
           <td><?php echo $descriptif; ?> </td>
         </tr> 
       <?php
    }
    ?>
    </table>
    <?php
}
?>

<form action=ajout_theme.php method="POST">
   <input type="submit" value="Ajouter un thème">
</form>

<br/><a href="index.php">Retour à l'accueil</a>
