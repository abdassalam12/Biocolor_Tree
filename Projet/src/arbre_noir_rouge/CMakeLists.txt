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







# Ajout d'un exécutable de test
add_executable(test-arbre_noir_rouge 
    test-arbre_noir_rouge.c
)

# Préciser l'ordre de construction
add_dependencies(test-arbre_noir_rouge arbre_noir_rouge)

# Lier la bibliothèque avec l'exécutable de test
target_link_libraries(test-arbre_noir_rouge arbre_noir_rouge)

# Activer les tests
enable_testing()

# Ajouter un test
add_test(NAME test-arbre_noir_rouge COMMAND test-arbre_noir_rouge)
target_link_libraries(test-arbre_noir_rouge arbre_noir_rouge)