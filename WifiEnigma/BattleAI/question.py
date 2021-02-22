import mysql.connector
import random
from voice import synthetize_voice, delete_wav

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
       result = [] #Tab which stores the query results


       #RECUPERATION DES TUPLES
       result.append(question[1])
       result.append(question[2])
       result.append(question[3])
       result.append(question[4])
       result.append(question[5])
       result.append(question[5]) #This last one is the answer

       print("*******************************************************************************")
       print("                                     QUESTION ",num_question+1,"                            ")
       print("*******************************************************************************")
       print("ENONCE : ", result[0])
       print("PROPOSITION 1 : ", result[1])
       print("PROPOSITION 2 : ", result[2])
       print("PROPOSITION 3 : ", result[3])
       print("PROPOSITION 4 : ", result[4])
       print("REPONSE : ", result[5])
 
       #complete_question =  ''.join(complete_question) #Convert tuple into string
       return result

    else:

       print("Ce thème ne contient pas de questions")


def tell_question(question):

    synthetize_voice(question[0])
    for i in range(1,5) :

        num_prop = "Proposition {} ".format(i)
        num_prop =  ''.join(num_prop)
        line =  ''.join(question[i])
        line = num_prop + line
        synthetize_voice(line)
    delete_wav()

def quiz():

    counter = 1
    while(counter <= 5):

       questionAI(1)


if (__name__ == '__main__'):

   result = questionAI(1)
   tell_question(result)
