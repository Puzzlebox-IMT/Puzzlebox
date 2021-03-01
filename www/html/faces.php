<head>
  <!-- Bootstrap -->
  <link href="css/bootstrap-5.0.0-beta1-dist/css/bootstrap.min.css"
  rel="stylesheet" media="screen">
  <link href="css/fontawesome-free-5.15.1-web/css/all.css" rel="stylesheet">
</head>

<h1>FACES</h1></br>

<h5>Faces actuellement utilisées : </h5>
<?php

include 'config.php';

$query="SELECT * From Face";


if ($result = mysqli_query($conn,$query))
{
    ?>
      <table class="table table-bordered">
         <tr>
           <th>Intitulé</th>
           <th>Descriptif</th>
           <th>Etat</th>
         </tr>
<?php
    while ($ligne = mysqli_fetch_assoc($result))
    {
       $id_face =  $ligne['id_face'];
       $intitule = $ligne['intitule'];
       $descriptif = $ligne['descriptif'];
       $etat = $ligne['etat'];
       ?>
         <tr>
           <td>
              <a href="EVS_supprimer_face.php?id_face=<?php echo $id_face?>"><i class="fas fa-trash"></i></a>
              <a href="consulter_face.php?id_theme=<?php echo $id_face?>"><?php echo $intitule; ?> </a>
           </td>
           <td><?php echo $descriptif; ?> </td>
           <td><?php echo $etat; ?> </td>
         </tr>
       <?php
    }
    ?>
    </table>
    <?php
}
?>

<form action=ajout_face.php method="POST">
   <input type="submit" value="Ajouter une nouvelle face">
</form>

<br/><a href="index.php">Retour à l'accueil</a>

