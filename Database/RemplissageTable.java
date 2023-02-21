import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class RemplissageTable{
    static final String CONN_URL = "jdbc:oracle:thin:@oracle1.ensimag.fr:1521:oracle1";
    static final String USER = "lim"; // A remplacer pour votre compte
    static final String PASSWD = "lim";
    static final String RQTREST = "restaurant VALUES('resto.mcdo.grenoble@mcdo.fr','McDo Grenoble','0606060606','200','McDonald de Grenoble ouvert tous les jours','Livraison')";
    static final String RQTYTPECOMM = "categorie VALUES('Cuisine générale')";
    static final String RQTHOR = "horaireouverture VALUES ('Lundi','19-23')";
    static final String RQTPLAT = "insert into plat VALUES ('resto.mcdo.grenoble@mcdo.fr', 1,'Burger','Burger avec 1 steak de boeuf, tomate et salade',5)";
    static final String RQTALL = "insert into allergenes VALUES ('E22')";
    static final String RQTTXTLIV = "insert into textelivraison VALUES (3ème porte à gauche au 3ème étage)";
    static final String RQTCOMMANDE = "commande VALUES ('resto.mcdo.grenoble@mcdo.fr', 1, 19:12,20.63,'livrée','livraison')";
    static final String RQTCOMMANDELIV = "commandeliv VALUES ('resto.mcdo.grenoble@mcdo.fr', 1, 19:12,20.63,'livrée','livraison','65 Rue de l'Eau', '19:45')";
    static final String RQTCOMMANDESP = "commande VALUES ('resto.mcdo.grenoble@mcdo.fr', 1, 19:12,20.63,'livrée','livraison','65 Rue de l'Eau', '19:45')";
    static final List<String> liste = List.of("attente de confirmation","validée","disponible", "en livraison", "annulée par le client", "annulée par le restaurant");
    static final String RQTEVAL = "";
}