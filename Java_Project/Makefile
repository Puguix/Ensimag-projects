# Ensimag 2A POO - TP 2018/19
# ============================
#
# Ce Makefile permet de compiler le test de l'ihm en ligne de commande.
# Alternative (recommandee?): utiliser un IDE (eclipse, netbeans, ...)
# Le but est ici d'illustrer les notions de "classpath", a vous de l'adapter
# a votre projet.
#
# Organisation:
#  1) Les sources (*.java) se trouvent dans le repertoire src
#     Les classes d'un package toto sont dans src/toto
#     Les classes du package par defaut sont dans src
#
#  2) Les bytecodes (*.class) se trouvent dans le repertoire bin
#     La hierarchie des sources (par package) est conservee.
#     L'archive bin/gui.jar contient les classes de l'interface graphique
#
# Compilation:
#  Options de javac:
#   -d : repertoire dans lequel sont places les .class compiles
#   -classpath : repertoire dans lequel sont cherches les .class deja compiles
#   -sourcepath : repertoire dans lequel sont cherches les .java (dependances)

all: testScenario2 exeScenario2

testInvader:
	javac -d bin -classpath bin/gui.jar -sourcepath src src/TestInvader.java

testLecture:
	javac -d bin -sourcepath src src/TestLecteurDonnees.java

testScenario0:
	javac -d bin -classpath bin/gui.jar -sourcepath src src/tests/Scenario0.java

testScenario1:
	javac -d bin -classpath bin/gui.jar -sourcepath src src/tests/Scenario1.java

testScenario2:
	javac -d bin -classpath bin/gui.jar -sourcepath src src/tests/Scenario2.java

testElementaire:
	javac -d bin -classpath bin/gui.jar -sourcepath src src/tests/TestStratElementaire.java
	
testEvolue:
	javac -d bin -classpath bin/gui.jar -sourcepath src src/tests/TestStratEvolue.java

# Execution:
# on peut taper directement la ligne de commande :
#   > java -classpath bin:bin/gui.jar TestInvader
# ou bien lancer l'execution en passant par ce Makefile:
#   > make exeInvader
exeInvader: 
	java -classpath bin:bin/gui.jar TestInvader

exeLecture: 
	java -classpath bin TestLecteurDonnees cartes/carteSujet.map

exeScenario0: 
	java -classpath bin:bin/gui.jar tests/Scenario0 cartes/carteSujet.map

exeScenario1: 
	java -classpath bin:bin/gui.jar tests/Scenario1 cartes/carteSujet.map

exeScenario2: 
	java -classpath bin:bin/gui.jar tests/Scenario2 cartes/carteSujet.map

exeElementaire: 
	java -classpath bin:bin/gui.jar tests/TestStratElementaire cartes/carteSujet.map

exeEvolue: 
	java -classpath bin:bin/gui.jar tests/TestStratEvolue cartes/carteSujet.map

clean:
	rm -rf bin/*.class
