cmake_minimum_required(VERSION 3.0)

# Utilisation de RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Nom du projet
project(ArbreNoirRouge C)

# Ajouter le chemin vers les fichiers d'en-tête
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Création de la bibliothèque partagée
add_library(arbre_noir_rouge SHARED 
    arbre_noir_rouge.c
    arbre_noir_rouge.h
)

# Installation de la bibliothèque
install(
    TARGETS arbre_noir_rouge
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Installation du fichier d'en-tête
install(
    FILES arbre_noir_rouge.h
    DESTINATION include
)

# Ajout d'un fichier de configuration de type pkgconfig
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/arbre_noir_rouge.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/arbre_noir_rouge.pc
    @ONLY
)

# Installation du fichier pkg-config
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/arbre_noir_rouge.pc
    DESTINATION share/pkgconfig
)

# Ajout d'un fichier de configuration de type cmake
include(CMakePackageConfigHelpers)



# Vérifie que le fichier .in existe
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ArbreNoirRougeConfig.cmake.in)
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/ArbreNoirRougeConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/ArbreNoirRougeConfig.cmake
        INSTALL_DESTINATION cmake
    )

    install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/ArbreNoirRougeConfig.cmake
        DESTINATION cmake
    )
else()
    message(WARNING "Le fichier ArbreNoirRougeConfig.cmake.in est manquant.")
endif()

# Nom du projet
project(BiocolorTree)

# Spécifier la norme C
set(CMAKE_C_STANDARD 99)

# Fichiers sources
set(SRC_FILES
    test-arbre_noir_rouge.c
    Insert.c
    Delete.c
    Rotation.c
    arbre_noir_rouge.c
)

# Créer l'exécutable à partir des fichiers sources
add_executable(test-arbre_noir_rouge ${SRC_FILES})

# Ajouter des options de compilation (par exemple, activer les warnings)
target_compile_options(test-arbre_noir_rouge PRIVATE -Wall)

