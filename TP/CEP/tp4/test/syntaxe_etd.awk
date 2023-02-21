BEGIN {
  feuille_re = fonction"\\s*:\\s*(non)?\\s+feuille\\s*$"
  prologue_re = "^\\s*"fonction"_fin_prologue:"
  epilogue_re = "^\\s*"fonction"_debut_epilogue:"
  feuille = -1
  prologue = -1
  epilogue = -1
  ret = -1
}

{
  if ($0 ~ feuille_re){
    if (feuille=-1) feuille=NR; else feuille = -2;
  }
  if ($0 ~ prologue_re){
    if (prologue=-1) prologue=NR; else prologue = -2;
  }
  if ($0 ~ epilogue_re){
    if (epilogue=-1) epilogue=NR; else epilogue = -2;
  }
  if ($0 ~ /^\s*ret\s*$/) {
    if (ret=-1) ret=NR; else ret = -2;    
  }
}

END {
  if (feuille > 0 && feuille<prologue && prologue<epilogue && epilogue<ret){
    exit 0
  }
  if (feuille<0) {
    print "Mauvaise définition du contexte. Préciser si la fonction est feuille ou non comme dans le modèle."
  }
  if (prologue<0) {
    print "Attention à l'étiquette "fonction"_fin_prologue:"
  }
  if (epilogue<0) {
    print "Attention à l'étiquette "fonction"_debut_epilogue:"
  }
  if (ret<0){
    print "L'instruction ret doit être à la fin de la fonction sans commentaire autour"
  }
  if (feuille >0 && prologue>0 && ret>0 && epilogue>0){
    print "Votre programme doit commencer par la définition du contexte, puis positionner l'étiquette de fin de prologue, puis par l'étiquette de debut d'epilogue et enfin par le ret"
  }
  exit 1
}