create table restaurant(
emailR varchar(254) not null,
nomR varchar(254) not null,
telR varchar(20) not null,
adresseR varchar(254) not null,
nbPlace integer not null check (nbPlace >=0),
textePres varchar(512) not null,
PRIMARY KEY (emailR)
);

create table categorie(
categorie varchar(254) not null,
primary key (categorie)
);

create table horaireouverture(
jourouverture varchar(254) not null check (jourouverture in ('Lundi','Mardi', 'Mercredi', 'Jeudi', 'Vendredi', 'Samedi','Dimanche')),
heureouverture varchar(254) not null,
primary key (jourouverture, heureouverture)
);

create table plat(
emailR varchar(254) not null,
idPlat integer not null,
nomPlat varchar(254) not null,
descPlat varchar(254) not null,
prixPlat float not null check(prixPlat >= 0),
FOREIGN KEY(emailR) references restaurant(emailR),
PRIMARY KEY(idPlat, emailR)
);

create table allergenes(
allergene varchar(254) not null,
primary key(allergene)
);
create table comptes(
idClient integer not null,
primary key(idclient)
);

create table clientA(
emailC varchar(254) not null,
mdp varchar(254) not null,
nomC varchar(64) not null,
prenomC varchar(64) not null,
adresseC varchar(254) not null,
idClient integer not null,
primary key (emailC),
foreign key (idClient) references comptes(idClient)
);

create table commande(
emailR varchar(254) not null,
idClient integer not null,
dateC timestamp(0) not null,
prixTotal float not null check (prixTotal >=0),
statut varchar(254) not null check (statut in ('attente de confirmation', 'validee', 'disponible', 'en livraison', 'annulee par le client', 'annulee par le restaurant')),
typeC varchar(254) not null  check (typeC in ('livraison', 'a emporter', 'sur place')),
FOREIGN KEY (emailR) references restaurant(emailR),
FOREIGN KEY (idClient) references comptes(idClient),
PRIMARY KEY (emailR, idClient, dateC)
);

create table commandelivraison(
emailR varchar(254) not null,
idClient integer not null,
dateC timestamp(0) not null,
prixTotal float not null check (prixTotal >=0),
statut varchar(254) not null check (statut in ('attente de confirmation', 'validee', 'disponible', 'en livraison', 'annulee par le client', 'annulee par le restaurant')),
typeC varchar(254) not null  check (typeC in ('livraison', 'a emporter', 'sur place')),
adresseLivraison varchar(254) not null,
heureLivraison timestamp(0) not null,
FOREIGN KEY (emailR) references restaurant(emailR),
FOREIGN KEY (idClient) references comptes(idClient),
PRIMARY KEY (emailR, idClient, dateC)
);

create table textelivraison(
texte varchar(512) not null,
primary key(texte)
);

create table commandesurplace(
emailR varchar(254) not null,
idClient integer not null,
dateC timestamp(0) not null,
prixTotal float not null check (prixTotal >=0),
statut varchar(254) not null check (statut in ('attente de confirmation', 'validee', 'disponible', 'en livraison', 'annulee par le client', 'annulee par le restaurant')),
typeC varchar(254) not null  check (typeC in ('livraison', 'a emporter', 'sur place')),
nbPersonnes integer not null check(nbPersonnes > 0),
heureArrivee timestamp(0) not null,
FOREIGN KEY (emailR) references restaurant(emailR),
FOREIGN KEY (idClient) references comptes(idClient),
PRIMARY KEY (emailR, idClient, dateC)
);

create table evaluationc(
dateE timestamp(0) not null,
avis varchar(512) not null,
note integer not null check (note >=0) check (note <=5),
primary key (dateE, avis, note)
);


create table typeCommande(
typeC varchar(254) not null check (typeC in ('livraison', 'a emporter', 'sur place')),
primary key (typeC)
);

create table acceptetype(
emailR varchar(254) not null,
typeC varchar(254) not null,
PRIMARY KEY(emailR, typeC),
FOREIGN KEY (emailR) references Restaurant(emailR),
FOREIGN KEY (typeC) references TypeCommande(typeC)
);

CREATE TABLE APourEval(emailR varchar(254) not null,
idClient integer not null,
dateC TIMESTAMP(0) not null,
dateE TIMESTAMP(0) not null,
avis varchar(512) not null,
note integer not null check (note >=0) check (note <=5),
PRIMARY KEY (emailR,idClient, dateC),
FOREIGN KEY (emailR, idClient, dateC) REFERENCES Commande(emailR, idClient, dateC),
check (dateC <= dateE)
);

CREATE TABLE ContientMsg(
emailR varchar(254) not null,
idClient integer not null,
dateC TIMESTAMP(0) not null,
texte varchar(512),
PRIMARY KEY (emailR,idClient, dateC),
FOREIGN KEY (emailR, idClient, dateC) REFERENCES Commande(emailR, idClient, dateC),
FOREIGN KEY (texte) REFERENCES TexteLivraison(Texte)
);

CREATE TABLE EstFils(
categoriePere varchar(254) not null,
categorieFils varchar(254) not null,
PRIMARY KEY (categorieFils),
FOREIGN KEY (categoriePere) REFERENCES Categorie(categorie),
FOREIGN KEY (categorieFils) REFERENCES Categorie(categorie)
);

CREATE TABLE EstOuvertLe(
emailR varchar(254) not null,
jourOuverture varchar(254) not null,
heureOuverture varchar(254) not null,
PRIMARY KEY (emailR, jourOuverture,heureOuverture),
FOREIGN KEY (emailR) REFERENCES Restaurant(emailR),
FOREIGN KEY (jourOuverture,heureOuverture) REFERENCES HoraireOuverture(jourOuverture,heureOuverture)
);


CREATE TABLE ContientAllergene(
emailR varchar(254) not null,
idPlat integer not null,
allergene varchar(254) not null,
PRIMARY KEY (emailR, idPlat, allergene),
FOREIGN KEY (emailR, idPlat) REFERENCES Plat(emailR, idPLat),
FOREIGN KEY (allergene) REFERENCES Allergenes(allergene)
);


CREATE TABLE APourCat(
emailR varchar(254) not null,
categorie varchar(254) not null,
PRIMARY KEY (emailR, categorie),
FOREIGN KEY (emailR) REFERENCES Restaurant(emailR),
FOREIGN KEY (categorie) REFERENCES Categorie(categorie)
);

CREATE TABLE acommande(
idPlat integer not null,
emailR varchar(254) not null,
idClient integer not null,
dateC timestamp(0) not null,
Quantite integer not null,
PRIMARY KEY (idPlat, emailR, idClient, dateC),
foreign key (emailR, idClient, dateC) references commande(emailR, idClient, dateC),
foreign key (idPlat, emailR) references plat(idPlat, emailR)
);
