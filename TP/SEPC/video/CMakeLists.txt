cmake_minimum_required(VERSION 2.6)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(Ensithreadsvideo)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)

#########
# Gestion des variantes
#########
# Vous devez editer les lignes suivantes pour y mettre vos logins
#########
set(LOGINS gauthpau bitaudel)

# Vérification du renseignement des login
list(SORT LOGINS)
if (LOGINS MATCHES "login[123]")
  message(FATAL_ERROR "** ERREUR **: Vous devez modifier CMakeLists.txt pour y mettre vos logins")
endif(LOGINS MATCHES "login[123]")

# Trouver la SDL2, ogg, theora et vorbis avec pkgconfig
execute_process(COMMAND bash -c "PKG_CONFIG_PATH=/opt/sdl2-2.0.5/lib/pkgconfig:$PKG_CONFIG_PATH pkg-config --cflags ogg vorbis theora theoradec sdl2" OUTPUT_VARIABLE ALL_PKG_CFLAGS)
execute_process(COMMAND bash -c "PKG_CONFIG_PATH=/opt/sdl2-2.0.5/lib/pkgconfig:$PKG_CONFIG_PATH pkg-config --libs ogg vorbis theora theoradec sdl2" OUTPUT_VARIABLE ALL_PKG_LDFLAGS)
string(STRIP "${ALL_PKG_CFLAGS}" ALLSTRIP_PKG_CFLAGS)
string(STRIP "${ALL_PKG_LDFLAGS}" ALLSTRIP_PKG_LDFLAGS)
# Le Cflags cenTOS Ensimag descends dans SDL2/
# Je le supprime pour être homogène dbns le source
# avec ubuntu et debian
string(REPLACE "-I/opt/sdl2-2.0.5/include/SDL2" "-I/opt/sdl2-2.0.5/include" ALLSTRIP_PKG_CFLAGS "${ALLSTRIP_PKG_CFLAGS}")
message(STATUS "cflags: ${ALLSTRIP_PKG_CFLAGS}")
message(STATUS "ldflags: ${ALLSTRIP_PKG_LDFLAGS}")


# Passer le compilateur C à C11 (gnu11) et donner les CFLAGS pour la sdl
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${ALLSTRIP_PKG_CFLAGS} -Wall -Werror -std=gnu11")


##
# Si vous utilisez d'autres fichiers pour votre lecteur video il faut
# les ajouter ici
##

add_executable(ensivideo src/ensivideo.c src/ensitheora.c src/ensivorbis.c src/oggstream.c src/stream_common.c src/synchro.c)

target_link_libraries(ensivideo pthread ${ALLSTRIP_PKG_LDFLAGS})

##
# Test utilisant Coccinelle
##
add_test(CommonPthreadError perl ${CMAKE_SOURCE_DIR}/tests/pthcocci.pl)

##
# Ajout d'une cible pour lancer les tests de manière verbeuse
##
add_custom_target(check ctest -V)


##
# Construction de l'archive
##
string(REPLACE ";" "-" LOGINS_SANS_POINTVIRGULE "${LOGINS}")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH ${LOGINS_SANS_POINTVIRGULE})
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES
  "~$"
  "\\\\.o$"
  "^${PROJECT_SOURCE_DIR}/build/"
  "^${PROJECT_SOURCE_DIR}/.git/"
)
include(CPack)
