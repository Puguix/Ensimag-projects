import subprocess

def start_cpp_server():
    # Remplacez le chemin vers votre exécutable C++ ici
    executable_path = "../Pricer/build/pricing_server"
    # Exécutez l'exécutable C++
    process = subprocess.Popen([executable_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    # Attendez que le serveur démarre
    output, error = process.communicate()
    if process.returncode != 0:
        print("Erreur lors   du démarrage du serveur C++:", error.decode("utf-8"))
    else:
        print("Serveur C++ démarré avec succès.")

if __name__ == "__main__":
    start_cpp_server()