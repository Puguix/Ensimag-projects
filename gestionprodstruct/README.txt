Avoir une librairie PNL installée (compilée)



Avoir grpc installé (https://grpc.io/docs/languages/cpp/quickstart/)



//GENERER LES FICHIERS GRPC PYTHON AVEC PROTOC (remplacer le path vers le fichier grpc_python_plugin).

protoc --python_out=. --grpc_python_out=. --plugin=protoc-gen-grpc_python=/home/gagar/grpc/cmake/build/grpc_python_plugin GrpcPricer.proto

//COMPILER (côté Pricer) les fichiers cpp (REMPLACER LE CHEMIN VERS LE BUILD DE PNL) :
	mkdir build
	cd build
	cmake -DCMAKE_PREFIX_PATH=/home/gagar/pnl/build/ .. 
	make
	
	./pricing_server
	OU
	python3 start-server.py



Description des fichiers:
	- constructJSON: 3 dates en entrée (T0, Tc et la date à laquelle on veut pricer/commencer à hedger)
					 
					 Crée un fichier JSON contenant les informations nécessaires pour créer le pricer,
					 ainsi que les données de marché.

	
