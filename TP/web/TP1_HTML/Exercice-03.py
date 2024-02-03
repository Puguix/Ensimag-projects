import csv

with open("Exercice-03.html", "w") as file:
  file.write('<!DOCTYPE html>')
  file.write('<html lang="fr">')
  file.write('<head>')
  file.write('<title>TP 1, Exo 3</title>')
  file.write('<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />')
  file.write('</head>')
  file.write('<body>')
  file.write('<table >')
  file.write('<thead >')
  file.write('<tr><th></th><th>Nom</th><th>Prénom</th><th>N°</th><th>Mail</th><th>Adresse</th><th>Code postal</th><th>Ville</th></tr>')
  file.write('</thead >')
  file.write('<tbody >')
  with open("contacts.txt") as csvfile:      
    input = csv.reader(csvfile, delimiter=';')
    print(type(input))
    input = sorted(input, key=lambda row: row[1])
    for row in input:
        row[0], row[1] = row[1], row[0]
        file.write('<tr><td></td>')
        for i in range(len(row)):
            if i == 2:
                file.write('<td><a href="tel:' + row[i].strip(".") + '">' + row[i] + '</a></td>')
            else:
                file.write("<td>" + row[i] + "</td>")
        file.write('</tr>')
  file.write('</tbody >')
  file.write('</table >')
  file.write('</body>')
  file.write('</html>')
