#!/bin/bash
QEMU="${RVDIR:=/matieres/3MMCEP/riscv}/bin/qemu-system-riscv32"
QEMU_OPTS="-machine cep -nographic"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
exos=$(awk 'match($0,/BINS\s*=\s*(.*)/,a){print a[1]}' Makefile)
exosok=""
for exo in $exos
do
  if [ -s test/$exo.sortie ]
  then
    echo "Analyse de $exo"
    if ! grep 'D[EÉ]BUT DU CONTEXTE' fct_${exo}.s > /dev/null 2>&1 ; then
      echo 'Pas de balise "DEBUT DU CONTEXTE", impossible de vérifier votre contexte'
      exit 1
    fi
    make $exo.stxetd
    if [ -s $exo.stxetd ]; then echo "Problème de syntaxe";cat "$exo.stxetd";rm *.stxetd; exit 1; fi
    echo "Vérification rapide du contenu de $exo : OK"
    rm *.stxetd
    make $exo
    if [ -f $exo ]
    then 
      echo "La génération de $exo a bien réussi."
    else
      echo "La génération de $exo a échoué."
      printf "${RED}A revoir la syntaxe de fct_${exo}.s${NC}\n"
      exit 1
    fi
    timeout 10 $QEMU $QEMU_OPTS -kernel $exo < test/$exo.entree > $exo.sortie
    if cmp --silent $exo.sortie test/$exo.sortie
    then
      echo "La sortie de $exo est bien identique à test/$exo.sortie."
      rm "$exo.sortie"
    else
      echo "La sortie de $exo n'est pas celle décrite dans test/$exo.sortie."
      rm "$exo.sortie"
      printf "${RED}A revoir test/${exo}.sortie et fct_${exo}.s${NC}\n"
      exit 1
    fi
    exosok="${exosok} ${exo}"
  fi
done
printf "${GREEN}C'est tout bon vous pouvez ajouter vos fichiers test/EXO.sortie et fct_EXO.s avec les EXO(s): ${exosok} ${NC}\n"
exit 0
