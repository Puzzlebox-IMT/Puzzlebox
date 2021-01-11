import mysql.connector
import random

def AllQuestionAI(id_theme):

    i = 0

    #CONNEXION A LA BDD
    conn = mysql.connector.connect(host="localhost",
                                   user="phpmyadmin", password="Vince@Mysql1997",
                                   database="Puzzlebox")
    cursor = conn.cursor()

    #EXECUTER LA REQUETE AVEC LA BDD
    query  = ("SELECT * FROM Question INNER JOIN themes_questions ON Question.ID_QUESTION = themes_questions.ID_QUESTION WHERE ID_THEME=%s")
    cursor.execute(query, (id_theme, ))

    #RECUPERATION DES INFORMATIONS
    rows = cursor.fetchall()
    if rows:
       for line in rows:

           i += 1
           enonce = line[1]
           proposition1 = line[2]
           proposition2 = line[3]
           proposition3 = line[4]
           proposition4 = line[5]
           reponse = line[5]

           print("*******************************************************************************")
           print("                                     QUESTION ",i,"                            ")
           print("*******************************************************************************")
           print("ENONCE : ", enonce)
           print("PROPOSITION 1 : ", proposition1)
           print("PROPOSITION 2 : ", proposition2)
           print("PROPOSITION 3 : ", proposition3)
           print("PROPOSITION 4 : ", proposition4)
           print("REPONSE : ", reponse)
    else:

       print("Ce thème ne contient pas de questions")


def questionAI(id_theme):

    i = 0

    #CONNEXION A LA BDD
    conn = mysql.connector.connect(host="localhost",
                                   user="phpmyadmin", password="Vince@Mysql1997",
                                   database="Puzzlebox")
    cursor = conn.cursor()

    #EXECUTER LA REQUETE AVEC LA BDD
    query  = ("SELECT * FROM Question INNER JOIN themes_questions ON Question.ID_QUESTION = themes_questions.ID_QUESTION WHERE ID_THEME=%s")
    cursor.execute(query, (id_theme, ))

    #RECUPERATION DES INFORMATIONS
    rows = cursor.fetchall()
    if rows:

       nb_rows = len(rows)
       num_question = random.randint(1, nb_rows)

       #L'index de la liste commence à zéro, il faut donc décaler d'un le numéro 
       num_question = num_question - 1
       question = rows[num_question]

       #RECUPERATION DES TUPLES
       enonce = question[1]
       proposition1 = question[2]
       proposition2 = question[3]
       proposition3 = question[4]
       proposition4 = question[5]
       reponse = question[5]

       print("*******************************************************************************")
       print("                                     QUESTION ",num_question+1,"                            ")
       print("*******************************************************************************")
       print("ENONCE : ", enonce)
       print("PROPOSITION 1 : ", proposition1)
       print("PROPOSITION 2 : ", proposition2)
       print("PROPOSITION 3 : ", proposition3)
       print("PROPOSITION 4 : ", proposition4)
       print("REPONSE : ", reponse)


    else:

       print("Ce thème ne contient pas de questions")




questionAI(1)
